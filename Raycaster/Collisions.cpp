#include "Collisions.h"

#include "SDL.h"

#include "Vector2D.h"
#include "GameObject.h"

#include <cmath>

Collisions::Collisions() {}

Collisions::~Collisions()
{
}

bool Collisions::BoxTrigger(GameObject* a, GameObject* b)
{
	if (a != nullptr && b != nullptr)
	{
		SDL_Rect rect1 = a->GetCollisionBox();
		SDL_Rect rect2 = b->GetCollisionBox();

		int rect1Left = rect1.x;
		int rect2Left = rect2.x;

		int rect1Right = rect1Left + rect1.w;
		int rect2Right = rect2Left + rect2.w;

		int rect1Top = rect1.y;
		int rect2Top = rect2.y;

		int rect1Bottom = rect1Top + rect1.h;
		int rect2Bottom = rect2Top + rect2.h;


		if ((rect1Left < rect2Right) &&
			(rect1Right > rect2Left) &&
			(rect1Top < rect2Bottom) &&
			(rect1Bottom > rect2Top))
		{
			return true;
		}
	}

	return false;
}

// My hatred for collision grows day by day.
bool Collisions::BoxHard(GameObject* a, GameObject* b)
{
	if (BoxTrigger(a, b))
	{
		// Get collisions rects.
		SDL_Rect rect1 = a->GetCollisionBox();
		SDL_Rect rect2 = b->GetCollisionBox();

		// Calculate midpoint of collision.
		float xCentre = (rect1.x + rect1.w / 2) - (rect2.x + rect2.w / 2);
		float yCentre = (rect1.y + rect1.w / 2) - (rect2.y + rect2.h / 2);

		// Position to set Game Object A.
		Vector2D newPos = a->m_position;

		// Set Rect 1s position based on the axis with most overlap.
		float xOverlap = (rect1.w / 2 + rect2.w / 2) - abs(xCentre);
		float zOverlap = (rect1.h / 2 + rect2.h / 2) - abs(yCentre);
		if (zOverlap < xOverlap)
		{
			// Adjust along the Z-axis
			if (yCentre > 0)
			{
				newPos.y = rect2.y + rect2.h; // Move below rect2
			}
			else
			{
				newPos.y = rect2.y - rect1.h; // Move above rect2
			}
		}
		else
		{
			// Adjust along the X-axis
			if (xCentre > 0)
			{
				newPos.x = rect2.x + rect2.w; // Move to the right of rect2
			}
			else
			{
				newPos.x = rect2.x - rect1.w; // Move to the left of rect2
			}
		}

		// Update Game Object A's position.
		a->m_position;

		return true;
	}

	return false;
}