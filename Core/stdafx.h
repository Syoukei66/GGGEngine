#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <functional>
#include <list>

#include <Core/Macro/ProgramMacro.h>
#include <Core/Util/Logger.h>
#include <Core/Macro/AssertMacro.h>
#include <Core/Macro/ObjectMacro.h>
#include <Core/Types.h>

#include <Core/Math/Mathf.h>
#include <Core/Math/Vector2.h>
#include <Core/Math/Vector3.h>
#include <Core/Math/Vector4.h>
#include <Core/Math/Matrix4x4.h>
#include <Core/Math/Quaternion.h>
#include <Core/Math/Bounds.h>
#include <Core/Math/Color.h>

#include <Core/Constants/DirectoryUtils.h>
#include <Core/Constants/ShaderUtils.h>
#include <Core/Constants/GraphicsUtils.h>

#include <Core/Application/Input/EngineInput.h>

#include <Core/Application/Object/Object.h>
#include <Core/Application/Object/Ref.h>
#include <Core/Application/Object/UniqueRef.h>
#include <Core/Application/Object/SharedRef.h>
#include <Core/Application/Object/WeakRef.h>

#include <math.h>
#include <array>
#include <vector>
#include <deque>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <math.h>

#include <Core/Constants/VertexUtils.h>

#include <Core/_Private/CerealIO.h>