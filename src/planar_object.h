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

#ifndef PLANAR_OBJECT_H
#define PLANAR_OBJECT_H

#include "object.h"
#include "plane.h"

#include <iostream>

namespace Protracer {

  class PlanarObject : public Object {
  protected:
    PlanarObject(const Vector& normal, const Vector& point,
		 Pigment* pigment, const Finish& finish) :
      Object(pigment, finish), span_plane(normal, point, pigment, finish) {

      std::cerr << "normal: (" << normal.get_x() << "," << normal.get_y() <<
	"," << normal.get_z() << ")" << std::endl;
      std::cerr << "point: (" << point.get_x() << "," << point.get_y() <<
	"," << point.get_z() << ")" << std::endl;

    }
    ~PlanarObject() { pigment = 0; }

    Plane span_plane;
  };

}

#endif //PLANAR_OBJECT_H