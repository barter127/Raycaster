#include "Collisions.h"

#include "SDL.h"

#include "Vector2D.h"
#include "GameObject.h"

#include <cmath>

Collisions::Collisions() {}

Collisions::~Collisions() {}

bool Collisions::BoxTrigger(BoxCollider a, BoxCollider b)
{
	int rect1Left = a.x;
	int rect2Left = b.x;

	int rect1Right = rect1Left + a.width;
	int rect2Right = rect2Left + b.width;

	int rect1Top = a.y;
	int rect2Top = b.y;

	int rect1Bottom = rect1Top + a.height;
	int rect2Bottom = rect2Top + b.height;


	if ((rect1Left < rect2Right) &&
		(rect1Right > rect2Left) &&
		(rect1Top < rect2Bottom) &&
		(rect1Bottom > rect2Top))
	{
		return true;
	}

	return false;
}

// My hatred for collision grows day by day.
bool Collisions::BoxHard(BoxCollider a, BoxCollider b)
{
	if (BoxTrigger(a, b))
	{
		// Calculate midpoint of collision.
		float xCentre = (a.x + a.width / 2) - (b.x + b.width / 2);
		float yCentre = (a.y + a.width / 2) - (b.y + b.height / 2);

		// Set Rect 1s position based on the axis with most overlap.
		float xOverlap = (a.width / 2 + b.width / 2) - abs(xCentre);
		float zOverlap = (a.height / 2 + b.height / 2) - abs(yCentre);
		if (zOverlap < xOverlap)
		{
			// Adjust along the Z-axis
			if (yCentre > 0 && a.owner != nullptr)
			{
				a.owner->m_position.y = b.y + b.height; // Move below b
			}
			else
			{
				a.owner->m_position.y = b.y - a.height; // Move above b
			}
		}
		else
		{
			// Adjust along the X-axis
			if (xCentre > 0 && a.owner != nullptr)
			{
				a.owner->m_position.x = b.x + b.width; // Move to the right of b
			}
			else
			{
				a.owner->m_position.x = b.x - a.width; // Move to the left of b
			}
		}

		return true;
	}

	return false;
}