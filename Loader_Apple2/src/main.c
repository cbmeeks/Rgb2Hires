/* Rgb2Hires
* Copyright (C) 2016 Christophe Meneboeuf <christophe@xtof.info>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

/* Standard headers */
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
/* My headers */
#include "file_io.h"

#define HIRES_PAGE1     0x2000
#define HIRES_PAGE_SIZE 0x2000
#define SWITCH_GRAPHICS *((uint8_t*)0xC050)=1
#define SWITCH_FULLSCREEN *((uint8_t*)0xC052)=1
#define SWITCH_PAGE1 *((uint8_t*)0xC054)=1
#define SWITCH_HIRES *((uint8_t*)0xC057)=1

void __fastcall__ error(const uint8_t err) {
  printf("\n ERROR: %u", err);
  exit(-1);
}


static char Filename[64] = "test.picture";
int main( int argc, char* argv[] )
{
  uint8_t handle;
  (void)argc;
  (void)argv;

  file_open(Filename, &handle);
  if( file_read( handle, (uint8_t*)HIRES_PAGE1, HIRES_PAGE_SIZE ) != HIRES_PAGE_SIZE )  {
    error(file_error());
  }
  file_close(handle);

  SWITCH_GRAPHICS;
  SWITCH_FULLSCREEN;
  SWITCH_PAGE1;
  SWITCH_HIRES;

  return 0;
}
