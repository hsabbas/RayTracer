#include <iostream>

int main() {
	int image_width = 255;
	int image_height = 255;
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
	for (int row = 0; row < image_height; row++) {
		for (int col = 0; col < image_width; col++) {
			int r = row;
			int g = col;
			int b = 0;
			std::cout << r << ' ' << g << ' ' << b << '\n';
		}
	}
}