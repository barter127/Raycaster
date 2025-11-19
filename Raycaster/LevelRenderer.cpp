#include "LevelRenderer.h"

#include <iostream>
#include <assert.h>

#include "WindowData.h"
#include "LevelTexture.h"
#include "Vector2D.h"

LevelRenderer::LevelRenderer(SDL_Renderer* renderer, LMap* map) 
    : m_renderer(renderer)
{
    m_map = map;

    std::vector<std::string> texturePaths = m_map->GetTexturePaths();

    for (std::string path : texturePaths)
    {
        LevelTexture* tempTexture = new LevelTexture(m_renderer);
        tempTexture->LoadFromFile(path);
        m_levelTextureArray.push_back(tempTexture);
    }

    m_floorTexture = new LevelTexture(m_renderer);
    m_floorTexture->LoadFromFile("Assets/Dirt_Road_64x64.png");

    m_ceilingTexture = new LevelTexture(m_renderer);
    m_ceilingTexture->LoadFromFile("Assets/Wooden_Floor_Horizontal_64x64.png");

    m_backBuffer = SDL_CreateRGBSurfaceWithFormat(0, g_windowData.width, g_windowData.height, 2, SDL_PIXELFORMAT_RGBA32);
}

LevelRenderer::~LevelRenderer()
{
    delete m_floorTexture;
    m_floorTexture = nullptr;
    m_floorTexture->Free();

    delete m_ceilingTexture;
    m_ceilingTexture = nullptr;
    m_ceilingTexture->Free();
}

void LevelRenderer::Render(Vector2D position, Vector2D direction, Vector2D plane)
{
    // Clear the buffer.
    SDL_LockSurface(m_backBuffer);
    SDL_FillRect(m_backBuffer, NULL, 0xe0afba);

    if (m_map->GetWidth() && m_map->GetHeight())
    {
        RenderCeilRoof(position, direction, plane);
        RenderWalls(position, direction, plane);
    }

    // Unlock buffer.
    SDL_UnlockSurface(m_backBuffer);
    m_frontBuffer = SDL_CreateTextureFromSurface(m_renderer, m_backBuffer);

    // Render to screen.
    SDL_RenderCopy(m_renderer, m_frontBuffer, NULL, NULL);

    // Destroy Texture for next render pass.
    SDL_DestroyTexture(m_frontBuffer);
}

void LevelRenderer::AddTexture(std::string path)
{
    LevelTexture* tempTexture = new LevelTexture(m_renderer);
    tempTexture->LoadFromFile(path);
    m_levelTextureArray.push_back(tempTexture);
}

void LevelRenderer::RenderWalls(Vector2D position, Vector2D direction, Vector2D plane)
{
    LevelArray lArray = m_map->GetLevelArray();

    for (int x = 0; x < g_windowData.width; x++)
    {
        // Calculate ray position and direction.
        float cameraX = 2 * x / float(g_windowData.width) - 1; // X coordinate in camera space.
        float rayDirX = direction.x + plane.x * cameraX;
        float rayDirY = direction.y + plane.y * cameraX;

        // Which box of the map we're in.
        int mapX = int(position.x);
        int mapY = int(position.y);

        // Length of ray from current position to next x or y side.
        float sideDistX;
        float sideDistY;

        // Length of ray from one x or y side to next x or y side.
        float deltaDistX = (rayDirX == 0) ? 1e30 : abs(1 / rayDirX);
        float deltaDistY = (rayDirY == 0) ? 1e30 : abs(1 / rayDirY);
        float perpWallDist;

        // What direction to step in x or y-direction (either +1 or -1).
        int stepX = 0;
        int stepY = 0;

        int hit = 0; // Was there a wall hit?
        int side = 0; // Was a NS or a EW wall hit?

        // Calculate step and initial sideDist.
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (position.x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - position.x) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (position.y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - position.y) * deltaDistY;
        }

        // Perform DDA.
        while (hit == 0)
        {
            // Jump to next map square, either in x-direction, or in y-direction.
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
            // Check if ray has hit a wall.
            if (lArray[mapX][mapY] > 0) hit = 1;
        }

        // Calculate distance projected on camera direction.
        if (side == 0) perpWallDist = (sideDistX - deltaDistX);
        else  perpWallDist = (sideDistY - deltaDistY);


        // Calculate height of line to draw on screen.
        int lineHeight = (int)(g_windowData.height / perpWallDist);

        // Calculate lowest and highest pixel to fill in current stripe.
        int drawStart = -lineHeight / 2 + g_windowData.height / 2;
        if (drawStart < 0)drawStart = 0;
        int drawEnd = lineHeight / 2 + g_windowData.height / 2;
        if (drawEnd >= g_windowData.height)drawEnd = g_windowData.height - 1;

        Uint32 colour = 0;

        // Texturing calculations.
        int texNum = lArray[mapX][mapY] - 1;

        int texWidth = m_levelTextureArray[texNum]->GetWidth();
        int texHeight = m_levelTextureArray[texNum]->GetHeight();

        // Calculate value of wallX.
        float wallX; //Where the wall was hit
        if (side == 0) wallX = position.y + perpWallDist * rayDirY;
        else           wallX = position.x + perpWallDist * rayDirX;
        wallX -= floor((wallX));

        // X coordinate on the texture.
        int texX = int(wallX * float(texWidth));
        if (side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
        if (side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

        // How much to increase the texture coordinate per screen pixel
        float step = 1.0f * texHeight / lineHeight;
        //Starting texture coordinate
        float texPos = (drawStart - g_windowData.height / 2 + lineHeight / 2) * step;
        for (int y = drawStart; y < drawEnd; y++)
        {
            // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
            int texY = (int)texPos & (texHeight - 1);
            texPos += step;

            colour = GetPixelColour(m_levelTextureArray[texNum], texY, texX);

            // Make colour darker for y-sides.
            // if (side == 1) colour = (colour & 0xfefefefe) >> 1; // Later break colour down to RGBA and allow control of components.

            CopyPixel(m_backBuffer, m_levelTextureArray[texNum], colour, x, y);
        }
    }
}

void LevelRenderer::RenderCeilRoof(Vector2D position, Vector2D direction, Vector2D plane)
{
    assert(m_floorTexture->GetHeight() == m_ceilingTexture->GetHeight());
    assert(m_floorTexture->GetWidth() == m_ceilingTexture->GetWidth());

    // Make sure ceiling and floor has the same dimensions.
    int texWidth = m_floorTexture->GetWidth();
    int texHeight = m_floorTexture->GetHeight();

    FloorData cachedFloorData = m_map->GetFloorData();
    FloorData cachedCeilData = m_map->GetCeilingData();

    Uint32 colour;

    for (int y = 0; y < g_windowData.height / 2; y++)
    {
        // rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
        float rayDirX0 = direction.x - plane.x;
        float rayDirY0 = direction.y - plane.y;
        float rayDirX1 = direction.x + plane.x;
        float rayDirY1 = direction.y + plane.y;

        // Current y position compared to the center of the screen (the horizon).
        float p = y - g_windowData.height / 2;

        // Vertical position of the camera.
        float posZ = 0.5 * g_windowData.height;

        // Horizontal distance from the camera to the floor for the current row.
        // 0.5 is the z position exactly in the middle between floor and ceiling.
        float rowDistance = posZ / p;

        // Calculate the real world step vector we have to add for each x (parallel to camera plane).
        // Adding step by step avoids multiplications with a weight in the inner loop.
        float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / g_windowData.width;
        float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / g_windowData.width;

        // Real world coordinates of the leftmost column. This will be updated as we step to the right.
        float floorX = position.x + rowDistance * rayDirX0;
        float floorY = position.y + rowDistance * rayDirY0;

        for (int x = 0; x < g_windowData.width; ++x)
        {
            // The cell coord is simply got from the integer parts of floorX and floorY.
            int cellX = int(floorX);
            int cellY = int(floorY);

            // Get the texture coordinate from the fractional part.
            int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
            int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);

            floorX += floorStepX;
            floorY += floorStepY;

            colour = 0;

            // Render Floor on the botton half of the screen.
            if (cachedFloorData.isCheckered)
            {
                int checkerBoardPattern = (int(cellX + cellY)) % cachedFloorData.multiplier1;

                if (checkerBoardPattern < cachedFloorData.multiplier2) colour = GetPixelColour(m_levelTextureArray[1], tx, ty);
                else colour = GetPixelColour(m_floorTexture, tx, ty); // Arbitrary texture.
            }
            else
            {
                colour = GetPixelColour(m_floorTexture, tx, ty);
            }

            CopyPixel(m_backBuffer, m_floorTexture, colour, x, g_windowData.height - y);

            // Render Ceiling on the top half of the screen.
            if (cachedCeilData.isCheckered)
            {
                int checkerBoardPattern = (int(cellX + cellY)) % cachedCeilData.multiplier1;

                if (checkerBoardPattern < cachedCeilData.multiplier2) colour = GetPixelColour(m_levelTextureArray[1], tx, ty);
                else colour = GetPixelColour(m_ceilingTexture, tx, ty); // Arbitrary texture.
            }
            else
            {
                colour = GetPixelColour(m_ceilingTexture, tx, ty);
            }

            CopyPixel(m_backBuffer, m_ceilingTexture, colour, x, y);
        }
    }
}

Uint32 LevelRenderer::GetPixelColour(LevelTexture* levelTexture, int pixelX, int pixelY)
{
    SDL_Surface* surface = levelTexture->GetSurface();
    int bpp = surface->format->BytesPerPixel;
    Uint8* pixelPtr = (Uint8*)surface->pixels + pixelX * surface->pitch + pixelY * bpp;
    Uint32 pixelColour = 0;

    switch (bpp) {
    case 1:
        pixelColour = *pixelPtr;
        break;
    case 2:
        pixelColour = *(Uint16*)pixelPtr;
        break;
    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            pixelColour = pixelPtr[0] << 16 | pixelPtr[1] << 8 | pixelPtr[2];
        else
            pixelColour = pixelPtr[0] | pixelPtr[1] << 8 | pixelPtr[2] << 16;
        break;
    case 4:
        pixelColour = *(Uint32*)pixelPtr;
        break;
    }

    return pixelColour;
}

void LevelRenderer::CopyPixel(SDL_Surface* buffer, LevelTexture* levelTexture, Uint32 colour,int xPos, int yPos)
{
    // Copy buffer into locked texture memory.
    Uint8* dstPixel = (Uint8*)buffer->pixels + yPos * buffer->pitch + xPos * buffer->format->BytesPerPixel;

    // Could be cache optimised?
    switch (levelTexture->GetSurface()->format->BytesPerPixel) {
    case 1:
        *dstPixel = (Uint8)colour;
        break;
    case 2:
        *(Uint16*)dstPixel = (Uint16)colour;
        break;
    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            dstPixel[0] = (colour >> 16) & 0xFF;
            dstPixel[1] = (colour >> 8) & 0xFF;
            dstPixel[2] = colour & 0xFF;
            dstPixel[3] = 0xFF;
        }
        else {
            dstPixel[0] = colour & 0xFF;
            dstPixel[1] = (colour >> 8) & 0xFF;
            dstPixel[2] = (colour >> 16) & 0xFF;
            dstPixel[3] = 0xFF;
        }
        break;
    case 4:
        *(Uint32*)dstPixel = colour;
        break;
    }
}