#include"factory.h"

int main() {
	Train train;
	Plane plane;
	plane.engine();
	plane.tyre();
	train.engine();
	train.tyre();
	return 0;
}