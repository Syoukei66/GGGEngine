#include "ModelData.h"
#include "SerializerTester.h"
#include "SerializerTestMacro.hpp"

#include <Cereal/types/vector.hpp>

//=============================================================================
// Cereal Archive
//=============================================================================
template <class Archive>
void serialize(Archive& archive, ModelData& value)
{
  archive(value.mesh_unique_id_);
  archive(value.material_unique_ids_);
}

//=============================================================================
// Serializer Test
//=============================================================================
class ModelDataSerializerTester : public SerializerTester
{
public:
  using SerializerTester::Compare;
  void Compare(const ModelData& a, const ModelData& b)
  {
    PushState("StaticModelData");
    COMPARE_ATTR(mesh_unique_id_);
    COMPARE_ATTRS(material_unique_ids_, material_unique_ids_.size());
    PopState();
  }
};

//=============================================================================
// Serializer / Deserializer
//=============================================================================
SERIALIZER_IMPL(ModelData)