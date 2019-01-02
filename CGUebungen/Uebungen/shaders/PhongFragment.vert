#version 330
#sginclude "/commonlight.vert.inc"

out vec3 N;
out vec3 L;
out vec3 E;
out vec3 H;

void main()
{
    gl_Position = vPos();

    N = normalize(nMatrix * vertexNormal.xyz);
    L = normalize(eyeLightPos().xyz - eyePosition().xyz);
    E = -normalize(eyePosition().xyz);
    H = normalize(L + E);
}
