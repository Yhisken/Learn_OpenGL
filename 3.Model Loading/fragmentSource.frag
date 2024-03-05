#version 330 core
//in vec4 vertexColor;
//in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;
struct Material{
	vec3 ambient;
	sampler2D diffuse;
	vec3 specular;
	float shininess;
};
struct lightDirectional{
	 vec3 pos;
	 vec3 dirToLight;
	 vec3 color;
};

struct lightPoint{
	//base
	 vec3 pos;
	 vec3 dirToLight;
	 vec3 color;
	 //Ë¥¼õ
	float constant;
	float linear;
	float quadratic;
};

struct lightSpot{
	//base
	 vec3 pos;
	 vec3 dirToLight;
	 vec3 color;
	 //Ë¥¼õ
	float constant;
	float linear;
	float quadratic;
	//angle
	float cosPhyInner;
	float cosPhyOutter;

};
uniform Material material;
uniform lightDirectional lightD;
uniform lightPoint lightP;
uniform lightPoint lightP0;
uniform lightPoint lightP1;
uniform lightPoint lightP2;
uniform lightPoint lightP3;
uniform lightSpot lightS;
//uniform sampler2D ourTexture;
//uniform sampler2D ourFace;

uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightDirUniform;
uniform vec3 lightColor;
uniform vec3 cameraPos;



out vec4 FragColor;  
vec3 CalcLightDirectional(lightDirectional light, vec3 uNormal , vec3 dirToCamera){
	//diffuse	dot(L,N);
	float diffuseIntensity = max(dot(light.dirToLight,uNormal), 0);
	vec3 diffuseColor = diffuseIntensity * light.color * texture(material.diffuse,TexCoord).rgb;

	//specular dot(R,cam)
	vec3 R = normalize(reflect(-light.dirToLight,uNormal));
	float specularIntensity = pow(max(dot(R,dirToCamera),0),material.shininess);
	vec3 specularColor = specularIntensity * light.color * texture(material.diffuse,TexCoord).rgb;

	vec3 result = diffuseColor + specularColor;


	return result;
}

vec3 CalcLightPoint(lightPoint light, vec3 uNormal , vec3 dirToCamera){
	//attenuation
	float dist = length(light.pos - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
	//diffuse
	float diffuseIntensity = max(dot(normalize(light.pos - FragPos),uNormal), 0) * attenuation;
	vec3 diffuseColor = diffuseIntensity * light.color * texture(material.diffuse,TexCoord).rgb;
	//specular
	vec3 R = normalize(reflect(-normalize(light.pos - FragPos),uNormal));
	float specularIntensity = pow(max(dot(R,dirToCamera),0),material.shininess) * attenuation;
	vec3 specularColor = specularIntensity * light.color * texture(material.diffuse,TexCoord).rgb;


	vec3 result= diffuseColor+ specularColor;
	return result;
}

vec3 CalcLightSpot(lightSpot light, vec3 uNormal , vec3 dirToCamera){
	//attenuation
	float dist = length(light.pos - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
	float spotRatio;
	float cosTheta = dot(normalize(FragPos-light.pos), -light.dirToLight);

	if(cosTheta  > lightS.cosPhyInner){
		spotRatio = 1.0f;
	}
	else if(cosTheta > lightS.cosPhyOutter){
		//spotRatio =1.0 - (cosTheta - lightS.cosPhyInner) / (lightS.cosPhyOutter - lightS.cosPhyInner);
		spotRatio = (cosTheta - lightS.cosPhyOutter) / (lightS.cosPhyInner - lightS.cosPhyOutter);
	}
	else{
		spotRatio = 0;
	}
	//diffuse
	float diffuseIntensity = max(dot(normalize(light.pos - FragPos),uNormal), 0) * attenuation * spotRatio;
	vec3 diffuseColor = diffuseIntensity * light.color * texture(material.diffuse,TexCoord).rgb;

	//specular
	vec3 R = normalize(reflect(-normalize(light.pos - FragPos),uNormal));
	float specularIntensity = pow(max(dot(R,dirToCamera),0),material.shininess) * attenuation * spotRatio;
	vec3 specularColor = specularIntensity * light.color * texture(material.diffuse,TexCoord).rgb;


	vec3 result= diffuseColor+ specularColor;
	return result;
}
void main()
{	
	vec3 finalResult = vec3(0,0,0);
	vec3 uNormal  = normalize(Normal);
	vec3 dirToCamera = normalize(cameraPos - FragPos);
	finalResult += CalcLightDirectional(lightD ,uNormal,  dirToCamera);

	finalResult += CalcLightPoint(lightP0 ,uNormal,  dirToCamera);
	finalResult += CalcLightPoint(lightP1 ,uNormal,  dirToCamera);
	finalResult += CalcLightPoint(lightP2 ,uNormal,  dirToCamera);
	finalResult += CalcLightPoint(lightP3 ,uNormal,  dirToCamera);

	finalResult += CalcLightSpot(lightS ,uNormal,  dirToCamera);

	FragColor = vec4(finalResult,1.0);














//	float dist = length(lightPos - FragPos);
//	//float attenuation = 1.0 / (lightP.constant + lightP.linear * dist + lightP.quadratic * (dist * dist));
//
//	vec3 lightDir = normalize(lightPos - FragPos);
//	vec3 reflectVec = reflect(-lightDir, Normal);
//	vec3 cameraVec = normalize(cameraPos - FragPos);//viewDir
//
//	//specular
//	float specularAmount = pow(max(dot(reflectVec, cameraVec)*0.07,0.0),material.shininess);
//	vec3 specular = material.specular * specularAmount * lightColor;
//
//	//diffuse
//	//vec3 diffuse = material.diffuse * max(dot(lightDir,Normal),0.0)*lightColor;
//	vec3 diffuse = texture(material.diffuse, TexCoord).rgb * max(dot(lightDirUniform,Normal),0.0)*lightColor;
//	//ambient
//	vec3 ambient =  texture(material.diffuse, TexCoord).rgb* ambientColor;// or material.ambient * ambientColor;
//
//	//
//	float cosTheta = dot(normalize(FragPos-lightPos), -lightDirUniform);
//	float spotRatio;
//	if(cosTheta  > lightS.cosPhyInner){
//		spotRatio = 1.0f;
//	}
//	else if(cosTheta > lightS.cosPhyOutter){
//		spotRatio =1.0 - (cosTheta - lightS.cosPhyInner) / (lightS.cosPhyOutter - lightS.cosPhyInner);
//	}
//	else{
//		spotRatio = 0;
//	}
//	FragColor = vec4( (((diffuse+specular)+ambient))*objColor*spotRatio ,1.0);
//
//   
}