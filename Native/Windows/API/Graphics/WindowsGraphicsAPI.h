#pragma once

#include <Native/Windows/PlatformMacro.h>

#pragma comment(lib, "xinput.lib")

#if GG_GRAPHICS_API_DX9
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#include <Native/Windows/API/Graphics/DX9/DX9GraphicsAPI.h>
#elif GG_GRAPHICS_API_DX11
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxerr.lib")
#pragma comment(lib, "dxguid.lib")
#include <Native/Windows/API/Graphics/DX11/DX11GraphicsAPI.h>
#else

#endif