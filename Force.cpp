#include "Force.h"

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
Vec2 Force::GenerateGravitationalForce(const Particle& a, const Particle& b, float G)
{
	Vec2 distance = b.m_position - a.m_position;

	float distanceSquared = distance.MagnitudeSquared();

	Vec2 attractionDirection = distance.UnitVector();
	float attractionMagnitude = G * (a.m_mass * b.m_mass) / distanceSquared;

	Vec2 attractionForce = attractionDirection * attractionMagnitude;

	return attractionForce;
}


//todo: generate spring force