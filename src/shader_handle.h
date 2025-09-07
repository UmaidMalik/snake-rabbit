#pragma once

#include "raylib.h"

typedef struct ShaderHandle
{
	RenderTexture2D target;
	Shader crt_shader;
	int time_loc;
} ShaderHandle;

