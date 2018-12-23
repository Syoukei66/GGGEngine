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
Pass
{
  LightMode Always
  Stencil
  {
    Ref 1
    ReadMask 3
    WriteMask 123
    Comp Never
    PassFront DecrSat
    PassBack IncrSat
    Fail IncrSat
    ZFail Invert
  }
}
Tags
{
  Queue BackGround
  RenderType Transparent
}
GrabPass
{

}
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
}