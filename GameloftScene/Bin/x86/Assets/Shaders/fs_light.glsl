uniform mat4 WVP;
uniform mat4 World;
uniform mat4 WorldView;
uniform mat4 LightVP;
uniform mat4 View;
uniform vec4 CameraPosition;
uniform vec4 LightPositions[2];
uniform vec4 LightColors[2];
uniform vec4 LightRadius[2];
uniform vec4 LightCameraPosition;

varying vec2 vecUVCoords;
varying vec4 Pos;
varying vec4 WorldPos;
varying vec4 Norm;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform samplerCube tex2;

vec3 CalculateDiffuse(float NdL, vec3 albedoColor){
	return NdL * albedoColor;
}
vec3 CalculateSpecular(float NdH, vec3 specularColor ) {
  return pow(NdH,16) * specularColor;
}
vec3 CalculateLight(vec3 lightPos, vec3 lightColor,vec3 albedo,vec3 specularColor, vec3 eyeDir, float radius){
	vec3 l = lightPos - WorldPos;
	float dist = length(l);
	vec3 lightDir = normalize(l);
	
	vec3 H = normalize(eyeDir+lightDir);
	
	float NdL = saturate(dot(Norm, lightDir));
	float NdH = saturate(dot( Norm, H ));
	
	vec3 diffuse = CalculateDiffuse(NdL,albedo);
	vec3 specular = CalculateSpecular(NdH,specularColor);
	float att = clamp(1.0 - dist*dist/(radius*radius), 0.0, 1.0); 
	att *= att;
	return NdL * lightColor * (diffuse + specular ) * att;
}

float CalculateShadow() {
	vec4 fromCamPos;
	WorldPos.w = 1.0;
	fromCamPos = LightVP*WorldPos;
	vec3 proj = fromCamPos.xyz / fromCamPos.w;
	proj = 0.5 * (proj + 1.0);
	vec2 shCoords =  proj.xy;
	float shadow = 0.0;
	if (shCoords.x <= 1 && shCoords.y <= 1 && shCoords.x >= 0 && shCoords.y >= 0
	&&proj.z <=1 && proj.z >= 0 ){
		vec2 texelSize =  1.0 /1024.0;
		for(int x = -1; x <= 1; ++x)
		{
			for(int y = -1; y <= 1; ++y)
			{
				float pcfDepth = texture2D(tex1, shCoords + vec2(x,y) * texelSize ).r;
				if (proj.z > pcfDepth  + 0.001)
				{
					shadow += 1.0;
				}
			}
		}
		shadow /= 9.0;
	}
	return 1.0 - shadow * 0.85;
}



void main() {
    vec3 AmbientColor = vec3(0.1,0.1,0.1);
	vec3 Albedo = texture2D(tex0,vecUVCoords).xyz;
    vec3 eyeDir = normalize(CameraPosition - WorldPos).xyz;
	vec3 SpecularColor = vec3(1,1,1) *0.4;

	vec4 Final = vec4(0,0,0,0);
	vec3 Ambient = AmbientColor * Albedo;
	for (int i = 0; i < 2; ++i){
	   Final += CalculateLight(LightPositions[i],LightColors[i], Albedo, SpecularColor, eyeDir, LightRadius[i]).xyzx;
	}
	float sh = CalculateShadow();
	Final *= sh;
	Final.w = 1.0;
	gl_FragColor =  vec4(Final.xyz + Ambient.xyz  *(sh *0.5) ,1);
}




