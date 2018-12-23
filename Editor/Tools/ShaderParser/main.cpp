#include <stdio.h>
#include <Windows.h>

#include "GGGShaderCompiler.h"
#include "ShaderToken.h"

class TestCompiler : public IHLSLCompiler
{
public:
  virtual void ConvertHLSL(const ShaderData& data, std::string* str) override
  {

  }
  virtual void CompileVertexShader(const std::string& str, std::vector<unsigned char>* dest) override
  {
    Log::Info(str.c_str());
  }
  virtual void CompilePixelShader(const std::string& str, std::vector<unsigned char>* dest) override
  {
    Log::Info(str.c_str());
  }
};

std::string ToString(const ScalaPropertyData& data)
{
  using namespace GGGShaderParser;
  std::string ret = std::string();
  ret.append(VariableTypeTokens[data.variable_type_] + " " + data.name_ + " = " + std::to_string(data.init_value_));
  std::string min_value = "";
  std::string max_value = "";
  if (data.min_value_ != Limit::T_FLOAT_MIN && data.min_value_ != Limit::T_INT32_MIN)
  {
    min_value = std::to_string(data.min_value_);
  }
  if (data.max_value_ != Limit::T_FLOAT_MAX && data.max_value_ != Limit::T_INT32_MAX)
  {
    max_value = std::to_string(data.max_value_);
  }
  std::string limit = "";
  if (min_value.size() > 0 || max_value.size() > 0)
  {
    limit = " (" + min_value + " Å` " + max_value + ")";
  }
  ret.append(" // " + data.display_name_ + limit);
  return ret;
}
std::string ToString(const VectorPropertyData& data)
{
  using namespace GGGShaderParser;
  std::string ret = std::string();
  ret.append(VariableTypeTokens[data.variable_type_] + " " + data.name_ + " = {" + std::to_string(data.init_value0_) + "," + std::to_string(data.init_value1_) + "," + std::to_string(data.init_value2_) + "," + std::to_string(data.init_value3_) + "}");
  ret.append(" // " + data.display_name_);
  return ret;
}
std::string ToString(const ColorPropertyData& data)
{
  using namespace GGGShaderParser;
  std::string ret = std::string();
  ret.append("Color " + data.name_ + " = {" + std::to_string(data.init_r_) + "," + std::to_string(data.init_g_) + "," + std::to_string(data.init_b_) + "," + std::to_string(data.init_a_) + "}");
  ret.append(" // " + data.display_name_);
  return ret;
}
std::string ToString(const SamplerPropertyData& data)
{
  using namespace GGGShaderParser;
  std::string ret = std::string();
  ret.append(SamplerTypeTokens[data.sampler_type_] + " " + data.name_ + " = " + DefaultTextureTypeTokens[data.default_texture_]);
  ret.append(" // " + data.display_name_);
  return ret;
}

std::string ToString(const RenderStateData& data)
{
  using namespace GGGShaderParser;
  std::string ret = std::string();
  ret.append("    RenderState{\n");
  ret.append("      CullMode " + CullModeTokens[data.cull_mode_] + "\n");
  ret.append("      ZWrite "   + ZWriteTokens[data.z_write_] + "\n");
  ret.append("      ZTest "    + ComparasionFuncTokens[data.z_test_] + "\n");
  for (T_UINT8 i = 0; i < data.blend_state_datas_.size(); ++i)
  {
    const BlendStateData& bdata = data.blend_state_datas_[i];
    ret.append("      RT" + std::to_string(i));
    if (bdata.enabled_)
    {
      ret.append(
        " ColorBlend(" +
          BlendFactorTokens[bdata.blend_color_src_factor_] + " " + BlendOpTokens[bdata.blend_color_op_] + " " + BlendFactorTokens[bdata.blend_color_dst_factor_] +
        ")" +
        " AlphaBlend(" + 
          BlendFactorTokens[bdata.blend_alpha_src_factor_] + " " + BlendOpTokens[bdata.blend_alpha_op_] + " " + BlendFactorTokens[bdata.blend_alpha_dst_factor_] +
        ")\n");
    }
    else
    {
      ret.append(" No Blend\n");
    }
  }
  if (data.stencil_state_data_.enabled_)
  {
    const StencilStateData& sdata = data.stencil_state_data_;
    ret.append("      Stencil{\n");
    ret.append("        Ref " + std::to_string(sdata.stencil_ref_) + "\n");
    ret.append("        ReadMask " + std::to_string(sdata.stencil_read_mask_) + "\n");
    ret.append("        WriteMask " + std::to_string(sdata.stencil_write_mask_) + "\n");
    ret.append("        Front{\n");
    ret.append("          Comp " + ComparasionFuncTokens[sdata.stencil_comp_front_] + "\n");
    ret.append("          Pass " + StencilOperationTokens[sdata.stencil_pass_front_] + "\n");
    ret.append("          Fail " + StencilOperationTokens[sdata.stencil_fail_front_] + "\n");
    ret.append("          ZFail " + StencilOperationTokens[sdata.stencil_zfail_front_] + "\n");
    ret.append("        }\n");
    ret.append("        Back{\n");
    ret.append("          Comp " + ComparasionFuncTokens[sdata.stencil_comp_back_] + "\n");
    ret.append("          Pass " + StencilOperationTokens[sdata.stencil_pass_back_] + "\n");
    ret.append("          Fail " + StencilOperationTokens[sdata.stencil_fail_back_] + "\n");
    ret.append("          ZFail " + StencilOperationTokens[sdata.stencil_zfail_back_] + "\n");
    ret.append("        }\n");
    ret.append("      }\n");
  }
  ret.append("    }\n");
  return ret;
}

std::string ToString(const PassData& data)
{
  using namespace GGGShaderParser;
  std::string ret = std::string();
  ret.append("  Pass " + LightModeTokens[data.light_mode_ ]+ "{\n");
  ret.append("    Grab " + std::to_string(data.grab_) + "\n");
  ret.append("    VS_Size " + std::to_string(data.vs_byte_code_.size()) + "\n");
  ret.append("    PS_Size " + std::to_string(data.ps_byte_code_.size()) + "\n");
  ret.append(ToString(data.render_state_data_));
  ret.append("  }\n");
  return ret;
}

std::string ToString(const ShaderData& data)
{
  using namespace GGGShaderParser;
  std::string ret = std::string();
  ret.append("name : "        + data.name_  + "\n");
  ret.append("queue : "       + RenderQueueTokens[data.queue_] + "\n");
  ret.append("render_type : " + RenderTypeTokens[data.render_type_] + "\n");
  ret.append("properties : [\n" );
  for (const ScalaPropertyData& prop : data.scala_properties_)
  {
    ret.append("  " + ToString(prop) + "\n");
  }
  for (const VectorPropertyData& prop : data.vector_properties_)
  {
    ret.append("  " + ToString(prop) + "\n");
  }
  for (const ColorPropertyData& prop : data.color_properties_)
  {
    ret.append("  " + ToString(prop) + "\n");
  }
  for (const SamplerPropertyData& prop : data.sampler_properties_)
  {
    ret.append("  " + ToString(prop) + "\n");
  }
  ret.append("]\n");
  ret.append("passes : [\n");
  for (const PassData& pass : data.passes_)
  {
    ret.append(ToString(pass) + "\n");
  }
  ret.append("]\n");
  return ret;
}

int main()
{
  TestCompiler test = TestCompiler();
  GGGShaderCompiler compiler = GGGShaderCompiler();
  std::string str = FileUtil::TextFile_Read("Test.shader");
  ShaderData data = ShaderData();
  compiler.Parse(str, &test, &data);
  printf(ToString(data).c_str());
  printf("\nèIóπÇ∑ÇÈÇ…ÇÕâΩÇ©ÉLÅ[ÇâüÇµÇƒÇ≠ÇæÇ≥Ç¢");
  getchar();
  return 0;
}

void Log::Out(Level level, const char* message)
{
  std::string str = message;
  OutputDebugString((str + "\n").c_str());
}