#pragma once

#include "ShaderLexer.h"

struct ParseException
{
  ParseException(const std::string& message)
    : message(message)
  {}
  std::string message;
};

class ShaderParser
{
public:
  ShaderParser(const std::string& str);

public:
  /*!
   * @brief Lexer���猻�݂̕�����TokenType���擾����
   */
  TokenType GetTokenType();

  /*!
   * @brief �󔒂��X�L�b�v����
   */
  void SkipSpace();

  /*!
   * @brief ���̃g�[�N���̏����擾���邪�A�����|�C���^��ω������Ȃ�
   * @return ���̃g�[�N���̏��
   */
  TokenType CheckNextToken(bool skip_space = true);

  /*!
   * @brief �^���w�肵�ăg�[�N�����擾����B�g�[�N�����w�肵���^�ƈ������G���[
   * @param type �g�[�N���̌^
   */
  void GetToken(TokenType type, bool skip_space = true);

  /*!
   * @brief ���̃g�[�N���������B
   */
  void EatToken(bool skip_space = true);

  /*!
   * @brief �_�u���N�H�[�e�[�V�����ň͂܂ꂽ������̃p�[�X
   */
  void ParseText(std::string* dest);

  /*!
   * @brief ���ʎq�̃p�[�X
   */
  void ParseIdentifier(std::string* dest);

  /*!
   * @brief ���ꎯ�ʎq�̃p�[�X
   * �e�N�X�`���v���p�e�B�w��Ő��l����n�܂鎯�ʎq(2D, 3D)�ɑΉ�����K�v���o�Ă���
   */
  void ParseSpecialIdentifier(std::string* dest);

  /*!
   * @brief �����l�̃p�[�X
   */
  void ParseInt(T_FLOAT* dest);

  /*!
   * @brief �����l�̃p�[�X
   */
  void ParseFloat(T_FLOAT* dest);

  /*!
   * @brief end_simbol�Ŏw�肵�������񂪏o������܂ł̕��������̂܂܎擾����B
   */
  void GetText(const std::string& end_simbol, std::string* dest);

private:
  /*!
   * @brief �����J�E���g��i�߂�
   */
  void NextChar();

  /*!
   * @brief ���݂̕������擾����
   */
  char GetChar();

  /*!
   * @brief �V�����p�[�X�����P�ʂ��J�n���������p�[�T�[�ɓ`����
   */
  void BeginParse(bool skip_space = true);

public:
  /*!
   * @brief ��O�𓊂���
   */
  void ThrowError(const std::string& message);

  /*!
   * @brief �\�����ʎ��ʎq���o���̗�O�𓊂���
   */
  void ThrowIdentifierError(const std::string& type, const std::string& identifier);

  /*!
   * @brief �\�����ʃg�[�N�����o���̗�O�𓊂���
   */
  void ThrowTokenError();

  /*!
   * @brief �\������EOF���o���̗�O�𓊂���
   */
  void ThrowEofError();

private:
  std::string str_;
  const char* p_;
  // ���݃p�[�X���Ă���s
  T_UINT32 line_index_;
  // ���݃g�[�N���Ƃ��Ĕ��肳��Ă��镶����̐擪�Ɩ����̃C���f�b�N�X
  T_UINT32 char_index_begin_;
  T_UINT32 char_index_end_;

  ShaderLexer lexer_;
};