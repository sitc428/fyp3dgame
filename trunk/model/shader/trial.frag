// Uniform variables, commented out numbers are the 
//    values normally used for Gooch shading.
//uniform vec4  myColor;

// these varying variables were sent by the vertex shader
//   and are used in the Gooch algorithm
varying float NdotL;
varying vec3  ReflectVec;
varying vec3  ViewVec;
varying vec3  normal;

void main (void)
{

vec3  SurfaceColor =  vec3(0.75, 0.75, 0.75);
vec3  WarmColor =  vec3(0.6, 0.6, 0.0);
vec3  CoolColor =  vec3(0.0, 0.0, 0.6);
float DiffuseWarm = 0.45;
float DiffuseCool = 0.45;

float intensity;
vec3 n = normalize(normal);

intensity = dot(vec3(gl_LightSource[0].position),n);

float intensityMod = 0.0;
vec3 Scolor;

if (intensity > 0.95)
intensityMod = 1.0; 
else if (intensity > 0.4)
intensityMod = 0.88;
else if (intensity > 0.25)
intensityMod = 0.66;
else
intensityMod = 0.0;


//------------------------

vec3 kCool    = min(CoolColor + DiffuseCool * SurfaceColor, 1.0);
vec3 kWarm    = min(WarmColor + DiffuseWarm * SurfaceColor, 1.0); 

// select color to use for output
vec3 kFinal   = mix(kCool, kWarm, NdotL);

// calculate lighting
vec3 nReflect = normalize(ReflectVec);
vec3 nView    = normalize(ViewVec);

float spec    = max(dot(nReflect, nView), 0.0);
spec          = pow(spec, 32.0);

// calculate final color based on mix between lighting and previous mix
gl_FragColor = vec4 (min(kFinal + spec, 1.0), 1.0)*intensityMod;
}
