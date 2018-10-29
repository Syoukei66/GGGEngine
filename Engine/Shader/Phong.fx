#define _WORLD_VIEW_PROJ
#define _WORLD
#define _CAMERA
#define _MAIN_TEXTURE
#define _LIGHT_PHONG
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

float4 calcPhongLighting(float4 diffuse, float3 N, float3 V, float3 R)
{
  float4 Ia = _Ambient * _AmbientFactor;
  float4 Id = diffuse * saturate(dot(N, _LightDirection));
  float4 Is = _Specular * _SpecularFactor * pow(saturate(dot(R, V)), _Power) * _Reflection * _ReflectionFactor;

  return Ia + (Id + Is) * _LightDiffuse;
}

v2f vert(appdata v)
{
  v2f o;
  o.vertex = mul(v.vertex, _WorldViewProj);
  float3 N = normalize(mul(v.normal, _World));
  float3 V = normalize(_CameraPosition - o.vertex);
  float3 R = reflect(-_LightDirection, N);
  o.color = calcPhongLighting(_Diffuse * _DiffuseFactor, N, V, R);
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
