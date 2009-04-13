uniform sampler2D myTexture0;

varying vec2 vTexCoord;
varying vec3 vNormal;
varying vec3 light;


void main (void)
{

	
	vec4 color = vec4(0.3, 0.3,1.0,0.5);
//	vec4 temp = texture2D( myTexture2, vTexCoord );
//	gl_FragColor = texture2D( myTexture2, vTexCoord )*texture2D(myTexture, vTexCoord);
//	gl_FragColor = texture2D( myTexture0, vTexCoord )*texture_line*intensityMod;
	gl_FragColor = color*texture2D( myTexture0, vTexCoord );
}