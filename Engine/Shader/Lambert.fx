#define _WORLD_VIEW_PROJ
#define _WORLD
#define _MAIN_TEXTURE
#define _LIGHT_LAMBERT
#include "DefaultProperty.hlsli"

struct appdata
{
  float4 vertex : POSITION;
  float3 normal : NORMAL0;
  float2 uv : TEXCOORD0;
};

struct v2f
{
  float2 uv : TEXCOORD0;
  float4 vertex : SV_POSITION;
  float4 color : COLOR0;
};

float _ModelScale = 1.0f;

v2f vert(appdata v)
{
  v2f o;
  o.vertex = mul(v.vertex, _WorldViewProj);
  float L = dot(normalize(mul(v.normal, _World)), _LightDirection);
  o.color = _Diffuse * max(0, L) + _Ambient * _AmbientFactor;
  o.uv = v.uv;
  return o;
}

float4 frag(v2f i) : SV_TARGET
{
  return i.color;
}

technique Default
{
  pass
  {
    ZEnable = TRUE;
    MultiSampleAntialias = TRUE;
    AlphaBlendEnable = FALSE;
    ShadeMode = GOURAUD;
    CullMode = CCW;
    vertexshader = compile vs_3_0 vert();
    pixelshader = compile ps_3_0 frag();
  }
}
