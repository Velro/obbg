#include "vector_math.h"

vec3f Vec3f(float x, float y, float z)
{
	vec3f result;

	result.x = x;
	result.y = y;
	result.z = z;
	return(result);
}

float vec3f_length(vec3f a)
{
	float result;
	result = sqrt(a.x * a.x + a.y * a.y * a.z * a.z);
	return result;
}

float vec3f_dot_product(vec3f a, vec3f b)
{
	float result;
	result =
		(a.x * b.x) +
		(a.y * b.y) +
		(a.z * b.z);

	return result;
}

vec3f vec3f_normalize(vec3f a)
{
	vec3f result;
	float l = vec3f_length(a);
	result.x = a.x / l;
	result.y = a.y / l;
	result.z = a.z / l;

	return result;
}

vec3f vec3f_cross_product(vec3f a, vec3f b)
{
	vec3f result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;

	return result;
}