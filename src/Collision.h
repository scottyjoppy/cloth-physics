#pragma once

#include "Ball.h"
#include "Stick.h"

#include <SFML/Graphics.hpp>

class Collision
{
    public:
        inline static float m_g = 0.f;
        inline static float m_b = 0.f;
        inline static float m_f = 0.f;

    public:
        static bool StickVsBall(const Stick& stick, const Ball& ball);
        static void BallVsWindow(Ball& ball, const sf::RenderWindow& window);
};
