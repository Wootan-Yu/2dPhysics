#pragma once
#include "Vec2.h"
#include <SFML/Graphics.hpp>

struct Particle
{
	float radius = 0;

	Vec2 m_position;
	Vec2 m_velocity;
	Vec2 m_acceleration;

	Vec2 sumForces; //netForce/sumForce - total sum of forces applied (wind, friction, weight,...)

	float m_mass = 0;
	float m_inverseMass = 0;	// 1/mass

	Particle();
	Particle(float x, float y, float mass);

	void AddForce(const Vec2& force);
	void ClearForces();

	void Integrate(float deltaTime);
};

//use case: particle.position = Vec2(x,y);