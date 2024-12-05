#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "ray.h"
#include "vec3.h"

class sphere : hittable {
public:
	point3 center;
	double radius;

	bool hit(const ray& r, hit_record& rec) {
		vec3 oc = center - r.start;
		double a = r.direction.length_squared();
		double h = dot(r.direction, oc);
		double c = oc.length_squared() - radius * radius;
		double discriminant = h * h - a * c;
		if (discriminant < 0) {
			return false;
		}

		double t = (h - std::sqrt(discriminant)) / a;
		rec.t = t;
		rec.p = r.at(t);
		rec.n = rec.p - center;
	}
};

#endif // !SPHERE_H

