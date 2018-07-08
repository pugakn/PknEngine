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
uniform samplerCube tex1;
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

void main() {
    vec3 AmbientColor = vec3(0.1,0.1,0.1);
	vec3 Albedo = texture2D(tex0,vecUVCoords).xyz;
    vec3 eyeDir = normalize(CameraPosition - WorldPos).xyz;
	vec3 SpecularColor = vec3(1,1,1) *0.3;

	vec4 Final = vec4(0,0,0,0);
	vec3 Ambient = AmbientColor * Albedo;
	for (int i = 0; i < 2; ++i){
	   Final += CalculateLight(LightPositions[i],LightColors[i], Albedo, SpecularColor, eyeDir, LightRadius[i]).xyzx;
	}
	Final.w = 1.0;
	gl_FragData[0] =  vec4(Final.xyz + Ambient.xyz,1);

	//vec4 ff  = CameraPosition;
	//gl_FragDepth =  length(vec3(WorldPos.xyz - ff.xyz)) / 1000.0;// 
	
	 // distance to light
   //float distanceToLight = distance(LightCameraPosition.xyz, WorldPos.xyz);

   //gl_FragDepth = 0 ;//saturate((distanceToLight ) /  (1000.0));
}




