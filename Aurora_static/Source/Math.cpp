#include "Math.h"
#include "Audio/SoundPlayer.h"

namespace au
{
	float Math::toDegrees(float radians)
	{
		return radians * 180.f / Math_PI;
	}

	float Math::toRadians(float degrees)
	{
		return degrees * Math_PI / 180.f;
	}

	float Math::calculateHypotenuse(const sf::Vector2f& vec)
	{
		return sqrtf(powf(vec.x, 2.f) + powf(vec.y, 2.f));
	}

	sf::Vector2f Math::normalizeVector(const sf::Vector2f& vec)
	{
		return vec / calculateHypotenuse(vec);
	}
}