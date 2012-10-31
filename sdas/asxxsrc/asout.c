/* asout.c */

/*
 *  Copyright (C) 1989-2009  Alan R. Baldwin
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * Alan R. Baldwin
 * 721 Berkeley St.
 * Kent, Ohio  44240
 *
 */

/*
 * 28-Oct-97 JLH:
 *           - outsym: show s_id as string rather than array [NCPS]
 *           - Added outr11 to support 8051's 11 bit destination address
 */

#include "sdas.h"
#include "asxxxx.h"


/*)Module       asout.c
 *
 *      The module asout.c contains all the functions used to
 *      generate the .REL assembler output file.
 *
 *
 *      The  assemblers' output object file is an ascii file containing
 *      the information needed by the linker  to  bind  multiple  object
 *      modules into a complete loadable memory image.
 *
 *      The object module contains the following designators:
 *
 *              [XDQ][HL]
 *                      X        Hexadecimal radix
 *                      D        Decimal radix
 *                      Q        Octal radix
 *
 *                      H        Most significant byte first
 *                      L        Least significant byte first
 *
 *              H       Header
 *              M       Module
 *              A       Area
 *              S       Symbol
 *              T       Object code
 *              R       Relocation information
 *              P       Paging information
 *
 *
 *      (1)     Radix Line
 *
 *      The  first  line  of  an object module contains the [XDQ][HL]
 *      format specifier (i.e.  XH indicates  a  hexadecimal  file  with
 *      most significant byte first) for the
 *      following designators.
 *
 *
 *      (2)     Header Line
 *
 *              H aa areas gg global symbols
 *
 *      The  header  line  specifies  the number of areas(aa) and the
 *      number of global symbols(gg) defined or referenced in  this  ob-
 *      ject module segment.
 *
 *
 *      (3)     Module Line
 *
 *              M name
 *
 *      The  module  line  specifies  the module name from which this
 *      header segment was assembled.  The module line will  not  appear
 *      if the .module directive was not used in the source program.
 *
 *
 *      (4)     Symbol Line
 *
 *              S string Defnnnn
 *
 *                      or
 *
 *              S string Refnnnn
 *
 *      The  symbol line defines (Def) or references (Ref) the symbol
 *      'string' with the value nnnn.  The defined value is relative  to
 *      the  current area base address.  References to constants and ex-
 *      ternal global symbols will always appear before the  first  area
 *      definition.  References to external symbols will have a value of
 *      zero.
 *
 *
 *      (5)     Area Line
 *
 *              A label size ss flags ff
 *
 *      The  area  line  defines the area label, the size (ss) of the
 *      area in bytes, and the area flags (ff).  The area flags
 *      specify the area properties:
 *
 *              OVR/CON (0x04/0x00 i.e.  bit position 2)
 *              ABS/REL (0x08/0x00 i.e.  bit position 3)
 *              PAG (0x10 i.e.  bit position 4)
 *
 *
 *      (6)     T Line
 *
 *              T xx xx nn nn nn nn nn ...
 *
 *      The  T  line contains the assembled code output by the assem-
 *      bler with xx xx being the offset address from the  current  area
 *      base address and nn being the assembled instructions and data in
 *      byte format.
 *
 *
 *      (7)     R Line
 *
 *              R 0 0 nn nn n1 n2 xx xx ...
 *
 *      The R line provides the relocation information to the linker.
 *      The nn nn value is the current area index, i.e.  which area  the
 *      current  values  were  assembled.  Relocation information is en-
 *      coded in groups of 4 bytes:
 *
 *      1.  n1 is the relocation mode and object format
 *              1.  bit 0 word(0x00)/byte(0x01)
 *              2.  bit 1 relocatable area(0x00)/symbol(0x02)
 *              3.  bit 2 normal(0x00)/PC relative(0x04) relocation
 *              4.  bit  3  1-byte(0x00)/2-byte(0x08) object format for
 *                  byte data
 *              5.  bit 4 signed(0x00)/unsigned(0x10) byte data
 *              6.  bit 5 normal(0x00)/page '0'(0x20) reference
 *              7.  bit 6 normal(0x00)/page 'nnn'(0x40) reference
 *              8.  bit 7 normal(0x00)/MSB of value
 *
 *      2.  n2  is  a byte index into the corresponding (i.e.  pre-
 *              ceeding) T line data (i.e.  a pointer to the data to be
 *              updated  by  the  relocation).   The T line data may be
 *              1-byte or  2-byte  byte  data  format  or  2-byte  word
 *              format.
 *
 *      3.  xx xx  is the area/symbol index for the area/symbol be-
 *              ing referenced.  the corresponding area/symbol is found
 *              in the header area/symbol lists.
 *
 *
 *      The groups of 4 bytes are repeated for each item requiring relo-
 *      cation in the preceeding T line.
 *
 *
 *      (8)     P Line
 *
 *              P 0 0 nn nn n1 n2 xx xx
 *
 *      The  P  line provides the paging information to the linker as
 *      specified by a .setdp directive.  The format of  the  relocation
 *      information is identical to that of the R line.  The correspond-
 *      ing T line has the following information:
 *              T xx xx aa aa bb bb
 *
 *      Where  aa aa is the area reference number which specifies the
 *      selected page area and bb bb is the base address  of  the  page.
 *      bb bb will require relocation processing if the 'n1 n2 xx xx' is
 *      specified in the P line.  The linker will verify that  the  base
 *      address is on a 256 byte boundary and that the page length of an
 *      area defined with the PAG type is not larger than 256 bytes.
 *
 *      The  linker  defaults any direct page references to the first
 *      area defined in the input REL file.  All ASxxxx assemblers  will
 *      specify the _CODE area first, making this the default page area.
 *
 *
 *      asout.c contains the following functions:
 *              int     lobyte()
 *              int     hibyte()
 *              int     thrdbyte()
 *              int     frthbyte()
 *              VOID    out()
 *              VOID    outall()
 *              VOID    outarea()
 *              VOID    outbuf()
 *              VOID    outchk()
 *              VOID    outdp()
 *              VOID    outdot()
 *              VOID    outgsd()
 *              VOID    outsym()
 *              VOID    outab()
 *              VOID    outaw()
 *              VOID    outa3b()
 *              VOID    outa4b()
 *              VOID    outaxb()
 *              VOID    outatxb()
 *              VOID    outrb()
 *              VOID    outrw()
 *              VOID    outr11()
 *              VOID    out_lb()
 *              VOID    out_lw()
 *              VOID    out_l3b()
 *              VOID    out_l4b()
 *              VOID    out_lxb()
 *              VOID    out_txb()
 */

/*)Function     VOID    outab(v)
 *)Function     VOID    outaw(v)
 *)Function     VOID    outa3b(v)
 *)Function     VOID    outa4b(v)
 *
 *              a_uint  v               assembler data
 *
 *      Dispatch to output routine of 1 to 4 absolute bytes.
 *
 *      local variables:
 *              none
 *
 *      global variables:
 *              none
 *
 *      functions called:
 *              VOID    outaxb()        asout.c
 *
 *      side effects:
 *              Absolute data is processed.
 */

VOID
outab(a_uint v)
{
        outaxb(1, v);
}

VOID
outaw(a_uint v)
{
        outaxb(2, v);
}

VOID
outa3b(a_uint v)
{
        outaxb(3, v);
}

VOID
outa4b(a_uint v)
{
        outaxb(4, v);
}

/*)Function     VOID    outaxb(i, v)
 *
 *              int     i               output byte count
 *              a_uint  v               assembler data
 *
 *      The function outaxb() processes 1 to 4 bytes of
 *      assembled data in absolute format.
 *
 *      local variables:
 *
 *      global variables:
 *              sym     dot             defined as sym[0]
 *              int     oflag           -o, generate relocatable output flag
 *              int     pass            assembler pass number
 *
 *      functions called:
 *              VOID    outatxb()       asout.c
 *              VOID    outchk()        asout.c
 *              VOID    out_lxb()       asout.c
 *
 *      side effects:
 *              The current assembly address is incremented by i.
 */

VOID
outaxb(int i, a_uint v)
{
        if (pass == 2) {
                out_lxb(i, v, 0);
                if (oflag) {
                        outchk(i, 0);
                        outatxb(i, v);
                }
        }
        /*
         * Update the Program Counter
         */
        dot.s_addr += i;
}

/* sdas specific */
/*)Function     VOID    write_rmode(r)
 *
 *              int     r               relocation mode
 *
 *      write_rmode puts the passed relocation mode into the
 *      output relp buffer, escaping it if necessary.
 *
 *      global variables:
 *              char *  relp            Pointer to R Line Values
 *
 *      functions called:
 *              VOID    rerr()          assubr.c
 *
 *      side effects:
 *              relp is incremented appropriately.
 */
VOID
write_rmode(int r)
{
    /* We need to escape the relocation mode if it is greater
     * than a byte, or if it happens to look like an escape.
     * (I don't think that the latter case is legal, but
     * better safe than sorry).
     */
    if ((r > 0xff) || ((r & R_ESCAPE_MASK) == R_ESCAPE_MASK))
    {
        /* Hack in up to an extra 4 bits of flags with escape. */
        if (r > 0xfff)
        {
             /* uh-oh.. we have more than 4 extra bits. */
             fprintf(stderr,
                     "Internal error: relocation mode 0x%X too big.\n",
                     r);
             rerr();
        }
        /* printf("escaping relocation mode\n"); */
        *relp++ = R_ESCAPE_MASK | (r >> 8);
        *relp++ = r & 0xff;
    }
    else
    {
        *relp++ = r;
    }
}
/* end sdas specific */

/*)Function     VOID    outatxb(i, v)
 *
 *              int     i               number of bytes to process
 *              int     v               assembler data
 *
 *      The function outatxb() outputs i bytes
 *
 *      local variables:
 *              none
 *
 *      global variables:
 *              int     hilo            byte order
 *              char *  txtp            Pointer to T Line Values
 *
 *      functions called:
 *              int     lobyte()        asout.c
 *              int     hibyte()        asout.c
 *              int     thrdbyte()      asout.c
 *              int     frthbyte()      asout.c
 *
 *      side effects:
 *              i bytes are placed into the T Line Buffer.
 */

VOID
outatxb(int i, a_uint v)
{
        if ((int) hilo) {
                if (i >= 4) *txtp++ = frthbyte(v);
                if (i >= 3) *txtp++ = thrdbyte(v);
                if (i >= 2) *txtp++ = hibyte(v);
                if (i >= 1) *txtp++ = lobyte(v);
        } else {
                if (i >= 1) *txtp++ = lobyte(v);
                if (i >= 2) *txtp++ = hibyte(v);
                if (i >= 3) *txtp++ = thrdbyte(v);
                if (i >= 4) *txtp++ = frthbyte(v);
        }
}

/*)Function     VOID    outrb(esp, r)
 *
 *              expr *  esp             pointer to expr structure
 *              int     r               relocation mode
 *
 *      The function outrb() processes a byte of generated code
 *      in either absolute or relocatable format dependent upon
 *      the data contained in the expr structure esp.  If the
 *      .REL output is enabled then the appropriate information
 *      is loaded into the txt and rel buffers.
 *
 *      local variables:
 *              int     m               signed value mask
 *              int     n               unsigned value mask
 *                                      symbol/area reference number
 *
 *      global variables:
 *              sym     dot             defined as sym[0]
 *              int     oflag           -o, generate relocatable output flag
 *              int     pass            assembler pass number
 *              char *  relp            Pointer to R Line Values
 *              char *  txtp            Pointer to T Line Values
 *
 *      functions called:
 *              VOID    outchk()        asout.c
 *              VOID    out_lb()        asout.c
 *              VOID    out_rb()        asout.c
 *              VOID    out_tb()        asout.c
 *
 *      side effects:
 *              The current assembly address is incremented by 1.
 */

VOID
outrb(struct expr *esp, int r)
{
        a_uint n;

        if (pass == 2) {
                if (esp->e_flag==0 && esp->e_base.e_ap==NULL) {
                        /* This is a constant; simply write the
                         * const byte to the T line and don't
                         * generate any relocation info.
                         */
                        n = (a_uint) ~0x000000FF;               /* 1 byte  */

                        /*
                         * Page0 Range Check
                         */
                        if (((r & (R_SGND | R_USGN | R_PAGX | R_PCR)) == R_PAG0) &&
                           ((n & esp->e_addr) != 0))
                                err('d');

                        out_lxb(1,esp->e_addr,0);
                        if (oflag) {
                                outchk(1,0);
                                outatxb(1,esp->e_addr);
                        }
                } else {
                        if (!is_sdas() || !is_sdas_target_8051_like()) {
                                r |= R_BYTE | R_BYTX | esp->e_rlcf;
                                if (r & R_MSB) {
                                        out_lb(hibyte(esp->e_addr),r|R_RELOC|R_HIGH);
                                } else {
                                        out_lb(lobyte(esp->e_addr),r|R_RELOC);
                                }
                                if (oflag) {
                                        outchk(2, 4);
                                        out_txb(2, esp->e_addr);
                                        if (esp->e_flag) {
                                                n = esp->e_base.e_sp->s_ref;
                                                r |= R_SYM;
                                        } else {
                                                n = esp->e_base.e_ap->a_ref;
                                        }
                                        *relp++ = r;
                                        *relp++ = txtp - txt - 2;
                                        out_rw(n);
                                }
                        } else {
                                /* sdas mcs51 specific */
                                /* We are generating a single byte of relocatable
                                 * info.
                                 *
                                 * We generate a 24 bit address. The linker will
                                 * select a single byte based on whether R_MSB or
                                 * R_HIB is set.
                                 */
                                /* 24 bit mode. */
                                r |= R_BYTE | R_BYT3 | esp->e_rlcf;
                                if (r & R_HIB)
                                {
                                    /* Probably should mark this differently in the
                                     * listing file.
                                     */
                                    out_lb(thrdbyte(esp->e_addr),r|R_RELOC|R_HIGH);
                                }
                                else if (r & R_MSB) {
                                    out_lb(hibyte(esp->e_addr),r|R_RELOC|R_HIGH);
                                } else {
                                    out_lb(lobyte(esp->e_addr),r|R_RELOC);
                                }
                                if (oflag) {
                                    outchk(3, 5);
                                    out_txb(3, esp->e_addr);
                                    if (esp->e_flag) {
                                            n = esp->e_base.e_sp->s_ref;
                                            r |= R_SYM;
                                    } else {
                                            n = esp->e_base.e_ap->a_ref;
                                    }
                                    write_rmode(r);
                                    *relp++ = txtp - txt - 3;
                                    out_rw(n);
                                }
                                /* end sdas mcs51 specific */
                        }
                }
        }
        /*
         * Update the Program Counter
         */
        dot.s_addr += 1;
}

/*)Function     VOID    outrw(esp, r)
 *
 *              expr *  esp             pointer to expr structure
 *              int     r               relocation mode
 *
 *      The function outrw() processes a word of generated code
 *      in either absolute or relocatable format dependent upon
 *      the data contained in the expr structure esp.  If the
 *      .REL output is enabled then the appropriate information
 *      is loaded into the txt and rel buffers.
 *
 *      local variables:
 *              int     n               symbol/area reference number
 *
 *      global variables:
 *              sym     dot             defined as sym[0]
 *              int     oflag           -o, generate relocatable output flag
 *              int     pass            assembler pass number
 *              char *  relp            Pointer to R Line Values
 *              char *  txtp            Pointer to T Line Values
 *
 *      functions called:
 *              VOID    outchk()        asout.c
 *              VOID    out_lw()        asout.c
 *              VOID    out_rw()        asout.c
 *              VOID    out_txb()       asout.c
 *
 *      side effects:
 *              The current assembly address is incremented by 2.
 */

VOID
outrw(struct expr *esp, int r)
{
        int n;

        if (pass == 2) {
                /* sdas specific */
                if (is_sdas() && is_sdas_target_8051_like() && esp->e_addr > 0xffff) {
                    warnBanner();
                    fprintf(stderr,
                            "large constant 0x%x truncated to 16 bits\n",
                            esp->e_addr);
                }
                /* end sdas specific */
                if (esp->e_flag==0 && esp->e_base.e_ap==NULL) {
                        out_lxb(2,esp->e_addr,0);
                        if (oflag) {
                                outchk(2,0);
                                out_txb(2,esp->e_addr);
                        }
                } else {
                        r |= R_WORD | esp->e_rlcf;
                        if (r & R_BYTX) {
                                rerr();
                                if (r & R_MSB) {
                                        out_lw(hibyte(esp->e_addr),r|R_RELOC);
                                } else {
                                        out_lw(lobyte(esp->e_addr),r|R_RELOC);
                                }
                        } else {
                                out_lw(esp->e_addr,r|R_RELOC);
                        }
                        if (oflag) {
                                if (!is_sdas() || !is_sdas_target_8051_like()) {
                                        outchk(2, 4);
                                        out_txb(2, esp->e_addr);
                                        if (esp->e_flag) {
                                                n = esp->e_base.e_sp->s_ref;
                                                r |= R_SYM;
                                        } else {
                                                n = esp->e_base.e_ap->a_ref;
                                        }
                                        *relp++ = r;
                                        *relp++ = txtp - txt - 2;
                                        out_rw(n);
                                } else {
                                        outchk(2, 5);
                                        out_txb(2, esp->e_addr);
                                        if (esp->e_flag) {
                                                n = esp->e_base.e_sp->s_ref;
                                                r |= R_SYM;
                                        } else {
                                                n = esp->e_base.e_ap->a_ref;
                                        }

                                        if (IS_C24(r))
                                        {
                                            /* If this happens, the linker will
                                             * attempt to process this 16 bit field
                                             * as 24 bits. That would be bad.
                                             */
                                            fprintf(stderr,
                                                    "***Internal error: C24 out in "
                                                    "outrw()\n");
                                            rerr();
                                        }
                                        write_rmode(r);
                                        *relp++ = txtp - txt - 2;
                                        out_rw(n);
                                }
                        }
                }
        }
        dot.s_addr += 2;
}

/* sdas specific */
/*)Function     VOID    outr24(esp, r)
 *
 *              expr *  esp             pointer to expr structure
 *              int     r               relocation mode
 *
 *      The function outr24() processes 24 bits of generated code
 *      in either absolute or relocatable format dependent upon
 *      the data contained in the expr structure esp.  If the
 *      .REL output is enabled then the appropriate information
 *      is loaded into the txt and rel buffers.
 *
 *      local variables:
 *              int     n               symbol/area reference number

 *
 *      global variables:
 *              sym     dot             defined as sym[0]
 *              int     oflag           -o, generate relocatable output flag
 *              int     pass            assembler pass number
 *              char *  relp            Pointer to R Line Values
 *              char *  txtp            Pointer to T Line Values
 *
 *      functions called:
 *              VOID    outchk()        asout.c
 *              VOID    out_l3b()       asout.c
 *              VOID    out_rw()        asout.c
 *              VOID    out_txb()       asout.c
 *
 *      side effects:
 *              The current assembly address is incremented by 3.
 */

VOID
outr24(struct expr *esp, int r)
{
        int n;

        if (pass == 2) {
                if (esp->e_flag==0 && esp->e_base.e_ap==NULL) {
                        /* This is a constant expression. */
                        out_l3b(esp->e_addr,0);
                        if (oflag) {
                                outchk(3, 0);
                                out_txb(3, esp->e_addr);
                        }
                } else {
                        /* This is a symbol. */
                        r |= R_WORD | esp->e_rlcf;
                        if (r & R_BYTX) {
                                /* I have no idea what this case is. */
                                rerr();
                                if (r & R_MSB) {
                                        out_lw(hibyte(esp->e_addr),r|R_RELOC);
                                } else {
                                        out_lw(lobyte(esp->e_addr),r|R_RELOC);
                                }
                        } else {
                                out_l3b(esp->e_addr,r|R_RELOC);
                        }
                        if (oflag) {
                                outchk(3, 5);
                                out_txb(3, esp->e_addr);
                                if (esp->e_flag) {
                                        n = esp->e_base.e_sp->s_ref;
                                        r |= R_SYM;
                                } else {
                                        n = esp->e_base.e_ap->a_ref;
                                }

                                if (r & R_BYTE)
                                {
                                    /* If this occurs, we cannot properly
                                     * code the relocation data with the
                                     * R_C24 flag. This means the linker
                                     * will fail to do the 24 bit relocation.
                                     * Which will suck.
                                     */
                                    fprintf(stderr,
                                            "***Internal error: BYTE out in 24 "
                                            "bit flat mode unexpected.\n");
                                    rerr();
                                }

                                write_rmode(r | R_C24);
                                *relp++ = txtp - txt - 3;
                                out_rw(n);
                        }
                }
        }
        /*
         * Update the Program Counter
         */
        dot.s_addr += 3;
}
/* end sdas specific */

/*)Function     VOID    outdp(carea, esp)
 *
 *              area *  carea           pointer to current area structure
 *              expr *  esp             pointer to expr structure
 *
 *      The function outdp() flushes the output buffer and
 *      outputs paging information to the .REL file.
 *
 *      local variables:
 *              int     n               symbol/area reference number
 *              int     r               relocation mode
 *
 *      global variables:
 *              int     oflag           -o, generate relocatable output flag
 *              int     pass            assembler pass number
 *              char *  relp            Pointer to R Line Values
 *              char *  txtp            Pointer to T Line Values
 *
 *      functions called:
 *              VOID    outbuf()        asout.c
 *              VOID    outchk()        asout.c
 *              VOID    out_rw()        asout.c
 *              VOID    out_txb()       asout.c
 *
 *      side effects:
 *              Output buffer flushed to .REL file.
 *              Paging information dumped to .REL file.
 */

VOID
outdp(struct area *carea, struct expr *esp, int r)
{
        int n;

        if (oflag && pass==2) {
                outchk(ASXHUGE, ASXHUGE);
                out_txb(2, carea->a_ref);
                out_txb(2, esp->e_addr);
                if (esp->e_flag || esp->e_base.e_ap!=NULL) {
                        r = R_WORD;
                        if (esp->e_flag) {
                                n = esp->e_base.e_sp->s_ref;
                                r |= R_SYM;
                        } else {
                                n = esp->e_base.e_ap->a_ref;
                        }
                        write_rmode(r);
                        *relp++ = txtp - txt - 2;
                        out_rw(n);
                }
                outbuf("P");
        }
}

/*)Function     VOID    outall()
 *
 *      The function outall() will output any bufferred assembled
 *      data and relocation information (during pass 2 if the .REL
 *      output has been enabled).
 *
 *      local variables:
 *              none
 *
 *      global variables:
 *              int     oflag           -o, generate relocatable output flag
 *              int     pass            assembler pass number
 *
 *      functions called:
 *              VOID    outbuf()        asout.c
 *
 *      side effects:
 *              assembled data and relocation buffers will be cleared.
 */

VOID
outall(void)
{
        if (oflag && pass==2)
                outbuf("R");
}

/*)Function     VOID    outdot()
 *
 *      The function outdot() outputs information about the
 *      current program counter value (during pass 2 if the .REL
 *      output has been enabled).
 *
 *      local variables:
 *              none
 *
 *      global variables:
 *              int     oflag           -o, generate relocatable output flag
 *              int     pass            assembler pass number
 *              char    rel[]           relocation data for code/data array
 *              char *  relp            Pointer to R Line Values
 *              char    txt[]           assembled code/data array
 *              char *  txtp            Pointer to T Line Values
 *
 *      functions called:
 *              int     fprintf()       c_library
 *              VOID    out()           asout.c
 *
 *      side effects:
 *              assembled data and relocation buffers will be cleared.
 */

VOID
outdot(void)
{
        if (oflag && pass==2) {
                fprintf(ofp, "T");
                out(txt,(int) (txtp-txt));
                fprintf(ofp, "\n");
                fprintf(ofp, "R");
                out(rel,(int) (relp-rel));
                fprintf(ofp, "\n");
                txtp = txt;
                relp = rel;
        }
}

/*)Function     outchk(nt, nr)
 *
 *              int     nr              number of additional relocation words
 *              int     nt              number of additional data words
 *
 *      The function outchk() checks the data and relocation buffers
 *      for space to insert the nt data words and nr relocation words.
 *      If space is not available then output the current data and
 *      initialize the data buffers to receive the new data.
 *
 *      local variables:
 *              area *  ap              pointer to an area structure
 *
 *      global variables:
 *              sym     dot             defined as sym[0]
 *              char    rel[]           relocation data for code/data array
 *              char *  relp            Pointer to R Line Values
 *              char    txt[]           assembled code/data array
 *              char *  txtp            Pointer to T Line Values
 *
 *      functions called:
 *              VOID    outbuf()        asout.c
 *              VOID    out_rw()        asout.c
 *              VOID    out_txb()       asout.c
 *
 *      side effects:
 *              Data and relocation buffers may be emptied and initialized.
 */

VOID
outchk(int nt, int nr)
{
        struct area *ap;

        if (txtp+nt > &txt[NTXT] || relp+nr > &rel[NREL]) {
                outbuf("R");
        }
        if (txtp == txt) {
                out_txb(2, dot.s_addr);
                if ((ap = dot.s_area) != NULL) {
                        write_rmode(R_WORD|R_AREA);
                        *relp++ = 0;
                        out_rw(ap->a_ref);
                }
        }
}

/*)Function     VOID    outbuf(s)
 *
 *              char *  s               "R" or "P" or ("I" illegal)
 *
 *      The function outbuf() will output any bufferred data
 *      and relocation information to the .REL file.  The output
 *      buffer pointers and counters are initialized.
 *
 *      local variables:
 *              none
 *
 *      global variables:
 *              FILE *  ofp             relocation output file handle
 *              char    rel[]           relocation data for code/data array
 *              char *  relp            Pointer to R Line Values
 *              char    txt[]           assembled code/data array
 *              char *  txtp            Pointer to T Line Values
 *
 *      functions called:
 *              int     fprintf()       c_library
 *              VOID    out()           asout.c
 *
 *      side effects:
 *              All bufferred data written to .REL file and
 *              buffer pointers and counters initialized.
 */

VOID
outbuf(char *s)
{
        if (txtp > &txt[2]) {
                fprintf(ofp, "T");
                out(txt,(int) (txtp-txt));
                fprintf(ofp, "\n");
                fprintf(ofp, "%s", s);
                out(rel,(int) (relp-rel));
                fprintf(ofp, "\n");
        }
        txtp = txt;
        relp = rel;
}

/*)Function     VOID    outgsd()
 *
 *      The function outgsd() performs the following:
 *      (1)     outputs the .REL file radix
 *      (2)     outputs the header specifying the number
 *              of areas and global symbols
 *      (3)     outputs the module name
 *      (4)     set the reference number and output a symbol line
 *              for all external global variables and absolutes
 *      (5)     output an area name, set reference number and output
 *              a symbol line for all global relocatables in the area.
 *              Repeat this proceedure for all areas.
 *
 *      local variables:
 *              area *  ap              pointer to an area structure
 *              sym *   sp              pointer to a sym structure
 *              int     i               loop counter
 *              int     j               loop counter
 *              int     c               string character value
 *              int     narea           number of code areas
 *              int     nglob           number of global symbols
 *              char *  ptr             string pointer
 *              int     rn              symbol reference number
 *
 *      global variables:
 *              area *  areap           pointer to an area structure
 *              int     hilo            byte order
 *              char    module[]        module name string
 *              sym *   symhash[]       array of pointers to NHASH
 *                                      linked symbol lists
 *              int     xflag           -x, listing radix flag
 *
 *      functions called:
 *              int     fprintf()       c_library
 *              VOID    outarea()       asout.c
 *              VOID    outsym()        asout.c
 *
 *      side effects:
 *              All symbols are given reference numbers, all symbol
 *              and area information is output to the .REL file.
 */

VOID
outgsd(void)
{
        struct area *ap;
        struct sym  *sp;
        int i, j;
        char *ptr;
        int narea, nglob, rn;

        /*
         * Number of areas
         */
        narea = areap->a_ref + 1;

        /*
         * Number of global references/absolutes
         */
        nglob = 0;
        for (i = 0; i < NHASH; ++i) {
                sp = symhash[i];
                while (sp) {
                        if (sp->s_flag&S_GBL)
                                nglob += 1;
                        sp = sp->s_sp;
                }
        }

        /*
         * Output Radix and number of areas and symbols
         */
        if (xflag == 0) {
                fprintf(ofp, "X%c\n", (int) hilo ? 'H' : 'L');
                fprintf(ofp, "H %X areas %X global symbols\n", narea, nglob);
        } else
        if (xflag == 1) {
                fprintf(ofp, "Q%c\n", (int) hilo ? 'H' : 'L');
                fprintf(ofp, "H %o areas %o global symbols\n", narea, nglob);
        } else
        if (xflag == 2) {
                fprintf(ofp, "D%c\n", (int) hilo ? 'H' : 'L');
                fprintf(ofp, "H %u areas %u global symbols\n", narea, nglob);
        }

        /*
         * Module name
         */
        if (module[0]) {
                fprintf(ofp, "M ");
                ptr = &module[0];
                fprintf(ofp, "%s\n", ptr);
        }

        /* sdas specific */
        /*
         * Sdcc compile options
         */
        if (is_sdas() && NULL != optsdcc) fprintf(ofp, "O %s\n", optsdcc);
        /* end sdas specific */

        /*
         * Global references and absolutes.
         */
        rn = 0;
        for (i=0; i<NHASH; ++i) {
                sp = symhash[i];
                while (sp) {
                        if (sp->s_area==NULL && sp->s_flag&S_GBL) {
                                sp->s_ref = rn++;
                                outsym(sp);
                        }
                        sp = sp->s_sp;
                }
        }

        /*
         * Global relocatables.
         */
        for (i=0; i<narea; ++i) {
                ap = areap;
                while (ap->a_ref != i)
                        ap = ap->a_ap;
                outarea(ap);
                for (j=0; j<NHASH; ++j) {
                        sp = symhash[j];
                        while (sp) {
                                if (sp->s_area==ap && sp->s_flag&S_GBL) {
                                        sp->s_ref = rn++;
                                        outsym(sp);
                                }
                                sp = sp->s_sp;
                        }
                }
        }
}

/*)Function     VOID    outarea(ap)
 *
 *              area *  ap              pointer to an area structure
 *
 *      The function outarea()  outputs the A line to the .REL
 *      file.  The A line contains the area's name, size,
 *      and attributes.
 *
 *      local variables:
 *              char *  frmt            pointer to format string
 *
 *      global variables:
 *              FILE *  ofp             relocation output file handle
 *              int     xflag           -x, listing radix flag
 *
 *      functions called:
 *              int     fprintf()       c_library
 *
 *      side effects:
 *              The A line is sent to the .REL file.
 */

VOID
outarea(struct area *ap)
{
        char * frmt;

        fprintf(ofp, "A ");
        fprintf(ofp, "%s", &ap->a_id[0]);

        switch(xflag) {
        default:
        case 0: frmt = " size %X flags %X";     break;
        case 1: frmt = " size %o flags %o";     break;
        case 2: frmt = " size %u flags %u";     break;
        }

        fprintf(ofp, frmt, ap->a_size, ap->a_flag);
        if (is_sdas()) {
                /* sdas specific */
                if (xflag == 0) {
                        fprintf(ofp, " addr %X", ap->a_addr);
                } else
                if (xflag == 1) {
                        fprintf(ofp, " addr %o", ap->a_addr);
                } else
                if (xflag == 2) {
                        fprintf(ofp, " addr %u", ap->a_addr);
                }
                /* end sdas specific */
        }
        fprintf(ofp, "\n");
}

/*)Function     VOID    outsym(sp)
 *
 *              sym *   sp              pointer to a sym structure
 *
 *      The function outsym() outputs the S line to the .REL
 *      file.  The S line contains the symbols name and whether the
 *      the symbol is defined or referenced.
 *
 *      local variables:
 *              char *  frmt            pointer to format string
 *              int     s_addr          (int) truncated to 2-bytes
 *
 *      global variables:
 *              FILE *  ofp             relocation output file handle
 *              int     xflag           -x, listing radix flag
 *
 *      functions called:
 *              int     fprintf()       c_library
 *
 *      side effects:
 *              The S line is sent to the .REL file.
 */

VOID
outsym(struct sym *sp)
{
        char *frmt;
        a_uint s_addr;

        s_addr = sp->s_addr;

        fprintf(ofp, "S ");
        fprintf(ofp, "%s", &sp->s_id[0]);
        fprintf(ofp, " %s", sp->s_type==S_NEW ? "Ref" : "Def");

        switch(xflag) {
        default:
        case 0:
                frmt = "%04X\n";
                break;

        case 1:
                frmt = "%06o\n";
                break;

        case 2:
                frmt = "%05u\n";
                break;
        }

        fprintf(ofp, frmt, s_addr);
}

/*)Function     VOID    out(p, n)
 *
 *              int     n               number of words to output
 *              int *   p               pointer to data words
 *
 *      The function out() outputs the data words to the .REL file
 *      in the specified radix.
 *
 *      local variables:
 *              none
 *
 *      global variables:
 *              FILE *  ofp             relocation output file handle
 *              int     xflag           -x, listing radix flag
 *
 *      functions called:
 *              int     fprintf()       c_library
 *
 *      side effects:
 *              Data is sent to the .REL file.
 */

VOID
out(char *p, int n)
{
        while (n--) {
                if (xflag == 0) {
                        fprintf(ofp, " %02X", (*p++)&0377);
                } else
                if (xflag == 1) {
                        fprintf(ofp, " %03o", (*p++)&0377);
                } else
                if (xflag == 2) {
                        fprintf(ofp, " %03u", (*p++)&0377);
                }
        }
}

/*)Function     VOID    out_lb(v, t)
 *
 *              a_uint  v               assembled data
 *              int     t               relocation type
 *
 *      The function out_lb() copies the assembled data and
 *      its relocation type to the list data buffers.
 *
 *      local variables:
 *              none
 *
 *      global variables:
 *              int *   cp              pointer to assembler output array cb[]
 *              int *   cpt             pointer to assembler relocation type
 *                                      output array cbt[]
 *
 *      functions called:
 *              none
 *
 *      side effects:
 *              Pointers to data and relocation buffers incremented by 1.
 */

VOID
out_lb(a_uint v, int t)
{
        if (cp < &cb[NCODE]) {
                *cp++ = (char) v;
                *cpt++ = t;
        }
}

/*)Function     VOID    out_lw(v, t)
 *)Function     VOID    out_l3b(v, t)
 *)Function     VOID    out_l4b(v, t)
 *
 *              a_uint  v               assembled data
 *              int     t               relocation type
 *
 *      Dispatch functions for processing listing data.
 *
 *      local variables:
 *              none
 *
 *      global variables:
 *              none
 *
 *      functions called:
 *              none
 *
 *      side effects:
 *              Listing data processed.
 */

VOID
out_lw(a_uint v, int t)
{
        out_lxb(2, v, t);
}

VOID
out_l3b(a_uint v, int t)
{
        out_lxb(3, v, t);
}

VOID
out_l4b(a_uint v, int t)
{
        out_lxb(4, v, t);
}

/*)Function     VOID    out_lxb(i, v, t)
 *
 *              int     i               output byte count
 *              a_uint  v               assembled data
 *              int     t               relocation type
 *
 *      Dispatch function for list processing.
 *
 *      local variables:
 *              none
 *
 *      global variables:
 *              int     hilo            byte order
 *
 *      functions called:
 *              VOID    out_lb()        asout.c
 *
 *      side effects:
 *              i list bytes are processed.
 */

VOID
out_lxb(int i, a_uint v, int t)
{
        if ((int) hilo) {
                if (i >= 3) out_lb(thrdbyte(v),t ? t|R_HIGH : 0);
                if (i >= 2) out_lb(hibyte(v),t);
                if (i >= 1) out_lb(lobyte(v),t);
        } else {
                if (i >= 1) out_lb(lobyte(v),t);
                if (i >= 2) out_lb(hibyte(v),t);
                if (i >= 3) out_lb(thrdbyte(v),t ? t|R_HIGH : 0);
        }
}

/*)Function     VOID    out_rw(v)
 *
 *              a_uint  v               assembled data
 *
 *      The function out_rw() outputs the relocation (R)
 *      data word as two bytes ordered according to hilo.
 *
 *      local variables:
 *              none
 *
 *      global variables:
 *              int     hilo            byte order
 *              char *  relp            Pointer to R Line Values
 *
 *      functions called:
 *              int     lobyte()        asout.c
 *              int     hibyte()        asout.c
 *
 *      side effects:
 *              Pointer to relocation buffer incremented by 2.
 */

VOID
out_rw(a_uint v)
{
        if ((int) hilo) {
                *relp++ = hibyte(v);
                *relp++ = lobyte(v);
        } else {
                *relp++ = lobyte(v);
                *relp++ = hibyte(v);
        }
}

/*)Function     VOID    out_txb(i, v)
 *
 *              int     i               T Line byte count
 *              a_uint  v               data word
 *
 *      The function out_txb() outputs the text (T)
 *      data word as i bytes ordered according to hilo.
 *
 *      local variables:
 *
 *      global variables:
 *              int     hilo            byte order
 *              char *  txtp            Pointer to T Line Values
 *
 *      functions called:
 *              int     lobyte()        asout.c
 *              int     hibyte()        asout.c
 *              int     thrdbyte()      asout.c
 *              int     frthbyte()      asout.c
 *
 *      side effects:
 *              T Line buffer updated.
 */

VOID
out_txb(int i, a_uint v)
{
        if ((int) hilo) {
                if (i >= 4) *txtp++ = frthbyte(v);
                if (i >= 3) *txtp++ = thrdbyte(v);
                if (i >= 2) *txtp++ = hibyte(v);
                if (i >= 1) *txtp++ = lobyte(v);
        } else {
                if (i >= 1) *txtp++ = lobyte(v);
                if (i >= 2) *txtp++ = hibyte(v);
                if (i >= 3) *txtp++ = thrdbyte(v);
                if (i >= 4) *txtp++ = frthbyte(v);
        }
}

/*)Function     int     lobyte(v)
 *)Function     int     hibyte(v)
 *)Function     int     thrdbyte(v)
 *)Function     int     frthbyte(v)
 *
 *              a_uint  v               assembled data
 *
 *      These functions return the 1st, 2nd, 3rd, or 4th byte
 *      of integer v.
 *
 *      local variables:
 *              none
 *
 *      global variables:
 *              none
 *
 *      functions called:
 *              none
 *
 *      side effects:
 *              none
 */

int
lobyte(a_uint v)
{
        return ((int) v&0377);
}

int
hibyte(a_uint v)
{
        return ((int) (v>>8)&0377);
}

int
thrdbyte(a_uint v)
{
        return ((int) (v>>16)&0377);
}

int
frthbyte(a_uint v)
{
        return ((int) (v>>24)&0377);
}

/*
 * JLH: Output relocatable 11 bit jump/call
 *
 * This function is derived from outrw(), adding the parameter for the
 * 11 bit address.  This form of address is used only on the 8051 and 8048.
 */
/*)Function     VOID    outr11(esp, op, r)
 *
 *              expr *  esp             pointer to expr structure
 *              int     op              opcode
 *              int     r               relocation mode
 *
 *      The function outr11() processes a word of generated code
 *      in either absolute or relocatable format dependent upon
 *      the data contained in the expr structure esp.  If the
 *      .REL output is enabled then the appropriate information
 *      is loaded into the txt and rel buffers.  The code is output
 *      in a special format to the linker to allow relocation and
 *      merging of the opcode and an 11 bit paged address as required
 *      by the 8051 architecture.
 *
 *      This function based on code by
 *              John L. Hartman
 *              jhartman@compuserve.com
 *
 *      local variables:
 *              int     n               symbol/area reference number
 *
 *      global variables:
 *              sym     dot             defined as sym[0]
 *              int     oflag           -o, generate relocatable output flag
 *              int     pass            assembler pass number
 *              char *  relp            Pointer to R Line Values
 *              char *  txtp            Pointer to T Line Values
 *              
 *      functions called:
 *              VOID    outchk()        asout.c
 *              VOID    out_lw()        asout.c
 *              VOID    out_rw()        asout.c
 *              VOID    out_txb()       asout.c
 *
 *      side effects:
 *              The current assembly address is incremented by 2.
 */
VOID
outr11(struct expr *esp, int op, int r)
{
        int n;

        if (pass == 2) {
                if (!is_sdas() || !is_sdas_target_8051_like()) {
                        if (esp->e_flag==0 && esp->e_base.e_ap==NULL) {
                                /*
                                 * Absolute Destination
                                 *
                                 * Use the global symbol '.__.ABS.'
                                 * of value zero and force the assembler
                                 * to use this absolute constant as the
                                 * base value for the relocation.
                                 */
                                esp->e_flag = 1;
                                esp->e_base.e_sp = &sym[1];
                        }
                        /*
                         * Relocatable Destination.  Build THREE
                         * byte output: relocatable word, followed
                         * by op-code.  Linker will combine them.
                         */
                        r |= R_WORD | esp->e_rlcf;
                        n = ((esp->e_addr & 0x0700) >> 3) | op;
                        n = (n << 8) | (esp->e_addr & 0xFF);
                        out_lw(n,r|R_RELOC);
                        if (oflag) {
                                outchk(3, 4);
                                out_txb(2, esp->e_addr);
                                *txtp++ = op;

                                if (esp->e_flag) {
                                        n = esp->e_base.e_sp->s_ref;
                                        r |= R_SYM;
                                } else {
                                        n = esp->e_base.e_ap->a_ref;
                                }
                                *relp++ = r;
                                *relp++ = txtp - txt - 3;
                                out_rw(n);
                        }
                } else {
                        if (esp->e_flag==0 && esp->e_base.e_ap==NULL) {
                                /* Absolute destination.
                                 * Listing shows only the address.
                                 */
                                out_lw(esp->e_addr,0);
                                if (oflag) {
                                        outchk(3, 0);
                                        out_txb(2, esp->e_addr);
                                        *txtp++ = op;

                                        write_rmode(r);
                                        *relp++ = txtp - txt - 3;
                                        out_rw(0xFFFF);
                                }
                        } else {
                                /* Relocatable destination.  Build THREE
                                 * byte output: relocatable word, followed
                                 * by op-code.  Linker will combine them.
                                 * Listing shows only the address.
                                 */
                                r |= R_WORD | esp->e_rlcf;
                                out_lw(esp->e_addr,r|R_RELOC);
                                if (oflag) {
                                        outchk(3, 5);
                                        out_txb(2, esp->e_addr);
                                        *txtp++ = op;

                                        if (esp->e_flag) {
                                                n = esp->e_base.e_sp->s_ref;
                                                r |= R_SYM;
                                        } else {
                                                n = esp->e_base.e_ap->a_ref;
                                        }
                                        write_rmode(r);
                                        *relp++ = txtp - txt - 3;
                                        out_rw(n);
                                }
                        }
                }
        }
        dot.s_addr += 2;
}

/* sdas specific */
/*
 * Output relocatable 19 bit jump/call
 *
 * This function is derived from outrw(), adding the parameter for the
 * 19 bit address.  This form of address is used only in the DS80C390
 * Flat24 mode.
 */
VOID
outr19(struct expr * esp, int op, int r)
{
        int n;

        if (pass == 2) {
                if (esp->e_flag==0 && esp->e_base.e_ap==NULL) {
                        /* Absolute destination.
                         * Listing shows only the address.
                         */
                        out_lw(esp->e_addr,0);
                        if (oflag) {
                                outchk(4, 0);
                                out_txb(3, esp->e_addr);
                                *txtp++ = op;

                                write_rmode(r);
                                *relp++ = txtp - txt - 4;
                                out_rw(0xFFFF);
                        }
                } else {
                        /* Relocatable destination.  Build FOUR
                         * byte output: relocatable 24-bit entity, followed
                         * by op-code.  Linker will combine them.
                         * Listing shows only the address.
                         */
                        r |= R_WORD | esp->e_rlcf;
                        out_l3b(esp->e_addr,r|R_RELOC);
                        if (oflag) {
                                outchk(4, 5);
                                out_txb(3, esp->e_addr);
                                *txtp++ = op;

                                if (esp->e_flag) {
                                        n = esp->e_base.e_sp->s_ref;
                                        r |= R_SYM;
                                } else {
                                        n = esp->e_base.e_ap->a_ref;
                                }
                                write_rmode(r);
                                *relp++ = txtp - txt - 4;
                                out_rw(n);
                        }
                }
        }
        dot.s_addr += 3;
}
/* end sdas specific */
