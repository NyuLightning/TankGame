#version 330
#sginclude "/commonlightmatdefs.inc"
#sginclude "/commonlightmodels.inc"

in vec3 N;
in vec3 L;
in vec3 E;
in vec3 H;
out vec4 fragColor;

void main()
{
     vec3 Normal = normalize(N);
     vec3 LightVec  = normalize(L);
     vec3 Eye    = normalize(E);
     vec3 Half   = normalize(H);

     fragColor = phong(LightVec, Eye, Normal, material, lights[0]);
}
