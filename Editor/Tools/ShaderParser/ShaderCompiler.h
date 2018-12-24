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
   * @return falseなら失敗
   */
  bool CompileName(ShaderData* dest);

  /*!
   * @brief Propertyのパース
   * @return falseなら失敗
   */
  bool CompileProperty(ShaderData* dest);

  /*!
   * @brief Propertiesのパース
   * @return falseなら失敗
   */
  bool CompileProperties(ShaderData* dest);

  /*!
   * @brief Tagのパース
   * @return falseなら失敗
   */
  bool CompileTag(ShaderData* dest);

  /*!
   * @brief Tagsのパース
   * @return falseなら失敗
   */
  bool CompileTags(ShaderData* dest);
  /*!
   * @brief Stencilブロックのパース
   * @return falseなら失敗
   */
  bool CompileStencilData(StencilStateData* dest);

  /*!
   * @brief Passに記述されている要素のパース
   * @return falseなら失敗
   */
  bool CompilePassData(HLSLCompiler* compiler, const ShaderData& data, PassData* dest);

  /*!
   * @brief Passのパース
   * @return falseなら失敗
   */
  bool CompilePass(HLSLCompiler* compiler, ShaderData* dest, bool grab);

  /*!
   * @brief GrabPassのパース
   * @return falseなら失敗
   */
  bool CompileGrabPass(ShaderData* dest);

private:
  ShaderParser parser_;

};