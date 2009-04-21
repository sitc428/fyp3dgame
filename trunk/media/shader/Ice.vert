varying vec3 vNormal;
void main(void)
{
   gl_Position = ftransform();
   vNormal = gl_NormalMatrix * gl_Normal;
}
