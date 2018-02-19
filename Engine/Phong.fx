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
  float3 normal : NORMAL0;
  float4 color : COLOR0;
};

float _ModelScale = 1.0f;

v2f vert(appdata v)
{
  v2f o;
  o.vertex = mul(v.vertex, _WorldViewProj);
  o.normal = normalize(mul(v.normal, _World));
  o.color = _Diffuse * _DiffuseFactor;
  o.uv = v.uv;
  return o;
}

float4 frag(v2f i) : SV_TARGET
{
  float L = dot(i.normal, _LightDirection);
  return i.color * max(0, L) + _Ambient * _AmbientFactor;
  //float3 N = normalize(i.normal);
  //float3 R = 2 * N * dot(_LightDirection, N) - _LightDirection;
  //float4 P = mul(float4(0.0f, 0.0f, 0.0f, 1.0f), _World);
  //float3 V = normalize(P - _CameraPosition);
  //float4 L = _Specular * _SpecularFactor * pow(dot(R, V), _Power) * _Reflection * _ReflectionFactor * _LightDiffuse;
  //return i.color * L * _Transparent * _TransparentFactor;
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
