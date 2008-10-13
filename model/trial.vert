uniform vec3  LightPosition;  // (0.0, 10.0, 4.0) 
uniform vec3 view_position;

varying float NdotL;
varying vec3  ReflectVec;
varying vec3  ViewVec;
varying vec3  normal;

void main(void)
{
    // calculate lighting and varying variables
    vec3 ecPos      = vec3 (gl_ModelViewMatrix * gl_Vertex);
    vec3 tnorm      = normalize(gl_NormalMatrix * gl_Normal);
    vec3 lightVec   = normalize(LightPosition - ecPos);
    ReflectVec      = normalize(reflect(-lightVec, tnorm));
    ViewVec         = normalize(-ecPos);
    NdotL           = (dot(lightVec, tnorm) + 1.0) * 0.5;
    normal = gl_NormalMatrix * gl_Normal;
    gl_Position     = ftransform();
}
