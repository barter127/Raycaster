#pragma once

#ifndef _COLLISIONS_H
#define _COLLISIONS_H

class GameObject;
class Vector2D;

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
	* \param Two GameObjects for collision check.
	* 
	* \returns true on overlap.
	*/
	bool BoxTrigger(GameObject* a, GameObject* b);

	/*
	* \brief Detect collision between two squares GameObjects.
	*
	* GameObjects cannot pass through one another and performs a collision response by changing the position of GameObject a
	*
	* \param Two GameObjects for collision check.
	*
	* \returns true on overlap.
	*/
	bool BoxHard(GameObject* a, GameObject* b);
};
#endif // _COLLISIONS_H

