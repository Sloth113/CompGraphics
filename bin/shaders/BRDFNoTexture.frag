// classic Phong fragment shader
#version 410

in vec4 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;
in vec3 vTangent;
in vec3 vBiTangent;
in float vRoughness;


out vec4 FragColour;

uniform sampler2D diffuseTexture;
uniform sampler2D normalTexture;
uniform sampler2D specularTexture;

uniform vec3 Ka; // ambient material colour 
uniform vec3 Kd; // diffuse material colour
uniform vec3 Ks; // specular material colour 
uniform float specularPower; // material specular power


uniform vec3 Ia; // ambient light colour
uniform vec3 Id; // diffuse light colour 
uniform vec3 Is; // specular light colour 
uniform vec3 LightDirection;

uniform float reflectionCoefficient;

uniform vec3 cameraPosition;

void main() {

	// ensure normal and light direction are normalised
	vec3 N = normalize(vNormal);
	vec3 L = normalize(-LightDirection);//-L 
	vec3 T = normalize(vTangent);
	vec3 B = normalize(vBiTangent);

	// calculate view vector and reflection vector 
	vec3 V = normalize(cameraPosition - vPosition.xyz);
	vec3 R = reflect( -L, N ); 
	//Surface to viewer
	vec3 E = V;

	float NdL= max( 0.0f, dot( N, L ) );
	float NdE = max( 0.0f, dot( N, E ) );
	
	float R2 = vRoughness * vRoughness;
	vec3 H = normalize( L + E ); // light and view half vector
	// Oren-NayarDiffuse Term
	float A2 = 1.0f -0.5f * R2 / (R2 + 0.33f);
	float B2 = 0.45f * R2 / (R2 + 0.09f);
	
	// CX = Max(0, cos(l,e))
	vec3 lightProjected = normalize( L -N * NdL);
	vec3 viewProjected = normalize( E -N * NdE);
	float CX = max( 0.0f, dot( lightProjected, viewProjected) );
	
	// DX = sin(alpha) * tan(beta)
	float alpha = sin( max( acos( NdE), acos( NdL) ) );
	float beta = tan( min( acos( NdE), acos( NdL) ) );
	float DX = alpha * beta;
	
	// Calculate Oren-Nayar, replaces the PhongLambertianTerm
	float OrenNayar = NdL* (A2 + B2 * CX * DX);
	
	// calculate lambert term (negate light direction)
	float lambertTerm;// = max( 0, min( 1, dot( N, -L ) ) );
	lambertTerm = OrenNayar;


	float NdH = max( 0.0f, dot( N, H ) );
	float NdH2 = NdH* NdH;
	float e = 2.71828182845904523536028747135f;
	float pi = 3.1415926535897932384626433832f;
	
	// Beckman's Distribution Function D
	float exponent = -(1 -NdH2) / (NdH2 * R2);
	float D = pow( e, exponent ) / (R2 * NdH2 * NdH2);
	
	// Fresnel Term F
	//float F = reflectionCoefficient+ (1 – reflectionCoefficient) * pow(1 - NdE, 5);
	  float F = reflectionCoefficient+ (1 - reflectionCoefficient) * pow(1 - NdE, 5);
	// Geometric Attenuation Factor G
	float X = 2.0f * NdH / dot( E, H );
	float G = min(1, min(X * NdL, X * NdE));
	
	// Calculate Cook-Torrance
	float CookTorrance = max( (D*G*F) / (NdE* pi), 0.0f );

	// calculate specular term 
	float specularTerm = CookTorrance; //= pow( max( 0, dot( R, V ) ), specularPower);
	
	
	
	//Colour?
	vec3 ambient = Ia * Ka;    
	vec3 diffuse = Id * Kd * lambertTerm ;
	vec3 specular = Is * Ks * specularTerm;

	FragColour = vec4( ambient + diffuse + specular, 1) ;
	//FragColour = vec4(texNormal, 1);
}