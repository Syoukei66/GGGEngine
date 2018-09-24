#include "ModelData.h"
#include "CerealStructArchive.hpp"
#include "CerealArchiveMacro.hpp"
#include "CerealIO.h"
#include "SerealizerTester.h"
#include "SerealizerTestMacro.hpp"

//=============================================================================
// Cereal Archive
//=============================================================================
template <class Archive>
void serialize(Archive& archive, ModelData& value)
{
  archive(value.mesh_unique_id_);
  archive(value.submesh_count_);
  ARRAY_ARCHIVE(value.mesh_material_indices_, T_UINT8, value.submesh_count_);
  archive(value.material_count_);
  ARRAY_ARCHIVE(value.material_unique_ids_, T_UINT32, value.material_count_);
}

//=============================================================================
// Serealizer Test
//=============================================================================
class ModelDataSerealizerTester : public SerealizerTester
{
public:
  using SerealizerTester::Compare;
  void Compare(const ModelData& a, const ModelData& b)
  {
    PushState("StaticModelData");
    COMPARE_ATTR(mesh_unique_id_);
    COMPARE_ATTR(submesh_count_);
    COMPARE_ATTRS(mesh_material_indices_, submesh_count_);
    COMPARE_ATTR(material_count_);
    COMPARE_ATTRS(material_unique_ids_, material_count_);
    PopState();
  }
};

//=============================================================================
// Serealizer / Deserealizer
//=============================================================================
SEREALIZERS(ModelData)