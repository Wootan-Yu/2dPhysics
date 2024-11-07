#pragma once
#include "Vec2.h"
#include <SFML/Graphics.hpp>

struct Particle
{
	sf::CircleShape m_circle;

	Vec2 m_position;
	Vec2 m_oldPosition;
	Vec2 m_velocity;
	Vec2 m_acceleration;

	Vec2 sumForces; //netForce/sumForce - total sum of forces applied (wind, friction, weight,...)

	float m_mass = 0;
	float m_inverseMass = 0;	// 1/mass
	float m_radius = 0;

	Particle();
	Particle(float x, float y, float mass, float radius, const sf::Color& color);
	
	void setCirclePosition(float x, float y);
	void setCircleRadius(float radius);
	void setCircleColor(const sf::Color& color);
	void setOrigin();

	float getRadius() const;

	void draw(sf::RenderWindow& window);

	void AddForce(const Vec2& force);
	void ClearForces();

	void IntegrateEuler(float deltaTime);
	void IntegrateVerlet(float deltaTime);
};

//use case: particle.position = Vec2(x,y);