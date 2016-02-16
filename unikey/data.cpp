// -*- coding:unix; mode:c++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-
/*------------------------------------------------------------------------------
VnConv: Vietnamese Encoding Converter Library
UniKey Project: http://unikey.sourceforge.net
Copyleft (C) 1998-2002 Pham Kim Long
Contact: longp@cslab.felk.cvut.cz

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
--------------------------------------------------------------------------------*/

#include "charset.h"

/*
Instructions on how to add more charset supports

Each charset enumerates all its characters according to a fixed order.
To understand this order, copy the TCVN3 charset bellow to some application
and view it with some TCVN3 font.

Steps to add an 1-byte charset:

- Determine the Id for your charset. See "vnconv.h". The Id
  for your charset is equal to the id of the last 1-byte charset PLUS 1.
  Then define a constant for that Id (e.g. #define MY_NEW_CHARSET 25)
- In "vnconv.h": Increase the variable CONV_TOTAL_SINGLE_CHARSETS by 1.
- Add an entry for your charset to the end of CharsetIdMap (in this file)
- Add your charset to the end of SingleBytesTable
- Note that and the end of each charset (after character z) there's a section
  for the symbols in western charsets (see TCVN3). Just copy
  this section for your charset, and set zero for each code point
  that is occupied by your charset (for representing Vietnamese characters).

Steps to add a 2-byte charset:
- Determine the Id for your charset. See "vnconv.h". The Id
  for your charset is equal to the id of the last 2-byte charset PLUS 1.
  Then define a constant for that Id (e.g. #define MY_NEW_CHARSET 44)
- In "vnconv.h": Increase the variable CONV_TOTAL_DOUBLE_CHARSETS by 1.
- Add an entry for your charset to the end of CharsetIdMap (in this file)
- Add your charset to the end of DoubleByteTables
- Note that and the end of each charset (after character z) there's a section
  for the symbols in western charsets. Just copy this section from
  VNI-WIN charset to your charset
- Double-byte characters are represented as a word in which the
  low byte is base character, high byte is tone mark (if present).
*/
extern CharsetNameId CharsetIdMap[];
extern const int CharsetCount;

CharsetNameId CharsetIdMap[] = {
	{"BKHCM1",		CONV_CHARSET_BKHCM1},
	{"BKHCM2",		CONV_CHARSET_BKHCM2},
	{"ISC",			CONV_CHARSET_ISC},
	{"NCR-DEC",		CONV_CHARSET_UNIREF},
	{"NCR-HEX",		CONV_CHARSET_UNIREF_HEX},
	{"TCVN3",		CONV_CHARSET_TCVN3},
	{"UNI-COMP",	CONV_CHARSET_UNIDECOMPOSED},
	{"UNICODE",		CONV_CHARSET_UNICODE},
	{"UTF-8",		CONV_CHARSET_UNIUTF8},
	{"UTF8",		CONV_CHARSET_UNIUTF8},
	{"UVIQR",       CONV_CHARSET_UTF8VIQR},
	{"VIETWARE-F",	CONV_CHARSET_VIETWAREF},
	{"VIETWARE-X",	CONV_CHARSET_VIETWAREX},
	{"VIQR",		CONV_CHARSET_VIQR},
	{"VISCII",		CONV_CHARSET_VISCII},
	{"VNI-MAC",		CONV_CHARSET_VNIMAC},
	{"VNI-WIN",		CONV_CHARSET_VNIWIN},
	{"VPS",			CONV_CHARSET_VPS},
	{"WINCP-1258",	CONV_CHARSET_WINCP1258}
};

const int CharsetCount = sizeof(CharsetIdMap)/sizeof(CharsetNameId);

/* Western symbols that need to be mapped
  0x80, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88,
  0x89, 0x8A, 0x8B, 0x8C, 0x8E, 0x91, 0x92, 0x93,
  0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B,
  0x9C, 0x9E, 0x9F,

If a single byte charset occupies a certain symbol,
its code point in the charset must be set to zero.
See TCVN3 & VPS below for examples
*/

unsigned char SingleByteTables[][TOTAL_VNCHARS] =

// TCVN3
{{static_cast<unsigned char>('A'),static_cast<unsigned char>('a'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),      // 0: a
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),		// 1: a^
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),		// 2: a(
  static_cast<unsigned char>('B'),static_cast<unsigned char>('b'),static_cast<unsigned char>('C'),static_cast<unsigned char>('c'),static_cast<unsigned char>('D'),static_cast<unsigned char>('d'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('E'),static_cast<unsigned char>('e'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),		// 3: e
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),      // 4: e^
  static_cast<unsigned char>('F'),static_cast<unsigned char>('f'),static_cast<unsigned char>('G'),static_cast<unsigned char>('g'),static_cast<unsigned char>('H'),static_cast<unsigned char>('h'),
  static_cast<unsigned char>('I'),static_cast<unsigned char>('i'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),		// 5: i
  static_cast<unsigned char>('J'),static_cast<unsigned char>('j'),static_cast<unsigned char>('K'),static_cast<unsigned char>('k'),static_cast<unsigned char>('L'),static_cast<unsigned char>('l'),static_cast<unsigned char>('M'),static_cast<unsigned char>('m'),static_cast<unsigned char>('N'),static_cast<unsigned char>('n'),
  static_cast<unsigned char>('O'),static_cast<unsigned char>('o'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),		// 6: o
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),		// 7: o^
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),		// 8: o+
  static_cast<unsigned char>('P'),static_cast<unsigned char>('p'),static_cast<unsigned char>('Q'),static_cast<unsigned char>('q'),static_cast<unsigned char>('R'),static_cast<unsigned char>('r'),static_cast<unsigned char>('S'),static_cast<unsigned char>('s'),static_cast<unsigned char>('T'),static_cast<unsigned char>('t'),
  static_cast<unsigned char>('U'),static_cast<unsigned char>('u'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),		// 9: u
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),		//10: u+
  static_cast<unsigned char>('V'),static_cast<unsigned char>('v'),static_cast<unsigned char>('W'),static_cast<unsigned char>('w'),static_cast<unsigned char>('X'),static_cast<unsigned char>('x'),
  static_cast<unsigned char>('Y'),static_cast<unsigned char>('y'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),		//11: y
  static_cast<unsigned char>('Z'),static_cast<unsigned char>('z'),
  0x80, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88,
  0x89, 0x8A, 0x8B, 0x8C, 0x8E, 0x91, 0x92, 0x93,
  0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B,
  0x9C, 0x9E, 0x9F},
//VPS
{ static_cast<unsigned char>('A'),static_cast<unsigned char>('a'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('B'),static_cast<unsigned char>('b'),static_cast<unsigned char>('C'),static_cast<unsigned char>('c'),static_cast<unsigned char>('D'),static_cast<unsigned char>('d'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('E'),static_cast<unsigned char>('e'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('F'),static_cast<unsigned char>('f'),static_cast<unsigned char>('G'),static_cast<unsigned char>('g'),static_cast<unsigned char>('H'),static_cast<unsigned char>('h'),
  static_cast<unsigned char>('I'),static_cast<unsigned char>('i'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('J'),static_cast<unsigned char>('j'),static_cast<unsigned char>('K'),static_cast<unsigned char>('k'),static_cast<unsigned char>('L'),static_cast<unsigned char>('l'),static_cast<unsigned char>('M'),static_cast<unsigned char>('m'),static_cast<unsigned char>('N'),static_cast<unsigned char>('n'),
  static_cast<unsigned char>('O'),static_cast<unsigned char>('o'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('P'),static_cast<unsigned char>('p'),static_cast<unsigned char>('Q'),static_cast<unsigned char>('q'),static_cast<unsigned char>('R'),static_cast<unsigned char>('r'),static_cast<unsigned char>('S'),static_cast<unsigned char>('s'),static_cast<unsigned char>('T'),static_cast<unsigned char>('t'),
  static_cast<unsigned char>('U'),static_cast<unsigned char>('u'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('V'),static_cast<unsigned char>('v'),static_cast<unsigned char>('W'),static_cast<unsigned char>('w'),static_cast<unsigned char>('X'),static_cast<unsigned char>('x'),
  static_cast<unsigned char>('Y'),static_cast<unsigned char>('y'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('Z'),static_cast<unsigned char>('z'),
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x8E, 0x91, 0x92, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x9E, 0x00},
//VISCII
{ static_cast<unsigned char>('A'),static_cast<unsigned char>('a'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('B'),static_cast<unsigned char>('b'),static_cast<unsigned char>('C'),static_cast<unsigned char>('c'),static_cast<unsigned char>('D'),static_cast<unsigned char>('d'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('E'),static_cast<unsigned char>('e'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('F'),static_cast<unsigned char>('f'),static_cast<unsigned char>('G'),static_cast<unsigned char>('g'),static_cast<unsigned char>('H'),static_cast<unsigned char>('h'),
  static_cast<unsigned char>('I'),static_cast<unsigned char>('i'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('J'),static_cast<unsigned char>('j'),static_cast<unsigned char>('K'),static_cast<unsigned char>('k'),static_cast<unsigned char>('L'),static_cast<unsigned char>('l'),static_cast<unsigned char>('M'),static_cast<unsigned char>('m'),static_cast<unsigned char>('N'),static_cast<unsigned char>('n'),
  static_cast<unsigned char>('O'),static_cast<unsigned char>('o'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('P'),static_cast<unsigned char>('p'),static_cast<unsigned char>('Q'),static_cast<unsigned char>('q'),static_cast<unsigned char>('R'),static_cast<unsigned char>('r'),static_cast<unsigned char>('S'),static_cast<unsigned char>('s'),static_cast<unsigned char>('T'),static_cast<unsigned char>('t'),
  static_cast<unsigned char>('U'),static_cast<unsigned char>('u'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('V'),static_cast<unsigned char>('v'),static_cast<unsigned char>('W'),static_cast<unsigned char>('w'),static_cast<unsigned char>('X'),static_cast<unsigned char>('x'),
  static_cast<unsigned char>('Y'),static_cast<unsigned char>('y'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('Z'),static_cast<unsigned char>('z'),
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x8E, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x9E, 0x00},
// BKHCM1
{static_cast<unsigned char>('A'),static_cast<unsigned char>('a'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('~'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('B'),static_cast<unsigned char>('b'),static_cast<unsigned char>('C'),static_cast<unsigned char>('c'),static_cast<unsigned char>('D'),static_cast<unsigned char>('d'),
  static_cast<unsigned char>('}'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('E'),static_cast<unsigned char>('e'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('F'),static_cast<unsigned char>('f'),static_cast<unsigned char>('G'),static_cast<unsigned char>('g'),static_cast<unsigned char>('H'),static_cast<unsigned char>('h'),
  static_cast<unsigned char>('I'),static_cast<unsigned char>('i'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('J'),static_cast<unsigned char>('j'),static_cast<unsigned char>('K'),static_cast<unsigned char>('k'),static_cast<unsigned char>('L'),static_cast<unsigned char>('l'),static_cast<unsigned char>('M'),static_cast<unsigned char>('m'),static_cast<unsigned char>('N'),static_cast<unsigned char>('n'),
  static_cast<unsigned char>('O'),static_cast<unsigned char>('o'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('P'),static_cast<unsigned char>('p'),static_cast<unsigned char>('Q'),static_cast<unsigned char>('q'),static_cast<unsigned char>('R'),static_cast<unsigned char>('r'),static_cast<unsigned char>('S'),static_cast<unsigned char>('s'),static_cast<unsigned char>('T'),static_cast<unsigned char>('t'),
  static_cast<unsigned char>('U'),static_cast<unsigned char>('u'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('V'),static_cast<unsigned char>('v'),static_cast<unsigned char>('W'),static_cast<unsigned char>('w'),static_cast<unsigned char>('X'),static_cast<unsigned char>('x'),
  static_cast<unsigned char>('Y'),static_cast<unsigned char>('y'),static_cast<unsigned char>('{'),static_cast<unsigned char>('�'),static_cast<unsigned char>('^'),static_cast<unsigned char>('�'),static_cast<unsigned char>('`'),static_cast<unsigned char>('�'),static_cast<unsigned char>('|'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('Z'),static_cast<unsigned char>('z'),
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x8E, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x9E, 0x00},
//Vietware-F
{ static_cast<unsigned char>('A'),static_cast<unsigned char>('a'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('B'),static_cast<unsigned char>('b'),static_cast<unsigned char>('C'),static_cast<unsigned char>('c'),static_cast<unsigned char>('D'),static_cast<unsigned char>('d'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('E'),static_cast<unsigned char>('e'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('F'),static_cast<unsigned char>('f'),static_cast<unsigned char>('G'),static_cast<unsigned char>('g'),static_cast<unsigned char>('H'),static_cast<unsigned char>('h'),
  static_cast<unsigned char>('I'),static_cast<unsigned char>('i'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('J'),static_cast<unsigned char>('j'),static_cast<unsigned char>('K'),static_cast<unsigned char>('k'),static_cast<unsigned char>('L'),static_cast<unsigned char>('l'),static_cast<unsigned char>('M'),static_cast<unsigned char>('m'),static_cast<unsigned char>('N'),static_cast<unsigned char>('n'),
  static_cast<unsigned char>('O'),static_cast<unsigned char>('o'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('P'),static_cast<unsigned char>('p'),static_cast<unsigned char>('Q'),static_cast<unsigned char>('q'),static_cast<unsigned char>('R'),static_cast<unsigned char>('r'),static_cast<unsigned char>('S'),static_cast<unsigned char>('s'),static_cast<unsigned char>('T'),static_cast<unsigned char>('t'),
  static_cast<unsigned char>('U'),static_cast<unsigned char>('u'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('V'),static_cast<unsigned char>('v'),static_cast<unsigned char>('W'),static_cast<unsigned char>('w'),static_cast<unsigned char>('X'),static_cast<unsigned char>('x'),
  static_cast<unsigned char>('Y'),static_cast<unsigned char>('y'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('Z'),static_cast<unsigned char>('z'),
  0x80, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88,
  0x89, 0x8A, 0x8B, 0x8C, 0x8E, 0x91, 0x92, 0x93,
  0x94, 0x95, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x9E, 0x00},
// ISC
 {static_cast<unsigned char>('A'),static_cast<unsigned char>('a'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('B'),static_cast<unsigned char>('b'),static_cast<unsigned char>('C'),static_cast<unsigned char>('c'),static_cast<unsigned char>('D'),static_cast<unsigned char>('d'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('E'),static_cast<unsigned char>('e'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('F'),static_cast<unsigned char>('f'),static_cast<unsigned char>('G'),static_cast<unsigned char>('g'),static_cast<unsigned char>('H'),static_cast<unsigned char>('h'),
  static_cast<unsigned char>('I'),static_cast<unsigned char>('i'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('J'),static_cast<unsigned char>('j'),static_cast<unsigned char>('K'),static_cast<unsigned char>('k'),static_cast<unsigned char>('L'),static_cast<unsigned char>('l'),static_cast<unsigned char>('M'),static_cast<unsigned char>('m'),static_cast<unsigned char>('N'),static_cast<unsigned char>('n'),
  static_cast<unsigned char>('O'),static_cast<unsigned char>('o'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('P'),static_cast<unsigned char>('p'),static_cast<unsigned char>('Q'),static_cast<unsigned char>('q'),static_cast<unsigned char>('R'),static_cast<unsigned char>('r'),static_cast<unsigned char>('S'),static_cast<unsigned char>('s'),static_cast<unsigned char>('T'),static_cast<unsigned char>('t'),
  static_cast<unsigned char>('U'),static_cast<unsigned char>('u'),static_cast<unsigned char>('@'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('|'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('`'),static_cast<unsigned char>('�'),0x5C,static_cast<unsigned char>('�'),static_cast<unsigned char>('^'),static_cast<unsigned char>('�'),static_cast<unsigned char>('~'),static_cast<unsigned char>('�'),static_cast<unsigned char>('#'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('V'),static_cast<unsigned char>('v'),static_cast<unsigned char>('W'),static_cast<unsigned char>('w'),static_cast<unsigned char>('X'),static_cast<unsigned char>('x'),
  static_cast<unsigned char>('Y'),static_cast<unsigned char>('y'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),static_cast<unsigned char>('�'),
  static_cast<unsigned char>('Z'),static_cast<unsigned char>('z'),
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x12, 0x13,
  0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00}
};

UKWORD DoubleByteTables[][TOTAL_VNCHARS] = {
//VNI-WIN
{ 0x0041, 0x0061, 0xd941, 0xf961, 0xd841, 0xf861, 0xdb41, 0xfb61, 0xd541, 0xf561, 0xcf41, 0xef61, //a
  0xc241, 0xe261, 0xc141, 0xe161, 0xc041, 0xe061, 0xc541, 0xe561, 0xc341, 0xe361, 0xc441, 0xe461, //a^
  0xca41, 0xea61, 0xc941, 0xe961, 0xc841, 0xe861, 0xda41, 0xfa61, 0xdc41, 0xfc61, 0xcb41, 0xeb61, //a(
  0x0042, 0x0062, 0x0043, 0x0063, 0x0044, 0x0064, //B b C c D d
  0x00d1, 0x00f1, //DD, dd
  0x0045, 0x0065, 0xd945, 0xf965, 0xd845, 0xf865, 0xdb45, 0xfb65, 0xd545, 0xf565, 0xcf45, 0xef65, //e
  0xc245, 0xe265, 0xc145, 0xe165, 0xc045, 0xe065, 0xc545, 0xe565, 0xc345, 0xe365, 0xc445, 0xe465, //e^
  0x0046, 0x0066, 0x0047, 0x0067, 0x0048, 0x0068, // F f G g H h
  0x0049, 0x0069, 0x00cd, 0x00ed, 0x00cc, 0x00ec, 0x00c6, 0x00e6, 0x00d3, 0x00f3, 0x00d2, 0x00f2, //i
  0x004a, 0x006a, 0x004b, 0x006b, 0x004c, 0x006c, 0x004d, 0x006d, 0x004e, 0x006e,  // J j K k L l M m N n
  0x004f, 0x006f, 0xd94f, 0xf96f, 0xd84f, 0xf86f, 0xdb4f, 0xfb6f, 0xd54f, 0xf56f, 0xcf4f, 0xef6f, //o
  0xc24f, 0xe26f, 0xc14f, 0xe16f, 0xc04f, 0xe06f, 0xc54f, 0xe56f, 0xc34f, 0xe36f, 0xc44f, 0xe46f, //o^
  0x00d4, 0x00f4, 0xd9d4, 0xf9f4, 0xd8d4, 0xf8f4, 0xdbd4, 0xfbf4, 0xd5d4, 0xf5f4, 0xcfd4, 0xeff4, //o+
  0x0050, 0x0070, 0x0051, 0x0071, 0x0052, 0x0072, 0x0053, 0x0073, 0x0054, 0x0074,                 //P p Q q R r S s T t
  0x0055, 0x0075, 0xd955, 0xf975, 0xd855, 0xf875, 0xdb55, 0xfb75, 0xd555, 0xf575, 0xcf55, 0xef75, //u
  0x00d6, 0x00f6, 0xd9d6, 0xf9f6, 0xd8d6, 0xf8f6, 0xdbd6, 0xfbf6, 0xd5d6, 0xf5f6, 0xcfd6, 0xeff6, //u+
  0x0056, 0x0076, 0x0057, 0x0077, 0x0058, 0x0078, // V v W w X x
  0x0059, 0x0079, 0xd959, 0xf979, 0xd859, 0xf879, 0xdb59, 0xfb79, 0xd559, 0xf579, 0x00ce, 0x00ee, //y
  0x005a, 0x007a, // Z z
  0x0080, 0x0082, 0x0083, 0x0084, 0x0085, 0x0086, 0x0087, 0x0088,
  0x0089, 0x008A, 0x008B, 0x008C, 0x008E, 0x0091, 0x0092, 0x0093,
  0x0094, 0x0095, 0x0096, 0x0097, 0x0098, 0x0099, 0x009A, 0x009B,
  0x009C, 0x009E, 0x009F},
//BKHCM2
{ 0x0041, 0x0061, 0xC141, 0xe161, 0xC241, 0xe261, 0xC341, 0xe361, 0xC441, 0xe461, 0xC541, 0xe561, //a
  0x00CA, 0x00EA, 0xCBCA, 0xEBEA, 0xCCCA, 0xECEA, 0xCDCA, 0xEDEA, 0xCECA, 0xEEEA, 0xC5CA, 0xE5EA, //a^
  0x00D9, 0x00F9, 0xC6D9, 0xE6F9, 0xC7D9, 0xE7F9, 0xC8D9, 0xE8F9, 0xC9D9, 0xE9F9, 0xC5D9, 0xE5F9,
  0x0042, 0x0062, 0x0043, 0x0063, 0x0044, 0x0064, //B b C c D d
  0x00C0, 0x00E0,
  0x0045, 0x0065, 0xC145, 0xE165, 0xC245, 0xE265, 0xC345, 0xE365, 0xC445, 0xE465, 0xC545, 0xE565, //e
  0x00CF, 0x00EF, 0xCBCF, 0xEBEF, 0xCCCF, 0xECEF, 0xCDCF, 0xEDEF, 0xCECF, 0xEEEF, 0xE5CF, 0xE5EF, //e^
  0x0046, 0x0066, 0x0047, 0x0067, 0x0048, 0x0068, // F f G g H h
  0x0049, 0x0069, 0x00D1, 0x00F1, 0x00D2, 0x00F2, 0x00D3, 0x00F3, 0x00D4, 0x00F4, 0x00D5, 0x00F5, //i
  0x004a, 0x006a, 0x004b, 0x006b, 0x004c, 0x006c, 0x004d, 0x006d, 0x004e, 0x006e,  // J j K k L l M m N n
  0x004F, 0x006F, 0xC14F, 0xE16F, 0xC24F, 0xE26F, 0xC34F, 0xE36F, 0xC44F, 0xE46F, 0xC54F, 0xE56F, //o
  0x00D6, 0x00F6, 0xCBD6, 0xEBF6, 0xCCD6, 0xECF6, 0xCDD6, 0xEDF6, 0xCED6, 0xEEF6, 0xC5D6, 0xE5F6, //o^
  0x00DA, 0x00FA, 0xC1DA, 0xE1FA, 0xC2DA, 0xE2FA, 0xC3DA, 0xE3FA, 0xC4DA, 0xE4FA, 0xC5DA, 0xE5FA, //o+
  0x0050, 0x0070, 0x0051, 0x0071, 0x0052, 0x0072, 0x0053, 0x0073, 0x0054, 0x0074,    //P p Q q R r S s T t
  0x0055, 0x0075, 0xC155, 0xE175, 0xC255, 0xE275, 0xC355, 0xE375, 0xC455, 0xE475, 0xC555, 0xE575, //u
  0x00DB, 0x00FB, 0xC1DB, 0xE1FB, 0xC2DB, 0xE2FB, 0xC3DB, 0xE3FB, 0xC4DB, 0xE4FB, 0xC5DB, 0xE5FB, //u+
  0x0056, 0x0076, 0x0057, 0x0077, 0x0058, 0x0078, // V v W w X x
  0x0059, 0x0079, 0xC159, 0xE179, 0xC259, 0xE279, 0xC359, 0xE379, 0xC459, 0xE479, 0xC559, 0xE579,
  0x005a, 0x007a,// Z z
  0x0080, 0x0082, 0x0083, 0x0084, 0x0085, 0x0086, 0x0087, 0x0088,
  0x0089, 0x008A, 0x008B, 0x008C, 0x008E, 0x0091, 0x0092, 0x0093,
  0x0094, 0x0095, 0x0096, 0x0097, 0x0098, 0x0099, 0x009A, 0x009B,
  0x009C, 0x009E, 0x009F},
//VIETWARE-X
{ 0x0041, 0x0061, 0xCF41, 0xEF61, 0xCC41, 0xEC61, 0xCD41, 0xED61, 0xCE41, 0xEE61, 0xDB41, 0xFB61, //a
  0x00C1, 0x00E1, 0xDAC1, 0xFAE1, 0xD6C1, 0xF6E1, 0xD8C1, 0xF8E1, 0xD9C1, 0xF9E1, 0xDBC1, 0xFBE1, //a^
  0x00C0, 0x00E0, 0xD5C0, 0xF5E0, 0xD2C0, 0xF2E0, 0xD3C0, 0xF3E0, 0xD4C0, 0xF4E0, 0xDBC0, 0xFBE0, //a(
  0x0042, 0x0062, 0x0043, 0x0063, 0x0044, 0x0064, //B b C c D d
  0x00C2, 0x00E2,
  0x0045, 0x0065, 0xCF45, 0xEF65, 0xCC45, 0xEC65, 0xCD45, 0xED65, 0xCE45, 0xEE65, 0xDB45, 0xFB65, //e
  0x00C3, 0x00E3, 0xDAC3, 0xFAE3, 0xD6C3, 0xF6E3, 0xD8C3, 0xF8E3, 0xD9C3, 0xF9E3, 0xDBC3, 0xFBE3, //e^
  0x0046, 0x0066, 0x0047, 0x0067, 0x0048, 0x0068, // F f G g H h
  0x0049, 0x0069, 0x00CA, 0x00EA, 0x00C7, 0x00E7, 0x00C8, 0x00E8, 0x00C9, 0x00E9, 0x00CB, 0x00EB, //i
  0x004a, 0x006a, 0x004b, 0x006b, 0x004c, 0x006c, 0x004d, 0x006d, 0x004e, 0x006e,  // J j K k L l M m N n
  0x004F, 0x006F, 0xCF4F, 0xEF6F, 0xCC4F, 0xEC6F, 0xCD4F, 0xED6F, 0xCE4F, 0xEE6F, 0xDC4F, 0xFC6F, //o
  0x00C4, 0x00E4, 0xDAC4, 0xFAE4, 0xD6C4, 0xF6E4, 0xD8C4, 0xF8E4, 0xD9C4, 0xF9E4, 0xDCC4, 0xFCE4, //o^
  0x00C5, 0x00E5, 0xCFC5, 0xEFE5, 0xCCC5, 0xECE5, 0xCDC5, 0xEDE5, 0xCEC5, 0xEEE5, 0xDCC5, 0xFCE5, //o+
  0x0050, 0x0070, 0x0051, 0x0071, 0x0052, 0x0072, 0x0053, 0x0073, 0x0054, 0x0074,                 //P p Q q R r S s T t
  0x0055, 0x0075, 0xCF55, 0xEF75, 0xCC55, 0xEC75, 0xCD55, 0xED75, 0xCE55, 0xEE75, 0xDB55, 0xFB75, //u
  0x00C6, 0x00E6, 0xCFC6, 0xEFE6, 0xCCC6, 0xECE6, 0xCDC6, 0xEDE6, 0xCEC6, 0xEEE6, 0xDBC6, 0xFBE6, //u+
  0x0056, 0x0076, 0x0057, 0x0077, 0x0058, 0x0078, // V v W w X x
  0x0059, 0x0079, 0xCF59, 0xEF79, 0xCC59, 0xEC79, 0xCD59, 0xED79, 0xCE59, 0xEE79, 0xD159, 0xF179, //Y
  0x005a, 0x007a,// Z z
  0x0080, 0x0082, 0x0083, 0x0084, 0x0085, 0x0086, 0x0087, 0x0088,
  0x0089, 0x008A, 0x008B, 0x008C, 0x008E, 0x0091, 0x0092, 0x0093,
  0x0094, 0x0095, 0x0096, 0x0097, 0x0098, 0x0099, 0x009A, 0x009B,
  0x009C, 0x009E, 0x009F},
// VNI-MAC
{ 0x0041, 0x0061, 0xf441, 0x9d61, 0xaf41, 0xbf61, 0xf341, 0x9e61, 0xcd41, 0x9b61, 0xec41, 0x9561, //a
  0xe541, 0x8961, 0xe741, 0x8761, 0xcb41, 0x8861, 0x8141, 0x8c61, 0xcc41, 0x8b61, 0x8041, 0x8a61, //a^
  0xe641, 0x9061, 0x8341, 0x8e61, 0xe941, 0x8f61, 0xf241, 0x9c61, 0x8641, 0x9f61, 0xe841, 0x9161, //a(
  0x0042, 0x0062, 0x0043, 0x0063, 0x0044, 0x0064, //B b C c D d
  0x0084, 0x0096, //DD, dd
  0x0045, 0x0065, 0xf445, 0x9d65, 0xaf45, 0xbf65, 0xf345, 0x9e65, 0xcd45, 0x9b65, 0xec45, 0x9565, //e
  0xe545, 0x8965, 0xe745, 0x8765, 0xcb45, 0x8865, 0x8145, 0x8c65, 0xcc45, 0x8b65, 0x8045, 0x8a65, //e^
  0x0046, 0x0066, 0x0047, 0x0067, 0x0048, 0x0068, // F f G g H h
  0x0049, 0x0069, 0x00ea, 0x0092, 0x00ed, 0x0093, 0x00ae, 0x00be, 0x00ee, 0x0097, 0x00f1, 0x0098, //i
  0x004a, 0x006a, 0x004b, 0x006b, 0x004c, 0x006c, 0x004d, 0x006d, 0x004e, 0x006e,  // J j K k L l M m N n
  0x004f, 0x006f, 0xf44f, 0x9d6f, 0xaf4f, 0xbf6f, 0xf34f, 0x9e6f, 0xcd4f, 0x9b6f, 0xec4f, 0x956f, //o
  0xe54f, 0x896f, 0xe74f, 0x876f, 0xcb4f, 0x886f, 0x814f, 0x8c6f, 0xcc4f, 0x8b6f, 0x804f, 0x8a6f, //o^
  0x00ef, 0x0099, 0xf4ef, 0x9d99, 0xafef, 0xbf99, 0xf3ef, 0x9e99, 0xcdef, 0x9b99, 0xecef, 0x9599, //o+
  0x0050, 0x0070, 0x0051, 0x0071, 0x0052, 0x0072, 0x0053, 0x0073, 0x0054, 0x0074,                 //P p Q q R r S s T t
  0x0055, 0x0075, 0xf455, 0x9d75, 0xaf55, 0xbf75, 0xf355, 0x9e75, 0xcd55, 0x9b75, 0xec55, 0x9575, //u
  0x0085, 0x009a, 0xf485, 0x9d9a, 0xaf85, 0xbf9a, 0xf385, 0x9e9a, 0xcd85, 0x9b9a, 0xec85, 0x959a, //u+
  0x0056, 0x0076, 0x0057, 0x0077, 0x0058, 0x0078, // V v W w X x
  0x0059, 0x0079, 0xf459, 0x9d79, 0xaf59, 0xbf79, 0xf359, 0x9e79, 0xcd59, 0x9b79, 0x00eb, 0x0094, //y
  0x005a, 0x007a, // Z z
  0x00db, 0x00e2, 0x00c4, 0x00e3, 0x00c9, 0x00a0, 0x00e0, 0x00f6,
  0x00e4, 0x003f, 0x00dc, 0x00ce, 0x003f, 0x00d4, 0x00d5, 0x00d2,
  0x00d3, 0x00a5, 0x00d0, 0x00d1, 0x00f7, 0x00aa, 0x003f, 0x00dd,
  0x00cf, 0x003f, 0x00d9}
};

UKWORD WinCP1258[TOTAL_VNCHARS]=
//Windows CP 1258
{ 0x0041, 0x0061, 0xec41, 0xec61, 0xcc41, 0xcc61, 0xd241, 0xd261, 0xde41, 0xde61, 0xf241, 0xf261, //a
  0x00c2, 0x00e2, 0xecc2, 0xece2, 0xccc2, 0xcce2, 0xd2c2, 0xd2e2, 0xdec2, 0xdee2, 0xf2c2, 0xf2e2, //a^
  0x00c3, 0x00e3, 0xecc3, 0xece3, 0xccc3, 0xcce3, 0xd2c3, 0xd2e3, 0xdec3, 0xdee3, 0xf2c3, 0xf2e3, //a(
  0x0042, 0x0062, 0x0043, 0x0063, 0x0044, 0x0064, //B b C c D d
  0x00d0, 0x00f0, //DD, dd
  0x0045, 0x0065, 0xec45, 0xec65, 0xcc45, 0xcc65, 0xd245, 0xd265, 0xde45, 0xde65, 0xf245, 0xf265, //e
  0x00ca, 0x00ea, 0xecca, 0xecea, 0xccca, 0xccea, 0xd2ca, 0xd2ea, 0xdeca, 0xdeea, 0xf2ca, 0xf2ea, //e^
  0x0046, 0x0066, 0x0047, 0x0067, 0x0048, 0x0068, // F f G g H h
  0x0049, 0x0069, 0xec49, 0xec69, 0xcc49, 0xcc69, 0xd249, 0xd269, 0xde49, 0xde69, 0xf249, 0xf269, //i
  0x004a, 0x006a, 0x004b, 0x006b, 0x004c, 0x006c, 0x004d, 0x006d, 0x004e, 0x006e,  // J j K k L l M m N n
  0x004f, 0x006f, 0xec4f, 0xec6f, 0xcc4f, 0xcc6f, 0xd24f, 0xd26f, 0xde4f, 0xde6f, 0xf24f, 0xf26f, //o
  0x00d4, 0x00f4, 0xecd4, 0xecf4, 0xccd4, 0xccf4, 0xd2d4, 0xd2f4, 0xded4, 0xdef4, 0xf2d4, 0xf2f4, //o^
  0x00d5, 0x00f5, 0xecd5, 0xecf5, 0xccd5, 0xccf5, 0xd2d5, 0xd2f5, 0xded5, 0xdef5, 0xf2d5, 0xf2f5, //o+
  0x0050, 0x0070, 0x0051, 0x0071, 0x0052, 0x0072, 0x0053, 0x0073, 0x0054, 0x0074,                 //P p Q q R r S s T t
  0x0055, 0x0075, 0xec55, 0xec75, 0xcc55, 0xcc75, 0xd255, 0xd275, 0xde55, 0xde75, 0xf255, 0xf275, //u
  0x00dd, 0x00fd, 0xecdd, 0xecfd, 0xccdd, 0xccfd, 0xd2dd, 0xd2fd, 0xdedd, 0xdefd, 0xf2dd, 0xf2fd, //u+
  0x0056, 0x0076, 0x0057, 0x0077, 0x0058, 0x0078, // V v W w X x
  0x0059, 0x0079, 0xec59, 0xec79, 0xcc59, 0xcc79, 0xd259, 0xd279, 0xde59, 0xde79, 0xf259, 0xf279, //y
  0x005a, 0x007a, // Z z
  0x0080, 0x0082, 0x0083, 0x0084, 0x0085, 0x0086, 0x0087, 0x0088,
  0x0089, 0x008A, 0x008B, 0x008C, 0x008E, 0x0091, 0x0092, 0x0093,
  0x0094, 0x0095, 0x0096, 0x0097, 0x0098, 0x0099, 0x009A, 0x009B,
  0x009C, 0x009E, 0x009F};

UKWORD WinCP1258Pre[TOTAL_VNCHARS]=
//Windows CP1258 - with some more precomposed characters
{ 0x0041, 0x0061, 0x00c1, 0x00e1, 0x00c0, 0x00e0, 0xd241, 0xd261, 0xde41, 0xde61, 0xf241, 0xf261, //a
  0x00c2, 0x00e2, 0xecc2, 0xece2, 0xccc2, 0xcce2, 0xd2c2, 0xd2e2, 0xdec2, 0xdee2, 0xf2c2, 0xf2e2, //a^
  0x00c3, 0x00e3, 0xecc3, 0xece3, 0xccc3, 0xcce3, 0xd2c3, 0xd2e3, 0xdec3, 0xdee3, 0xf2c3, 0xf2e3, //a(
  0x0042, 0x0062, 0x0043, 0x0063, 0x0044, 0x0064, //B b C c D d
  0x00d0, 0x00f0, //DD, dd
  0x0045, 0x0065, 0x00c9, 0x00e9, 0x00c8, 0x00e8, 0xd245, 0xd265, 0xde45, 0xde65, 0xf245, 0xf265, //e
  0x00ca, 0x00ea, 0xecca, 0xecea, 0xccca, 0xccea, 0xd2ca, 0xd2ea, 0xdeca, 0xdeea, 0xf2ca, 0xf2ea, //e^
  0x0046, 0x0066, 0x0047, 0x0067, 0x0048, 0x0068, // F f G g H h
  0x0049, 0x0069, 0x00cd, 0x00ed, 0xcc49, 0xcc69, 0xd249, 0xd269, 0xde49, 0xde69, 0xf249, 0xf269, //i
  0x004a, 0x006a, 0x004b, 0x006b, 0x004c, 0x006c, 0x004d, 0x006d, 0x004e, 0x006e,  // J j K k L l M m N n
  0x004f, 0x006f, 0x00d3, 0x00f3, 0xcc4f, 0xcc6f, 0xd24f, 0xd26f, 0xde4f, 0xde6f, 0xf24f, 0xf26f, //o
  0x00d4, 0x00f4, 0xecd4, 0xecf4, 0xccd4, 0xccf4, 0xd2d4, 0xd2f4, 0xded4, 0xdef4, 0xf2d4, 0xf2f4, //o^
  0x00d5, 0x00f5, 0xecd5, 0xecf5, 0xccd5, 0xccf5, 0xd2d5, 0xd2f5, 0xded5, 0xdef5, 0xf2d5, 0xf2f5, //o+
  0x0050, 0x0070, 0x0051, 0x0071, 0x0052, 0x0072, 0x0053, 0x0073, 0x0054, 0x0074,                 //P p Q q R r S s T t
  0x0055, 0x0075, 0x00da, 0x00fa, 0x00d9, 0x00f9, 0xd255, 0xd275, 0xde55, 0xde75, 0xf255, 0xf275, //u
  0x00dd, 0x00fd, 0xecdd, 0xecfd, 0xccdd, 0xccfd, 0xd2dd, 0xd2fd, 0xdedd, 0xdefd, 0xf2dd, 0xf2fd, //u+
  0x0056, 0x0076, 0x0057, 0x0077, 0x0058, 0x0078, // V v W w X x
  0x0059, 0x0079, 0xec59, 0xec79, 0xcc59, 0xcc79, 0xd259, 0xd279, 0xde59, 0xde79, 0xf259, 0xf279, //y
  0x005a, 0x007a, // Z z
  0x0080, 0x0082, 0x0083, 0x0084, 0x0085, 0x0086, 0x0087, 0x0088,
  0x0089, 0x008A, 0x008B, 0x008C, 0x008E, 0x0091, 0x0092, 0x0093,
  0x0094, 0x0095, 0x0096, 0x0097, 0x0098, 0x0099, 0x009A, 0x009B,
  0x009C, 0x009E, 0x009F};

UnicodeChar UnicodeTable[TOTAL_VNCHARS] =
	{0x0041, 0x0061, 0x00c1, 0x00e1, 0x00c0, 0x00e0, 0x1ea2, 0x1ea3, 0x00c3, 0x00e3, 0x1ea0, 0x1ea1, //a
     0x00c2, 0x00e2, 0x1ea4, 0x1ea5, 0x1ea6, 0x1ea7, 0x1ea8, 0x1ea9, 0x1eaa, 0x1eab, 0x1eac, 0x1ead, //a^
	 0x0102, 0x0103, 0x1eae, 0x1eaf, 0x1eb0, 0x1eb1, 0x1eb2, 0x1eb3, 0x1eb4, 0x1eb5, 0x1eb6, 0x1eb7, //a(
     0x0042, 0x0062, 0x0043, 0x0063, 0x0044, 0x0064,                                                 //B b C c D d
     0x0110, 0x0111,                                                                                 // DD, dd
	 0x0045, 0x0065, 0x00c9, 0x00e9, 0x00c8, 0x00e8, 0x1eba, 0x1ebb, 0x1ebc, 0x1ebd, 0x1eb8, 0x1eb9, //e
	 0x00ca, 0x00ea, 0x1ebe, 0x1ebf, 0x1ec0, 0x1ec1, 0x1ec2, 0x1ec3, 0x1ec4, 0x1ec5, 0x1ec6, 0x1ec7, //e^
     0x0046, 0x0066, 0x0047, 0x0067, 0x0048, 0x0068,                                                 // F f G g H h
	 0x0049, 0x0069, 0x00cd, 0x00ed, 0x00cc, 0x00ec, 0x1ec8, 0x1ec9, 0x0128, 0x0129, 0x1eca, 0x1ecb, //i
     0x004a, 0x006a, 0x004b, 0x006b, 0x004c, 0x006c, 0x004d, 0x006d, 0x004e, 0x006e,                 // J j K k L l M m N n
	 0x004f, 0x006f, 0x00d3, 0x00f3, 0x00d2, 0x00f2, 0x1ece, 0x1ecf, 0x00d5, 0x00f5, 0x1ecc, 0x1ecd, //o
     0x00d4, 0x00f4, 0x1ed0, 0x1ed1, 0x1ed2, 0x1ed3, 0x1ed4, 0x1ed5, 0x1ed6, 0x1ed7, 0x1ed8, 0x1ed9, //o^
	 0x01a0, 0x01a1, 0x1eda, 0x1edb, 0x1edc, 0x1edd, 0x1ede, 0x1edf, 0x1ee0, 0x1ee1, 0x1ee2, 0x1ee3, //o+
	 0x0050, 0x0070, 0x0051, 0x0071, 0x0052, 0x0072, 0x0053, 0x0073, 0x0054, 0x0074,                 //P p Q q R r S s T t
	 0x0055, 0x0075, 0x00da, 0x00fa, 0x00d9, 0x00f9, 0x1ee6, 0x1ee7, 0x0168, 0x0169, 0x1ee4, 0x1ee5, //u
	 0x01af, 0x01b0, 0x1ee8, 0x1ee9, 0x1eea, 0x1eeb, 0x1eec, 0x1eed, 0x1eee, 0x1eef, 0x1ef0, 0x1ef1, //u+
     0x0056, 0x0076, 0x0057, 0x0077, 0x0058, 0x0078,                                                 // V v W w X x
     0x0059, 0x0079, 0x00dd, 0x00fd, 0x1ef2, 0x1ef3, 0x1ef6, 0x1ef7, 0x1ef8, 0x1ef9, 0x1ef4, 0x1ef5, //y
     0x005a, 0x007a,                                                                                // Z z
// Symbols that have different code points in Unicode and Western charsets
	 0x20AC, 0x20A1, 0x0192, 0x201E, 0x2026, 0x2020, 0x2021, 0x02C6,
	 0x2030, 0x0160, 0x2039, 0x0152, 0x017D, 0x2018, 0x2019, 0x201C,
	 0x201D, 0x2022, 0x2013, 0x2014, 0x02DC, 0x2122, 0x0161, 0x203A,
	 0x0153, 0x017E, 0x0178};

/*
unsigned char WesternSymbols[] =
	{0x80, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88,
	 0x89, 0x8A, 0x8B, 0x8C, 0x8E, 0x91, 0x92, 0x93,
	 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B,
	 0x9C, 0x9E, 0x9F};
*/

/*
' 0x27
` 0x60
? 0x3f
~ 0x7e
. 0x2e

^ 0x5e
( 0x28
+ 0x2b

*/
UKDWORD VIQRTable[TOTAL_VNCHARS] =
	{  0x41,   0x61,   0x2741,   0x2761,   0x6041,   0x6061,   0x3f41,   0x3f61,   0x7e41,   0x7e61,   0x2e41,   0x2e61, //a
	 0x5e41, 0x5e61, 0x275e41, 0x275e61, 0x605e41, 0x605e61, 0x3f5e41, 0x3f5e61, 0x7e5e41, 0x7e5e61, 0x2e5e41, 0x2e5e61, //a^
	 0x2841, 0x2861, 0x272841, 0x272861, 0x602841, 0x602861, 0x3f2841, 0x3f2861, 0x7e2841, 0x7e2861, 0x2e2841, 0x2e2861, //a(
       0x42,   0x62,     0x43,     0x63,     0x44,     0x64,                                                 //B b C c D d
	 0x4444, 0x6464,                                                                                 // DD, dd
	   0x45,   0x65,   0x2745,   0x2765,   0x6045,   0x6065,   0x3f45,   0x3f65,   0x7e45,   0x7e65,   0x2e45,   0x2e65, //e
	 0x5e45, 0x5e65, 0x275e45, 0x275e65, 0x605e45, 0x605e65, 0x3f5e45, 0x3f5e65, 0x7e5e45, 0x7e5e65, 0x2e5e45, 0x2e5e65, //e^
       0x46,   0x66,     0x47,     0x67,     0x48,     0x68,                                                 // F f G g H h
	   0x49,   0x69,   0x2749,   0x2769,   0x6049,   0x6069,   0x3f49,   0x3f69,   0x7e49,   0x7e69,   0x2e49,   0x2e69, //i
       0x4a,   0x6a,     0x4b,     0x6b,     0x4c,     0x6c,     0x4d,     0x6d,     0x4e,     0x6e,                     // J j K k L l M m N n
	   0x4f,   0x6f,   0x274f,   0x276f,   0x604f,   0x606f,   0x3f4f,   0x3f6f,   0x7e4f,   0x7e6f,   0x2e4f,   0x2e6f, //o
	 0x5e4f, 0x5e6f, 0x275e4f, 0x275e6f, 0x605e4f, 0x605e6f, 0x3f5e4f, 0x3f5e6f, 0x7e5e4f, 0x7e5e6f, 0x2e5e4f, 0x2e5e6f, //o^
	 0x2b4f, 0x2b6f, 0x272b4f, 0x272b6f, 0x602b4f, 0x602b6f, 0x3f2b4f, 0x3f2b6f, 0x7e2b4f, 0x7e2b6f, 0x2e2b4f, 0x2e2b6f, //o+
	   0x50,   0x70,     0x51,     0x71,     0x52,     0x72,     0x53,     0x73,     0x54,     0x74,                     //P p Q q R r S s T t
       0x55,   0x75,   0x2755,   0x2775,   0x6055,   0x6075,   0x3f55,   0x3f75,   0x7e55,   0x7e75,   0x2e55,   0x2e75, //u
	 0x2b55, 0x2b75, 0x272b55, 0x272b75, 0x602b55, 0x602b75, 0x3f2b55, 0x3f2b75, 0x7e2b55, 0x7e2b75, 0x2e2b55, 0x2e2b75, //u+
       0x56,   0x76,     0x57,     0x77,     0x58,     0x78,                                                 // V v W w X x
	   0x59,   0x79,   0x2759,   0x2779,   0x6059,   0x6079,   0x3f59,   0x3f79,   0x7e59,   0x7e79,   0x2e59,   0x2e79,
       0x5a,   0x7a,                                                                                // Z z
	   0x80, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88,
	   0x89, 0x8A, 0x8B, 0x8C, 0x8E, 0x91, 0x92, 0x93,
	   0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B,
	   0x9C, 0x9E, 0x9F};


UKDWORD UnicodeComposite[TOTAL_VNCHARS] =
{ 0x00000041, 0x00000061, 0x03010041, 0x03010061, 0x03000041, 0x03000061, //a
  0x03090041, 0x03090061, 0x03030041, 0x03030061, 0x03230041, 0x03230061, //a

  0x000000c2, 0x000000e2, 0x030100c2, 0x030100e2, 0x030000c2, 0x030000e2,
  0x030900c2, 0x030900e2, 0x030300c2, 0x030300e2, 0x032300c2, 0x032300e2, //a^

  0x00000102, 0x00000103, 0x03010102, 0x03010103, 0x03000102, 0x03000103,
  0x03090102, 0x03090103, 0x03030102, 0x03030103, 0x03230102, 0x03230103, //a(

  0x0042, 0x0062, 0x0043, 0x0063, 0x0044, 0x0064, //B b C c D d
  0x0110, 0x0111, //0x00d1, 0x00f1, //DD, dd

  0x00000045, 0x00000065, 0x03010045, 0x03010065, 0x03000045, 0x03000065,
  0x03090045, 0x03090065, 0x03030045, 0x03030065, 0x03230045, 0x03230065, //e

  0x000000ca, 0x000000ea, 0x030100ca, 0x030100ea, 0x030000ca, 0x030000ea,
  0x030900ca, 0x030900ea, 0x030300ca, 0x030300ea, 0x032300ca, 0x032300ea, //e^

  0x0046, 0x0066, 0x0047, 0x0067, 0x0048, 0x0068, // F f G g H h

  0x00000049, 0x00000069, 0x03010049, 0x03010069, 0x03000049, 0x03000069,
  0x03090049, 0x03090069, 0x03030049, 0x03030069, 0x03230049, 0x03230069, //i

  0x004a, 0x006a, 0x004b, 0x006b, 0x004c, 0x006c, 0x004d, 0x006d, 0x004e, 0x006e,  // J j K k L l M m N n

  0x0000004f, 0x0000006f, 0x0301004f, 0x0301006f, 0x0300004f, 0x0300006f,
  0x0309004f, 0x0309006f, 0x0303004f, 0x0303006f, 0x0323004f, 0x0323006f, //o

  0x000000d4, 0x000000f4, 0x030100d4, 0x030100f4, 0x030000d4, 0x030000f4,
  0x030900d4, 0x030900f4, 0x030300d4, 0x030300f4, 0x032300d4, 0x032300f4, //o^

  0x000001a0, 0x000001a1, 0x030101a0, 0x030101a1, 0x030001a0, 0x030001a1,
  0x030901a0, 0x030901a1, 0x030301a0, 0x030301a1, 0x032301a0, 0x032301a1, //o+

  0x0050, 0x0070, 0x0051, 0x0071, 0x0052, 0x0072, 0x0053, 0x0073, 0x0054, 0x0074,                 //P p Q q R r S s T t

  0x00000055, 0x00000075, 0x03010055, 0x03010075, 0x03000055, 0x03000075,
  0x03090055, 0x03090075, 0x03030055, 0x03030075, 0x03230055, 0x03230075, //u

  0x000001af, 0x000001b0, 0x030101af, 0x030101b0, 0x030001af, 0x030001b0,
  0x030901af, 0x030901b0, 0x030301af, 0x030301b0, 0x032301af, 0x032301b0, //u+

  0x0056, 0x0076, 0x0057, 0x0077, 0x0058, 0x0078, // V v W w X x

  0x00000059, 0x00000079, 0x03010059, 0x03010079, 0x03000059, 0x03000079,
  0x03090059, 0x03090079, 0x03030059, 0x03030079, 0x03230059, 0x03230079, //y
  0x005a, 0x007a, // Z z
// Symbols that have different code points in Unicode and Western charsets
  0x20AC, 0x20A1, 0x0192, 0x201E, 0x2026, 0x2020, 0x2021, 0x02C6,
  0x2030, 0x0160, 0x2039, 0x0152, 0x017D, 0x2018, 0x2019, 0x201C,
  0x201D, 0x2022, 0x2013, 0x2014, 0x02DC, 0x2122, 0x0161, 0x203A,
  0x0153, 0x017E, 0x0178};

int StdVnRootChar[TOTAL_VNCHARS] = {
  0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, //a [A=0]
  0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, //a^ -> a
  0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, //a( -> a
  36, 37, 38, 39, 40, 41, // bcd [D=40, d=41]
  40, 41,                 // DD dd [mapped to D, d]
  44, 45, 44, 45, 44, 45, 44, 45, 44, 45, 44, 45, // 3: e [E = 44]
  44, 45, 44, 45, 44, 45, 44, 45, 44, 45, 44, 45, // 4: e^ -> e
  68, 69, 70, 71, 72, 73, // fgh
  74, 75, 74, 75, 74, 75, 74, 75, 74, 75, 74, 75, // 5: i
  86, 87, 88, 89, 90, 91, 92, 93, 94, 95,  //jklmn
  96, 97, 96, 97, 96, 97, 96, 97, 96, 97, 96, 97, // 6: o [o=96]
  96, 97, 96, 97, 96, 97, 96, 97, 96, 97, 96, 97, // 7: o^ -> o
  96, 97, 96, 97, 96, 97, 96, 97, 96, 97, 96, 97, // 8: o+ -> o
  132, 133, 134, 135, 136, 137, 138, 139, 140, 141, // pqrst
  142, 143, 142, 143, 142, 143, 142, 143, 142, 143, 142, 143, // 9: u [U=142]
  142, 143, 142, 143, 142, 143, 142, 143, 142, 143, 142, 143, //10: u+ -> u
  166, 167, 168, 169, 170, 171, //vwx
  172, 173, 172, 173, 172, 173, 172, 173, 172, 173, 172, 173, //11: y [Y=172]
  184, 185, // z
  186, 187, 188, 189, 190, 191, 192, 193,
  194, 195, 196, 197, 198, 199, 200, 201,
  202, 203, 204, 205, 206, 207, 208, 209,
  210, 211, 212
};

int StdVnNoTone[TOTAL_VNCHARS] = {
  0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, //a [A=0]
  12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, //a^
  24, 25, 24, 25, 24, 25, 24, 25, 24, 25, 24, 25, //a(
  36, 37, 38, 39, 40, 41, // bcd [D=40, d=41]
  42, 43,                 // DD dd
  44, 45, 44, 45, 44, 45, 44, 45, 44, 45, 44, 45, // 3: e [E = 44]
  56, 57, 56, 57, 56, 57, 56, 57, 56, 57, 56, 57, // 4: e^
  68, 69, 70, 71, 72, 73, // fgh
  74, 75, 74, 75, 74, 75, 74, 75, 74, 75, 74, 75, // 5: i
  86, 87, 88, 89, 90, 91, 92, 93, 94, 95,  //jklmn
  96, 97, 96, 97, 96, 97, 96, 97, 96, 97, 96, 97, // 6: o [o=96]
  108, 109, 108, 109, 108, 109, 108, 109, 108, 109, 108, 109, // 7: o^
  120, 121, 120, 121, 120, 121, 120, 121, 120, 121, 120, 121, // 8: o+
  132, 133, 134, 135, 136, 137, 138, 139, 140, 141, // pqrst
  142, 143, 142, 143, 142, 143, 142, 143, 142, 143, 142, 143, // 9: u [U=142]
  154, 155, 154, 155, 154, 155, 154, 155, 154, 155, 154, 155, //10: u+
  166, 167, 168, 169, 170, 171, //vwx
  172, 173, 172, 173, 172, 173, 172, 173, 172, 173, 172, 173, //11: y [Y=172]
  184, 185, // z
  186, 187, 188, 189, 190, 191, 192, 193,
  194, 195, 196, 197, 198, 199, 200, 201,
  202, 203, 204, 205, 206, 207, 208, 209,
  210, 211, 212
};
