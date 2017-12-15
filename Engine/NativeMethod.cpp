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

//Matrix

INativeProcess_Matrix* matrix;

INativeProcess_Matrix& Matrix()
{
  return *matrix;
}

void Matrix_SetInstance(INativeProcess_Matrix* process)
{
  matrix = process;
}

void Matrix_DeleteInstance()
{
  delete matrix;
}

//Texture

INativeProcess_Texture* texture;

INativeProcess_Texture& Texture()
{
  return *texture;
}

void Texture_SetInstance(INativeProcess_Texture* process)
{
  texture = process;
}

void Texture_DeleteInstance()
{
  delete texture;
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

//Model

INativeProcess_Model* model;

INativeProcess_Model& Model()
{
  return *model;
}

void Model_SetInstance(INativeProcess_Model* process)
{
  model = process;
}

void Model_DeleteInstance()
{
  delete model;
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
