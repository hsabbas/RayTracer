#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

#include "sphere.h"
#include "hittable_list.h"
#include "raytracer.h"

class camera {
public:
	double aspect_ratio;
	int image_width;

	camera() : center(point3(0, 0, 0)) {}
	camera(point3 center, double aspect_ratio, int image_width) 
		: center(center), aspect_ratio(aspect_ratio), image_width(image_width) {}

	void render(const hittable_list& objects) {
		initialize();

		std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
		for (int row = 0; row < image_height; row++) {
			for (int col = 0; col < image_width; col++) {
				point3 pixel_center = pixel00loc + delta_v * row + delta_u * col;
				vec3 ray_dir = pixel_center - center;
				ray r(center, ray_dir);
				color ray_color = find_ray_color(r, objects);
				ray_color.print_color(std::cout);
			}
		}
	}

private:
	int samples_per_pixel = 10;
	double focal_length;
	int image_height;
	double viewport_width;
	double viewport_height;
	point3 center;
	point3 pixel00loc;
	vec3 viewport_v;
	vec3 viewport_u;
	vec3 delta_v;
	vec3 delta_u;

	void initialize() {
		focal_length = 1.0;
		image_height = image_width / aspect_ratio;
		image_height = image_height < 1 ? 1 : image_height;
		
		viewport_height = 2.0;
		viewport_width = viewport_height * double(image_width) / image_height;
		viewport_v = vec3(0, -viewport_height, 0);
		viewport_u = vec3(viewport_width, 0, 0);

		delta_v = viewport_v / image_height;
		delta_u = viewport_u / image_width;

		point3 viewport_top_left = center + vec3(0, 0, -focal_length) - 0.5 * viewport_u - 0.5 * viewport_v;
		pixel00loc = viewport_top_left + 0.5 * delta_v + 0.5 * delta_u;
	}

	color find_ray_color(const ray& r, const hittable_list& objects) {
		hit_record rec;
		if (objects.hit(r, 0, infinity, rec)) {
			vec3 unit_normal = to_unit_vec(rec.n);
			return color(unit_normal.x, unit_normal.y, unit_normal.z);
		}
		color light_blue(0.2, 0.2, 1.0);
		color dark_blue(0.0, 0.0, 0.2);
		vec3 unit_direction = to_unit_vec(r.direction);
		double a = 0.5 * (unit_direction.y + 1.0);
		return (1 - a) * dark_blue + a * light_blue;
	}
};

#endif // !CAMERA_H

