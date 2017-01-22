#include <SFML/Audio/Listener.hpp>

namespace au
{
	/// <summary>
	/// Default constructor<para/>
	/// The global volume is set to 100%<para/>
	/// The listener's position is set to (0, 0, 300)
	/// </summary>
	template <typename T>
	SoundPlayer<T>::SoundPlayer()
		: global_volume_(100.f)
	{
		sf::Listener::setPosition(0.f, 0.f, 300.f);
	}

	/// <summary>Play a pre-loaded sound effect</summary>
	/// <param name="effect_id">The sound id associated with the desired sound effect</param>
	/// <see cref="loadEffect"/>
	template <typename T>
	void SoundPlayer<T>::play(T effect_id)
	{
		play(getListenerPosition(), effect_id);
	}

	/// <summary>Play a pre-loaded sound effect</summary>
	/// <param name="pos">The position of the sound's source</param>
	/// <param name="effect_id">The sound id associated with the desired sound effect</param>
	/// <see cref="loadEffect"/>
	template <typename T>
	void SoundPlayer<T>::play(const sf::Vector2f& pos, T effect_id)
	{
		removeStoppedSounds();
		const SoundProperties& properties = sound_properties_.find(effect_id)->second;

		sounds_.emplace_back(sf::Sound());
		sounds_.back().setBuffer(sound_buffers_.get(effect_id));
		sounds_.back().setPosition(pos.x, -pos.y, 0.f);
		sounds_.back().setVolume(global_volume_ * properties.getVolume() / 100.f);
		sounds_.back().setAttenuation(properties.getAttenuation());
		sounds_.back().setPitch(properties.getPitch());
		sounds_.back().setMinDistance(properties.getMinDistance3D());
		sounds_.back().setRelativeToListener(properties.isRelativeToListener());
		sounds_.back().play();
	}

	/// <summary>Load in a sound effect</summary>
	/// <param name="filename">The sound effect's filepath</param>
	/// <param name="sound_properties">The sound properties associated with the sound to be loaded in</param>
	/// <param name="effect_id">An ID with which to associate the sound effect (enum value)</param>
	template <typename T>
	void SoundPlayer<T>::loadEffect(const std::string& filename, const SoundProperties& sound_properties,
		                            T effect_id)
	{
		sound_buffers_.load(filename, effect_id);
		sound_properties_.insert(std::make_pair(effect_id, sound_properties));
	}

	/// <summary>Pause all active sounds</summary>
	/// <param name="flag">True to pause, false to unpause</param>
	/// <see cref="stopSounds"/>
	template <typename T>
	void SoundPlayer<T>::pauseSounds(bool flag)
	{
		if (flag)
			for (auto& sound : sounds_)
				sound.pause();
		else
			for (auto& sound : sounds_)
				sound.play();
	}

	/// <summary>Stop all active sounds (sounds will be removed)</summary>
	/// <see cref="pauseSounds"/>
	template <typename T>
	void SoundPlayer<T>::stopSounds()
	{
		for (auto& sound : sounds_)
			sound.stop();

		removeStoppedSounds();
	}

	/// <summary>Set the position of the listener (i.e. the player position)</summary>
	/// <param name="pos">The listener's position</param>
	/// <see cref="getListenerPosition"/>
	template <typename T>
	void SoundPlayer<T>::setListenerPosition(const sf::Vector2f& pos)
	{
		sf::Listener::setPosition(pos.x, -pos.y, sf::Listener::getPosition().z);
	}

	/// <summary>Get the listener's position</summary>
	/// <returns>The listener's position</returns>
	/// <see cref="setListenerPosition"/>
	template <typename T>
	sf::Vector2f SoundPlayer<T>::getListenerPosition() const
	{
		sf::Vector3f pos(sf::Listener::getPosition());
		return sf::Vector2f(pos.x, -pos.y);
	}

	/// <summary>Remove all stopped sounds</summary>
	template <typename T>
	void SoundPlayer<T>::removeStoppedSounds()
	{
		sounds_.remove_if([](const sf::Sound& s) { return s.getStatus() == sf::Sound::Stopped; });
	}

	/// <summary>
	/// Set the sound player's global volume(0-100)<para/>
	/// A global volume of 50 will reduce the sound effects'<para/>
	/// volume by half regardless of their own volume
	/// </summary>
	/// <param name="volume">The global volume</param>
	/// <see cref="getGlobalVolume"/>
	template <typename T>
	void SoundPlayer<T>::setGlobalVolume(float volume)
	{
		if (volume < 0.f)
			global_volume_ = 0.f;
		else if (volume > 100.f)
			global_volume_ = 100.f;
		else
			global_volume_ = volume;
	}

	/// <summary>Get the sound player's global volume</summary>
	/// <returns>The global volume</returns>
	/// <see cref="setGlobalVolume"/>
	template <typename T>
	float SoundPlayer<T>::getGlobalVolume() const
	{
		return global_volume_;
	}
}