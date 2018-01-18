float4x4 _WorldViewProj;

float4 vert(float4 vertex : POSITION) : POSITION
{
  return mul(vertex, _WorldViewProj);
}

float4 frag() : SV_TARGET
{
  float4 o;
  o.r = 1.0f;
  o.g = 1.0f;
  o.b = 1.0f;
  o.a = 1.0f;
  return o;
}

technique Default
{
  pass
  {
    vertexshader = compile vs_2_0 vert();
    pixelshader = compile ps_2_0 frag();
  }
}
