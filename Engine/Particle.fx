#define _WORLD_VIEW_PROJ
#define _MAIN_TEXTURE
#define _DIFFUSE
#include "DefaultProperty.hlsli"

struct appdata
{
  float4 vertex : POSITION;
  float2 uv : TEXCOORD0;
};

struct v2f
{
  float2 uv : TEXCOORD0;
  float4 vertex : SV_POSITION;
};

v2f vert(appdata v)
{
  v2f o;
  o.vertex = mul(v.vertex, _WorldViewProj);
  o.uv = v.uv;
  return o;
}

float4 frag(v2f i) : SV_TARGET
{
  float4 col = tex2D(_MainTexSampler, i.uv) * _Diffuse;
	return col;
}

technique Default
{
  pass
  {
    vertexshader = compile vs_2_0 vert();
    pixelshader = compile ps_2_0 frag();
  }
}
