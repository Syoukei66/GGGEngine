struct appdata
{
  float4 vertex : POSITION;
};

struct v2f
{
  float4 vertex : SV_POSITION;
};

float4x4 _WorldViewProj;
float4 _Diffuse = float4(1.0f, 1.0f, 1.0f, 1.0f);

v2f vert(appdata v)
{
  v2f o;
  o.vertex = mul(v.vertex, _WorldViewProj);
  return o;
}

float4 frag0(v2f i) : SV_TARGET
{
  return float4(1.0f, 0.0f, 0.0f, 0.5f);
}

float4 frag1(v2f i) : SV_TARGET
{
  return float4(0.0f, 1.0f, 0.0f, 0.5f);
}

technique Default
{
  pass
  {
    AlphaBlendEnable = FALSE;
    ShadeMode = FLAT;
    ZWriteEnable = FALSE;
    ZEnable = TRUE;
    StencilEnable = TRUE;
    ColorWriteEnable = 0;
    StencilFunc = ALWAYS;
    StencilPass = Incr;
    StencilRef = 1;
    CullMode = CCW;

    //AlphaBlendEnable = TRUE;
    //BlendOp = ADD;
    //SrcBlend = SRCALPHA;
    //DestBlend = INVSRCALPHA;
    //ShadeMode = FLAT;
    //CullMode = CCW;
    vertexshader = compile vs_3_0 vert();   
    pixelshader = NULL;

    //pixelshader = compile ps_3_0 frag0();
  }

  pass
  {
    AlphaBlendEnable = FALSE;
    ShadeMode = FLAT;
    ZWriteEnable = FALSE;
    ZEnable = TRUE;
    StencilEnable = TRUE;
    ColorWriteEnable = 0;
    StencilFunc = ALWAYS;
    StencilPass = Decr;
    StencilRef = 1;
    CullMode = CW;

    //AlphaBlendEnable = TRUE;
    //BlendOp = ADD;
    //SrcBlend = SRCALPHA;
    //DestBlend = INVSRCALPHA;
    //ShadeMode = FLAT;
    //ZEnable = TRUE;
    //ZWriteEnable = TRUE;
    //StencilEnable = FALSE;
    //CullMode = CW;
    //ColorWriteEnable = 0xf;
    vertexshader = compile vs_3_0 vert();
    pixelshader = NULL;

   // pixelshader = compile ps_3_0 frag1();
  }
}
