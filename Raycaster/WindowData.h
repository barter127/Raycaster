#pragma once

#ifndef _WINDOW_DATA_H
#define _WINDOW_DATA_H

struct WindowData
{
	int width = 1280;
	int height = 720;

	SDL_Texture* frontBuffer = nullptr;
};

static WindowData g_windowData;
#endif // !_WINDOW_DATA_H

