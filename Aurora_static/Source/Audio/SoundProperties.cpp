#include <cmath>

#include <SFML/Audio/Listener.hpp>

#include "SoundProperties.h"

namespace au
{
	SoundProperties::SoundProperties(float volume, float attenuation, float pitch,
		                             float min_distance_2d, bool relative_to_listener)
		: attenuation_(attenuation)
		, pitch_(pitch)
		, relative_to_listener_(relative_to_listener)
	{
		setVolume(volume);
		setMinDistance2D(min_distance_2d);
	}

	void SoundProperties::setVolume(float volume)
	{
		if (volume < 0.f)
			volume_ = 0.f;
		else if (volume > 100.f)
			volume_ = 100.f;
		else
			volume_ = volume;
	}

	void SoundProperties::setMinDistance2D(float min_distance2d)
	{
		min_distance2d_ = min_distance2d != 0 ? min_distance2d : 1;
		min_distance3d_ = sqrtf(powf(min_distance2d_, 2.f) + powf(sf::Listener::getPosition().z, 2.f));
	}
}