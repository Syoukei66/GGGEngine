#include "MaterialData.h"
#include "CerealStructArchive.hpp"
#include "CerealArchiveMacro.hpp"
#include "CerealIO.h"
#include "SerealizerTester.h"
#include "SerealizerTestMacro.hpp"

#include "Cereal/types/unordered_map.hpp"

#include "CerealShaderPropertiesArchive.hpp"

//=============================================================================
// Cereal Archive
//=============================================================================
template <class Archive>
void serialize(Archive& ar, MaterialData& value)
{
  ar(value.shader_unique_id_);
  ar(value.protect_);
  ar(value.main_tex_unique_id_);
  ar(value.color_);
  ar(value.tiling_);
  ar(value.tiling_offset_);
  ar(value.billbording_);
  ar(value.properties_);
}

//=============================================================================
// Serealizer Test
//=============================================================================
class MaterialDataSerealizerTester : public SerealizerTester
{
public:
  using SerealizerTester::Compare;
  void Compare(const MaterialData& a, const MaterialData& b)
  {
    PushState("MaterialData");
    COMPARE_ATTR(shader_unique_id_);
    COMPARE_ATTR(protect_);
    COMPARE_ATTR(main_tex_unique_id_);
    COMPARE_ATTR(color_);
    COMPARE_ATTR(tiling_);
    COMPARE_ATTR(tiling_offset_);
    COMPARE_ATTR(billbording_);
    COMPARE_ATTRMAP(texture_properties_, T_UINT32);
    COMPARE_ATTRMAP(properties_, ShaderProperty);
    PopState();
  }
};

//=============================================================================
// Serealizer / Deserealizer
//=============================================================================
MaterialData* MaterialData::Deserealize(const std::string& path)
{
  return CerealIO::Binary::Import<MaterialData>(path.c_str());
}

void MaterialData::Serealize(const std::string& path, bool test)
{
  CerealIO::Binary::Export<MaterialData>(path.c_str(), this);
  if (test)
  {
    MaterialDataSerealizerTester tester;
    MaterialData* data = Deserealize(path);
    tester.Compare(*this, *data);
    delete data;
  }
}
