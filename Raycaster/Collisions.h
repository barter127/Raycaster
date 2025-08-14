#pragma once

#ifndef _COLLISIONS_H
#define _COLLISIONS_H

#define BLOCK_WIDTH 1.01
#define BLOCK_HEIGHT 1.01

class GameObject;
class Vector2D;

struct BoxCollider
{
	bool isTrigger = false;

	GameObject* owner = nullptr;

	float x = 0;
	float y = 0;

	float width = 0;
	float height = 0;
};

static class Collisions
{
public:
	Collisions();
	~Collisions();

	/*
	* \brief Detect collision between two squares GameObjects.
	* 
	* GameObjects can pass through one another
	* 
	* \param Two BoxColliders for collision check.
	* 
	* \returns true on overlap.
	*/
	static bool BoxTrigger(BoxCollider a, BoxCollider b);

	/*
	* \brief Detect collision between two squares GameObjects.
	*
	* Detects BoxCollider overlap and performs a collision response by changing the position of a box colliders "owner" GameObject.
	*
	* \param Two BoxColliders for collision check.
	*
	* \returns true on overlap.
	*/
	static bool BoxHard(BoxCollider a, BoxCollider b);
};
#endif // _COLLISIONS_H

