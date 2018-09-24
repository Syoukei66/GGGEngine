#include "MeshData.h"
#include "CerealStructArchive.hpp"
#include "CerealArchiveMacro.hpp"
#include "CerealIO.h"
#include "SerealizerTester.h"
#include "SerealizerTestMacro.hpp"

//=============================================================================
// Cereal Archive
//=============================================================================
template <class Archive>
void serialize(Archive& archive, MeshData& value)
{
  archive(value.vertex_format_);
  archive(value.vertex_size_);
  archive(value.vertex_count_);
  ARRAY_ARCHIVE(value.data_, unsigned char, value.vertex_count_ * value.vertex_size_);
  archive(value.polygon_count_);
  archive(value.index_count_);
  ARRAY_ARCHIVE(value.indices_, T_UINT32, value.index_count_);
  archive(value.submesh_count_);
  ARRAY_ARCHIVE(value.submesh_index_counts_, T_UINT32, value.submesh_count_);
  archive(value.bounds_);
}

//=============================================================================
// Serealizer Test
//=============================================================================
class MeshDataSerealizerTester : public SerealizerTester
{
public:
  using SerealizerTester::Compare;
  void Compare(const MeshData& a, const MeshData& b)
  {
    PushState("StaticMeshData");
    COMPARE_ATTR(vertex_format_);
    COMPARE_ATTR(vertex_size_);
    COMPARE_ATTR(vertex_count_);
    COMPARE_ATTRS(data_, vertex_count_ * a.vertex_size_);
    COMPARE_ATTR(polygon_count_);
    COMPARE_ATTR(index_count_);
    COMPARE_ATTRS(indices_, index_count_);
    COMPARE_ATTR(submesh_count_);
    COMPARE_ATTRS(submesh_index_counts_, submesh_count_);
    COMPARE_ATTR(bounds_);
    PopState();
  }
};

//=============================================================================
// Serealizer / Deserealizer
//=============================================================================
SEREALIZERS(MeshData)
