#pragma once

#include <Asset/Shader/Shader.h>

struct HLSLCompileException
{
  HLSLCompileException(const char* shader_name, const char* message)
    : shader_name(shader_name)
    , message(message)
    , line(0)
  {}
  std::string shader_name;
  std::string message;
  T_UINT32 line;
};

class HLSLCompiler
{
public:
  HLSLCompiler(const std::string& input_directory_path);

public:
  // プロパティから変数宣言のプログラムを追加
  // ビルトイン変数を追加
  // DX9世代ライクな書き方をDX11ライクな書き方に変換
  void ConvertHLSL(const ShaderData& data, std::string* str);
  void CompileVertexShader(const std::string& str, std::vector<unsigned char>* dest);
  void CompilePixelShader(const std::string& str, std::vector<unsigned char>* dest);

private:
  std::string input_directory_path_;

};
