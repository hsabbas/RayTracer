#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <vector>
#include <memory>
#include "hittable.h"
#include "ray.h"
#include "interval.h"

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

	bool hit(const ray& r, interval t_int, hit_record& rec) const override{
		bool hit_obj = false;

		hit_record temp;
		double closest = t_int.max;
		for (const auto& object : objects) {
			if (object->hit(r, interval(t_int.min, closest), temp)) {
				hit_obj = true;
				closest = temp.t;
				rec = temp;
			}
		}
		return hit_obj;
	}
};


#endif // !HITTABLE_LIST_H

