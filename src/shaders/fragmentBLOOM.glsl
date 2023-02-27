#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D hdrBuffer;
uniform sampler2D bloomBlur;
uniform sampler2D brightPixels;

uniform bool hdr;
uniform bool bloom;
uniform bool OnlyBright;
uniform float exposure;

void main()
{             
    const float gamma = 2.2;
    // const float gamma = 1.0;
    vec3 hdrColor = texture(hdrBuffer, TexCoords).rgb;
    vec3 bloomColor = texture(bloomBlur, TexCoords).rgb;
    vec3 brightColor = texture(brightPixels, TexCoords).rgb;

    if (OnlyBright){
        FragColor = vec4(brightColor, 1.0);
        return;
    }

    if (bloom)
        hdrColor += bloomColor;
        
    if(hdr)
    {
        // reinhard
        // vec3 result = hdrColor / (hdrColor + vec3(1.0));
        // exposure
        vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
        // also gamma correct while we're at it       
        result = pow(result, vec3(1.0 / gamma));
        FragColor = vec4(result, 1.0);
    }
    else
    {   
        // vec3 result = pow(hdrColor, vec3(1.0 / gamma));
        // FragColor = vec4(result, 1.0);
        FragColor = vec4(hdrColor, 1.0);
    }
}