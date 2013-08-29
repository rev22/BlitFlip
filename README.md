blitflip
========

Fast sprite rendering routine that supports horizontal and vertical flipping

Usage

````c
    BlitFlip(
        SDL_Surface*src,
        SDL_Surface*dst,
        int x,
        int y,
        int flip_h, /* Flip left/right */
        int flip_v, /* Flip top/bottom */
        int true_alpha /* Use true alpha blending */
        )
````

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
