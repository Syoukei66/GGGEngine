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
//  //�ʏ�̓ǂݎ�菈��
//  for (const char& c : line)
//  {
//    this->stack_.push_back(c);
//    //�R�����g�Ȃ�s���ƃX�L�b�v
//    if (this->stack_ == "//")
//    {
//      this->stack_.clear();
//      return;
//    }
//    //�󔒂̓g�[�N���̏I����\���B�󔒂������O�ɐH�ׂ��Ȃ������g�[�N���͖���
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
