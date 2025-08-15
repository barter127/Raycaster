#include "Player.h"

Player::Player(SDL_Renderer* renderer, Vector2D startPosition) : GameObject(m_renderer, startPosition) {}

Player::~Player() {}

void Player::Update(float deltaTime, SDL_Event event)
{
    m_collider.x = m_position.x;
    m_collider.y = m_position.y;

    Input(event);
    Movement(deltaTime);
}

void Player::Render()
{

}

void Player::Movement(float deltaTime)
{
    if (m_forwardDown)
    {
        m_position += m_direction * m_movementSpeed * deltaTime;
    }

    if (m_backwardsDown)
    {
        m_position -= m_direction * m_movementSpeed * deltaTime;
    }

    if (m_rightDown)
    {
        // Cache Cos and Sin values to prevent recaclulcation.
        float rotationCos = cosf(-m_rotationSpeed);
        float rotationSin = sinf(-m_rotationSpeed);

        // Both camera direction and camera plane must be rotated.
        float oldDirX = m_direction.x;
        m_direction.x = m_direction.x * rotationCos - m_direction.y * rotationSin;
        m_direction.y = oldDirX * rotationSin + m_direction.y * rotationCos;

        float oldPlaneX = m_plane.x;
        m_plane.x = m_plane.x * rotationCos - m_plane.y * rotationSin;
        m_plane.y = oldPlaneX * rotationSin + m_plane.y * rotationCos;

        m_position += m_direction * m_movementSpeed * deltaTime;
    }

    if (m_leftDown)
    {
        // Cache Cos and Sin values to prevent recaclulcation.
        float rotationCos = cosf(m_rotationSpeed);
        float rotationSin = sinf(m_rotationSpeed);

        // Both camera direction and camera plane must be rotated.
        float oldDirX = m_direction.x;
        m_direction.x = m_direction.x * rotationCos - m_direction.y * rotationSin;
        m_direction.y = oldDirX * rotationSin + m_direction.y * rotationCos;

        float oldPlaneX = m_plane.x;
        m_plane.x = m_plane.x * rotationCos - m_plane.y * rotationSin;
        m_plane.y = oldPlaneX * rotationSin + m_plane.y * rotationCos;

        //both camera direction and camera plane must be rotated
        m_position -= m_direction * m_movementSpeed * deltaTime;
    }
}

void Player::Input(SDL_Event event)
{
    switch (event.type)
    {
        case SDL_KEYDOWN:
        {
            switch (event.key.keysym.sym) 
            {
                case SDLK_UP:
                {
                    m_forwardDown = true;
                    break;
                }

                // Move backwards.
                case SDLK_DOWN:
                {
                    m_backwardsDown = true;
                    break;
                }

                // Rotate to the right.
                case SDLK_RIGHT:
                {
                    m_rightDown = true;
                    break;
                }

                // Rotate to the left.
                case SDLK_LEFT:
                {
                    m_leftDown = true;
                    break;
                }
            }
            break;
        }

        case SDL_KEYUP:
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_UP:
                {
                    m_forwardDown = false;
                    break;
                }

                // Move backwards.
                case SDLK_DOWN:
                {
                    m_backwardsDown = false;;
                    break;
                }

                // Rotate to the right.
                case SDLK_RIGHT:
                {
                    m_rightDown = false;
                    break;
                }

                // Rotate to the left.
                case SDLK_LEFT:
                {
                    m_leftDown = false;
                    break;
                }
            }
            break;
        }
    }
}