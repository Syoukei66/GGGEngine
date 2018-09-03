#include "StaticMeshData.h"
#include "CerealStructArchive.hpp"
#include "CerealArchiveMacro.hpp"
#include "CerealIO.h"
#include "SerealizerTester.h"
#include "SerealizerTestMacro.hpp"

//=============================================================================
// Cereal Archive
//=============================================================================
template <class Archive>
void serialize(Archive& archive, StaticMeshData& value)
{
  archive(value.vertex_format_);
  archive(value.vertex_size_);
  archive(value.vertex_count_);
  SAFE_NEW(value.data_, unsigned char[value.vertex_count_ * value.vertex_size_]);
  archive(cereal::binary_data(value.data_, sizeof(unsigned char) * value.vertex_count_ * value.vertex_size_));
  archive(value.polygon_count_);
  archive(value.index_count_);
  SAFE_NEW(value.indices_, T_UINT32[value.index_count_]);
  archive(cereal::binary_data(value.indices_, sizeof(T_UINT32) * value.index_count_));
  archive(value.submesh_count_);
  SAFE_NEW(value.submesh_index_counts_, T_UINT32[value.submesh_count_]);
  archive(cereal::binary_data(value.submesh_index_counts_, sizeof(T_UINT32) * value.submesh_count_));
  archive(value.bounds_);
}

//=============================================================================
// Serealizer Test
//=============================================================================
class StaticMeshSerealizerTester : public SerealizerTester
{
public:
  using SerealizerTester::Compare;
  void Compare(const StaticMeshData& a, const StaticMeshData& b)
  {
    PushState("StaticModelData");
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
StaticMeshData* StaticMeshData::Deserealize(const std::string& path)
{
  return CerealIO::Binary::Import<StaticMeshData>(path.c_str());
}

void StaticMeshData::Serealize(const std::string& path, bool test)
{
  CerealIO::Binary::Export<StaticMeshData>(path.c_str(), this);
  if (test)
  {
    StaticMeshSerealizerTester tester;
    StaticMeshData* data = Deserealize(path);
    tester.Compare(*this, *data);
    delete data;
  }
}
