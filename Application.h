#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "Line.h"
#include "Particle.h"

struct ParticleConfig { int INDEX, X, Y, MASS, RADIUS; };

class Application
{
	sf::RenderWindow m_window;
	sf::Font m_font;
	sf::Text m_text;
	sf::Clock m_clock;

	ParticleConfig m_particleConfig;
	Particle m_particle;

	Vec2 m_pushForce = Vec2(0.f, 0.f);
	Vec2 m_mouseCursor = Vec2(0.f, 0.f);

	//todo: create fluid
	sf::RectangleShape m_liquid;

	//impulse config
	Line m_impulseLine;

	//spring config
	Vec2 anchor = Vec2(0, 0);
	float k = 300.f;
	float restLength = 15.f;
	const int NUM_PARTICLES = 13;
	
	std::vector<ParticleConfig> m_particleConfigStorage;
	std::vector<Particle> m_particles;
	std::vector<Line> m_lines;

	std::string m_type;
	bool m_running = true;
	bool m_leftMouseButtonDown = false;
	bool m_lineAppear = false;
	int m_numParticles = 2; //change this according to the number of particles inside config file

	void init(const std::string& path);
	void sCollision();
	void sMovement();
	void sUserInput();
	void sRender();

	void spawnParticle();
	void spawnLiquid();
	void spawnLine();

public:
	Application(const std::string& config);
	void run(); //update 
};