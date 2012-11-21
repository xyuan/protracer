/* -*- mode: C++; indent-tabs-mode: nil; c-basic-offset: 2  -*- */
/*
 * This file is part of Protracer
 *
 * Protracer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Protracer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Protracer.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "bitmap.h"

#include <Magick++/Image.h>

namespace Protracer {
  Bitmap::Bitmap(const std::string& path)
  {
    Magick::Image image(path);

    width = image.columns();
    height = image.rows();
    pixels = new Color[width * height];

    for (int x = 0 ; x < width ; x++) {
      for (int y = 0 ; y < height ; y++) {
        pixels[x + y * width] = Color(image.pixelColor(x, y));
      }
    }
  }

  Bitmap::Bitmap(unsigned int width, unsigned int height)
  {
    this->width = width;
    this->height = height;
    this->pixels = new Color[width * height];
  }

  Bitmap::~Bitmap()
  {
    delete [] pixels;
  }

}
