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

#include "finish.h"

namespace Protracer {

  const float Finish::DEFAULT_REFLECTION = 0.0f;
  const float Finish::DEFAULT_DIFFUSION = 1.0f;

  Finish::Finish(float diffusion, float reflection)
  {
    this->diffusion = diffusion;
    this->reflection = reflection;
  }

  void
  Finish::set_diffusion(float diffusion)
  {
    this->diffusion = diffusion;
  }

  void
  Finish::set_reflection(float reflection)
  {
    this->reflection = reflection;
  }

}
