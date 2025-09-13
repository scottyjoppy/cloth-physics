#include "Point.h"
#include "Math.h"
#include <iostream>

Point::Point
(
 sf::RenderWindow& window, 
 sf::Vector2f pos, 
 sf::Vector2f prePos, 
 float radius,
 bool hidden
 ) :
    m_window(window), 
    m_pos(pos), 
    m_prePos(prePos), 
    m_color(sf::Color::White),
    m_radius(radius),
    m_hidden(hidden),
    m_pinned(false),
    leftMousePressed(false)
{
}

Point::~Point()
{
}

void Point::Initialize()
{
    circle.setRadius(m_radius);
    circle.setOrigin(m_radius, m_radius);
    circle.setPosition(m_pos);
    circle.setFillColor(m_color);
}

void Point::Load()
{
}

void Point::Update(float friction, float gravity)
{
    sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(m_window));

    bool mouseCurrent = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    if (mouseCurrent && !leftMousePressed && Math::Length(mousePos - m_pos) <=  m_radius)
        m_pinned = !m_pinned;

    leftMousePressed = mouseCurrent;

    if (Math::Length(mousePos - m_pos) <= m_radius && !m_pinned)
    {
        m_color = sf::Color::Yellow;
    }
    else if (m_pinned)
    {
        m_color = sf::Color::Red;
    }
    else
    {
        m_color = sf::Color::White;
    }

    if (!m_pinned)
    {
        m_v = Math::Velocity(m_pos, m_prePos, friction);

        m_prePos = m_pos;
        m_pos += m_v + sf::Vector2f(0, gravity);
    }
    circle.setFillColor(m_color);
}

void Point::Draw()
{
    if (!m_hidden)
    {
        circle.setPosition(m_pos);
        m_window.draw(circle);
    }
}

void Point::Constrain(float friction, float bounce)
{
    sf::Vector2u windowSize = m_window.getSize();

    if (!m_pinned)
    {
        if (m_pos.x > windowSize.x - m_radius)
        {
            m_pos.x = windowSize.x - m_radius;
            m_prePos.x = m_pos.x + m_v.x * bounce;
        }
        else if (m_pos.x < m_radius)
        {
            m_pos.x = m_radius;
            m_prePos.x = m_pos.x + m_v.x * bounce;
        }

        if (m_pos.y > windowSize.y - m_radius)
        {
            m_pos.y = windowSize.y - m_radius;
            m_prePos.y = m_pos.y + m_v.y * bounce;
        }
        else if (m_pos.y < m_radius)
        {
            m_pos.y = m_radius;
            m_prePos.y = m_pos.y + m_v.y * bounce;
        }
    }
}
