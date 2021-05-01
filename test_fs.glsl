#version 400

uniform float fade;
in vec3 colour;
//in vec2 UV;

out vec4 frag_colour;
//uniform sampler2D myTextureSampler;

void main(){
    frag_colour = vec4(colour, fade);
    //frag_colour = texture(myTextureSampler,UV).rgb;
};