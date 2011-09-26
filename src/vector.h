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

#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

namespace Protracer {
  class Vector {
  public:
    Vector() : x(0), y(0), z(0) {}
    Vector(float x, float y, float z) : x(x), y(y), z(z) {}

    float get_x() const { return x; }
    float get_y() const { return y; }
    float get_z() const { return z; }    

    Vector& operator=(const Vector& u);

    float dot(const Vector& u) const { return x * u.x + y * u.y + z * u.z; }
    Vector operator*(const Vector& u) const;
    Vector operator-() const;
    Vector operator+(const Vector& u) const;
    Vector operator-(const Vector& u) const;
    Vector operator*(float s) const;

    float length() const { return sqrt(x * x + y * y + z * z); }
    Vector normal() const;
    
  private:
    float x;
    float y;
    float z;
  };

  Vector operator*(float s, const Vector& v);
}

#endif //VECTOR_H
