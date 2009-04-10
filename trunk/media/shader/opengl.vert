

varying vec2 vTexCoord;
varying vec3 vNormal;


void main(void)
{
/*	gl_Position = mWorldViewProj * gl_Vertex;
	
	vec4 normal = vec4(gl_Normal, 0.0);
	normal = mInvWorld * normal;
	normal = normalize(normal);
	
	vec4 worldpos = gl_Vertex * mTransWorld;
	
	vec4 lightVector = worldpos - vec4(mLightPos,1.0);
	lightVector = normalize(lightVector);
	
	float tmp2 = dot(-lightVector, normal);
	
	vec4 tmp = mLightColor * tmp2;
	//gl_FrontColor = gl_BackColor = vec4(tmp.x, tmp.y, tmp.z, 0.0);
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
*/	
	
	gl_Position= ftransform();
	vTexCoord = gl_MultiTexCoord0.st;
	vNormal = gl_NormalMatrix * gl_Normal;
	
}
