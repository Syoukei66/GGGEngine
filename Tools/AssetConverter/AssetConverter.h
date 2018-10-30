#pragma once

#include "IAssetConverter.h"
#include "AssetEntity.h"
#include "AssetImporter.h"
#include "AssetEditor.h"
#include "AssetExporter.h"
#include "AssetProgramGenerator.h"

template <class Entity_>
class AssetConverter : public IAssetConverter
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AssetConverter(
    AssetImporter<Entity_>* importer,
    AssetEditor<Entity_>* editor,
    AssetExporter<Entity_>* exporter,
    AssetProgramGenerator<Entity_>* program_generator
  );

  virtual ~AssetConverter();

  // =================================================================
  // Methods
  // =================================================================
public:
  inline T_UINT32 GetID() const override;

  inline bool Reserve(const URI& uri, AssetConverterContext* context) override;

  inline void Import(AssetConverterContext* context) override;
  inline bool ImportOnce(AssetConverterContext* context) override;
  inline Entity_* ImportImmediately(const URI& uri, AssetConverterContext* context);

  inline void AddEntity(Entity_* entity);
  inline Entity_* GetEntity(const URI& uri, const AssetConverterContext* context);
  inline Entity_* GetEntity(const AssetInfo* info);

  inline void Export(const AssetConverterContext* context) const override;

  inline void CreateHeaderProgram(std::string* dest) const override;
  inline void CreateCppProgram(std::string* dest) const override;

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::unordered_map<T_UINT32, Entity_*> entities_;
  AssetImporter<Entity_>* importer_;
  AssetEditor<Entity_>* editor_;
  //AssetViewer<Entity_>* viewer_;
  AssetExporter<Entity_>* exporter_;
  AssetProgramGenerator<Entity_>* program_generator_;

};

// =================================================================
// Constructor / Destructor
// =================================================================
template<class Entity_>
inline AssetConverter<Entity_>::AssetConverter(AssetImporter<Entity_>* importer, AssetEditor<Entity_>* editor, AssetExporter<Entity_>* exporter, AssetProgramGenerator<Entity_>* program_generator)
  : importer_(importer)
  , editor_(editor)
  , exporter_(exporter)
  , program_generator_(program_generator)
{}

template<class Entity_>
inline AssetConverter<Entity_>::~AssetConverter()
{
  for (auto& pair : this->entities_)
  {
    delete pair.second;
  }
  delete this->importer_;
  delete this->editor_;
  delete this->exporter_;
  delete this->program_generator_;
}

// =================================================================
// Methods
// =================================================================
template<class Entity_>
inline T_UINT32 AssetConverter<Entity_>::GetID() const
{
  return Entity_::ID;
}

template<class Entity_>
inline bool AssetConverter<Entity_>::Reserve(const URI& uri, AssetConverterContext* context)
{
  const auto& itr = this->entities_.find(context->GetUniqueID(uri));
  if (itr != this->entities_.end())
  {
    return true;
  }
  return this->importer_ ? this->importer_->Reserve(uri, context) : false;
}

template<class Entity_>
inline void AssetConverter<Entity_>::Import(AssetConverterContext* context)
{
  if (this->importer_) this->importer_->Import(&this->entities_, context);
}

template<class Entity_>
inline bool AssetConverter<Entity_>::ImportOnce(AssetConverterContext* context)
{
  return this->importer_ ? this->importer_->ImportOnce(&this->entities_, context) : false;
}

template<class Entity_>
inline Entity_* AssetConverter<Entity_>::ImportImmediately(const URI& uri, AssetConverterContext* context)
{
  const auto& itr = this->entities_.find(context->GetUniqueID(uri));
  if (itr != this->entities_.end())
  {
    return itr->second;
  }
  return this->importer_ ? this->importer_->ImportImmediately(uri, &this->entities_, context) : nullptr;
}

template<class Entity_>
inline void AssetConverter<Entity_>::AddEntity(Entity_* entity)
{
  this->entities_[entity->GetAssetInfo()->GetUniqueID()] = entity;
}

template<class Entity_>
inline Entity_* AssetConverter<Entity_>::GetEntity(const URI& uri, const AssetConverterContext* context)
{
  const auto& itr = this->entities_.find(context->GetUniqueID(uri));
  if (itr != this->entities_.end())
  {
    return itr->second;
  }
  return nullptr;
}

template<class Entity_>
inline Entity_* AssetConverter<Entity_>::GetEntity(const AssetInfo* info)
{
  const auto& itr = this->entities_.find(info->GetUniqueID());
  if (itr != this->entities_.end())
  {
    return itr->second;
  }
  return nullptr;
}

template<class Entity_>
inline void AssetConverter<Entity_>::Export(const AssetConverterContext* context) const
{
  this->exporter_->Export(this->entities_, context);
}

template<class Entity_>
inline void AssetConverter<Entity_>::CreateHeaderProgram(std::string* dest) const
{
  if (this->program_generator_) this->program_generator_->CreateHeaderProgram(this->entities_, dest);
}

template<class Entity_>
inline void AssetConverter<Entity_>::CreateCppProgram(std::string* dest) const
{
  if (this->program_generator_) this->program_generator_->CreateCppProgram(this->entities_, dest);
}
