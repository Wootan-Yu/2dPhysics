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
	
	//change this according to the number of particles inside 'config.txt file'
	int m_numParticles = 2; 



	//spring config
	//Vec2 anchor = Vec2(0.f, 0.f);
	float k = 2000.f; //stiffness
	float restLength = 200.f; //distance
	const int NUM_PARTICLES = 4;
	//const int NUM_PARTICLES = 13;
	

	std::vector<ParticleConfig> m_particleConfigStorage;
	std::vector<Particle> m_particles;
	std::vector<Line> m_lines;

	std::string m_type;
	bool m_running = true;
	bool m_leftMouseButtonDown = false;
	bool m_lineAppear = false;
	

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