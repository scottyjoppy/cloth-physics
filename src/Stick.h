#pragma once

#include "Point.h"
#include <SFML/Graphics.hpp>

class Stick
{
    public:
        Point& m_p0;
        Point& m_p1;
        float m_length;
        bool m_hidden;

    private:
        sf::RenderWindow& m_window;

    public:
        Stick
            (
             sf::RenderWindow& window, 
             Point& p0,
             Point& p1,
             bool hidden
            );
        ~Stick();

        void Initialize();
        void Load();
        void Update();
        void Draw();
};
