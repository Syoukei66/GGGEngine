Shader "TestShader"
Properties
{
  _TestRange  ("range value", Range(0.0, 1.0)) = 0.0
  _TestFloat  ("float value", Float) = 1.0
  _TestInt    ("int value", Int) = 12345
  _TestColor  ("Color value", Color) = {1.0, 1.0, 1.0, 1.0}
  _TestVector ("Vector value", Vector) = {}
  _Test2D     ("Texture value", 2D) = "white"
}
Tags
{
  Queue BackGround
  RenderType Transparent
}
GrabPass
{}
Pass
{
  LightMode ForwardBase
  Cull Off
  ZWrite On
  ZTest Equal
  Blend One SrcColor
  Blend 3 One SrcColor, Zero InvSrcColor
  Blend 4 Off
  BlendOp RevSub
  BlendOp 7 Sub, Max

  CODE_BEGIN

struct VS_INPUT
{
    float4 Pos : POSITION;
    float2 Tex : TEXCOORD0;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD0;
};

PS_INPUT VS(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT)0;
    output.Pos = mul(_MatMVP, input.Pos);
    output.Tex = input.Tex;

    return output;
}

float4 PS(PS_INPUT input) : SV_Target
{
  return tex2D(_Test2D, input.Tex);
}

  CODE_END
}