#ifndef HITTABLE_H
#define HITTABLE_H

class hittable {
public:
	virtual bool hit(const ray& r) = 0;
};

#endif
