
uniform sampler2D myTexture0;
uniform sampler2D myTexture1;

//uniform sampler2D Noise2d;
//uniform sampler2D Texture1;
//uniform float ErosionFactor, IntensityFactor1, IntensityFactor2;
//uniform vec4 Color1, Color2;

varying float LightIntensity; 
varying vec3 Position;

void main (void)
{
	vec4 Color1 = vec4(0.2,0.09,0.0,1.0);
	vec4 Color2 = vec4(0.8,0.8,0.8,1.0);
   float ErosionFactor = 0.45;//0.35->0.47
   float IntensityFactor1 =  0.77;//0.75
   float IntensityFactor2 =  4.95;//1.95->4.95
    vec3 offset     = vec3(- ErosionFactor, - ErosionFactor + 0.06, - ErosionFactor * 0.92);
    vec3 color;   
    
    // Compute noise
    vec3 noiseCoord = Position.xyz + offset;
    vec4 noiseVec   = texture2D(myTexture0, noiseCoord.yz);
    float intensity = abs(noiseVec[0] - 0.25) +
                      abs(noiseVec[1] - 0.125) +
                      abs(noiseVec[2] - 0.0625) +
                      abs(noiseVec[3] - 0.03125);
    
    // continue noise evaluation                  
    intensity = IntensityFactor1 * (noiseVec.x + noiseVec.y + noiseVec.z + noiseVec.w);
    intensity = IntensityFactor2 * abs(2.0 * intensity - 1.0);
    intensity = clamp(intensity, 0.0, 1.0);

    // discard pixels in a psuedo-random fashion (noise)
    if (intensity < fract(0.5-offset.x-offset.y-offset.z)) discard;

    // color fragments different colors using noise
    color = mix(Color1.rgb, Color2.rgb, intensity);
    
    color *= LightIntensity;
    color = clamp(color, 0.0, 1.0); 

    gl_FragColor = vec4 (color, 1.0);
    
}
