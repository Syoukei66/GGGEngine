#ifndef HAL_ENGINE_NATIVE_NATIVEMETHOD_H_
#define HAL_ENGINE_NATIVE_NATIVEMETHOD_H_

#include "INativeProcess_Graphics.h"
#include "INativeProcess_Texture.h"
#include "INativeProcess_Material.h"
#include "INativeProcess_Model.h"
#include "INativeProcess_IO.h"
#include "INativeProcess_Time.h"

//Ç±ÇÃÇ†ÇΩÇËÇ»ÇÒÇ©ëSëÃìIÇ…î˜ñ≠
//SetInstance,DeleteInstanceÇ™èÌÇ…òIèoÇµÇƒÇ¢ÇÈÇ∆Ç±ÇÎÇ∆Ç©
namespace NativeMethod
{

INativeProcess_Graphics& Graphics();
void Graphics_SetInstance(INativeProcess_Graphics* process);
void Graphics_DeleteInstance();

INativeProcess_Texture& Texture();
void Texture_SetInstance(INativeProcess_Texture* process);
void Texture_DeleteInstance();

INativeProcess_Material& Material();
void Material_SetInstance(INativeProcess_Material* process);
void Material_DeleteInstance();

INativeProcess_Model& Model();
void Model_SetInstance(INativeProcess_Model* process);
void Model_DeleteInstance();

INativeProcess_IO& IO();
void IO_SetInstance(INativeProcess_IO* process);
void IO_DeleteInstance();

INativeProcess_Time& Time();
void Time_SetInstance(INativeProcess_Time* process);
void Time_DeleteInstance();

} // namespace NativeMethod

#endif//HAL_ENGINE_NATIVE_NATIVEMETHOD_H_
