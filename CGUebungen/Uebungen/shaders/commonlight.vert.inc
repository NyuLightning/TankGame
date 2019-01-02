#sgdefine COMMONLIGHT_VERT_INC //Define setzen um Mehrfache inkludierung auszuschliessen

#sginclude "/common.vert.inc"
#sginclude "/commonlightmatdefs.inc"
#sginclude "/commonlightmodels.inc"

vec3 eyePosition() {return((mMatrix * vertexPosition)).xyz;}
vec3 eyeLightPos() {return((mMatrix * lights[0].position).xyz);}
vec3 eyeNormalVec() {return(normalize(nMatrix * vertexNormal.xyz));}
vec3 eyeLightVec() {return(normalize(eyeLightPos().xyz - eyePosition().xyz));}
vec3 eyeViewVec() {return(-normalize(eyePosition().xyz));}
vec3 eyeReflectVec() {return(-reflect(eyeLightVec(), eyeNormalVec()));}

vec4 phong()
{
    return(phong(eyeLightVec(), eyeViewVec(), eyeNormalVec(), material, lights[0]));
}

vec4 phongHalf()
{
    return(phongHalf(eyeLightVec(), eyeViewVec(), eyeNormalVec(), material, lights[0]));
}
