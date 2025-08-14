#include "GameObject.h"

#include<iostream>
#include<string>

GameObject::GameObject(SDL_Renderer* renderer, Vector2D startPosition) : m_renderer(renderer), m_position(startPosition) {}


GameObject::~GameObject()
{
	m_renderer = nullptr;
}