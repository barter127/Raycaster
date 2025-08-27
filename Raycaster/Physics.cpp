#include "Physics.h"

#include <iostream>
#include "Constants.h"

// Initalise physics variables using default values or 0 where applicable.
Physics::Physics()
{
	Vector3D m_velocity = { 0, 0, 0 };
	Vector3D m_acceleration = { 0, 0, 0 };

	m_mass = 1;

	// Counter forces.
	m_dragMultiplier = 1;
	m_frictionCoefficent = 1;
}

// Initalise physics variables using input parameters.
Physics::Physics(float mass, float friction, float drag) : m_mass(mass), m_frictionCoefficent(friction), m_dragMultiplier(drag)
{
	m_velocity = Vector3D(0, 0, 0);

	m_acceleration = Vector3D(0, 0, 0);
}

Physics::~Physics() {}

// Called in GameObject update to calculate physics.
// Holds all physics calculations in one place.
Vector3D Physics::PhysicsCalculation(float deltaTime)
{
	m_velocity += m_acceleration;

	ApplyFriction();
	ApplyDrag();

	m_velocity += m_acceleration; // Change veloicty.
	m_acceleration *= 0; // Reset accleration for next frame.

	return m_velocity * deltaTime;
}

void Physics::ApplyFriction()
{
	// Only apply friction if magnitude > 0.01f
	Vector3D friction = m_velocity;
	friction.Normalize();
	friction *= -1;
	friction *= m_frictionCoefficent;
	AddForce(friction, FORCE);
}

void Physics::ApplyDrag()
{
	// Only apply friction if magnitude > 0.01f
	Vector3D friction = m_velocity;
	friction.Normalize();
	friction *= -1;
	friction *= (m_dragMultiplier / m_mass);
	AddForce(friction, FORCE);
}

// ===== Set Force values =====

// Adds force in forceDirection. Forcemode specifies how the driving force fall off will apply.
void Physics::AddForce(Vector3D forceDirection, FORCEMODE forceMode)
{
	if (forceMode == FORCE)
	{
		Vector3D F = forceDirection / m_mass;
		m_acceleration = F;
	}
	// If forcemode impulse.
	else
	{
		m_velocity = forceDirection;
	}
}

void Physics::AddCounterForce(float forceCoefficent, FORCEMODE forceMode)
{
	if (forceMode == FORCE)
	{
		Vector3D F = (- m_velocity / m_mass) * forceCoefficent;
		m_acceleration = F;
	}
	// If forcemode impulse.
	else
	{
		m_velocity = -m_velocity * forceCoefficent;
	}
}