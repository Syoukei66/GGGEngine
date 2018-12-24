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
   */
  void GetToken(TokenType type, bool skip_space = true);

  /*!
   * @brief 次のトークンを消費する。
   */
  void EatToken(bool skip_space = true);

  /*!
   * @brief ダブルクォーテーションで囲まれた文字列のパース
   */
  void ParseText(std::string* dest);

  /*!
   * @brief 識別子のパース
   */
  void ParseIdentifier(std::string* dest);

  /*!
   * @brief 特殊識別子のパース
   * テクスチャプロパティ指定で数値から始まる識別子(2D, 3D)に対応する必要が出てきた
   */
  void ParseSpecialIdentifier(std::string* dest);

  /*!
   * @brief 整数値のパース
   */
  void ParseInt(T_FLOAT* dest);

  /*!
   * @brief 実数値のパース
   */
  void ParseFloat(T_FLOAT* dest);

  /*!
   * @brief end_simbolで指定した文字列が出現するまでの文字をそのまま取得する。
   */
  void GetText(const std::string& end_simbol, std::string* dest);

private:
  /*!
   * @brief 文字カウントを進める
   */
  void NextChar();

  /*!
   * @brief 現在の文字を取得する
   */
  char GetChar();

  /*!
   * @brief 新しくパース処理単位が開始した事をパーサーに伝える
   */
  void BeginParse(bool skip_space = true);

public:
  /*!
   * @brief 例外を投げる
   */
  void ThrowError(const std::string& message);

  /*!
   * @brief 予期せぬ識別子検出時の例外を投げる
   */
  void ThrowIdentifierError(const std::string& type, const std::string& identifier);

  /*!
   * @brief 予期せぬトークン検出時の例外を投げる
   */
  void ThrowTokenError();

  /*!
   * @brief 予期せぬEOF検出時の例外を投げる
   */
  void ThrowEofError();

private:
  std::string str_;
  const char* p_;
  // 現在パースしている行
  T_UINT32 line_index_;
  // 現在トークンとして判定されている文字列の先頭と末尾のインデックス
  T_UINT32 char_index_begin_;
  T_UINT32 char_index_end_;

  ShaderLexer lexer_;
};