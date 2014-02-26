static const char* SimpleVertexShader1 = STRINGIFY(

attribute vec4 Position;
attribute vec3 Normal;
attribute vec2 TextureCoord;

uniform vec3 DiffuseMaterial;
uniform mat3 NormalMatrix;
uniform vec3 LightPosition;
uniform vec3 AmbientMaterial;
uniform vec3 SpecularMaterial;
uniform float Shininess;

varying vec4 DestinationColor;
varying vec2 TextureCoordOut;

void main(void)
{
    /*
     vec3 N = normalize(NormalMatrix * Normal);
     //vec3 L = LightPosition;// normalize(LightPosition);
     vec3 E = vec3(0, 0, 1);
     vec3 H = normalize(LightPosition + E);

     float df = max(0.0, dot(N, LightPosition));
     float sf = max(0.0, dot(N, H));
     sf = pow(sf, Shininess);

     vec3 color = AmbientMaterial + df * DiffuseMaterial + sf * SpecularMaterial + df/2.0;

     DestinationColor = vec4(color, 1);
     gl_Position = Projection * Modelview * Position;
     TextureCoordOut = TextureCoord;


     /*/
    vec3 N = normalize(NormalMatrix * Normal);
    //vec3 L = LightPosition;// normalize(LightPosition);
    //vec3 E = vec3(0, 0, 1);
    //vec3 H = normalize(LightPosition + E);

    float df = max(0.0, dot(N, LightPosition));
    //float sf = max(0.0, dot(N, H));
    //sf = pow(sf, Shininess);

    vec3 color = df * 1.5 * DiffuseMaterial + 0.3;

    DestinationColor = vec4(color, 1);
    gl_Position = CC_PMatrix * CC_MVMatrix * Position;
    TextureCoordOut = TextureCoord;
    //*/
}
);
