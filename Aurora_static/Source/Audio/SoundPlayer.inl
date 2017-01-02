#include <SFML/Audio/Listener.hpp>

namespace au
{
	/// <summary>
	/// Default constructor<para/>
	/// The listener's position is set to (0, 0, 300)
	/// </summary>
	template <typename SoundID>
	SoundPlayer<SoundID>::SoundPlayer()
	{
		sf::Listener::setPosition(0.f, 0.f, 300.f);
	}

	/// <summary>Play a pre-loaded sound effect</summary>
	/// <param name="effectID">The sound id associated with the desired sound effect</param>
	/// <see cref="loadEffect"/>
	template <typename SoundID>
	void SoundPlayer<SoundID>::play(SoundID effectID)
	{
		play(getListenerPosition(), effectID);
	}

	/// <summary>Play a pre-loaded sound effect</summary>
	/// <param name="pos">The position of the sound's source</param>
	/// <param name="effectID">The sound id associated with the desired sound effect</param>
	/// <see cref="loadEffect"/>
	template <typename SoundID>
	void SoundPlayer<SoundID>::play(const sf::Vector2f& pos, SoundID effectID)
	{
		removeStoppedSounds();
		const SoundProperties& properties = mSoundProperties.find(effectID)->second;

		mSounds.emplace_back(sf::Sound());
		mSounds.back().setBuffer(mSoundBuffers.get(effectID));
		mSounds.back().setPosition(pos.x, -pos.y, 0.f);
		mSounds.back().setVolume(properties.getVolume());
		mSounds.back().setAttenuation(properties.getAttenuation());
		mSounds.back().setPitch(properties.getPitch());
		mSounds.back().setMinDistance(properties.getMinDistance3D());
		mSounds.back().setRelativeToListener(properties.isRelativeToListener());
		mSounds.back().play();
	}

	/// <summary>Load in a sound effect</summary>
	/// <param name="filename">The sound effect's filepath</param>
	/// <param name="soundProperties">The sound properties associated with the sound to be loaded in</param>
	/// <param name="effectID">An ID with which to associate the sound effect (enum value)</param>
	template <typename SoundID>
	void SoundPlayer<SoundID>::loadEffect(const std::string& filename, const SoundProperties& soundProperties,
		                                  SoundID effectID)
	{
		mSoundBuffers.load(filename, effectID);
		mSoundProperties.insert(std::make_pair(effectID, soundProperties));
	}

	/// <summary>Pause all active sounds</summary>
	/// <param name="flag">True to pause, false to unpause</param>
	/// <see cref="stopSounds"/>
	template <typename SoundID>
	void SoundPlayer<SoundID>::pauseSounds(bool flag)
	{
		if (flag)
			for (auto& sound : mSounds)
				sound.pause();
		else
			for (auto& sound : mSounds)
				sound.play();
	}

	/// <summary>Stop all active sounds (sounds will be removed)</summary>
	/// <see cref="pauseSounds"/>
	template <typename SoundID>
	void SoundPlayer<SoundID>::stopSounds()
	{
		for (auto& sound : mSounds)
			sound.stop();

		removeStoppedSounds();
	}

	/// <summary>Set the position of the listener (i.e. the player position)</summary>
	/// <param name="pos">The listener's position</param>
	/// <see cref="getListenerPosition"/>
	template <typename SoundID>
	void SoundPlayer<SoundID>::setListenerPosition(const sf::Vector2f& pos)
	{
		sf::Listener::setPosition(pos.x, -pos.y, sf::Listener::getPosition().z);
	}

	/// <summary>Get the listener's position</summary>
	/// <returns>The listener's position</returns>
	/// <see cref="setListenerPosition"/>
	template <typename SoundID>
	sf::Vector2f SoundPlayer<SoundID>::getListenerPosition() const
	{
		sf::Vector3f pos(sf::Listener::getPosition());
		return sf::Vector2f(pos.x, -pos.y);
	}

	/// <summary>Remove all stopped sounds</summary>
	template <typename SoundID>
	void SoundPlayer<SoundID>::removeStoppedSounds()
	{
		mSounds.remove_if([](const sf::Sound& s) { return s.getStatus() == sf::Sound::Stopped; });
	}
}