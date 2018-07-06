uniform mat4 WVP;
uniform mat4 World;
uniform mat4 WorldView;
uniform mat4 LightVP;
uniform vec4 CameraPosition;

varying vec2 vecUVCoords;
varying vec4 Pos;
varying vec4 WorldPos;
varying vec4 Norm;

uniform sampler2D tex0;
uniform sampler2D tex1;

vec3 CalculateDiffuse(float NdL, vec3 albedoColor){
	return NdL * albedoColor;
}
vec3 CalculateSpecular(float NdH, vec3 specularColor ) {
  return pow(NdH,2) * specularColor;
}
vec3 CalculateLight(vec3 lightPos, vec3 lightColor,vec3 albedo,vec3 specularColor, vec3 eyeDir){
	vec3 lightDir = normalize(lightPos - WorldPos);
	float lightRadius = 10;
	
	vec3 H = normalize(eyeDir+lightDir);
	
	float NdL = saturate(dot(Norm, lightDir));
	float NdH = saturate(dot( Norm, H ));
	
	vec3 diffuse = CalculateDiffuse(NdL,albedo);
	vec3 specular = CalculateSpecular(NdH,specularColor);
	return NdL * lightColor * (diffuse + specular);
}

void main(){
    vec3 AmbientColor = vec3(0.1,0.1,0.1);
	
	vec3 lightPos = vec3(0,5,5);
    vec3 eyeDir = normalize(CameraPosition - WorldPos);
	vec3 Albedo = texture2D(tex0,vecUVCoords).xyz;
	vec3 SpecularColor = vec3(1,1,1);
	
	vec4 LightDepth = texture2D(tex1,vecUVCoords).xyzw;
	
	vec3 Ambient = AmbientColor * Albedo;
	vec3 light1 = CalculateLight(lightPos,vec3(1,1,1),Albedo,vec3(1,1,1),eyeDir);
	
	
	vec4 Final = vec4(light1,1);
	//Shadow Map=============================
			vec4 fromCamPos;
			Pos.w = 1.0;
			fromCamPos = LightVP*WorldPos;
			vec3 proj = fromCamPos.xyz / fromCamPos.w;
			proj = 0.5 * (proj + 1.0);
			//proj = Pos.xyz;
			vec2 shCoords =  proj.xy;
			float shadow = 0.0;
			if (shCoords.x <= 1 && shCoords.y <= 1 && shCoords.x >= 0 && shCoords.y >= 0
			&&proj.z <=1 && proj.z >= 0 ){
				vec2 texelSize =  1.0 /1024;       //ShadowTexSize;
				for(int x = -1; x <= 1; ++x)
				{
				    for(int y = -1; y <= 1; ++y)
				    {
				        float pcfDepth = texture2D(tex1, shCoords ).r;//+ vec2(x,y) * texelSize
								if (proj.z > pcfDepth +0.002)
								{
									//pixel en la sombra
									shadow += 1.0;
									Final.xyz = vec3(1,0,0);
								}
								/*if (pcfDepth  > 0.99)
								{
									//pixel en la sombra
									shadow += 1.0;
									Final.xyz = vec3(1,0,0);
								}*/
				    }
				}
				shadow /= 9.0;
				//Final.xyz *(1.0-shadow);
			}
			//End Shadow Map ========================
	
	gl_FragColor =  vec4(Final.xyz + Ambient ,1);
	//gl_FragColor = LightDepth;
}




