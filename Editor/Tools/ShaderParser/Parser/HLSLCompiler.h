#pragma once

#include <Asset/Shader/Shader.h>

class HLSLCompiler
{
public:
  // �v���p�e�B����ϐ��錾�̃v���O������ǉ�
  // �r���g�C���ϐ���ǉ�
  // DX9���ド�C�N�ȏ�������DX11���C�N�ȏ������ɕϊ�
  virtual void ConvertHLSL(const ShaderData& data, std::string* str) = 0;
  virtual void CompileVertexShader(const std::string& str, std::vector<unsigned char>* dest) = 0;
  virtual void CompilePixelShader(const std::string& str, std::vector<unsigned char>* dest) = 0;
};
