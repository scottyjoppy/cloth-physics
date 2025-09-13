#include "Ball.h"
#include "Math.h"
#include <iostream>

Ball::Ball
(
 sf::RenderWindow& window, 
 sf::Vector2f pos, 
 sf::Vector2f prePos, 
 float radius
 ) :
    m_window(window), 
    m_pos(pos), 
    m_prePos(prePos), 
    m_color(sf::Color::White),
    m_radius(radius)
{
}

Ball::~Ball()
{
}

void Ball::Initialize()
{
    circle.setRadius(m_radius);
    circle.setOrigin(m_radius, m_radius);
    circle.setPosition(m_pos);
    circle.setFillColor(m_color);
}

void Ball::Load()
{
}

void Ball::Update(float friction, float gravity)
{
    m_v = Math::Velocity(m_pos, m_prePos, friction);

    m_prePos = m_pos;
    m_pos += m_v + sf::Vector2f(0, gravity);
}

void Ball::Draw()
{
    circle.setPosition(m_pos);
    m_window.draw(circle);
}
