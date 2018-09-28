#include "DefaultUniqueID.h"

#include "SerializerTester.h"
#include "SerializerTestMacro.hpp"

#include <Cereal/types/unordered_map.hpp>

//=============================================================================
// Cereal Archive
//=============================================================================
template <class Archive>
void serialize(Archive& ar, DefaultUniqueID& value)
{
  ar(value.correspondences_);
}

//=============================================================================
// Serializer Test
//=============================================================================
class DefaultUniqueIDSerializerTester : public SerializerTester
{
public:
  using SerializerTester::Compare;
  void Compare(const DefaultUniqueID& a, const DefaultUniqueID& b)
  {
    PushState("DefaultUniqueID");
    COMPARE_ATTRMAP(correspondences_, T_UINT32);
    PopState();
  }
};

SERIALIZER_IMPL(DefaultUniqueID)
