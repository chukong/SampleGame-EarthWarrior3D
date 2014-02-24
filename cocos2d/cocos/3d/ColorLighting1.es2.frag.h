static const char* ColorLighting1 = STRINGIFY(

#ifdef GL_ES
varying lowp vec4 DestinationColor;
#else
varying vec4 DestinationColor;
#endif

//varying mediump vec2 TextureCoordOut;

//uniform sampler2D Sampler;

void main(void)
{
    gl_FragColor =  DestinationColor;
    gl_FragColor.a = 1.0;
}
);
