uniform sampler2D myTexture0;
uniform sampler2D myTexture1;

varying vec3 vTexCoord;

varying float NdotL;
varying float Time0_x;
   
   void main()
   {

     
      
     	float waveSpeed = 0.44;
		float noiseSpeed = 0.12;
         
   vec3 tcoord = vTexCoord;
   tcoord.x += waveSpeed  * Time0_x;
   tcoord.z += noiseSpeed * Time0_x;


         
     gl_FragColor = mix(texture2D(myTexture0, vTexCoord.zy)*1.4, texture2D(myTexture1, vTexCoord.zy), NdotL);
		//gl_FragColor = vec4(Time0_x,0,0,1);
	  //clamp(fadeBias + pow(lrp, fadeExp),0.0, 1.0)
      //gl_FragColor = myColor*intensityMod*nw;
   } 