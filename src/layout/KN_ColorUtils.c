#include "KN_ColorUtils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

KN_Color HSLAToRGBA(double h, double s, double l, double a) {
	KN_Color color = {0};
	
	double c = (1.0 - fabs(2.0 * l - 1.0)) * s;
	double h_prime = h / 60.0;
	double x = c * (1 - fabs(fmod(h_prime, 2.0) - 1));
	double m = l - c / 2.0;

  
  switch ((int)floor(h_prime)) {
		case 0:
			color.r = c + m;
			color.g = x + m;
			color.b = 0 + m;
			break;
		case 1:
			color.r = x + m;
			color.g = c + m;
			color.b = 0 + m;
			break;
		case 2:
			color.r = 0 + m;
			color.g = c + m;
			color.b = x + m;
			break;
		case 3:
			color.r = 0 + m;
			color.g = x + m;
			color.b = c + m;
			break;
		case 4:
			color.r = x + m;
			color.g = 0 + m;
			color.b = c + m;
			break;
		case 5:
			color.r = c + m;
			color.g = 0 + m;
			color.b = x + m;
			break;
		default:
			fprintf(stderr, "the fuck?\n");
			exit(1);
	}

	color.a = a;

	return color;
}
