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

  ~AssetConverter();

  // =================================================================
  // Methods
  // =================================================================
public:
  inline T_UINT32 GetID() const override;

  inline AssetInfo* Reserve(const std::string& directory_path, const std::string& file_name, const std::string& extension, AssetConverterContext* context) override;

  inline void Import(AssetConverterContext* context) override;

  inline bool ImportOnce(AssetConverterContext* context) override;

  inline Entity_* ImportImmediately(const std::string& directory_path, const std::string& file_name, const std::string& extension, AssetConverterContext* context);

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
  delete this->importer;
  delete this->editor_;
  delete this->exporter_;
  delete this->program_generator_;
}

template<class Entity_>
inline T_UINT32 AssetConverter<Entity_>::GetID() const
{
  return Entity_::ID();
}

template<class Entity_>
inline AssetInfo * AssetConverter<Entity_>::Reserve(const std::string & directory_path, const std::string & file_name, const std::string & extension, AssetConverterContext * context)
{
  return this->importer_->Reserve(directory_path, file_name, extension, context);
}

template<class Entity_>
inline void AssetConverter<Entity_>::Import(AssetConverterContext * context)
{
  this->importer_->Import(&this->entities_, context);
}

template<class Entity_>
inline bool AssetConverter<Entity_>::ImportOnce(AssetConverterContext * context)
{
  return this->importer_->ImportOnce(&this->entities_, context);
}

template<class Entity_>
inline Entity_ * AssetConverter<Entity_>::ImportImmediately(const std::string & directory_path, const std::string & file_name, const std::string & extension, AssetConverterContext * context)
{
  return this->importer_->ImportImmediately(directory_path, file_name, extension, &this->entities_, context);
}

template<class Entity_>
inline void AssetConverter<Entity_>::Export(const AssetConverterContext * context) const
{
  this->exporter_->Export(this->entities_, context);
}

template<class Entity_>
inline void AssetConverter<Entity_>::CreateHeaderProgram(std::string * dest) const
{
  this->program_generator_->CreateHeaderProgram(this->entities_, dest);
}

template<class Entity_>
inline void AssetConverter<Entity_>::CreateCppProgram(std::string * dest) const
{
  this->program_generator_->CreateCppProgram(this->entities_, dest);
}
