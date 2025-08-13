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
                    m_position.x -= m_direction.x * m_movementSpeed * deltaTime;
                    break;
                }

                // Move backwards.
                case SDLK_DOWN:
                {
                    m_position.x += m_direction.x * m_movementSpeed * deltaTime;
                    break;
                }

                // Rotate to the right.
                case SDLK_RIGHT:
                {
                    // Both camera direction and camera plane must be rotated.
                    float oldDirX = m_direction.x;
                    m_direction.x = m_direction.x * cos(-m_rotationSpeed) - m_direction.y * sin(-m_rotationSpeed);
                    m_direction.y = oldDirX * sin(-m_rotationSpeed) + m_direction.y * cos(-m_rotationSpeed);

                    float oldPlaneX = m_plane.x;
                    m_plane.x = m_plane.x * cos(-m_rotationSpeed) - m_plane.y * sin(-m_rotationSpeed);
                    m_plane.y = oldPlaneX * sin(-m_rotationSpeed) + m_plane.y * cos(-m_rotationSpeed);

                    m_position.y += m_plane.y * m_movementSpeed * deltaTime;
                    break;
                }

                // Rotate to the left.
                case SDLK_LEFT:
                {
                    // Both camera direction and camera plane must be rotated.
                    float oldDirX = m_direction.x;
                    m_direction.x = m_direction.x * cos(m_rotationSpeed) - m_direction.y * sin(m_rotationSpeed);
                    m_direction.y = oldDirX * sin(m_rotationSpeed) + m_direction.y * cos(m_rotationSpeed);

                    float oldPlaneX = m_plane.x;
                    m_plane.x = m_plane.x * cos(m_rotationSpeed) - m_plane.y * sin(m_rotationSpeed);
                    m_plane.y = oldPlaneX * sin(m_rotationSpeed) + m_plane.y * cos(m_rotationSpeed);

                    //both camera direction and camera plane must be rotated
                    m_position.y -= m_plane.y * m_movementSpeed * deltaTime;
                    break;
                }
            }
        }
    }
}

void Player::Render()
{

}