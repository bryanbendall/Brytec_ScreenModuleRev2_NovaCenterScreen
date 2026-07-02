#pragma once

// 10.1" Waveshare Screen
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 1280

#ifdef PC_BUILD
#define SCREEN_ROTATION Renderer::Rotation::Rotate0
#else
#define SCREEN_ROTATION Renderer::Rotation::Rotate180
#endif

// Starting Layer
#include "layer/ButtonLayer.h"

#define STARTING_LAYER ButtonLayer