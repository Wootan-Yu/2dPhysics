#pragma once
#include <SFML/Graphics.hpp>
#include "Particle.h"
#include <vector>
#include "Line.h"

struct ParticleConfig { int INDEX, X, Y, MASS, RADIUS; };

class Application
{
	sf::RenderWindow m_window;
	sf::CircleShape m_circle;
	sf::Font m_font;
	sf::Text m_text;
	sf::Clock m_clock;

	ParticleConfig m_particleConfig;
	Particle m_particle;

	Line m_line;

	Vec2 m_pushForce = Vec2(0.f, 0.f);
	Vec2 m_mouseCursor = Vec2(0.f, 0.f);

	//todo: create fluid
	sf::RectangleShape m_liquid;
	
	std::vector<ParticleConfig> m_particleConfigStorage;
	std::vector<sf::CircleShape> m_particleShapes;
	std::vector<Particle> m_particles;

	std::string m_type;
	bool m_running = true;
	bool m_leftMouseButtonDown = false;
	bool m_lineAppear = false;
	int m_numParticles = 1; //change this according to the number of particles inside config file

	void init(const std::string& path);
	void sCollision();
	void sMovement();
	void sUserInput();
	void sRender();

	void spawnParticle(int numParticle);
	void spawnLiquid();

public:
	Application(const std::string& config);
	void run(); //update 
};