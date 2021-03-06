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

#include "triangle.h"

#include <algorithm>

namespace Protracer {

  Triangle::Triangle(const Vector& c0, const Vector& c1, const Vector& c2) 
    : va(c1 - c0), vb(c2 - c0),
      PlanarObject(Vector((c1 - c0) * (c2 - c0)).normal(), c0)
  {
    t0 = c0;
    aa = va.dot(va);
    bb = vb.dot(vb);
    ab = va.dot(vb);
  }


  Triangle*
  Triangle::copy() const
  {
    Triangle* triangle = new Triangle(t0, va + t0, vb + t0); 

    triangle->copy_modifications(this);
    return triangle;
  }

  HitCalculation
  Triangle::calculate_hit(const Ray& ray) const
  {
    return std::get<0>(calculate_hit_with_coords(ray));
  }

  std::tuple<HitCalculation, float, float>
  Triangle::calculate_hit_with_coords(const Ray& ray) const
  {
    HitCalculation hc = span_plane.calculate_hit(ray);

    if (hc.is_hit()) {
      Vector ri = ray.get_origin() + hc.get_distance() * ray.get_direction(); 
      Vector q = ri - t0;

      float u = (bb * q.dot(va) - ab * q.dot(vb)) / (aa * bb - ab * ab);
      
      if (0 < u && u < 1) {
	float v = (q.dot(vb) - u * ab) / bb;
	
	if (0 < v && v < 1 && u + v <= 1) {
          const Pigment& pigment = get_pigment();
	  if (!pigment.is_uniform()) {
	    hc.set_color(pigment.get_color(u, v));
          }

	  return std::make_tuple(hc, u, v);
	}
      }
    }

    return std::make_tuple(HitCalculation(false), 0, 0);
  }

  void
  Triangle::translate(const Vector& v)
  {
    t0 += v;
    span_plane.translate(v);
  }

  void
  Triangle::rotate(const Vector& rot)
  {
    t0 = t0.rotate(rot);
    va = va.rotate(rot);
    vb = vb.rotate(rot);
    // note: we don't need to recalculate the dot products since
    // a . a = length(a) ^ 2
    // a . b = length(a) * length(b) * cos(phi), where phi is the angle b/w
    // those vectors, and angle and length is unaffected by rotation
    span_plane.rotate(rot);
  }

  Vector
  Triangle::get_max_extent() const
  {
    float x0 = t0.get_x();
    float y0 = t0.get_y();
    float z0 = t0.get_z();
    float x1 = x0 + va.get_x();
    float y1 = y0 + va.get_y();
    float z1 = z0 + va.get_z();
    float x2 = x0 + vb.get_x();
    float y2 = y0 + vb.get_y();
    float z2 = z0 + vb.get_z();

    return Vector(std::max(x0, std::max(x1, x2)),
                  std::max(y0, std::max(y1, y2)),
                  std::max(z0, std::max(z1, z2)));
  }

  Vector
  Triangle::get_min_extent() const
  {
    float x0 = t0.get_x();
    float y0 = t0.get_y();
    float z0 = t0.get_z();
    float x1 = x0 + va.get_x();
    float y1 = y0 + va.get_y();
    float z1 = z0 + va.get_z();
    float x2 = x0 + vb.get_x();
    float y2 = y0 + vb.get_y();
    float z2 = z0 + vb.get_z();

    return Vector(std::min(x0, std::min(x1, x2)),
                  std::min(y0, std::min(y1, y2)),
                  std::min(z0, std::min(z1, z2)));
  }

}
