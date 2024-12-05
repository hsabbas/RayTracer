#ifndef COLOR_H
#define COLOR_H

#include "interval.h"

class color {
public:
	double r, g, b;
	color(){}
	color(double r, double g, double b) : r(r), g(g), b(b) {}

	void print_color(std::ostream& out) {
		const interval intensity(0.0, 0.999);
		int r_byte = int(256 * intensity.clamp(r));
		int g_byte = int(256 * intensity.clamp(g));
		int b_byte = int(256 * intensity.clamp(b));
		out << r_byte << ' ' << g_byte << ' ' << b_byte << '\n';
	}

	color& operator+=(const color& other) {
		r += other.r;
		g += other.g;
		b += other.b;
		return *this;
	}

	color& operator/=(double x) {
		r /= x;
		g /= x;
		b /= x;
		return *this;
	}
};

inline color operator+(const color& left_color, const color& right_color) {
	return color(left_color.r + right_color.r, left_color.g + right_color.g, left_color.b + right_color.b);
}

inline color operator*(double t, const color& c) {
	return color(c.r * t, c.g * t, c.b * t);
}

#endif
