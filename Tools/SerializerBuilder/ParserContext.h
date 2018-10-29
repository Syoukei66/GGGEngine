#pragma once

class Parser;
class TypeEntity;

class ParserContext
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ParserContext(Parser* root);
  ~ParserContext();

  // =================================================================
  // Methods
  // =================================================================
public:
  void PushParser(Parser* parser);
  void PopParser();

  GG_INLINE void AddSerializableType(const TypeEntity& entity)
  {
    this->serializable_types_.emplace_back(entity);
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE Parser* CurrentParser()
  {
    return this->current_;
  }

  // =================================================================
  // Data Members
  // =================================================================
public:
  Parser* root_;
  Parser* current_;

  std::vector<TypeEntity> serializable_types_;

};