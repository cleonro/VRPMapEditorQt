#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

#define piover2		 1.5707963267948966f
#define piover3		 1.0471975511965977f
#define piover4		 0.7853981633974483f
#define piover6		 0.5235987755982988f
#define piover12	 0.2617993877991490f
#define piover180	 0.0174532925199432f
#define _180overpi	57.2957795130823208f

#define deg2rad(x)	((x) * piover180)
#define rad2deg(x)	((x) * _180overpi)

//Very fast sqrt
float SQRT(float number);

//Very fast 1/sqrt
float RSQRT(float number);