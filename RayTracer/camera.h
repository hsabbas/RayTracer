#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

#include "sphere.h"
#include "hittable_list.h"
#include "raytracer.h"
#include "hittable.h"

class camera {
public:
	int samples_per_pixel = 10;
	double aspect_ratio;
	int image_width;
	int background = 0;

	camera() : center(point3(0, 0, 0)) {}
	camera(point3 center, double aspect_ratio, int image_width) 
		: center(center), aspect_ratio(aspect_ratio), image_width(image_width) {}

	void render(const hittable_list& objects) {
		initialize();

		std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
		for (int row = 0; row < image_height; row++) {
			for (int col = 0; col < image_width; col++) {
				color ray_color;
				for (int sample = 0; sample < samples_per_pixel; sample++) {
					ray r = get_ray(row, col);
					ray_color += find_ray_color(r, 0, objects);
				}
				ray_color /= samples_per_pixel;
				ray_color.print_color(std::cout);
			}
		}
	}

private:
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
	int max_depth;

	void initialize() {
		max_depth = 40;

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

	ray get_ray(int row, int col) {
		double offset_row = row + (random_double() - 0.5);
		double offset_col = col + (random_double() - 0.5);
		point3 pixel_center = pixel00loc + delta_v * offset_row + delta_u * offset_col;
		vec3 ray_dir = pixel_center - center;
		ray r(center, ray_dir);
		return r;
	}

	ray find_scattered_ray(const hit_record& rec) {
		return ray(rec.p, random_unit_vector() + rec.n);
	}

	color find_ray_color(const ray& r, int depth, const hittable_list& objects) {
		if (depth == max_depth) {
			return color(0, 0, 0);
		}

		hit_record rec;
		if (objects.hit(r, interval(0.001, infinity), rec)) {
			ray bounce = find_scattered_ray(rec);
			return 0.5 * find_ray_color(bounce, depth + 1, objects);
		}
		color top_color(1.0, 1.0, 1.0);
		color bottom_color(1.0, 1.0, 1.0);
		if (background == 0) {
			top_color = color(0.5, 0.7, 1.0);
			bottom_color = color(1.0, 1.0, 1.0);
		}
		else if (background == 1) {
			top_color = color(0.2, 0.2, 1.0);
			bottom_color = color(0.0, 0.0, 0.2);
		}
		vec3 unit_direction = to_unit_vec(r.direction);
		double a = 0.5 * (unit_direction.y + 1.0);
		return (1 - a) * bottom_color + a * top_color;
	}
};

#endif // !CAMERA_H

