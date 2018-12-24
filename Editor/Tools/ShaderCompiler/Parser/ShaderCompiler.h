#pragma once

#include <Asset/Shader/Shader.h>
#include "HLSLCompiler.h"
#include "ShaderParser.h"

class ShaderCompiler
{
public:
  ShaderCompiler(const std::string& str);

public:
  void Compile(HLSLCompiler* compiler, ShaderData* dest);

private:
  /*!
   * @brief Nameのパース
   */
  void CompileName(ShaderData* dest);

  /*!
   * @brief Propertyのパース
   */
  void CompileProperty(ShaderData* dest);

  /*!
   * @brief Propertiesのパース
   */
  void CompileProperties(ShaderData* dest);

  /*!
   * @brief Tagのパース
   */
  void CompileTag(ShaderData* dest);

  /*!
   * @brief Tagsのパース
   */
  void CompileTags(ShaderData* dest);
  /*!
   * @brief Stencilブロックのパース
   */
  void CompileStencilData(StencilStateData* dest);

  /*!
   * @brief Passに記述されている要素のパース
   */
  void CompilePassData(HLSLCompiler* compiler, const ShaderData& data, PassData* dest);

  /*!
   * @brief Passのパース
   */
  void CompilePass(HLSLCompiler* compiler, ShaderData* dest, bool grab);

  /*!
   * @brief GrabPassのパース
   */
  void CompileGrabPass(ShaderData* dest);

private:
  ShaderParser parser_;

};