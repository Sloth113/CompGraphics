// classic Phong fragment shader
#version 410

in vec4 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;

uniform vec3 cameraPosition;
uniform vec3 Ia; // ambient light colour
uniform vec3 Id; // diffuse light colour 
uniform vec3 Is; // specular light colour 
uniform vec3 LightDirection;

uniform vec3 Ka; // ambient material colour 
uniform vec3 Kd; // diffuse material colour
uniform vec3 Ks; // specular material colour 
uniform float specularPower; // material specular power

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;

out vec4 FragColour;

void main() {

	// ensure normal and light direction are normalised
	vec3 N = normalize(vNormal);
	vec3 L = normalize(LightDirection);

	// calculate lambert term (negate light direction)
	float lambertTerm = max( 0, min( 1, dot( N, -L ) ) );

	// calculate view vector and reflection vector 
	vec3 V = normalize(cameraPosition - vPosition.xyz);
	vec3 R = reflect( L, N ); 
	// calculate specular term 
	float specularTerm = pow( max( 0, dot( R, V ) ), specularPower);
	
	vec3 diffColour = vec3(1.0, 1.0, 1.0);
	vec3 specColour = vec3(1.0, 1.0, 1.0);

		diffColour = texture( diffuseTexture, vTexCoord ).rgb;

		specColour = texture( specularTexture, vTexCoord ).rgb;
	
	
	//Colour?
	vec3 ambient = Ia * Ka * diffColour;    
	vec3 diffuse = Id * Kd * lambertTerm * diffColour ;
	vec3 specular = Is * Ks * specularTerm * specColour;

	FragColour = vec4( ambient + diffuse + specular, 1) ;

}