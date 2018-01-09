#include "NativeMethod.h"

namespace NativeMethod
{

//Graphics

INativeProcess_Graphics* graphics;

INativeProcess_Graphics& Graphics()
{
  return *graphics;
}

void Graphics_SetInstance(INativeProcess_Graphics* process)
{
  graphics = process;
}

void Graphics_DeleteInstance()
{
  delete graphics;
}

//Material

INativeProcess_Material* material;

INativeProcess_Material& Material()
{
  return *material;
}

void Material_SetInstance(INativeProcess_Material* process)
{
  material = process;
}

void Material_DeleteInstance()
{
  delete material;
}

//IO

INativeProcess_IO* io;

INativeProcess_IO& IO()
{
  return *io;
}

void IO_SetInstance(INativeProcess_IO* process)
{
  io = process;
}

void IO_DeleteInstance()
{
  delete io;
}

//Time

INativeProcess_Time* time;

INativeProcess_Time& Time()
{
  return *time;
}

void Time_SetInstance(INativeProcess_Time* process)
{
  time = process;
}

void Time_DeleteInstance()
{
  delete time;
}

} // namespace NativeMethod
