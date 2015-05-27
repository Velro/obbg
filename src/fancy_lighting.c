#include "stb.h"//data types for obbg_data and obbg_func are defined in here
#include "obbg_data.h"
#include "obbg_funcs.h"
#include "stb_voxel_render.h"
#include "vector_math.h"



//TODO point light struct containing position, direction, aperture angle, cutoff
static char* fancy_lighting = {
	"\n" //Point light implementation based on http://www.lighthouse3d.com/tutorials/glsl-tutorial/spot-light-per-pixel/
	"struct spotlight{\n"
	"    vec3 position;\n"
	"    vec3 dir;\n"
	"    float cosCutoff;\n"//aperture of cone
	"    float spotExponent;\n"//falloff from center
	"    float constantAttenuation;\n"//depth
	"    float linearAttenuation;\n"//depth
	"    float quadraticAttenuation;\n"//depth
	"};\n"

	"int spotlightCount = 1;\n"
	//TODO find a better way to pass this data, or if there's a way to cast an array to struct?
	"uniform float spotlights[11];\n"//can't pass array of structs ... http://pyopengl.sourceforge.net/context/tutorials/shader_7.html

	"\n"
	"vec3 compute_lighting(vec3 pos, vec3 norm, vec3 albedo, vec3 ambient)\n"
	"{\n"
	"    spotlight light;\n"
	"    vec3 n,halfV;\n"
	"    float NdotL,NdotHV;\n"
	"    vec3 color = albedo * ambient;\n"
	"    float att,spotEffect;\n"
	"    n = normalize(norm);\n"
	"    for (int i = 0; i < spotlightCount; i++){\n"
	//ugliness ahead
	"        light.position.x = spotlights[0];\n"
	"        light.position.y = spotlights[1];\n"
	"        light.position.z = spotlights[2];\n"
	"        light.dir.x = spotlights[3];\n"
	"        light.dir.y = spotlights[4];\n"
	"        light.dir.z = spotlights[5];\n"
	"        light.cosCutoff = spotlights[6];\n"
	"        light.spotExponent = spotlights[7];\n"
	"        light.constantAttenuation = spotlights[8];\n"
	"        light.linearAttenuation = spotlights[9];\n"
	"        light.quadraticAttenuation = spotlights[10];\n"
	"\n"
	"        vec3 dirToSource = vec3(light.position - pos);\n"
	"        float distToSource = length(dirToSource);\n"
	"        NdotL = max(dot(n,normalize(dirToSource)),0.0);\n"
	"        if (NdotL > 0.0){\n"
	"            spotEffect = dot(normalize(light.dir), normalize(-dirToSource));\n"
	"            if (spotEffect > light.cosCutoff){\n"
	"                spotEffect = pow(spotEffect, light.spotExponent);\n"
	"	   	 	     att = spotEffect / (light.constantAttenuation +\n"
	"		 		     light.linearAttenuation * distToSource +\n"
	"		 		     light.quadraticAttenuation * distToSource * distToSource);\n"
	"				 color += att * (albedo * NdotL);\n"
	"          }\n"
	"       }\n"//end of (NdotL > 0.0)
	"   }\n"//end of for
	"   return color;\n"
	"}\n"//end of function
};

char *get_fancy_lighting_function(void)
{
   return (char *) fancy_lighting;
}
