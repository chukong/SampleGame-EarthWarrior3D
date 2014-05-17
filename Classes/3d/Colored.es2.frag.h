static const char* baseColoredFrag = STRINGIFY(
\r\n
#ifdef GL_ES \r\n
varying lowp vec4 DestinationColor; \r\n
#else \r\n
varying vec4 DestinationColor; \r\n
#endif \r\n
//varying mediump vec2 TextureCoordOut; \r\n
//uniform sampler2D Sampler; \r\n
\r\n
void main(void) \r\n
{ \r\n
    gl_FragColor =  DestinationColor; \r\n
    gl_FragColor.a = 1.0; \r\n
} \r\n
);

// pure black frag shader
static const char* blackFrag = STRINGIFY(
uniform vec3 OutLineColor; \r\n
void main(void) \r\n
{ \r\n
    gl_FragColor =  vec4(OutLineColor,1.0); \r\n
} \r\n
);
