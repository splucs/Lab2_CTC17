#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-9

inline double sumsqr(double dx, double dy) {
	return exp(-dx*dx-dy*dy);
}

double f(double x, double y) {
	return 4*sumsqr(x, y) + sumsqr(x-5, y-5) + sumsqr(x-5, y+5) + sumsqr(x+5, y-5) + sumsqr(x+5, y+5);
}

double dx(double x, double y) {
	return -8*x*sumsqr(x, y) - 2*(x-5)*sumsqr(x-5, y-5) - 2*(x-5)*sumsqr(x-5, y+5) - 2*(x+5)*sumsqr(x+5, y-5) - 2*(x+5)*sumsqr(x+5, y+5);
}

double dy(double x, double y) {
	return -8*y*sumsqr(x, y) - 2*(y-5)*sumsqr(x-5, y-5) - 2*(y+5)*sumsqr(x-5, y+5) - 2*(y-5)*sumsqr(x+5, y-5) - 2*(y+5)*sumsqr(x+5, y+5);
}

void gradientDescent(double x0, double y0, double alpha, int nIter) {
	int it = 0;
	for(it=0; it<nIter; it++){
		double gx = dx(x0, y0);
		double gy = dy(x0, y0);
		x0 += alpha*gx;
		y0 += alpha*gy;
		//printf("(x,y) = (%.6f,%.6f), (dx,dy) = (%.6f,%.6f)\n", x0, y0, gx, gy);
	}
	printf("alpha = %.6f, iterations = %d, max found = (%.6f,%.6f)\n", alpha, it, x0, y0);
}

int main() {
	/*for(double x=-5; x<=5; x += 1) {
		for(double y=-5; y<=5; y += 1) {
			printf("%.3f ", f(x, y));
		}
		printf("\n");
	}
	gradientDescent(rand()%10 - 5, rand()%10 - 5, 1e-1, 10000);*/
	
	for(int nTest = 1; nTest <= 20; nTest++) {
		double x = rand()%(nTest*2) - nTest;
		double y = rand()%(nTest*2) - nTest;
		printf("initial point = (%.6f,%.6f)\n", x, y);
		for(double alpha = 1e-4; alpha <= 1; alpha *= 10) {
			gradientDescent(x, y, alpha, 100000);
		}
	}
	return 0;
}