#include "GameObject.h"

#include<iostream>
#include<string>

GameObject::GameObject(SDL_Renderer* renderer, Vector2D startPosition) : m_renderer(renderer), m_position(startPosition) {}


GameObject::~GameObject()
{
	m_renderer = nullptr;
}

// Returns Rect2D with size based on GameObjects image.
SDL_Rect GameObject::GetCollisionBox()
{
	if (m_collisionBoxWidth < 0)
	{
		std::cerr << "[!] Error: GameObject Collision Width is Negative" << std::endl;
		return SDL_Rect(0, 0, 0, 0);
	}
	else if (m_collisionBoxHeight < 0)
	{
		std::cerr << "[!] Error: GameObject Collision Width is Negative" << std::endl;
		return SDL_Rect(0, 0, 0, 0);
	}

	return SDL_Rect(m_position.x, m_position.y, m_collisionBoxWidth, m_collisionBoxHeight);
}