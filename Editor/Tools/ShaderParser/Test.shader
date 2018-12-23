Shader "TestShader"
Properties
{
  _TestRange  ("range value", Range(0.0, 1.0)) = 0.0
  _TestFloat  ("float value", Float) = 1.0
  _TestInt    ("int value", Int) = 12345
  _TestColor("Color value", Color) = {1.0, 1.0, 1.0, 1.0}
  _TestVector("Vector value", Vector) = {}
  _Test2D     ("Texture value", 2D) = "white"
}
Tags
{
  Queue BackGround
  RenderType Transparent
}
Pass
{

}