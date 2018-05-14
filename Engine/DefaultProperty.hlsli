#ifdef _MAIN_TEXTURE
texture _MainTex;
sampler _MainTexSampler = sampler_state
{
  Texture = _MainTex;
  MipFilter = LINEAR;
  MinFilter = LINEAR;
  MagFilter = LINEAR;
};
#endif

#ifdef _MAIN_TEXTURE_POINT
texture _MainTex;
sampler _MainTexSampler = sampler_state
{
  Texture = _MainTex;
  MipFilter = POINT;
  MinFilter = POINT;
  MagFilter = POINT;
};
#endif

#ifdef _WORLD
float4x4 _World;
#endif

#ifdef _WORLD_VIEW_PROJ
float4x4 _WorldViewProj;
#endif

#ifdef _CAMERA
float4 _CameraPosition = float4(0.0f, 0.0f, 0.0f, 1.0f);
float3 _CameraDirection = float3(0.0f, 0.0f, 1.0f);
#endif

#ifdef _LIGHT_PHONG
#define _LIGHT_LAMBERT
float4 _Specular = float4(1.0f, 1.0f, 1.0f, 1.0f);
float _SpecularFactor = 1.0f;
float _Power = 1.0f;
float4 _Reflection = float4(1.0f, 1.0f, 1.0f, 1.0f);
float _ReflectionFactor = 1.0f;
float4 _Transparent = float4(1.0f, 1.0f, 1.0f, 1.0f);
float _TransparentFactor = 1.0f;
#endif

#ifdef _LIGHT_LAMBERT
#define _DIFFUSE
float _DiffuseFactor = 1.0f;
#define _AMBIENT
float _AmbientFactor = 1.0f;
#define _LIGHT_PARAMS
float4 _Emissive = float4(1.0f, 1.0f, 1.0f, 1.0f);
float3 _Bump = float3(0.0f, 0.0f, 0.0f);
float _BumpFactor = 1.0f;
#endif

#ifdef _DIFFUSE
float4 _Diffuse = float4(1.0f, 1.0f, 1.0f, 1.0f);
#endif

#ifdef _AMBIENT
float4 _Ambient = float4(0.0f, 0.0f, 0.0f, 1.0f);
#endif

#ifdef _LIGHT_PARAMS
float4 _LightPosition = float4(1.0f, 1.0f, -1.0f, 1.0f);
float _LightBrightness = 500.0f;
float3 _LightDirection = float3(0.0f, 0.0f, 1.0f);
float4 _LightDiffuse = float4(1.0f, 1.0f, 1.0f, 1.0f);
#endif