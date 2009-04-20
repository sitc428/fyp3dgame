uniform float time_0_X;

varying vec2  vTexCoord;
varying vec3  vNormal;
varying vec3  vLightVec;
varying vec3  vViewVec;

void main(void)
{
	vec4 lightDir = vec4(-.0403,-0.294,0.866,1.0);
	float scroll_speed_X = 22.0;
	float scroll_speed_Y = -12.0;
   // Output transformed vertex position:
   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

   // Compute the light vector (view space):
   vLightVec   = -lightDir.xyz;
   vLightVec.z = -vLightVec.z;    // notice that we need to flip the z here to let OGL match D3D

   // Transform vertex position into view space:
   vec3 Pview =  vec3(gl_ModelViewMatrix * gl_Vertex);

   // Transform normal into view space:        
   vNormal = normalize( gl_NormalMatrix * gl_Normal);

   // Compute view vector (view space):
   vViewVec = -normalize(Pview);  
   
   // Propagate texture coordinate for the object:
   vTexCoord.x = gl_MultiTexCoord0.x + time_0_X / (-scroll_speed_X);
   vTexCoord.y = gl_MultiTexCoord0.y + time_0_X / (-scroll_speed_Y);
   
}