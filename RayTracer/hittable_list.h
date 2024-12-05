#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <vector>
#include <memory>
#include "hittable.h"
#include "ray.h"

class hittable_list : hittable {
public:
	std::vector<std::shared_ptr<hittable>> objects;
	hittable_list(){}
	hittable_list(std::shared_ptr<hittable> object) {
		objects.push_back(object);
	}

	void add(std::shared_ptr<hittable> object) {
		objects.push_back(object);
	}

	bool hit(const ray& r, double tmin, double tmax, hit_record& rec) const override{
		bool hit_obj = false;

		hit_record temp;
		double closest = tmax;
		for (const auto& object : objects) {
			if (object->hit(r, tmin, closest, temp)) {
				hit_obj = true;
				closest = temp.t;
				rec = temp;
			}
		}
		return hit_obj;
	}
};


#endif // !HITTABLE_LIST_H

