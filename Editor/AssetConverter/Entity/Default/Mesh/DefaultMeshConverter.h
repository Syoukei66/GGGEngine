#pragma once

#include <Entity/Default/DefaultAssetConverter.h>

class DefaulMeshConverter : public DefaultAssetConverter<rcMesh, StaticMeshData>
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  DefaulMeshConverter(
    const std::string& id,
    const std::string& class_name
  );

};
