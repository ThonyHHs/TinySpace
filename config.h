#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <array>
#include <memory>

#include <raylib.h>
#include <raymath.h>

struct WindowSettings {
    float Width = 800;
    float Height = 800;
    int Fps = 60;
    const char* Title = "Expansion Battle";
};