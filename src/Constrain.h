#pragma once

#include <SFML/Graphics.hpp>
#include "Stick.h"
#include "Point.h"
#include "Ball.h"

class Constrain
{
    public:
        static void ResolveStickVsBall(const Stick& stick, const Ball& ball);
};
