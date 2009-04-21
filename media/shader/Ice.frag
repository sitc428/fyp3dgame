varying vec3 vNormal;


vec3 map( in vec3 s );

void main(void)
{
	
	float gamma = 4.2;//2.2
   vec3 color = map( normalize( vNormal ) );
   color = pow ( color, vec3( 1.0/gamma ) );
   gl_FragColor = vec4( color, 1.0 )+vec4(0,0,1,1);
}

vec3 map( in vec3 s )
{
   vec3 result = s * 0.4 + 0.5;
   return result;
}