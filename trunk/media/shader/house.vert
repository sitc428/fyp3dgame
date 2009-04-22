
varying float LightIntensity;
varying vec3 Position;

void main(void) {
	gl_Position    = ftransform();
   vec3 LightPosition = vec3(0,0,4.0);
   float Scale = 0.02;
   vec4 pos       = gl_ModelViewMatrix * gl_Vertex;
   Position       = vec3(gl_Vertex) * Scale;
   vec3 tnorm     = normalize(gl_NormalMatrix * gl_Normal);
   float dotval   = abs(dot(normalize(LightPosition - vec3(pos)), tnorm));
   LightIntensity = dotval * 1.5;
   }
