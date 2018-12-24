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
   * @brief Name�̃p�[�X
   */
  void CompileName(ShaderData* dest);

  /*!
   * @brief Property�̃p�[�X
   */
  void CompileProperty(ShaderData* dest);

  /*!
   * @brief Properties�̃p�[�X
   */
  void CompileProperties(ShaderData* dest);

  /*!
   * @brief Tag�̃p�[�X
   */
  void CompileTag(ShaderData* dest);

  /*!
   * @brief Tags�̃p�[�X
   */
  void CompileTags(ShaderData* dest);
  /*!
   * @brief Stencil�u���b�N�̃p�[�X
   */
  void CompileStencilData(StencilStateData* dest);

  /*!
   * @brief Pass�ɋL�q����Ă���v�f�̃p�[�X
   */
  void CompilePassData(HLSLCompiler* compiler, const ShaderData& data, PassData* dest);

  /*!
   * @brief Pass�̃p�[�X
   */
  void CompilePass(HLSLCompiler* compiler, ShaderData* dest, bool grab);

  /*!
   * @brief GrabPass�̃p�[�X
   */
  void CompileGrabPass(ShaderData* dest);

private:
  ShaderParser parser_;

};