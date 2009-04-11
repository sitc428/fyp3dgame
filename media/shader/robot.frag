
uniform sampler2D myTexture0;
uniform sampler2D myTexture1;

varying vec2 vTexCoord;
varying vec3 vNormal;


void main (void)
{
	//vec4 col = texture2D(myTexture, vec2(gl_TexCoord[0]));
    //col = gl_Color;
	
	float ina;
   vec3 n = normalize(vNormal);
      
   ina = dot(vec3(gl_LightSource[0].position),n);
				
   float intensityMod = 0.0;
     // vec3 Scolor= vec3(0.5,0.4,0.3);
      
      if (ina > 0.05)
         intensityMod = 1.0; 
      else if (ina > 0.02)
         intensityMod = 0.88;
      else if (ina > 0.005)
         intensityMod = 0.66;
      else
         intensityMod = 0.6;
		 
	
	float Intensity = normalize( vNormal ).z * 0.5 + 0.5;
	vec4 texture_line;
	if(ina> 0.1)
        texture_line= vec4(0.9);
     else  texture_line = texture2D( myTexture1, vTexCoord)*0.2;
	
	vec4 color=vec4(1.0, 0.7,0.3,1.0);
//	vec4 temp = texture2D( myTexture2, vTexCoord );
//	gl_FragColor = texture2D( myTexture2, vTexCoord )*texture2D(myTexture, vTexCoord);
	gl_FragColor = texture2D( myTexture0, vTexCoord );
//	gl_FragColor = color*texture_line*intensityMod;
}
