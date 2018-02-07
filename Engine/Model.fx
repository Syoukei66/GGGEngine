#define _WORLD_VIEW_PROJ
#define _MAIN_TEXTURE
#define _DIFFUSE
#define _LIGHT_PARAMS
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
  o.uv = v.uv;

  float3 normal = mul(v.normal, _WorldViewProj);

  // ディフューズ色を計算(点光源)
  //float3 vL = _LightPosition - o.vertex;   // 光源ベクトル
  //float  lengL = length(vL) * _ModelScale; // 光源ベクトルの長さ(光源への距離)
  //float3 normL = normalize(vL);            // 光源ベクトル(単位ベクトル)
  //float3 normN = normalize(normal);        // 法線ベクトル(単位ベクトル)
  //float  L = _LightBrightness * dot(normN, normL) / (lengL * lengL);  // 光の強さ
  //o.color = _Diffuse * max(0, min(1, L));  // ディフューズ色
  //o.color.a = 1.0f;
  o.color = _Diffuse;
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
    vertexshader = compile vs_2_0 vert();
    pixelshader = compile ps_2_0 frag();
  }
}
