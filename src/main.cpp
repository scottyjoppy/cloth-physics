#include <iostream>
#include <SFML/Graphics.hpp>

#include "Stick.h"
#include "Point.h"
#include "Ball.h"

#include "FrameRate.h"
#include "Math.h"
#include "Collision.h"


sf::Vector2u windowSize(1920, 1080);


int main()
{
    // MAGIC
    float bounce = 0.9f;
    float gravity = 0.5f;
    float friction = 0.999f;
    float fps = 60.f;

    int gridY = 10;
    int gridX = 30;

	//-----INITIALIZE-----

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Cloth", sf::Style::Default, settings);
	window.setFramerateLimit(fps);

	//-----INITIALIZE-----

    FrameRate fr;
    fr.Initialize();
    fr.Load();


    std::vector<Stick> sticks;
    std::vector<Point> points;
    std::vector<Ball> balls;
    

    // Make Grid
    
    for (size_t y = 0; y < gridY; y++)
    {
        for (size_t x = 0; x < gridX; x++)
        {
            points.emplace_back
                (
                 window,
                 sf::Vector2f(50 * x + 50, 50 * y + 50),
                 sf::Vector2f(50 * x + 50, 50 * y + 50),
                 10.f,
                 false
                );
        }
    }

    for (size_t y = 0; y < gridY; y++)
    {
        for (size_t x = 0; x < gridX - 1; x++)
        {
            size_t idx1 = y * gridX + x;
            size_t idx2 = y * gridX + (x + 1);
            sticks.emplace_back
                (
                 window,
                 points[idx1],
                 points[idx2],
                 false
                );
        }
    }

    for (size_t y = 0; y < gridY - 1; y++)
    {
        for (size_t x = 0; x < gridX; x++)
        {
            size_t idx1 = y * gridX + x;
            size_t idx2 = (y + 1) * gridX + x;
            sticks.emplace_back
                (
                 window,
                 points[idx1],
                 points[idx2],
                 false
                );
        }
    }

    points[0].m_pinned = true;
    points[10].m_pinned = true;
    points[gridX - 1].m_pinned = true;
    points[gridX * gridY - gridX].m_pinned = true;
    points[gridX * gridY - 1].m_pinned = true;

    for (auto& p : points)
    {
        p.Initialize();
        p.Load();
    }

    for (auto& s : sticks)
    {
        s.Initialize();
        s.Load();
    }

	//-----INITIALIZE-----

	//-----GAME LOOP-----
	
    float fixedDt = 1.0f / fps; 
    float accumulator = 0.0f;
	sf::Clock clock;

	while (window.isOpen())
	{	
		double deltaTime = clock.restart().asSeconds();
        accumulator += deltaTime;

		//-----UPDATE-----
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                window.close();
                main();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
                balls.emplace_back
                    (
                     window,
                     mousePos,
                     mousePos,
                     20.f
                    );
                balls.back().Initialize();
                balls.back().Load();
                balls.back().Draw();
            }
		}

        while (accumulator >= fixedDt)
        {
            fr.Update(deltaTime);

            // Update Points
            for (auto& p : points) p.Update(friction, gravity);
            for (auto& b : balls) b.Update(friction, gravity);

            for (size_t i = 0; i < 3; i++)
            {
                // Update Sticks
                for (auto& s : sticks)
                {
                    s.Update();
                    for (auto& b : balls)
                    {
                        if (Collision::StickVsBall(s, b))
                            std::cout << "AHH" << std::endl;
                    }
                }

                // Constrain Points
                for (auto& p : points) p.Constrain(friction, bounce);
                for (auto& b : balls) b.Constrain(friction, bounce);
            }

            accumulator -= fixedDt;
        }

        
        //-----UPDATE-----

        //-----DRAW-----
        
        window.clear();
        for (auto& p : points) p.Draw();
        for (auto& s : sticks) s.Draw();
        for (auto& b : balls) b.Draw();
        fr.Draw(window);

		window.display();

		//-----DRAW-----

	}

	return 0;
}
