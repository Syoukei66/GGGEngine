#pragma once

#include "ShaderLexer.h"

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
   * @return type�ŗ^�����g�[�N���̌^���Ⴄ�ꍇfalse
   */
  bool GetToken(TokenType type, bool skip_space = true);

  /*!
   * @brief ���̃g�[�N���������B
   * @return EOF���o�������ꍇfalse
   */
  bool EatToken(bool skip_space = true);

  /*!
   * @brief �_�u���N�H�[�e�[�V�����ň͂܂ꂽ������̃p�[�X
   * @return false�Ȃ玸�s
   */
  bool ParseText(std::string* dest);

  /*!
   * @brief ���ʎq�̃p�[�X
   * @return false�Ȃ玸�s
   */
  bool ParseIdentifier(std::string* dest);

  /*!
   * @brief ���ꎯ�ʎq�̃p�[�X
   * �e�N�X�`���v���p�e�B�w��Ő��l����n�܂鎯�ʎq(2D, 3D)�ɑΉ�����K�v���o�Ă���
   * @return false�Ȃ玸�s
   */
  bool ParseSpecialIdentifier(std::string* dest);

  /*!
   * @brief �����l�̃p�[�X
   * @return false�Ȃ玸�s
   */
  bool ParseInt(T_FLOAT* dest);

  /*!
   * @brief �����l�̃p�[�X
   * @return false�Ȃ玸�s
   */
  bool ParseFloat(T_FLOAT* dest);

  /*!
   * @brief end_simbol�Ŏw�肵�������񂪏o������܂ł̕��������̂܂܎擾����B
   * @return false�Ȃ玸�s
   */
  bool GetText(const std::string& end_simbol, std::string* dest);


private:
  std::string str_;
  const char* p_;

  ShaderLexer lexer_;

};