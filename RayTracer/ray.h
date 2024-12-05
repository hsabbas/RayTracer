#ifndef RAY_H
#define RAY_H

class ray {
public:
	point3 start;
	vec3 direction;
	ray(const point3& start, const vec3& direction) : start(start), direction(direction) {}
	point3 at(double t) const {
		return start + t * direction;
	}
};

#endif
