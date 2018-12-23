#pragma once

#include <Asset/Shader/Shader.h>
#include "HLSLCompiler.h"

class ShaderCompiler
{
public:
  void Parse(const std::string& str, HLSLCompiler* compiler, ShaderData* dest);

};