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


	spawnParticle();
	//spawnLiquid();
	spawnLine();

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

void Application::spawnLine()
{
	m_lines.reserve(NUM_PARTICLES);
	//spring (connection 1, index = 0)
	//Line spring(
	//	sf::Vector2f(anchor.x, anchor.y),
	//	sf::Vector2f(m_particles[0].m_position.x, m_particles[0].m_position.y),
	//	sf::Color::Magenta
	//);
	//m_lines.emplace_back(spring);

	//for (int i = 1; i < NUM_PARTICLES - 1; i++) //(index = 1-12)
	//{
	//	int currParticle = i;
	//	int nextParticle = i + 1;
	//	Line spring(
	//		sf::Vector2f(m_particles[currParticle].m_position.x, m_particles[currParticle].m_position.y),
	//		sf::Vector2f(m_particles[nextParticle].m_position.x, m_particles[nextParticle].m_position.y),
	//		sf::Color::White
	//	);
	//	m_lines.emplace_back(spring);
	//}

	Line s1(
		sf::Vector2f(m_particles[0].m_position.x, m_particles[0].m_position.y),
		sf::Vector2f(m_particles[1].m_position.x, m_particles[1].m_position.y),
		sf::Color::White
	);
	m_lines.emplace_back(s1);

	Line s2(
		sf::Vector2f(m_particles[1].m_position.x, m_particles[1].m_position.y),
		sf::Vector2f(m_particles[2].m_position.x, m_particles[2].m_position.y),
		sf::Color::White
	);
	m_lines.emplace_back(s2);

	Line s3(
		sf::Vector2f(m_particles[2].m_position.x, m_particles[2].m_position.y),
		sf::Vector2f(m_particles[3].m_position.x, m_particles[3].m_position.y),
		sf::Color::White
	);
	m_lines.emplace_back(s3);

	Line s4(
		sf::Vector2f(m_particles[3].m_position.x, m_particles[3].m_position.y),
		sf::Vector2f(m_particles[0].m_position.x, m_particles[0].m_position.y),
		sf::Color::White
	);
	m_lines.emplace_back(s4);

	Line s5(
		sf::Vector2f(m_particles[0].m_position.x, m_particles[0].m_position.y),
		sf::Vector2f(m_particles[2].m_position.x, m_particles[2].m_position.y),
		sf::Color::White
	);
	m_lines.emplace_back(s5);

	Line s6(
		sf::Vector2f(m_particles[1].m_position.x, m_particles[1].m_position.y),
		sf::Vector2f(m_particles[3].m_position.x, m_particles[3].m_position.y),
		sf::Color::White
	);
	m_lines.emplace_back(s6);
}

void Application::spawnParticle()
{
	m_particles.reserve(NUM_PARTICLES);

	//for (auto& i : m_particleConfigStorage)
	//{
	//	m_particle.m_position = Vec2(i.X, i.Y); //attributes of particle
	//	m_particle.m_mass = i.MASS;
	//	m_particle.setCircleRadius(i.RADIUS);
	//	m_particles.emplace_back(m_particle);
	//}

	//anchor = Vec2(m_window.getSize().x / 2.f, 30.f);

	/*Particle originP(anchor.x, anchor.y, 0.f, 5.f, sf::Color::Red);
	originP.setOrigin();
	m_particles.emplace_back(originP);

	for (size_t i = 1; i < NUM_PARTICLES; i++)
	{
		Particle p(anchor.x, anchor.y + (i * restLength), 2.f, 6.f, sf::Color::White);
		p.setOrigin();
		m_particles.emplace_back(p);
	}*/

	Particle a(100.f, 100.f, 1.f, 6.f, sf::Color::Red);
	a.setOrigin();
	m_particles.emplace_back(a);

	Particle b(300.f, 100.f, 1.f, 6.f, sf::Color::Red);
	b.setOrigin();
	m_particles.emplace_back(b);

	Particle c(300.f, 300.f, 1.f, 6.f, sf::Color::Red);
	c.setOrigin();
	m_particles.emplace_back(c);

	Particle d(100.f, 300.f, 1.f, 6.f, sf::Color::Red);
	d.setOrigin();
	m_particles.emplace_back(d);

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

		if (m_lineAppear) //line impulse
		{
			m_impulseLine.setPosition(
				sf::Vector2f(m_mouseCursor.x, m_mouseCursor.y),
				sf::Vector2f(m_particles[NUM_PARTICLES - 1].m_position.x, m_particles[NUM_PARTICLES - 1].m_position.y)
			);
			m_impulseLine.setColor(sf::Color::Red);
		}



		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (m_leftMouseButtonDown)
			{
				m_leftMouseButtonDown = false;
				m_lineAppear = false;

				//spring config
				int lastParticle = NUM_PARTICLES - 1;
				Vec2 impluseDirection = (m_particles[lastParticle].m_position - m_mouseCursor).UnitVector();
				float impulseMagnitude = (m_particles[lastParticle].m_position - m_mouseCursor).Magnitude() * 5.f;
				m_particles[lastParticle].m_velocity = impluseDirection * impulseMagnitude;

				//'impulse' force
				/*Vec2 impluseDirection = (m_particles[0].m_position - m_mouseCursor).UnitVector();
				float impulseMagnitude = (m_particles[0].m_position - m_mouseCursor).Magnitude() * 5.f;
				m_particles[0].m_velocity = impluseDirection * impulseMagnitude;*/
				std::cout << "mouse released" << '\n';
			}
		}

		if (!m_lineAppear)
		{
			m_impulseLine.clear();
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

	//'gravitational attraction' force
	//Vec2 attraction = Force::GenerateGravitationalForce(m_particles[0], m_particles[1], 1000000.f, 5.f, 100.f); //0.00000000006674f
	//m_particles[0].AddForce(attraction);
	//m_particles[1].AddForce(-attraction);

	//apply the forces here: (wind/air resistance, weight, friction, drag,...)
	for (auto& p : m_particles)
	{
		//'wind' force to the right
		/*Vec2 wind = Vec2(0.2f * PIXEL_PER_METER, 0.f);
		p.AddForce(wind);*/

		//apply drag/damp
		Vec2 drag = Force::GenerateDragForce(p, 0.002);
		p.AddForce(drag);

		//'push' force 
		p.AddForce(m_pushForce);

		//'weight' force down (weight = mass * gravity)
		Vec2 weight = Vec2(0.f, p.m_mass * GRAVITY * PIXEL_PER_METER);
		p.AddForce(weight);


		//'drag' force if inside the liquid
		//if (p.m_position.y >= m_liquid.getPosition().y)
		//{
		//	Vec2 drag = Force::GenerateDragForce(p, 0.02); //Case: DragForce is bigger than the velocity (results to unexpected behavior)
		//	p.AddForce(drag);							   //k = 0.01 -> 0.1
		//}

		//'friction' force
		/*Vec2 friction = Force::GenerateFrictionForce(p, 20.f * PIXEL_PER_METER);
		p.AddForce(friction);*/

	}

	//'spring' force (anchor)
	/*Vec2 springForce = Force::GenerateSpringForce(m_particles[0], anchor, restLength, k);
	m_particles[0].AddForce(springForce);*/

	//'spring' force (connected particles in chain of springs)
	/*for (int i = 1; i < NUM_PARTICLES; i++)
	{
		int currParticle = i;
		int prevParticle = i - 1;
		Vec2 springForce = Force::GenerateSpringForce(m_particles[currParticle], m_particles[prevParticle], restLength, k);
		m_particles[currParticle].AddForce(springForce);
		m_particles[prevParticle].AddForce(-springForce);
	}*/

	// 'square shape' part
	Vec2 ab = Force::GenerateSpringForce(m_particles[0], m_particles[1], restLength, k); // a <-> b
	m_particles[0].AddForce(ab);
	m_particles[1].AddForce(-ab);

	Vec2 bc = Force::GenerateSpringForce(m_particles[1], m_particles[2], restLength, k); // b <-> c
	m_particles[1].AddForce(bc);
	m_particles[2].AddForce(-bc);

	Vec2 cd = Force::GenerateSpringForce(m_particles[2], m_particles[3], restLength, k); // c <-> d
	m_particles[2].AddForce(cd);
	m_particles[3].AddForce(-cd);

	Vec2 da = Force::GenerateSpringForce(m_particles[3], m_particles[0], restLength, k); // d <-> a
	m_particles[3].AddForce(da);
	m_particles[0].AddForce(-da);

	// 'x shape' part
	Vec2 ac = Force::GenerateSpringForce(m_particles[0], m_particles[2], restLength, k); // a <-> c
	m_particles[0].AddForce(ac);
	m_particles[2].AddForce(-ac);

	Vec2 bd = Force::GenerateSpringForce(m_particles[1], m_particles[3], restLength, k); // b <-> d
	m_particles[1].AddForce(bd);
	m_particles[3].AddForce(-bd);


	/*std::cout << "p1  x: " << m_particles[0].m_position.x << " y: " << m_particles[0].m_position.y << '\n';
	std::cout << "p2  x: " << m_particles[1].m_position.x << " y: " << m_particles[1].m_position.y << '\n';*/


	for (auto& i : m_particles)
	{
		// (implicit euler integration)
		i.IntegrateVerlet(deltaTime);
	}
}



void Application::sCollision()
{
	for (auto& i : m_particles)
	{
		if (i.m_position.x - i.getRadius() <= 0) //left
		{
			i.m_position.x = i.getRadius();
			i.m_velocity.x *= -1.f;
		}
		else if (i.m_position.x + i.getRadius() >= m_window.getSize().x) //right
		{
			i.m_position.x = m_window.getSize().x - i.getRadius();
			i.m_velocity.x *= -1.f;
		}

		if (i.m_position.y - i.getRadius() <= 0) //top
		{
			i.m_position.y = i.getRadius();
			i.m_velocity.y *= -1.f;
		}
		else if (i.m_position.y + i.getRadius() >= m_window.getSize().y) //bottom
		{
			i.m_position.y = m_window.getSize().y - i.getRadius();
			i.m_velocity.y *= -1.f;
		}
	}
}


void Application::sRender()
{
	m_window.clear(sf::Color(9, 36, 79));
	m_window.draw(m_text);
	//m_window.draw(m_liquid);

	/*for (auto& i : m_particles)
	{
		i.setCirclePosition(i.m_position.x, i.m_position.y);
		i.draw(m_window);
	}*/

	/*for (int i = 0; i < NUM_PARTICLES - 1; i++)
	{
		int currParticle = i;
		int nextParticle = i + 1;
		m_lines[i].setPosition(
			sf::Vector2f(m_particles[currParticle].m_position.x, m_particles[currParticle].m_position.y),
			sf::Vector2f(m_particles[nextParticle].m_position.x, m_particles[nextParticle].m_position.y)
		);
	}*/

	m_lines[0].setPosition(
		sf::Vector2f(m_particles[0].m_position.x, m_particles[0].m_position.y),
		sf::Vector2f(m_particles[1].m_position.x, m_particles[1].m_position.y)
	);

	m_lines[1].setPosition(
		sf::Vector2f(m_particles[1].m_position.x, m_particles[1].m_position.y),
		sf::Vector2f(m_particles[2].m_position.x, m_particles[2].m_position.y)
	);

	m_lines[2].setPosition(
		sf::Vector2f(m_particles[2].m_position.x, m_particles[2].m_position.y),
		sf::Vector2f(m_particles[3].m_position.x, m_particles[3].m_position.y)
	);

	m_lines[3].setPosition(
		sf::Vector2f(m_particles[3].m_position.x, m_particles[3].m_position.y),
		sf::Vector2f(m_particles[0].m_position.x, m_particles[0].m_position.y)
	);

	m_lines[4].setPosition(
		sf::Vector2f(m_particles[0].m_position.x, m_particles[0].m_position.y),
		sf::Vector2f(m_particles[2].m_position.x, m_particles[2].m_position.y)
	);

	m_lines[5].setPosition(
		sf::Vector2f(m_particles[1].m_position.x, m_particles[1].m_position.y),
		sf::Vector2f(m_particles[3].m_position.x, m_particles[3].m_position.y)
	);



	for (auto& i : m_lines)
	{
		i.draw(m_window);
	}

	m_impulseLine.draw(m_window);

	for (auto& i : m_particles)
	{
		i.setCirclePosition(i.m_position.x, i.m_position.y);
		i.draw(m_window);
	}

	m_window.display();
}