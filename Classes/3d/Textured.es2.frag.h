static const char* baseTexturedFrag = STRINGIFY(

#ifdef GL_ES \r\n
varying lowp vec4 DestinationColor; \r\n
varying mediump vec2 TextureCoordOut; \r\n
#else \r\n
varying vec4 DestinationColor; \r\n
varying vec2 TextureCoordOut; \r\n
#endif \r\n
\r\n
uniform sampler2D Sampler; \r\n
\r\n
void main(void) \r\n
{ \r\n
    gl_FragColor = texture2D(Sampler, TextureCoordOut) * DestinationColor; \r\n
} \r\n
);