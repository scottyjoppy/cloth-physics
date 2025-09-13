#include <math.h>
#include "Math.h"
#include <iostream>

float Math::Length(const sf::Vector2f& v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

sf::Vector2f Math::Normalize(const sf::Vector2f& v)
{
    float len = Length(v);
    if (len != 0.0f)
        return { v.x / len, v.y / len};
    
    std::cout << "Dividing by 0 Math.h" << std::endl;
    return { 0.f, 0.f };
}

void Math::SolveCollisions(std::vector<Point>& objs)
{
    for (size_t iterations = 0; iterations < 300; iterations++)
    {
        size_t amt = objs.size();
        for (size_t i = 0; i < amt; i++)
        {
            Point& obj1 = objs[i];
            for (size_t j = i + 1; j < amt; j++)
            {
                Point& obj2 = objs[j];
                sf::Vector2f collisionAxis = obj1.m_pos - obj2.m_pos;
                float dist = Length(collisionAxis);
                float minDist = obj1.m_radius + obj2.m_radius;

                if (dist < minDist && dist > 0.0f)
                {
                    sf::Vector2f displacement = collisionAxis / dist;
                    float delta = minDist - dist;

                    sf::Vector2f correction = 0.5f * delta * displacement;

                    obj1.m_pos += correction;
                    obj2.m_pos -= correction;

                }
            }
        }
    }
}

sf::Vector2f Math::Velocity(sf::Vector2f pos, sf::Vector2f prePos, float friction)
{
    return (pos - prePos) * friction;
}

