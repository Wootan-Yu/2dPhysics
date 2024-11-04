#include "Particle.h"
#include <iostream>
#include "Constants.h"

Particle::Particle()
	: m_position(Vec2(0.f,0.f)), m_mass(0)
{
	/*m_circle.setPointCount(100);
	m_circle.setOrigin(m_circle.getRadius(), m_circle.getRadius());
	m_circle.setFillColor(sf::Color::White);
	m_circle.setRadius(10.f);*/
}

Particle::Particle(float x, float y, float mass, float radius, const sf::Color& color)
	: m_position(Vec2(x,y)), m_mass(mass), m_radius(radius)
{
	m_circle.setPointCount(100);
	m_circle.setOrigin(m_circle.getRadius(), m_circle.getRadius());
	m_circle.setFillColor(color);
	m_circle.setRadius(m_radius);
	//std::cout << "particle constructor called!" << '\n';
}


void Particle::AddForce(const Vec2& force)
{
	sumForces += force;
}

void Particle::ClearForces()
{
	sumForces = Vec2(0.f, 0.f);
}

void Particle::Integrate(float deltaTime)
{
	if (m_mass != 0.f)
	{
		m_inverseMass = 1.f / m_mass;
	}
	else
	{
		m_inverseMass = 0.f;
	}

	// integration techniques:
	// 1. implicit euler - most popular and simplest integration techniques in game physics. its accuracy is 'good enough'
	//			velocity += acceleration * dt
	//			position += velocity * dt
	// 2. verlet integration - provide great accuracy than implicit euler and less memory usage when simulating 'large number of particles'
	// 3. runga-kutta integration - family of integrator. 
	//			-RK4 is the most popular implementation.
	//			-accumulates error in order of 4th derivative which makes it very accurate than euler which only 1st order

	//given constant value of 9.8m/s^2
	//m_acceleration = Vec2(2.f * PIXEL_PER_METER, GRAVITY * PIXEL_PER_METER);

	//acceleration = netforce / mass (not constant anymore) from F = ma (netForce = mass * acceleration) 2nd law of motion
	//m_acceleration = sumForces / m_mass;
	m_acceleration = sumForces * m_inverseMass;

	// (implicit euler integration)
	//integrate the 'acceleration' to find the 'new velocity' (velocity = integralSign(acceleration * deltaTime))
	m_velocity += m_acceleration * deltaTime;

	//integrate the 'velocity' to find the 'new position' (position = integralSign(velocity * deltaTime))
	m_position += m_velocity * deltaTime;

	ClearForces();
}

//todo: draw function
void Particle::draw(sf::RenderWindow& window)
{
	window.draw(m_circle);
}

void Particle::setCirclePosition(float x, float y)
{
	m_circle.setPosition(sf::Vector2f(x, y));
}

void Particle::setCircleRadius(float radius)
{
	m_radius = radius;
	m_circle.setRadius(radius);
}

float Particle::getRadius() const
{
	return m_circle.getRadius();
}

void Particle::setCircleColor(const sf::Color& color)
{
	m_circle.setFillColor(color);
}

void Particle::setOrigin()
{
	m_circle.setOrigin(m_radius, m_radius);
}