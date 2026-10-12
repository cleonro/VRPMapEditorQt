#include "math_utils.h"
#include <cmath>

float SQRT(float number)
{
    return std::sqrt(number);
}

float RSQRT(float number)
{
    return 1.0f / std::sqrt(number);
}
