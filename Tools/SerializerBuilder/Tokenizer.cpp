//#include "Tokenizer.h"
//
//// =================================================================
//// Constructor / Destructor
//// =================================================================
//Tokenizer::Tokenizer()
//  : stack_()
//{
//  this->context_ = new ParserContext();
//}
//
//Tokenizer::~Tokenizer()
//{
//  delete this->context_;
//}
//
//// =================================================================
//// Methods
//// =================================================================
//void Tokenizer::ParseLine(const std::string & line)
//{
//  //通常の読み取り処理
//  for (const char& c : line)
//  {
//    this->stack_.push_back(c);
//    //コメントなら行ごとスキップ
//    if (this->stack_ == "//")
//    {
//      this->stack_.clear();
//      return;
//    }
//    //空白はトークンの終了を表す。空白が現れる前に食べられなかったトークンは無視
//    if (this->IsSpace(c))
//    {
//      this->stack_.clear();
//      continue;
//    }
//    if (this->context_->CurrentParser()->Eat(this->stack_, this->context_))
//    {
//      this->stack_.clear();
//      continue;
//    }
//  }
//}
