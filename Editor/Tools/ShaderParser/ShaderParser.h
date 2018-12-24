#pragma once

#include "ShaderLexer.h"

class ShaderParser
{
public:
  ShaderParser(const std::string& str);

public:
  /*!
   * @brief Lexerから現在の文字のTokenTypeを取得する
   */
  TokenType GetTokenType();

  /*!
   * @brief 空白をスキップする
   */
  void SkipSpace();

  /*!
   * @brief 次のトークンの情報を取得するが、文字ポインタを変化させない
   * @return 次のトークンの情報
   */
  TokenType CheckNextToken(bool skip_space = true);

  /*!
   * @brief 型を指定してトークンを取得する。トークンが指定した型と違ったらエラー
   * @param type トークンの型
   * @return typeで与えたトークンの型が違う場合false
   */
  bool GetToken(TokenType type, bool skip_space = true);

  /*!
   * @brief 次のトークンを消費する。
   * @return EOFが出現した場合false
   */
  bool EatToken(bool skip_space = true);

  /*!
   * @brief ダブルクォーテーションで囲まれた文字列のパース
   * @return falseなら失敗
   */
  bool ParseText(std::string* dest);

  /*!
   * @brief 識別子のパース
   * @return falseなら失敗
   */
  bool ParseIdentifier(std::string* dest);

  /*!
   * @brief 特殊識別子のパース
   * テクスチャプロパティ指定で数値から始まる識別子(2D, 3D)に対応する必要が出てきた
   * @return falseなら失敗
   */
  bool ParseSpecialIdentifier(std::string* dest);

  /*!
   * @brief 整数値のパース
   * @return falseなら失敗
   */
  bool ParseInt(T_FLOAT* dest);

  /*!
   * @brief 実数値のパース
   * @return falseなら失敗
   */
  bool ParseFloat(T_FLOAT* dest);

  /*!
   * @brief end_simbolで指定した文字列が出現するまでの文字をそのまま取得する。
   * @return falseなら失敗
   */
  bool GetText(const std::string& end_simbol, std::string* dest);


private:
  std::string str_;
  const char* p_;

  ShaderLexer lexer_;

};