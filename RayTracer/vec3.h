#ifndef VEC3_H
#define VEC3_H

#include <cmath>

class vec3 {
public:
	double x, y, z;
	vec3(){}
	vec3(double x, double y, double z) : x(x), y(y), z(z) {}

	double length() const {
		return std::sqrt(length_squared());
	}

	double length_squared() const {
		return x*x + y*y + z*z;
	}

};

using point3 = vec3;

inline vec3 operator+(const vec3& v, const vec3& u) {
	return vec3(v.x + u.x, v.y + u.y, v.z + u.z);
}

inline vec3 operator-(const vec3& v, const vec3& u) {
	return vec3(v.x - u.x, v.y - u.y, v.z - u.z);
}

inline vec3 operator*(const vec3& v, double t) {
	return vec3(v.x * t, v.y * t, v.z * t);
}

inline vec3 operator*(double t, const vec3& v) {
	return vec3(v.x * t, v.y * t, v.z * t);
}

inline vec3 operator/(const vec3& v, double t) {
	return v * (1 / t);
}

inline vec3 operator-(const vec3& v) {
	return vec3(-v.x, -v.y, -v.z);
}

inline vec3 to_unit_vec(const vec3& v) {
	return v / v.length();
}

inline double dot(const vec3& v, const vec3& u) {
	return v.x * u.x + v.y * u.y + v.z * u.z;
}

#endif // !VEC3_H

