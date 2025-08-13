#include "Player.h"

Player::Player(SDL_Renderer* renderer, Vector2D startPosition) : GameObject(m_renderer, startPosition) {}

Player::~Player() {}

void Player::Update(float deltaTime, SDL_Event event)
{
    switch (event.type)
    {
        case SDL_KEYDOWN:
        {
            switch (event.key.keysym.sym) {

                case SDLK_UP:
                {
                    m_position.x -= m_movementSpeed * deltaTime;
                    break;
                }

                // Move backwards.
                case SDLK_DOWN:
                {
                    m_position.x += m_movementSpeed * deltaTime;
                    break;
                }

                // Rotate to the right.
                case SDLK_RIGHT:
                {
                    //both camera direction and camera plane must be rotated
                    m_position.y += m_movementSpeed * deltaTime;
                    break;
                }

                // Rotate to the left.
                case SDLK_LEFT:
                {
                    //both camera direction and camera plane must be rotated
                    m_position.y -= m_movementSpeed * deltaTime;
                    break;
                }
            }
        }
    }
}

void Player::Render()
{

}