#include <iostream>

#include "camera.h"

int main() {
	hittable_list objects;
	objects.add(std::make_shared<sphere>(point3(0, 0, -1), 0.5));
	objects.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100));

	camera cam(point3(0, 0, 0), 16.0/9.0, 400);
	cam.render(objects);
}