#ifndef HITTABLE_H
#define HITTABLE_H

class hit_record {
public:
	point3 p;
	vec3 n;
	double t;
};

class hittable {
public:
	virtual bool hit(const ray& r, hit_record& rec) = 0;
};

#endif
