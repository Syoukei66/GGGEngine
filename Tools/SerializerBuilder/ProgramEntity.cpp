//#include "ProgramEntity.h"
//
//#include <fstream>
//
//class Block
//{
//public:
//  Block(Block* parent_)
//    : stack_()
//    , identifiers_()
//    , parent_(parent_)
//    , children_()
//  {
//    parent_->children_.push_back(this);
//  }
//
//  ~Block()
//  {
//    for (Block* child : this->children_)
//    {
//      delete child;
//    }
//  }
//
//  bool IsSpace(const char& c)
//  {
//    return c == ' ' || c == '\t' || c == '\n';
//  }
//
//  void AddChar(const char& c)
//  {
//    if (IsSpace(c))
//    {
//      if (this->stack_ == )
//      {
//
//      }
//      identifiers_.push_back(stack_);
//      stack_.clear();
//    }
//    this->stack_.push_back(c);
//  }
//
//private:
//  std::string stack_;
//  std::vector<std::string> identifiers_;
//  Block* parent_;
//  std::vector<Block*> children_;
//
//};
//
//
//ProgramEntity* ProgramEntity::Create(const std::string& path)
//{
//  std::ifstream ifs(path);
//  std::string str;
//  while (getline(ifs, str))
//  {
//    const char& head = str[0];
//    if (head == '\n')
//    {
//      continue;
//    }
//
//  }
//
//
//  Block* root = new Block(nullptr);
//  Block* current = root;
//  for (const char& c : text)
//  {
//    if (c == '{')
//    {
//      current = new Block(current);
//    }
//    if (c == '}')
//    {
//      current = current->parent_;
//    }
//    current->AddChar(c);
//  }
//
//  return nullptr;
//}
//
//ProgramEntity::ProgramEntity(const std::string& text)
//{
//
//}
//
//ProgramEntity::~ProgramEntity()
//{
//}
//
//void ProgramEntity::ParseBlock(std::string text)
//{
//}
//
//void ProgramEntity::ParseType()
//{
//}
