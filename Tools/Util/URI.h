#pragma once

#include <string>
#include <Cereal/types/string.hpp>

class URI
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  URI(const std::string& full_path);
  URI(const std::string& directory_path, const std::string& file_name);
  URI(const std::string& directory_path, const std::string& prefix, const std::string& extension);

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  const std::string& GetDirectoryPath() const;
  const std::string& GetFileName() const;
  const std::string& GetPrefix() const;
  const std::string& GetExtension() const;
  const std::string& GetProgramID() const;

  inline const std::string& GetFullPath() const
  {
    return this->full_path_;
  }

  // =================================================================
  // Serialize Method
  // =================================================================
public:
  template<class Archive>
  void serialize(Archive& ar)
  {
    ar(cereal::make_nvp("FullPath", this->full_path_));
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::string full_path_;

  //caches
  std::string directory_path_;
  std::string file_name_;
  std::string prefix_;
  std::string extension_;
  std::string program_id_;

};