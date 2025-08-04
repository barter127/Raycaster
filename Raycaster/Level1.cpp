#include "Level1.h"
#include <cmath>
#include <iostream>

#define MAP_WIDTH 24
#define MAP_HEIGHT 24
int worldMap[MAP_WIDTH][MAP_HEIGHT] = {
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

#include "Surface2D.h"
#include "WindowConstants.h"

#ifndef _TRANSLATE_COLOUR
#define _TRANSLATE_COLOUR
SDL_Color TranslateColour(Uint32 int_colour) {
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    SDL_Color colour = {
        (int_colour >> 24) & 0xFF,  // Red
        (int_colour >> 16) & 0xFF,  // Green
        (int_colour >> 8) & 0xFF,  // Blue
        int_colour & 0xFF   // Alpha
    };

#else
    SDL_Color colour = {
        int_colour & 0xFF,        // Red
        (int_colour >> 8) & 0xFF,        // Green
        (int_colour >> 16) & 0xFF,        // Blue
        (int_colour >> 24) & 0xFF         // Alpha
    };
#endif

    return colour;
}

#endif // !_TRANSLATE_COLOUR

Surface2D* tempTexture = nullptr;
// SDL_Texture* screenBuffer = nullptr;

Level1::Level1(SDL_Renderer* renderer) : Screen(renderer)
{
    // screenBuffer = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

    tempTexture = new Surface2D(m_renderer);
    tempTexture->LoadFromFile("Assets/redbrick.png");
}

Level1::~Level1()
{

}

float posX = 22, posY = 12;  // X and y start position.
float dirX = -1, dirY = 0; // Initial direction vector.
float planeX = 0, planeY = 0.66; // The 2d raycaster version of camera plane.
float moveSpeed = 2.0f;
float rotSpeed = 1.0f;

void Level1::Update(float deltaTime, SDL_Event event)
{
    switch (event.type)
    {
        case SDL_KEYDOWN:
        {
            switch (event.key.keysym.sym) {

                case SDLK_UP:
                {
                    if (worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
                    if (worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
                    break;
                }

                    //move backwards if no wall behind you
                case SDLK_DOWN:
                {
                    if (worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
                    if (worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
                    break;
                }
                    //rotate to the right
                case SDLK_RIGHT:
                {
                    //both camera direction and camera plane must be rotated
                    double oldDirX = dirX;
                    dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
                    dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
                    double oldPlaneX = planeX;
                    planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
                    planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
                    break;
                }

                    //rotate to the left
                case SDLK_LEFT:
                {
                    //both camera direction and camera plane must be rotated
                    double oldDirX = dirX;
                    dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
                    dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
                    double oldPlaneX = planeX;
                    planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
                    planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
                    break;
                }

                default:
                    std::cout << "No input";
            }
        }
    }
}

void Level1::Render()
{
    int width = 640;
    int height = 480;

    int texWidth = 64;
    int texHeight = 64;

    int* pixelData = (int*)tempTexture->GetPixelData();

    SDL_Texture* screenBuffer = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

    void* pixels;
    int pitch;
    SDL_LockTexture(screenBuffer, NULL, &pixels, &pitch);

    // Clear the buffer.

    for (int x = 0; x < width; x++)
    {

        // GUT THIS AFTER RAYCAST FINISHED.
        // Calculate ray position and direction.
        float cameraX = 2 * x / float(width) - 1; // X coordinate in camera space.
        float rayDirX = dirX + planeX * cameraX;
        float rayDirY = dirY + planeY * cameraX;

        // Which box of the map we're in.
        int mapX = int(posX);
        int mapY = int(posY);

        // Length of ray from current position to next x or y side.
        float sideDistX;
        float sideDistY;

        // Length of ray from one x or y side to next x or y side.
        float deltaDistX = (rayDirX == 0) ? 1e30 : abs(1 / rayDirX);
        float deltaDistY = (rayDirY == 0) ? 1e30 : abs(1 / rayDirY);
        float perpWallDist;

        // What direction to step in x or y-direction (either +1 or -1.
        int stepX;
        int stepY;

        int hit = 0; // Was there a wall hit?
        int side; // Was a NS or a EW wall hit?

        // Calculate step and initial sideDist.
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }

        //perform DDA
        while (hit == 0)
        {
            //jump to next map square, either in x-direction, or in y-direction
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            //Check if ray has hit a wall
            if (worldMap[mapX][mapY] > 0) hit = 1;
        }

        //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
        if (side == 0) perpWallDist = (sideDistX - deltaDistX);
        else  perpWallDist = (sideDistY - deltaDistY);


        //Calculate height of line to draw on screen
        int lineHeight = (int)(height / perpWallDist);

        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + height / 2;
        if (drawStart < 0)drawStart = 0;
        int drawEnd = lineHeight / 2 + height / 2;
        if (drawEnd >= height)drawEnd = height - 1;

        Uint32 colour = 0;

        //texturing calculations
        int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

        //calculate value of wallX
        double wallX; //where exactly the wall was hit
        if (side == 0) wallX = posY + perpWallDist * rayDirY;
        else           wallX = posX + perpWallDist * rayDirX;
        wallX -= floor((wallX));

        //x coordinate on the texture
       int texX = int(wallX * double(texWidth));
       if (side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
       if (side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

        // How much to increase the texture coordinate per screen pixel
        double step = 1.0f * texHeight / lineHeight;
        //Starting texture coordinate
        double texPos = (drawStart - height / 2 + lineHeight / 2) * step;
        for (int y = drawStart; y < drawEnd; y++)
        {
            // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
            int texY = (int)texPos & (texHeight - 1);
            texPos += step;
            colour = pixelData[texHeight * texY + texX];

            // Make colour darker for y-sides.
            if (side == 1) colour = colour / 2;

            // Copy buffer into locked texture memory
            std::memcpy((int*)pixels + y * SCREEN_WIDTH + x, &colour, sizeof(colour));
        }

    }
        SDL_UnlockTexture(screenBuffer);

        // Render to screen
        SDL_RenderCopy(m_renderer, screenBuffer, NULL, NULL);
}