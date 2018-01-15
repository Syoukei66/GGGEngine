#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include <NativeShader.h>

class NativeShader : public INativeShader 
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  NativeShader(const char* path);
  ~NativeShader();
  
  // =================================================================
  // Method for/from SuperClass/Interfaces
  // =================================================================
public:

  // =================================================================
  // Data Members
  // =================================================================
private:
  ID3DXEffect* effect_;

};