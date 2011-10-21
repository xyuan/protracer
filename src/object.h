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

#ifndef OBJECT_H
#define OBJECT_H

#include "finish.h"
#include "pigment.h"
#include "hit_calculation.h"
#include "ray.h"

namespace Protracer {
  class Object {
  public:
    Object(Pigment* pigment, const Finish& finish) :
      pigment(pigment), finish(finish) {}

    virtual ~Object() { delete pigment; }

    virtual HitCalculation calculate_hit(const Ray& ray) const = 0;
    const Finish& get_finish() const { return finish; }
    const Pigment& get_pigment() const { return *pigment; }

  protected:
    Finish finish;
    Pigment* pigment;
  };
}

#endif //OBJECT_H
