#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class hit_record {
public:
	point3 p;
	vec3 n;
	double t;
	bool front_face;

	void set_front_normal(const ray& r, const vec3& outward_normal) {
		front_face = dot(r.direction, outward_normal) < 0;
		n = front_face ? outward_normal : -outward_normal;
	}
};

class hittable {
public:
	virtual bool hit(const ray& r, double tmin, double tmax, hit_record& rec) const = 0;
};

#endif
