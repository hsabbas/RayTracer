#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"

class sphere : public hittable {
public:
	sphere(const point3& center, double radius) : center(center), radius(radius) {}
	bool hit(const ray& r, interval t_int, hit_record& rec) const override {
		vec3 oc = center - r.start;
		double a = r.direction.length_squared();
		double h = dot(r.direction, oc);
		double c = oc.length_squared() - radius * radius;
		double discriminant = h * h - a * c;
		if (discriminant < 0) {
			return false;
		}

		double t = (h - std::sqrt(discriminant)) / a;
		if (!t_int.contains(t)) {
			t = (h + std::sqrt(discriminant)) / a;
			if (!t_int.contains(t)) {
				return false;
			}
		}

		rec.t = t;
		rec.p = r.at(t);
		vec3 outward_normal = (rec.p - center) / radius;
		rec.set_front_normal(r, outward_normal);
		return true;
	}

private:
	point3 center;
	double radius;
};

#endif // !SPHERE_H

