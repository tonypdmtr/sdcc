// Derived from test case from the memory model study group of SC22 WG14
// For this test, behaviour is defined in the PNVI-ae-udi memory model.

/*
Original test copyright (c) 2012-2016 David Chisnall, Kayvan Memarian, and Peter Sewell.

Permission to use, copy, modify, and/or distribute this software for
any purpose with or without fee is hereby granted, provided that the
above copyright notice and this permission notice appear in all
copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
PERFORMANCE OF THIS SOFTWARE.
*/

// Adapted for SDCC by Philipp Klaus Krause in 2020.

#include <testfwk.h>

#pragma disable_warning 127

#include <stdint.h>

int x=1;
typedef union { uintptr_t ui; int *up; } un;

void
testMM(void)
{
  un u; 
  int *p = &x;
  u.up = p;
  uintptr_t i = u.ui;
  int *q = (int*)i;
  *q = 11;  // does this have UB?
  ASSERT (x == *p);
  ASSERT (x == *q);
}

