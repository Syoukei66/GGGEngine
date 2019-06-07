#pragma once

#include <string>
#include <Util/FileUtil.h>

namespace DefaultAsset
{
static const std::string& SHADER_PATH_ERROR = "shader/default/Error.shader";
static const std::string& SHADER_PATH_LAMBERT = "shader/default/Lambert.shader";
static const std::string& SHADER_PATH_PHONG   = "shader/default/Phong.shader";
static const std::string& SHADER_PATH_WHITE   = "shader/default/White.shader";
static const std::string& SHADER_PATH_UNLIT  = "shader/default/Unlit.shader";

//仮想のパス
static const std::string& MESH_PATH_CUBE   = "mesh/default/Cube.mesh";
static const std::string& MESH_PATH_PLANE  = "mesh/default/Plane.mesh";
static const std::string& MESH_PATH_CAPSULE = "mesh/default/Capsule.mesh";
static const std::string& MESH_PATH_CUBE_SPHERE = "mesh/default/CubeSphere.mesh";
static const std::string& MESH_PATH_UV_SPHERE = "mesh/default/UvSphere.mesh";

//仮想のパス
static const std::string& MATERIAL_PATH_LAMBERT = "material/default/Lambert.mat";
static const std::string& MATERIAL_PATH_WHITE   = "material/default/White.mat";
static const std::string& MATERIAL_PATH_UNLIT  = "material/default/Unlit.mat";

static const std::string& TEXTURE_PATH_WHITE = "texture/default/white.png";
static const std::string& TEXTURE_PATH_BLACK = "texture/default/black.png";
static const std::string& TEXTURE_PATH_GRAY = "texture/default/gray.png";
static const std::string& TEXTURE_PATH_BUMP = "texture/default/bump.png";

}
