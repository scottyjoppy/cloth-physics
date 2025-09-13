#pragma once

#include <SFML/Graphics.hpp>

class Point
{
    public:
        sf::CircleShape circle;
        sf::Vector2f m_pos;
        sf::Vector2f m_prePos;
        sf::Vector2f m_v;
        float m_radius;
        bool m_hidden;
        bool m_pinned;
        bool leftMousePressed;
        sf::Color m_color;

    private:
        sf::RenderWindow& m_window;

    public:
        Point
            (
             sf::RenderWindow& window, 
             sf::Vector2f pos, 
             sf::Vector2f prePos, 
             float radius,
             bool hidden
            );
        ~Point();

        void Initialize();
        void Load();
        void Update(float friction, float gravity);
        void Draw();
};
