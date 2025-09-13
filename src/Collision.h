#pragma once

#include "Ball.h"
#include "Stick.h"

#include <SFML/Graphics.hpp>

class Collision
{
    public:
        static bool StickVsBall(const Stick& stick, const Ball& ball);
};
