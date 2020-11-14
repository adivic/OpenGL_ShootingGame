#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D muzzleFlash;
uniform bool bShow;

void main() {    
	if(bShow) { 
		vec4 texColor = texture(muzzleFlash, TexCoords);
		if(texColor.a < 0.1) 
			discard;
		FragColor = texColor;
	} else discard;
}