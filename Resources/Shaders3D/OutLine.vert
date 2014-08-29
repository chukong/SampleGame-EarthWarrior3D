attribute vec4 a_position;
attribute vec3 a_normal;
attribute vec2 a_texCoord;
uniform float OutlineWidth;

void main(void)
{
    vec4 pos = CC_MVPMatrix * a_position;
    vec4 normalproj = CC_MVPMatrix * vec4(a_normal, 0);
    normalproj = normalize(normalproj);
    pos.xy += normalproj.xy * (OutlineWidth * (pos.z * 0.25));
    a_texCoord;
    gl_Position = pos;
}
