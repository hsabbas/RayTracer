#ifndef COLOR_H
#define COLOR_H

class color {
public:
	double r, g, b;
	color(){}
	color(double r, double g, double b) : r(r), g(g), b(b) {}

	void print_color(std::ostream& out) {
		int r_byte = 255.999 * r;
		int g_byte = 255.999 * g;
		int b_byte = 255.999 * b;
		out << r_byte << ' ' << g_byte << ' ' << b_byte << '\n';
	}
};

inline color operator+(const color& left_color, const color& right_color) {
	return color(left_color.r + right_color.r, left_color.g + right_color.g, left_color.b + right_color.b);
}

inline color operator*(double t, const color& c) {
	return color(c.r * t, c.g * t, c.b * t);
}

#endif
