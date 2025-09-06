#pragma once

#ifndef SHADER_HANDLE_H
#define SHADER_HANDLE_H

#include "raylib.h"

typedef struct ShaderHandle
{
	RenderTexture2D target;
	Shader crt_shader;
	int time_loc;
} ShaderHandle;

#endif
