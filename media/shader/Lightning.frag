uniform sampler2D myTexture0;


varying vec2  vTexCoord;
varying vec3  vNormal;
varying vec3  vLightVec;
varying vec3  vViewVec;

void main(void)
{
	float n_specular = 10.0;
	float Ks = 1.0;
	float Ka = 1.0;
	float Kd = 0.8;
	vec4 diffuse = vec4(0.84,0.86,0.89,1.0);
	vec4 specular = vec4(1.0,0.95,0.67,1.0);
	vec4 ambient = vec4(0.92,0.93,0.93,1.0);
	
   // Compute the reflection vector:
   vec3 vReflect = normalize( 2.0 * dot( vNormal, vLightVec) * vNormal - vLightVec );       

   // Compute ambient term:
   vec4 AmbientColor = ambient * Ka;

   // Compute diffuse term:
   vec4 DiffuseColor = diffuse * Kd * max( 0.0, dot( vNormal, vLightVec ));

   // Compute specular term:
   vec4 SpecularColor = specular * Ks * pow( max( 0.0, dot(vReflect, vViewVec)), n_specular );
   
   vec4 FinalColor = (AmbientColor + DiffuseColor) * texture2D( myTexture0, vTexCoord) + SpecularColor;
   
   gl_FragColor = FinalColor+vec4(0.5,0,0.5,1);
}