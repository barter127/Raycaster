#pragma once

#ifndef _PHYSICS_H
#define _PHYSICS_H

#include "Vector3D.h";

enum FORCEMODE
{
	FORCE,
	IMPULSE
};

class Physics
{
private:
	// Velocity.
	Vector3D m_velocity = { 0, 0, 0 };
	Vector3D m_acceleration = {0, 0, 0};

	float m_mass = 4.0f;

	// Counter forces.
	float m_dragMultiplier = 50.0f; // Maybe this could be const.

	float m_frictionCoefficent = 1.5f;

	void ApplyFriction();
	void ApplyDrag();

public:
	// Initalise physics variables using default values or 0 where applicable.
	Physics();
	// Initalise physics variables using input parameters.
	Physics(float mass, float friction, float drag);

	~Physics();

	/// Call to activate main physics loop.
	/// Calculates objects current velocity using drivingForce, accleration, and delta.
	/// Calls ReduceDrivingForce() to apply counterforces
	/// Resets acceleration.
	Vector3D PhysicsCalculation(float deltaTime);


	/// Add force to be applied.
	/// Forcemode specifies how the force will affect the GameObject.
	/// Forcemode FORCE: Applies constant force with acceleration, drag, and friction.
	/// Forcemode IMPULSE: Applies instant force.
	void AddForce(Vector3D forceDirection, FORCEMODE forceMode);

	/// Add force in the opposite direction of the current velocity.
	/// Multiply vector by forceCoefficent.
	/// Forcemode specifies how the force will affect the GameObject.
	/// Forcemode FORCE: Applies constant force with acceleration, drag, and friction.
	/// Forcemode IMPULSE: Applies instant force.
	void AddCounterForce(float forceCoefficent, FORCEMODE forceMode);

	inline void SetDrag(float newDrag) { m_dragMultiplier = newDrag; }

	inline void SetFriction(float newFriction) { m_frictionCoefficent = newFriction;  }

	inline void SetMass(float newMass) { m_mass = newMass; }
};
#endif

