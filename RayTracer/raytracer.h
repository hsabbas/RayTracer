#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "hittable.h"
#include <limits>
#include <memory>
#include <cstdlib>

const double infinity = std::numeric_limits<double>::infinity();

inline double random_double() {
	return std::rand() / (RAND_MAX + 1.0);
}

inline double random_double(int min, int max) {
	return random_double() * (max - min) + min;
}

#endif // !RAYTRACER_H
