float4x4 _WorldViewProj;

float4 vert(float4 vertex : POSITION) : SV_POSITION
{
  return mul(vertex, _WorldViewProj);
}

float4 frag(float4 o : COLOR0) : SV_TARGET
{
  return float4(1.0f, 1.0f, 1.0f, 1.0f);
}

technique Default
{
  pass
  {
    AlphaBlendEnable = FALSE;
    ShadeMode = FLAT;
    ZEnable = TRUE;
    CullMode = NONE;
    vertexshader = compile vs_2_0 vert();
    pixelshader = compile ps_2_0 frag();
  }
}
