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

#include <cmath>

#include "util.h"
#include "constants.h"

namespace Protracer {
  
  float
  Util::shade_factor(const Vector& l0, const Vector& ri, const Vector& rn)
  {
    Vector t1 = Vector_add(ri, Vector_multiply(EPS, rn)); 
    Vector t2 = Vector_normalize(Vector_subtract(l0, t1));

    return std::fabs(Vector_dotProduct(rn, t2));
  }
}
