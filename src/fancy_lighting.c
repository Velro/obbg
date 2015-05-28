#include "stb.h"//data types for obbg_data and obbg_func are defined in here
#include "obbg_data.h"
#include "obbg_funcs.h"
#include "stb_voxel_render.h"
#include "vector_math.h"

static char* fancy_lighting = {
	"\n" //Point light implementation based on http://www.lighthouse3d.com/tutorials/glsl-tutorial/spot-light-per-pixel/
	"struct spotlightData{\n"
	"    vec3 position;\n"
	"    vec3 dir;\n"
	"    float cosCutoff;\n"//aperture of cone
	"    float spotExponent;\n"//falloff from center
	"    float constantAttenuation;\n"//depth
	"    float linearAttenuation;\n"//depth
	"    float quadraticAttenuation;\n"//depth
	"};\n"

	//TODO find a better way to pass this data, or if there's a way to cast an array to struct?
	"uniform float spotlight[11];\n"//11 == sizeof(spotlight)
	"uniform vec3 pointlight[2];\n"
	"\n"
	"vec3 compute_lighting(vec3 pos, vec3 norm, vec3 albedo, vec3 ambient)\n"
	"{\n"
	"    spotlightData light;\n"
	"    vec3 n,halfV;\n"
	"    float NdotL,NdotHV;\n"
	"    vec3 color = albedo * ambient;\n"
	"    float att,spotEffect;\n"
	"    n = normalize(norm);\n"
	//ugliness ahead
	"    light.position.x = spotlight[0];\n"
	"    light.position.y = spotlight[1];\n"
	"    light.position.z = spotlight[2];\n"
	"    light.dir.x = spotlight[3];\n"
	"    light.dir.y = spotlight[4];\n"
	"    light.dir.z = spotlight[5];\n"
	"    light.cosCutoff = spotlight[6];\n"
	"    light.spotExponent = spotlight[7];\n"
	"    light.constantAttenuation = spotlight[8];\n"
	"    light.linearAttenuation = spotlight[9];\n"
	"    light.quadraticAttenuation = spotlight[10];\n"
	"\n"
	"    vec3 dirToSource = vec3(light.position - pos);\n"
	"    float distToSource = length(dirToSource);\n"
	"    NdotL = max(dot(n,normalize(dirToSource)),0.0);\n"
	"    if (NdotL > 0.0){\n"
	"       spotEffect = dot(normalize(light.dir), normalize(-dirToSource));\n"
	"       if (spotEffect > light.cosCutoff){\n"
	"           spotEffect = pow(spotEffect, light.spotExponent);\n"
	"   	     att = spotEffect / (light.constantAttenuation +\n"
	"	 		     light.linearAttenuation * distToSource +\n"
	"	 		     light.quadraticAttenuation * distToSource * distToSource);\n"
	"    		 color += att * (albedo * NdotL);\n"
	"       }\n"
	"    }\n"//end of (NdotL > 0.0)
	"\n"
	"\n//point light"
	"\n"
	"   vec3 light_dir = pointlight[0] - pos;\n"
	"   float lambert = dot(light_dir, norm) / dot(light_dir, light_dir);\n"
	"   vec3 diffuse = clamp(pointlight[1] * clamp(lambert, 0.0, 1.0), 0.0, 1.0);\n"
	"   color += (diffuse + ambient) * albedo;\n"
	"   return color;\n"
	"}\n"//end of function
};

char *get_fancy_lighting_function(void)
{
   return (char *) fancy_lighting;
}
