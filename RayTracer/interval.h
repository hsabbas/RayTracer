#ifndef INTERVAL_H
#define INTERVAL_H

class interval {
public:
	double min, max;
	interval() : min(0.0), max(1.0) {}
	interval(double min, double max) : min(min), max(max) {}

	bool contains(double x) const {
		return min <= x && x <= max;
	}

	double clamp(double x) const {
		if (x > max) {
			return max;
		}
		if (x < min) {
			return min;
		}
		return x;
	}
};

#endif

