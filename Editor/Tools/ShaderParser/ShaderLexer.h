#pragma once

enum class TokenType : T_UINT8
{
  kNoExcepted,
  kEOF,
  kSpace,
  kEnter,
  kBlockBegin,
  kBlockEnd,
  kParenBegin,
  kParenEnd,
  kTextParen,
  kComma,
  kEqual,
  kAlphabet,
  kNumber,
  kUnderBar,
  kDot,
  kPlus,
  kMinus,
};

class ShaderLexer
{
public:
  TokenType GetTokenType(const char c);

};