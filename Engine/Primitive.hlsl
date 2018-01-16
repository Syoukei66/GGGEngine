struct appdata
{
  float4 vertex : POSITION;
};

struct v2f
{
  float4 vertex : SV_POSITION;
};

float4x4 _WorldViewProj;
float4 _Diffuse;

v2f vert(appdata v)
{
  v2f o;
  o.vertex = mul(v.vertex, _WorldViewProj);
  return o;
}

float4 frag(v2f i) : SV_TARGET
{
	return _Diffuse;
}

technique Default
{
  pass
  {
    vertexshader = compile vs_2_0 vert();
    pixelshader = compile ps_2_0 frag();
  }
}
