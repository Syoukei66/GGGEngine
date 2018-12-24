#pragma once

#include "BaseParser.h"
#include "ShaderToken.h"

#define SHADER_TOKEN_PARSER(Name)\
T_INT32 Parse##Name()\
{\
  std::string token;\
  this->ParseIdentifier(&token);\
  for (T_FIXED_UINT8 i = 0; i < static_cast<T_FIXED_UINT8>(Shader::##Name##::DATANUM); ++i)\
  {\
    if (token == GGGShaderParser::Name##Tokens[i])\
    {\
      return i;\
    }\
  }\
  this->ThrowIdentifierError(#Name, token);\
  return -1;\
}\
\
T_INT32 Parse##Name(const std::string& token)\
{\
  for (T_FIXED_UINT8 i = 0; i < static_cast<T_FIXED_UINT8>(Shader::##Name##::DATANUM); ++i)\
  {\
    if (token == GGGShaderParser::Name##Tokens[i])\
    {\
      return i;\
    }\
  }\
  this->ThrowIdentifierError(#Name, token);\
  return -1;\
}

class ShaderParser : public BaseParser
{
public:
  ShaderParser(const std::string& str)
    : BaseParser(str)
  {}

public:
  SHADER_TOKEN_PARSER(BuiltinVariable);
  SHADER_TOKEN_PARSER(LightMode);
  SHADER_TOKEN_PARSER(CullMode);
  SHADER_TOKEN_PARSER(ZWrite);
  SHADER_TOKEN_PARSER(ComparasionFunc);
  SHADER_TOKEN_PARSER(BlendFactor);
  SHADER_TOKEN_PARSER(BlendOp);
  SHADER_TOKEN_PARSER(StencilOperation);
  SHADER_TOKEN_PARSER(VariableType);
  SHADER_TOKEN_PARSER(ColorType);
  SHADER_TOKEN_PARSER(SamplerType);
  SHADER_TOKEN_PARSER(DefaultTextureType);
  SHADER_TOKEN_PARSER(RenderQueue);
  SHADER_TOKEN_PARSER(RenderType);
};

