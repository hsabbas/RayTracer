#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

#include "vec3.h"
#include "ray.h"
#include "color.h"

class camera {
public:
	point3 center;
	double aspect_ratio;
	int image_width;

	camera() : center(point3(0, 0, 0)) {}
	camera(point3 center, double aspect_ratio, int image_width) 
		: center(center), aspect_ratio(aspect_ratio), image_width(image_width) {}

	void render() {
		initialize();

		std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
		for (int row = 0; row < image_height; row++) {
			for (int col = 0; col < image_width; col++) {
				point3 pixel_center = pixel00loc + delta_v * row + delta_u * col;
				vec3 ray_dir = pixel_center - center;
				ray r(center, ray_dir);
				color ray_color = find_ray_color(r);
				ray_color.print_color(std::cout);
			}
		}
	}

private:
	double focal_length;
	int image_height;
	double viewport_width;
	double viewport_height;
	point3 pixel00loc;
	vec3 viewport_v;
	vec3 viewport_u;
	vec3 delta_v;
	vec3 delta_u;

	void initialize() {
		focal_length = 1.0;
		image_height = image_width / aspect_ratio;
		
		viewport_height = 2.0;
		viewport_width = viewport_height * double(image_width / image_height);
		viewport_v = vec3(0, -viewport_height, 0);
		viewport_u = vec3(viewport_width, 0, 0);

		delta_v = viewport_v / image_height;
		delta_u = viewport_u / image_width;

		point3 viewport_top_left = center + vec3(0, 0, -focal_length) - 0.5 * viewport_u - 0.5 * viewport_v;
		pixel00loc = viewport_top_left + 0.5 * delta_v + 0.5 * delta_u;
	}

	color find_ray_color(const ray& r) {
		color light_blue(0.2, 0.2, 1.0);
		color dark_blue(0.0, 0.0, 0.2);
		vec3 unit_direction = to_unit_vec(r.direction);
		double a = 0.5 * (unit_direction.y + 1.0);
		return (1 - a) * dark_blue + a * light_blue;
	}
};

#endif // !CAMERA_H
