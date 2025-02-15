/*
 * Simulator of microcontrollers (ialu.cc)
 *
 * Copyright (C) @@S@@,@@Y@@ Drotos Daniel, Talker Bt.
 * 
 * To contact author send email to drdani@mazsola.iit.uni-miskolc.hu
 *
 */

/* This file is part of microcontroller simulator: ucsim.

UCSIM is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

UCSIM is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with UCSIM; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA. */

#include "rxkcl.h"


int
cl_rxk::inc_ss(class cl_cell16 &rp, u16_t op)
{
  rp.W(op+1);
  tick(1);
  return resGO;
}

int
cl_rxk::inc_r(class cl_cell8 &cr, u8_t op)
{
  class cl_cell8 &rf= destF();
  u8_t r, f= rF & ~(flagS|flagZ|flagV), na7, r7;
  na7= (op&0x80)^0x80;
  cr.W(r= op+1);
  r7= r&0x80;
  if (r & 0x80) f|= flagS;
  if (!r) f|= flagZ;
  if (na7 & r7) f|= flagV;
  rf.W(f);
  tick(1);
  return resGO;
}

int
cl_rxk::dec_ss(class cl_cell16 &rp, u16_t op)
{
  rp.W(op-1);
  tick(1);
  return resGO;
}

int
cl_rxk::dec_r(class cl_cell8 &cr, u8_t op)
{
  class cl_cell8 &rf= destF();
  u8_t r, f= rF & ~(flagS|flagZ|flagV), a7, nr7;
  a7= op&0x80;
  cr.W(r= op-1);
  nr7= (r&0x80)^0x80;
  if (r & 0x80) f|= flagS;
  if (!r) f|= flagZ;
  if (a7 & nr7) f|= flagV;
  rf.W(f);
  tick(1);
  return resGO;
}

/*
     C <-- 7..<-...0 <--+
        |               |
        +---------------+
 */
int
cl_rxk::rot8left(class cl_cell8 &dest, u8_t op)
{
  class cl_cell8 &f= destF();
  u8_t a7;
  a7= op&0x80;
  dest.W((op<<1) | (a7?1:0));
  f.W((rF & ~flagC) | (a7?flagC:0));
  tick(1);
  return resGO;
}

/*
     C <-- 7..<-...0 <--+
     |                  |
     +------------------+
 */
int
cl_rxk::rot9left(class cl_cell8 &dest, u8_t op)
{
  class cl_cell8 &f= destF();
  u8_t a7, c= rF&flagC;
  a7= op&0x80;
  dest.W((op<<1) | (c?1:0));
  f.W((rF & ~flagC) | (a7?flagC:0));
  tick(1);
  return resGO;
}

/*
     7..->...0 --> C
     |         |
     +---------+
 */
int
cl_rxk::rot8right(class cl_cell8 &dest, u8_t op)
{
  class cl_cell8 &f= destF();
  u8_t a0;
  a0= op&0x01;
  dest.W((op>>1) | (a0?0x80:0));
  f.W((rF & ~flagC) | (a0?flagC:0));
  tick(1);
  return resGO;
}

/*
     7..->...0 --> C
     |             |
     +-------------+
 */
int
cl_rxk::rot9right(class cl_cell8 &dest, u8_t op)
{
  class cl_cell8 &f= destF();
  u8_t a0, c= rF&flagC;
  a0= op&0x01;
  dest.W((op>>1) | (c?0x80:0));
  f.W((rF & ~flagC) | (a0?flagC:0));
  tick(1);
  return resGO;
}

int
cl_rxk::CPL(t_mem code)
{
  destA().W(~rA);
  tick(1);
  return resGO;
}

int
cl_rxk::add_hl_ss(u16_t op)
{
  class cl_cell16 &hl= destHL();
  class cl_cell8 &f= destF();
  u8_t forg= f.R();
  u32_t res= rHL + op;
  hl.W(res);
  if (res > 0xffff)
    f.W(forg|= flagC);
  else
    f.W(forg|=~flagC);
  tick(1);
  return resGO;
}

int
cl_rxk::ADD_SP_d(t_mem code)
{
  i8_t d= fetch();
  u32_t res= rSP+d;
  class cl_cell8 &f= destF();
  u8_t forg= f.R();
  cSP.W(res);
  if (res > 0xffff)
    f.W(forg|= flagC);
  else
    f.W(forg&= ~flagC);
  tick(3);
  return resGO;
}


/* End of rxk.src/ialu.cc */
