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
   * @return false�Ȃ玸�s
   */
  bool CompileName(ShaderData* dest);

  /*!
   * @brief Property�̃p�[�X
   * @return false�Ȃ玸�s
   */
  bool CompileProperty(ShaderData* dest);

  /*!
   * @brief Properties�̃p�[�X
   * @return false�Ȃ玸�s
   */
  bool CompileProperties(ShaderData* dest);

  /*!
   * @brief Tag�̃p�[�X
   * @return false�Ȃ玸�s
   */
  bool CompileTag(ShaderData* dest);

  /*!
   * @brief Tags�̃p�[�X
   * @return false�Ȃ玸�s
   */
  bool CompileTags(ShaderData* dest);
  /*!
   * @brief Stencil�u���b�N�̃p�[�X
   * @return false�Ȃ玸�s
   */
  bool CompileStencilData(StencilStateData* dest);

  /*!
   * @brief Pass�ɋL�q����Ă���v�f�̃p�[�X
   * @return false�Ȃ玸�s
   */
  bool CompilePassData(HLSLCompiler* compiler, const ShaderData& data, PassData* dest);

  /*!
   * @brief Pass�̃p�[�X
   * @return false�Ȃ玸�s
   */
  bool CompilePass(HLSLCompiler* compiler, ShaderData* dest, bool grab);

  /*!
   * @brief GrabPass�̃p�[�X
   * @return false�Ȃ玸�s
   */
  bool CompileGrabPass(ShaderData* dest);

private:
  ShaderParser parser_;

};