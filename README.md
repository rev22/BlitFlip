blitflip
========

Fast sprite rendering routine that supports horizontal and vertical flipping.  It uses the SDL library but can be adapted to other environments.

Usage:

````c
    BlitFlip(
        SDL_Surface*src,
        SDL_Surface*dst,
        int x,
        int y,
        int flip_h, /* Flip left/right */
        int flip_v, /* Flip top/bottom */
        int true_alpha /* Use true alpha blending */
        );
````

Before using bitflip, please make sure that both source and destinations images are SDL_Lock'ed; the sprite may be partly or fully offscreen.

You source surface must be 32 bit RGBA, with 0xff000000 as the alpha bit-mask.
The destination surface must be 32 bit RGB, with the same color component ordering as the source image.


Author and Licensing
--------------------

Copyright © 2013 Michele Bini <michele.bini@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 of the GNU General Public License
as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
