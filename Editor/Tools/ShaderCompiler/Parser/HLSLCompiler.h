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
  // �v���p�e�B����ϐ��錾�̃v���O������ǉ�
  // �r���g�C���ϐ���ǉ�
  // DX9���ド�C�N�ȏ�������DX11���C�N�ȏ������ɕϊ�
  void ConvertHLSL(const ShaderData& data, std::string* str);
  void CompileVertexShader(const std::string& str, std::vector<unsigned char>* dest);
  void CompilePixelShader(const std::string& str, std::vector<unsigned char>* dest);

private:
  std::string input_directory_path_;

};
