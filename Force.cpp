#include "Force.h"
#include <algorithm>


//drag - resistive force acting in the opposite direction of the relative motion
//		 of any moving object with respect to surrounding liquid
//	   - depends on velocity
// dragForce = 1/2 * fluidDensity * coefficientOfDrag(Kd) * Cross-SectionalArea(A) * magnitudeOfVelocity(||V||^2) * inverseOfVelocityDirection(-v)

// 1/2 * fluidDensity * coefficientOfDrag(Kd) * Cross-SectionalArea(A) = k (can be replaced by 1 constant)

// final formula: dragForce = k * magnitudeOfVelocity(||V||^2) * inverseOfVelocityDirection(-v)
Vec2 Force::GenerateDragForce(const Particle& particle, float k)
{
	Vec2 dragForce = Vec2(0.f, 0.f);
	if (particle.m_velocity.MagnitudeSquared() > 0)
	{
		//calculate the drag direction (inverse of velocity unit vector)
		Vec2 dragDirection = particle.m_velocity.UnitVector() * -1.f;

		//calculate the drag magnitude, k * |v|^2
		float dragMagnitude = k * particle.m_velocity.MagnitudeSquared();

		//generate the final drag force with direction and magnitude
		dragForce = dragDirection * dragMagnitude;
	}
	return dragForce;
}


//todo: generate friction force
// friction - is a contact force that resist sliding between surfaces
//		2 types of friction:
//			kinetic friction - friction force when object is sliding (moving) along the surface.
//			static friction - friction force that prevents an object from sliding along the surface.

//		frictionForce = coefficientOfFriction * normalForce(||Fn||) * inverseOfVelocityDirection(-v)
Vec2 Force::GenerateFrictionForce(const Particle& particle, float k)
{
	Vec2 frictionForce = Vec2(0.f, 0.f);

	//calculate the friction direction (inverse of velocity unit vector)
	Vec2 frictionDirection = particle.m_velocity.UnitVector() * -1.f;

	//calculate the friction magnitude (constant for now)
	float frictionMagnitude = k;

	//calculate the final friction force
	frictionForce = frictionDirection * frictionMagnitude;

	return frictionForce;
}


//todo: generate gravitational force
// every object with mass exerts a gravitational force on every other object

//		gravitationalAttractionForce = universal_GravitationConstant * ((mass_a * mass_b) / magnitudeDistance_squared) * direction_of_the_attractionForce
Vec2 Force::GenerateGravitationalForce(const Particle& a, const Particle& b, float G, float minDistance, float maxDistance)
{
	//distance between 2 objects
	Vec2 distance = b.m_position - a.m_position;

	float distanceSquared = distance.MagnitudeSquared();


	//this is only used to feel the attraction between objects
	distanceSquared = std::clamp(distanceSquared, minDistance, maxDistance); //clamp the values of the distance (for some interesting visual effects)


	//direction of the attraction force
	Vec2 attractionDirection = distance.UnitVector();

	//strength of the attraction force
	float attractionMagnitude = G * (a.m_mass * b.m_mass) / distanceSquared;

	//final resulting attraction of force vector
	Vec2 attractionForce = attractionDirection * attractionMagnitude;
	return attractionForce;
}


//todo: generate spring force
// spring force - calculate according to Hooke's law, which states that
//				  "the force of the spring is proportional to the displacement of the spring(extanded or compressed)"

//		springForce = spring_constant(-k) * spring_displacement(deltaLength)
Vec2 Force::GenerateSpringForce(const Particle& particle, Vec2 anchor, float restLength, float k)
{
	//calculate the distance between the anchor and the object
	Vec2 distance = particle.m_position - anchor;

	//find the spring displacement considering the rest length
	float displacement = distance.Magnitude() - restLength;

	//calculate the direction and the magnitude of the spring force
	Vec2 springDirection = distance.UnitVector();
	float springMagnitude = -k * displacement;

	//calculate the final resulting spring force vector
	Vec2 springForce = springDirection * springMagnitude;
	return springForce;
}

Vec2 Force::GenerateSpringForce(const Particle& a, const Particle& b, float restLength, float k)
{
	//calculate the distance between 2 particles
	Vec2 distance = a.m_position - b.m_position;

	//find the spring displacement considering the rest length
	float displacement = distance.Magnitude() - restLength;

	//calculate the direction and the magnitude of the spring force
	Vec2 springDirection = distance.UnitVector();
	float springMagnitude = -k * displacement;

	//calculate the final resulting spring force vector
	Vec2 springForce = springDirection * springMagnitude;
	return springForce;
}