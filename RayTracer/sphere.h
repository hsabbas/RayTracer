#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "ray.h"
#include "vec3.h"

class sphere : hittable {
public:
	point3 center;
	double radius;

	bool hit(const ray& r) {
		vec3 oc = center - r.start;
		double a = r.direction.length_squared();
		double h = dot(r.direction, oc);
		double c = oc.length_squared() - radius * radius;
		return h * h - a * c >= 0;
	}
};

#endif // !SPHERE_H

