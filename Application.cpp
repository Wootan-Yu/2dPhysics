#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>

#include "Application.h"
#include "Constants.h"
#include "Force.h"
#include "Line.h"

Application::Application(const std::string& config)
{
	init(config);
}

void Application::init(const std::string& path)
{
	m_particleConfigStorage.reserve(m_numParticles);

	//read config file
	std::ifstream fin(path);
	
	while (fin >> m_type)
	{
		if (m_type == "Particle")
		{
			fin >> m_particleConfig.INDEX;
			for (int i = 0; i < m_numParticles; i++) //0
			{
				if (m_particleConfig.INDEX == i) //0
				{
					fin >> m_particleConfig.X >> m_particleConfig.Y >> m_particleConfig.MASS >> m_particleConfig.RADIUS;
					std::cout << m_type << " " << m_particleConfig.X << " " << m_particleConfig.Y << " " << m_particleConfig.MASS << " " << m_particleConfig.RADIUS << '\n';
					m_particleConfigStorage.emplace_back(m_particleConfig);
				}
			}
		}
	}

	m_window.create(sf::VideoMode(800, 800), "test");
	m_window.setFramerateLimit(FPS);


	spawnParticle(m_numParticles);
	//spawnLiquid();

	if (!m_font.loadFromFile("fonts/Tech.ttf"))
	{
		std::cout << "could not load font!\n";
		exit(-1);
	}

	m_text.setString("Test");
	m_text.setFont(m_font);
	m_text.setCharacterSize(25);
	m_text.setFillColor(sf::Color::White);
	m_text.setPosition(10.f, 20.f);

}

void Application::spawnLiquid()
{
	m_liquid.setSize(sf::Vector2f(m_window.getSize().x, m_window.getSize().y / 2));
	m_liquid.setPosition(sf::Vector2f(0, m_window.getSize().y / 2));
	m_liquid.setFillColor(sf::Color(50, 141, 168));
}

void Application::spawnParticle(int numParticle)
{
	m_particles.reserve(numParticle);
	m_particleShapes.reserve(numParticle);
	for (auto& i : m_particleConfigStorage)
	{
		m_particle.m_position = Vec2(i.X, i.Y); //attributes of particle
		m_particle.m_mass = i.MASS;
		m_particle.radius = i.RADIUS; //not used yet
		m_particles.emplace_back(m_particle);
	}
	
	for (int i = 0; i < numParticle; i++)
	{
		m_circle.setRadius(20.f);	//attributes of shape of particle
		m_circle.setOrigin(m_circle.getRadius(), m_circle.getRadius());
		m_circle.setFillColor(sf::Color::White); 
		m_circle.setPointCount(100);
		m_particleShapes.emplace_back(m_circle);
	}

	/*for (int i = 0; i < numParticle; i++)
	{
		std::cout << i << " r: " << m_circle.getRadius() << '\n';
	}*/
}

void Application::run()
{
	while (m_running)
	{
		sUserInput();
		sMovement();
		sCollision();
		sRender();
	}
}

void Application::sUserInput()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_running = false;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
				case sf::Keyboard::Q:
					m_running = false;
					break;
				case sf::Keyboard::Up:
					m_pushForce.y = -50.f * PIXEL_PER_METER;
					break;
				case sf::Keyboard::Right:
					m_pushForce.x = 50.f * PIXEL_PER_METER;
					break;
				case sf::Keyboard::Down:
					m_pushForce.y = 50.f * PIXEL_PER_METER;
					break;
				case sf::Keyboard::Left:
					m_pushForce.x = -50.f * PIXEL_PER_METER;
					break;
			}
		}
		if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
				case sf::Keyboard::Up:
					m_pushForce.y = 0.f;
					break;
				case sf::Keyboard::Right:
					m_pushForce.x = 0.f;
					break;
				case sf::Keyboard::Down:
					m_pushForce.y = 0.f;
					break;
				case sf::Keyboard::Left:
					m_pushForce.x = 0.f;
					break;
			}
		}

		m_mouseCursor.x = sf::Mouse::getPosition(m_window).x;
		m_mouseCursor.y = sf::Mouse::getPosition(m_window).y;
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (!m_leftMouseButtonDown && event.mouseButton.button == sf::Mouse::Left)
			{
				m_leftMouseButtonDown = true;
				m_lineAppear = true;
				std::cout << "mouse pressed" << '\n';
			}
		}

		if (m_lineAppear)
		{
			m_line.setPosition(
				sf::Vector2f(m_mouseCursor.x, m_mouseCursor.y),
				sf::Vector2f(m_particles[0].m_position.x, m_particles[0].m_position.y)
			);
			m_line.setColor(sf::Color::Red);
		}
		
		

		if (event.type == sf::Event::MouseButtonReleased)
		{
			if(m_leftMouseButtonDown)
			{
				m_leftMouseButtonDown = false;
				m_lineAppear = false;

				//'impulse' force
				Vec2 impluseDirection = (m_particles[0].m_position - m_mouseCursor).UnitVector();
				float impulseMagnitude = (m_particles[0].m_position - m_mouseCursor).Magnitude() * 5.f;
				m_particles[0].m_velocity = impluseDirection * impulseMagnitude;
				std::cout << "mouse released" << '\n';
			}
		}

		if (!m_lineAppear)
		{
			m_line.clear();
		}
		

		//if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		//{
		//	float mouse_x = sf::Mouse::getPosition(m_window).x;
		//	float mouse_y = sf::Mouse::getPosition(m_window).y;
		//	Particle p(mouse_x, mouse_y, 1.f);
		//	m_particles.emplace_back(p);

		//	m_circle.setRadius(10.f);	//attributes of shape of particle
		//	m_circle.setFillColor(sf::Color::White);
		//	m_circle.setPointCount(100);
		//	m_particleShapes.emplace_back(m_circle);
		//}
	}
}

void Application::sMovement()
{
	//todo: check if we are too fast: (for consistency)
	//			waste some ms until we reach MILLISECONDS_PER_FRAME
	int prevTime = 0;
	sf::Time currentTime = m_clock.getElapsedTime();

	//delta time - how many pixels we want to move PER SECONDS (not per frame)
	float deltaTime = (currentTime.asMilliseconds() - prevTime) / 1000000.f;
	prevTime = currentTime.asMilliseconds();


	//apply the forces here: (wind/air resistance, weight, friction, drag,...)
	for (auto& p : m_particles)
	{	
		//'wind' force to the right
		/*Vec2 wind = Vec2(0.2f * PIXEL_PER_METER, 0.f);
		p.AddForce(wind);*/

		//'weight' force down (weight = mass * gravity)
		/*Vec2 weight = Vec2(0.f, p.m_mass * GRAVITY * PIXEL_PER_METER);
		p.AddForce(weight);*/

		//'push' force 
		p.AddForce(m_pushForce);

		//'drag' force if inside the liquid
		//if (p.m_position.y >= m_liquid.getPosition().y)
		//{
		//	Vec2 drag = Force::GenerateDragForce(p, 0.02); //Case: DragForce is bigger than the velocity (results to unexpected behavior)
		//	p.AddForce(drag);							   //k = 0.01 -> 0.1
		//}

		//'friction' force
		Vec2 friction = Force::GenerateFrictionForce(p, 10.f * PIXEL_PER_METER);
		p.AddForce(friction);
	}

	for (auto& i : m_particles)
	{
		// (implicit euler integration)
		i.Integrate(deltaTime);
	}
}



void Application::sCollision()
{
	int diameter = m_circle.getRadius() * 2;
	for (auto& i : m_particles)
	{
		if (i.m_position.x - m_circle.getRadius() <= 0) //left
		{
			i.m_position.x = m_circle.getRadius();
			i.m_velocity.x *= -1.f;
		}
		else if (i.m_position.x + m_circle.getRadius() >= m_window.getSize().x) //right
		{
			i.m_position.x = m_window.getSize().x - m_circle.getRadius();
			i.m_velocity.x *= -1.f;
		}

		if (i.m_position.y - m_circle.getRadius() <= 0) //top
		{
			i.m_position.y = m_circle.getRadius();
			i.m_velocity.y *= -1.f;
		}

		else if (i.m_position.y + m_circle.getRadius() >= m_window.getSize().y) //bottom
		{
			i.m_position.y = m_window.getSize().y - m_circle.getRadius();
			i.m_velocity.y *= -1.f;
		}
	}
	
}


void Application::sRender()
{
	m_window.clear(sf::Color(10, 87, 12));
	m_window.draw(m_text);
	//m_window.draw(m_liquid);

	for (auto& i : m_particles)
	{
		for (auto& j : m_particleShapes)
		{
			j.setPosition(i.m_position.x, i.m_position.y);
			m_window.draw(j);
		}
	}
	
	m_line.draw(m_window);
	
	m_window.display();
}


