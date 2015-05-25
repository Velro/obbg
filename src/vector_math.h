#ifndef INCLUDE_STB_VOXEL_RENDER_H
#define INCLUDE_STB_VOXEL_RENDER_H

#include <math.h>
#include <assert.h>
// this file should probably be replaced with some 3rd party lib thats
// assembly optimized and everything

//this should probably be defined in a more general file
#define rad2deg 57.2957795
//this should probably be defined in a more general file
#define PI 3.14159265

//this should probably be defined in a more general file
//TODO try Casey's union v2 on episode 042-ish so we can do array initialization and access
//might not be possible in C ?
typedef struct
{
	float x, y, z;
} vec3f;

typedef struct
{
	float x, y, z, w;
} vec4f;

//
//
//

float vec3f_length(vec3f a)
{
	float result;
	result = sqrt(a.x * a.x + a.y * a.y * a.z * a.z);
	return result;
}

float length(vec4f a)
{
	return 0;
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

//@TODO implement these
/*
vec3f vec3f_clamp(vec3f a)
{

}

vec3f vec3f_length(vec3f a)
{

}

float vec3f_angle(vec3f a, vec3f b)
{

}
*/

#endif