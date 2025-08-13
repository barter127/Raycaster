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

                    m_position.y += m_plane.y * m_movementSpeed * deltaTime;
                    break;
                }

                // Rotate to the left.
                case SDLK_LEFT:
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