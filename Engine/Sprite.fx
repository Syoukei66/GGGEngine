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

float2 _UV0 = float2(0.0f, 0.0f);
float2 _UV1 = float2(1.0f, 1.0f);
float _Width = 1.0f;
float _Height = 1.0f;

v2f vert(appdata v)
{
  v2f o;
  v.vertex.x *= _Width;
  v.vertex.y *= _Height;
  o.vertex = mul(v.vertex, _WorldViewProj);

  v.uv *= _UV1 - _UV0;
  v.uv += _UV0;
  o.uv = v.uv;
  return o;
}

float4 frag(v2f i) : SV_TARGET
{
  return tex2D(_MainTexSampler, i.uv) * _Diffuse;
}

technique Default
{
  pass
  {
    AlphaBlendEnable = TRUE;
    BlendOp = ADD;
    SrcBlend = SRCALPHA;
    DestBlend = INVSRCALPHA;
    ShadeMode = FLAT;
    ZEnable = TRUE;
    vertexshader = compile vs_2_0 vert();
    pixelshader = compile ps_2_0 frag();
  }
}
