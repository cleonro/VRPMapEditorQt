//#include "stdafx.h"
#include "math_utils.h"

// Very fast sqrt
float SQRT(float number)
{
	long i;
	float x, y;
	const float threehalfs = 1.5f;

	x = number * 0.5f;
	y  = number;
	i  = * ( long * ) &y;
	i  = 0x5F3759DF - ( i >> 1 );
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x * y * y ) );
	y  = y * ( threehalfs - ( x * y * y ) );
	return number * y;	
}

//Very fast 1/sqrt
float RSQRT(float number)
{
	long i;
	float x, y;
	const float threehalfs = 1.5f;

	x = number * 0.5f;
	y  = number;
	i  = * ( long * ) &y;					// evil floating point bit level hacking
	i  = 0x5F3759DF - ( i >> 1 );			// what the fuck?
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x * y * y ) ); // 1st iteration
	y  = y * ( threehalfs - ( x * y * y ) ); // 2nd iteration, this can be removed
	return y;
}