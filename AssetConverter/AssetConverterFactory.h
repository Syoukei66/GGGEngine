#pragma once

#include <vector>
#include <string>

class IAssetConverter;

class AssetConverterFactory
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AssetConverterFactory() = default;
  virtual ~AssetConverterFactory() = default;

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual IAssetConverter* Create() const = 0;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline const std::vector<std::string>& GetTargetExtensions() const
  {
    return this->target_extensions_;
  }

  // =================================================================
  // Serealizer
  // =================================================================
public:
  template<class Archive>
  void serialize(Archive& ar, std::uint32_t const version)
  {
    ar(cereal::make_nvp("TargetExtensions", this->target_extensions_));
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::vector<std::string> target_extensions_;

};