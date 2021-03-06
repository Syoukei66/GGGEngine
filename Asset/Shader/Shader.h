#pragma once

#include <Core/Application/Platform/API/_Resource/PixelShader.h>
#include <Core/Application/Platform/API/_Resource/VertexShader.h>
#include <Core/Application/Platform/API/_Resource/RenderState.h>

/*!
 * @brief シェーダー内のスカラープロパティ
 */
struct ScalaPropertyData
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(ScalaPropertyData)
  {
    archive(name_);
    archive(display_name_);
    archive(index_);
    archive(variable_type_);
    archive(min_value_);
    archive(max_value_);
    archive(init_value_);
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ScalaPropertyData()
    : name_("scala")
    , display_name_("scala")
    , index_()
    , variable_type_(static_cast<T_FIXED_UINT8>(Shader::VariableType::kFloat))
    , min_value_(Limit::T_FLOAT_MIN)
    , max_value_(Limit::T_FLOAT_MAX)
    , init_value_(0.0f)
  {}

  // =================================================================
  // Data Member
  // =================================================================
public:
  std::string name_;
  std::string display_name_;
  T_FIXED_UINT8 index_;
  T_FIXED_UINT8 variable_type_; // VariableType
  T_FIXED_FLOAT min_value_;
  T_FIXED_FLOAT max_value_;
  T_FIXED_FLOAT init_value_;
};

/*!
 * @brief シェーダー内のベクトルプロパティ
 */
struct VectorPropertyData
{ 
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(VectorPropertyData)
  {
    archive(name_);
    archive(display_name_);
    archive(index_);
    archive(variable_type_);
    archive(init_value0_);
    archive(init_value1_);
    archive(init_value2_);
    archive(init_value3_);
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  VectorPropertyData()
    : name_("vector")
    , display_name_("vector")
    , index_()
    , variable_type_(static_cast<T_FIXED_UINT8>(Shader::VariableType::kFloat))
    , init_value0_(0.0f)
    , init_value1_(0.0f)
    , init_value2_(0.0f)
    , init_value3_(0.0f)
  {}

  // =================================================================
  // Data Member
  // =================================================================
public:
  std::string name_;
  std::string display_name_;
  T_FIXED_UINT8 index_;
  T_FIXED_UINT8 variable_type_; // VariableType
  T_FIXED_FLOAT init_value0_;
  T_FIXED_FLOAT init_value1_;
  T_FIXED_FLOAT init_value2_;
  T_FIXED_FLOAT init_value3_;
};

/*!
 * @brief シェーダー内のカラープロパティ
 */
struct ColorPropertyData
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(ColorPropertyData)
  {
    archive(name_);
    archive(display_name_);
    archive(index_);
    archive(init_r_);
    archive(init_g_);
    archive(init_b_);
    archive(init_a_);
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ColorPropertyData()
    : name_("color")
    , display_name_("color")
    , index_()
    , init_r_(1.0f)
    , init_g_(1.0f)
    , init_b_(1.0f)
    , init_a_(1.0f)
  {}

  // =================================================================
  // Data Member
  // =================================================================
public:
  std::string name_;
  std::string display_name_;
  T_FIXED_UINT8 index_;
  T_FIXED_FLOAT init_r_;
  T_FIXED_FLOAT init_g_;
  T_FIXED_FLOAT init_b_;
  T_FIXED_FLOAT init_a_;
};

/*!
 * @brief シェーダー内のサンプラープロパティ
 */
struct SamplerPropertyData
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(SamplerPropertyData)
  {
    archive(name_);
    archive(display_name_);
    archive(index_);
    archive(sampler_type_);
    archive(default_texture_);
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  SamplerPropertyData()
    : name_("sampler")
    , display_name_("sampler")
    , index_()
    , sampler_type_(static_cast<T_FIXED_UINT8>(Shader::SamplerType::kSampler2D))
    , default_texture_(static_cast<T_FIXED_UINT8>(Shader::DefaultTextureType::kWhite))
  {}

  // =================================================================
  // Data Member
  // =================================================================
public:
  std::string name_;
  std::string display_name_;
  T_FIXED_UINT8 index_;
  T_FIXED_UINT8 sampler_type_; // SamplerType
  T_FIXED_UINT8 default_texture_; // DefaultTextureType
};

/*!
 * @brief シェーダー内のパスデータ
 */
struct PassData
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(PassData)
  {
    archive(grab_);
    archive(light_mode_);
    archive(render_state_data_);
    archive(vs_byte_code_);
    archive(ps_byte_code_);
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  PassData()
    : grab_(false)
    , light_mode_(static_cast<T_FIXED_UINT8>(Shader::LightMode::kAlways))
    , render_state_data_()
    , vs_byte_code_()
    , ps_byte_code_()
  {}

  // =================================================================
  // Data Member
  // =================================================================
public:
  bool grab_;
  T_FIXED_UINT8 light_mode_; // LightMode
  RenderStateData render_state_data_;
  std::vector<unsigned char> vs_byte_code_;
  std::vector<unsigned char> ps_byte_code_;
};

/*!
 * @brief シェーダーが持つプロパティのデータ
 */
struct ShaderPropertyData
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(ShaderPropertyData)
  {
    archive(buffer_size_);
    archive(scala_properties_);
    archive(vector_properties_);
    archive(color_properties_);
    archive(sampler_properties_);
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ShaderPropertyData()
    : buffer_size_()
    , scala_properties_()
    , vector_properties_()
    , color_properties_()
    , sampler_properties_()
  {}

  // =================================================================
  // Method
  // =================================================================
public:
  void AddBufferSize(T_UINT32 value)
  {
    this->buffer_size_ = Shader::AlignmentBufferBegin(this->buffer_size_, value) + value;
  }

  void AlignmentBufferSize()
  {
    this->buffer_size_ = Shader::AlignmentBufferSize(this->buffer_size_);
  }

  // =================================================================
  // Data Member
  // =================================================================
public:
  T_FIXED_UINT32 buffer_size_; // ConstantBufferに必要なサイズ
  std::vector<ScalaPropertyData> scala_properties_;
  std::vector<VectorPropertyData> vector_properties_;
  std::vector<ColorPropertyData> color_properties_;
  std::vector<SamplerPropertyData> sampler_properties_;
};

/*!
 * @brief シェーダーのパスデータ
 */
struct ShaderData
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(ShaderData)
  {
    archive(name_);
    archive(queue_);
    archive(render_type_);
    archive(properties_);
    archive(passes_);
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ShaderData()
    : name_("shader")
    , queue_(static_cast<T_UINT8>(Shader::RenderQueue::kGeometry))
    , render_type_(static_cast<T_UINT8>(Shader::RenderType::kOpaque))
    , properties_()
    , passes_()
  {}

  // =================================================================
  // Data Member
  // =================================================================
public:
  std::string name_;

  T_FIXED_UINT8 queue_; // RenderQueue
  T_FIXED_UINT8 render_type_; // RenderType

  ShaderPropertyData properties_;
  std::vector<PassData> passes_;
};

/*!
 * @brief シェーダークラス
 */
class rcShader : public GGAssetObject
{
public:
  struct Pass
  {
    bool grab_;
    T_FIXED_UINT8 light_mode_; // LightMode

    SharedRef<rcRenderState> render_state;
    SharedRef<rcVertexShader> vertex_shader;
    SharedRef<rcPixelShader> pixel_shader;
  };

  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcShader);
  GG_ASSET(rcShader, ShaderData);

  // =================================================================
  // Method 
  // =================================================================
public:
  bool BeginPass(T_UINT8 path_id, const SharedRef<const rcVertexDeclaration>& declaration) const;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE const std::string& GetShaderName() const
  {
    return this->name_;
  }
  GG_INLINE Graphics::RenderQueue GetRenderQueue() const
  {
    return this->queue_;
  }
  GG_INLINE const ShaderPropertyData& GetPropertyData() const
  {
    return this->properties_;
  }
  GG_INLINE const std::vector<ScalaPropertyData>& GetScalaPropertyDatas() const
  {
    return this->properties_.scala_properties_;
  }
  GG_INLINE const std::vector<VectorPropertyData>& GetVectorPropertyDatas() const
  {
    return this->properties_.vector_properties_;
  }
  GG_INLINE const std::vector<ColorPropertyData>& GetColorPropertyDatas() const
  {
    return this->properties_.color_properties_;
  }
  GG_INLINE const std::vector<SamplerPropertyData>& GetSamplerPropertyDatas() const
  {
    return this->properties_.sampler_properties_;
  }
  GG_INLINE T_UINT32 GetBufferSize() const
  {
    return this->properties_.buffer_size_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  std::string name_;

  Graphics::RenderQueue queue_;
  Shader::RenderType render_type_; // RenderType

  ShaderPropertyData properties_;
  std::unordered_map<T_FIXED_UINT8, Pass> passes_;
};
