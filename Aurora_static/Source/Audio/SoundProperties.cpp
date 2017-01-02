#include <cmath>

#include <SFML/Audio/Listener.hpp>

#include "SoundProperties.h"

namespace au
{
	SoundProperties::SoundProperties(float volume, float attenuation, float pitch,
		                             float minDistance2D, bool relativeToListener)
		: mAttenuation(attenuation)
		, mPitch(pitch)
		, mRelativeToListener(relativeToListener)
	{
		setVolume(volume);
		setMinDistance2D(minDistance2D);
	}

	void SoundProperties::setVolume(float volume)
	{
		if (volume < 0.f)
			mVolume = 0.f;
		else if (volume > 100.f)
			mVolume = 100.f;
		else
			mVolume = volume;
	}

	void SoundProperties::setMinDistance2D(float minDistance2D)
	{
		mMinDistance2D = minDistance2D != 0 ? minDistance2D : 1;
		mMinDistance3D = sqrtf(powf(mMinDistance2D, 2.f) + powf(sf::Listener::getPosition().z, 2.f));
	}
}