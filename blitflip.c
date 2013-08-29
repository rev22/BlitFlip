/* Copyright (c) 2013 Michele Bini
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the version 3 of the GNU General Public License
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#define BLITFLIP_BLEND(o, v, alpha) ((((v - o)*alpha)>>8) + o)

void BlitFlip(
	      SDL_Surface*src,
	      SDL_Surface*dst,
	      int x,
	      int y,
	      int flip_h, /* Flip left/right */
	      int flip_w, /* Flip top/bottom */
	      int full_alpha /* Use true alpha blending */
	      ) {
  if (!tex->adapted) adapt_texture(tex);

  unsigned int sw = src->w;
  unsigned int sh = src->h;
  unsigned int w = dst->w;
  unsigned int h = dst->h;

  int y0, yM, yL;
  if (Sy < 0) {
    y0 = -Sy;
    Sy = 0;
  } else {
    y0 = 0;
  }
  yL = sh - Sy;
  {
    int yL1 = h - y0;
    if (yL < yL1) {
      yM = y0 + yL;
    } else {
      yM = h;
      yL = yL1;
    }
  }
  if (yL <= 0) return;

  int x0, xM, xL;
  if (Sx < 0) {
    x0 = -Sx;
    Sx = 0;
  } else {
    x0 = 0;
  }
  xL = sw - Sx;
  {
    int xL1 = w - x0;
    if (xL < xL1) {
      xM = x0 + xL;
    } else {
      xM = w;
      xL = xL1;
    }
  }
  if (xL <= 0) return;
  
  Uint32 *dS = src->pixels;
  unsigned int sp = src->pitch;
  Uint32 *dD = dst->pixels;

  int xP;
  int yP;

  sp /= sizeof(Uint32);

  if (full_alpha) {
    if (flip_v) {
      if (flip_h) {
	for (yP = yM - 1; yP >= y0; yP--, Sy++) {
	  for (xP = xM - 1; xP >= x0; xP--, Sx++) {
	    Uint32 si = Sy*sp + Sx;
	    Uint32 v = dD[yP*w+xP];
	    Uint32 o = dS[si];
	    Uint8 alpha = v>>24;
	    dS[si] =
	      BLITFLIP_BLEND((o&0xff), (v&0xff), alpha) |
	      BLITFLIP_BLEND(((o>>8)&0xff), ((v>>8)&0xff), alpha) << 8 |
	      BLITFLIP_BLEND(((o>>16)&0xff), ((v>>16)&0xff), alpha) << 16;
	  }
	  Sx -= xL;
	}
      } else {
	for (yP = yM - 1; yP >= y0; yP--, Sy++) {
	  for (xP = x0; xP < xM; xP++, Sx++) {
	    Uint32 si = Sy*sp + Sx;
	    Uint32 v = dD[yP*w+xP];
	    Uint32 o = dS[si];
	    Uint8 alpha = v>>24;
	    dS[si] =
	      BLITFLIP_BLEND((o&0xff), (v&0xff), alpha) |
	      BLITFLIP_BLEND(((o>>8)&0xff), ((v>>8)&0xff), alpha)<<8 |
	      BLITFLIP_BLEND(((o>>16)&0xff), ((v>>16)&0xff), alpha) << 16;
	  }
	  Sx -= xL;
	}
      }
    } else {
      if (flip_h) {
	for (yP = y0; yP < yM; yP++, Sy++) {
	  for (xP = xM - 1; xP >= x0; xP--, Sx++) {
	    Uint32 si = Sy*sp + Sx;
	    Uint32 v = dD[yP*w+xP];
	    Uint32 o = dS[si];
	    Uint8 alpha = v>>24;
	    dS[si] =
	      BLITFLIP_BLEND((o&0xff), (v&0xff), alpha) |
	      BLITFLIP_BLEND(((o>>8)&0xff), ((v>>8)&0xff), alpha)<<8 |
	      BLITFLIP_BLEND(((o>>16)&0xff), ((v>>16)&0xff), alpha) << 16;
	  }
	  Sx -= xL;
	}
      } else {
	for (yP = y0; yP < yM; yP++, Sy++) {
	  for (xP = x0; xP < xM; xP++, Sx++) {
	    Uint32 si = Sy*sp + Sx;
	    Uint32 v = dD[yP*w+xP];
	    Uint32 o = dS[si];
	    Uint8 alpha = v>>24;
	    dS[si] =
	      BLITFLIP_BLEND((o&0xff), (v&0xff), alpha) |
	      BLITFLIP_BLEND(((o>>8)&0xff), ((v>>8)&0xff), alpha)<<8 |
	      BLITFLIP_BLEND(((o>>16)&0xff), ((v>>16)&0xff), alpha) << 16;
	  }
	  Sx -= xL;
	}
      }
    }
  } else {
    if (flip_v) {
      if (flip_h) {
	for (yP = yM - 1; yP >= y0; yP--, Sy++) {
	  for (xP = xM - 1; xP >= x0; xP--, Sx++) {
	    Uint32 v = dD[yP*w+xP];
	    if (v&0xff000000) {
	      dS[Sy*sp + Sx] = v&0xffffff;
	    }
	  }
	  Sx -= xL;
	}
      } else {
	for (yP = yM - 1; yP >= y0; yP--, Sy++) {
	  for (xP = x0; xP < xM; xP++, Sx++) {
	    Uint32 v = dD[yP*w+xP];
	    if (v&0xff000000) {
	      dS[Sy*sp + Sx] = v&0xffffff;
	    }
	  }
	  Sx -= xL;
	}
      }
    } else {
      if (flip_h) {
	for (yP = y0; yP < yM; yP++, Sy++) {
	  for (xP = xM - 1; xP >= x0; xP--, Sx++) {
	    Uint32 v = dD[yP*w + xP];
	    if (v&0xff000000) {
	      dS[Sy*sp + Sx] = v&0xffffff;
	    }
	  }
	  Sx -= xL;
	}
      } else {
	for (yP = y0; yP < yM; yP++, Sy++) {
	  for (xP = x0; xP < xM; xP++, Sx++) {
	    Uint32 v = dD[yP*w + xP];
	    if (v&0xff000000) {
	      dS[Sy*sp + Sx] = v&0xffffff;
	    }
	  }
	  Sx -= xL;
	}
      }
    }
  }
}
