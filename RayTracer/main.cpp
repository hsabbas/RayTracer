#include <iostream>

#include "camera.h"

int main() {
	camera cam(point3(0, 0, 0), 16.0/9.0, 400);
	cam.render();
}