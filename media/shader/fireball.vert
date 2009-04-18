uniform float Time0_X;



varying float NdotL;
varying float Time0_x;
varying vec3 vTexCoord;  
 
   void main()
   {
   
      vec3  LightPosition = vec3(0.0, 10.0, 4.0);  // (0.0, 10.0, 4.0) 
     // gl_Position = vec4(vTexCoord, 0.0, 1.0);
      vec4 Position = gl_Vertex.xyzw;

      vec3 ecPos      = vec3 (gl_ModelViewMatrix * gl_Vertex);
      vec3 tnorm      = normalize(gl_NormalMatrix * gl_Normal);
      vec3 lightVec   = normalize(LightPosition - ecPos);
      NdotL           = (dot(lightVec, tnorm) + 1.0) * 0.5;
      Time0_x = Time0_X;
      
      vec3 normal = gl_NormalMatrix * gl_Normal;
      
      vTexCoord = vec3(normalize(normal));
   
      gl_Position = ftransform();
   } 