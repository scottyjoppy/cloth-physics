#include "Stick.h"
#include "Math.h"
#include <iostream>

Stick::Stick
(
 sf::RenderWindow& window, 
 Point& p0,
 Point& p1,
 bool hidden
 ) :
    m_window(window), m_p0(p0), m_p1(p1), m_hidden(hidden)
{
}

Stick::~Stick()
{
}

void Stick::Initialize()
{
    m_length = Math::Length({m_p1.m_pos.x - m_p0.m_pos.x, m_p1.m_pos.y - m_p0.m_pos.y});
}

void Stick::Load()
{
}

void Stick::Update()
{
    float dx = m_p1.m_pos.x - m_p0.m_pos.x;
    float dy = m_p1.m_pos.y - m_p0.m_pos.y;
    float dist = Math::Length({dx, dy});

    float diff = m_length - dist;
    float percent = diff / dist / 2;
    float offsetX = dx * percent;
    float offsetY = dy * percent;

    if (!m_p0.m_pinned)
    {
        m_p0.m_pos.x -= offsetX;
        m_p0.m_pos.y -= offsetY;
    }

    if (!m_p1.m_pinned)
    {
        m_p1.m_pos.x += offsetX;
        m_p1.m_pos.y += offsetY;
    }
}

void Stick::Draw()
{
    if (!m_hidden)
    {
        sf::Vertex line[] =
        {
            sf::Vertex(m_p0.m_pos, sf::Color::White),
            sf::Vertex(m_p1.m_pos, sf::Color::White)
        };
        m_window.draw(line, 2, sf::Lines);
    }
}
