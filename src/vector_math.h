#ifndef INCLUDE_VECTOR_MATH
#define INCLUDE_VECTOR_MATH

#include <math.h>
#include <assert.h>
// this file should probably be replaced with some 3rd party lib thats
// assembly optimized and everything

//this should probably be defined in a more general file
#define rad2deg 57.2957795
//this should probably be defined in a more general file
#define PI 3.14159265

//would be nice to be able to initialize as
//vec3f example = {1, 2};
//not sure if that is possible
typedef union
{
	
	struct {
		float x, y, z;
	};
	float E[3];
} vec3f;

// TODO(casey): Consider v2 A = v2{5, 3}; ?
//inline vec3f
vec3f Vec3f(float x, float y, float z);

float vec3f_length(vec3f a);
float vec3f_dot_product(vec3f a, vec3f b);
vec3f vec3f_normalize(vec3f a);
vec3f vec3f_cross_product(vec3f a, vec3f b);


vec3f vec3f_clamp(vec3f a);//@TODO implement this!
float vec3f_angle(vec3f a, vec3f b);//@TODO implement this!
#endif