#include "stb.h"//data types for obbg_data and obbg_func are defined in here
#include "obbg_data.h"
#include "obbg_funcs.h"
#include "stb_voxel_render.h"



//TODO point light struct containing position, direction, aperture angle, cutoff
static char* fancy_lighting = {
"\n" //Point light implementation based on http://www.lighthouse3d.com/tutorials/glsl-tutorial/spot-light-per-pixel/
"struct spotlight{\n"
"    vec3 position;\n"
"};\n"

"float spotlightCount = 2;\n"
"uniform vec3 light_source[2];\n"
"uniform float light_source_cosCutOff = 0.85f;\n"//aperture of light, between 0 and 1
"uniform vec3 light_source_spotDir = vec3(0.0,1.0,0.0);\n"//hardcoded for now, pull this from struct
"uniform float light_source_spotExponent = 1.0f;\n"//decay from center of cone to edges, larger the value the faster the decay
"uniform float light_source_constantAttenuation = 0.0;\n"//different depth decays, larger the faster the dieoff
"uniform float light_source_linearAttenuation = 0.1;\n"//different depth decays, larger the faster the dieoff
"uniform float light_source_quadraticAttenuation = 0.1;\n"//different depth decays, larger the faster the dieoff

"\n"
"vec3 compute_lighting(vec3 pos, vec3 norm, vec3 albedo, vec3 ambient)\n"
"{\n"

"   vec3 n,halfV;\n"
"   float NdotL,NdotHV;\n"
"   vec3 color = albedo * ambient;\n"
"   float att,spotEffect;\n"
"   n = normalize(norm);\n"
"   for (int i = 0; i < spotlightCount; i++){\n"
"   \n"
"   }\n"
"   vec3 dirToSource = vec3(light_source[0] - pos);\n"

"   float distToSource = length(dirToSource);\n"

"   NdotL = max(dot(n,normalize(dirToSource)),0.0);\n"
"   if (NdotL > 0.0){\n"
"      spotEffect = dot(normalize(light_source_spotDir), normalize(-dirToSource));\n"
"      if (spotEffect > light_source_cosCutOff){\n"
"          spotEffect = pow(spotEffect, light_source_spotExponent);\n"
"			att = spotEffect / (light_source_constantAttenuation +\n"
"				light_source_linearAttenuation * distToSource +\n"
"				light_source_quadraticAttenuation * distToSource * distToSource);\n"
"				color += att * (albedo * NdotL);\n"
"      }\n"
"   }\n"//end of (NdotL > 0.0)
"   return color;\n"
"}\n"//end of function
};


char *get_fancy_lighting_function(void)
{
   return (char *) fancy_lighting;
}
