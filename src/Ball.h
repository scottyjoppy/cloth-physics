#pragma once

#include <SFML/Graphics.hpp>

class Ball
{
    public:
        sf::CircleShape circle;
        sf::Vector2f m_pos;
        sf::Vector2f m_prePos;
        sf::Vector2f m_v;
        float m_radius;
        sf::Color m_color;

    private:
        sf::RenderWindow& m_window;

    public:
        Ball
            (
             sf::RenderWindow& window, 
             sf::Vector2f pos, 
             sf::Vector2f prePos, 
             float radius
            );
        ~Ball();

        void Initialize();
        void Load();
        void Update(float friction, float gravity);
        void Draw();
};
