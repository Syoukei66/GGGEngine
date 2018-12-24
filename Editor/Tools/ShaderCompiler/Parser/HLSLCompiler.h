#pragma once

#include <Asset/Shader/Shader.h>

class HLSLCompiler
{
public:
  // プロパティから変数宣言のプログラムを追加
  // ビルトイン変数を追加
  // DX9世代ライクな書き方をDX11ライクな書き方に変換
  virtual void ConvertHLSL(const ShaderData& data, std::string* str) = 0;
  virtual void CompileVertexShader(const std::string& str, std::vector<unsigned char>* dest) = 0;
  virtual void CompilePixelShader(const std::string& str, std::vector<unsigned char>* dest) = 0;
};
