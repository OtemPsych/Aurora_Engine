#include <cassert>
#include <iostream>

#include <SFML/Audio/Listener.hpp>

namespace au
{
	/// <summary>
	/// Default constructor<para/>
	/// The global volume is set to 100%<para/>
	/// The listener's position is set to (0, 0, 300)
	/// </summary>
	template <typename T>
	MusicPlayer<T>::MusicPlayer()
		: global_volume_(100.f)
	{
		sf::Listener::setPosition(0.f, 0.f, 300.f);
	}

	/// <summary>Play a pre-loaded music track</summary>
	/// <param name="track_id">The music id associated with the desired track</param>
	/// <param name="loop">True to put the track on loop, false otherwise</param>
	/// <see cref="stop"/>
	/// <see cref="pause"/>
	/// <seealso cref="loadTrack"/>
	template <typename T>
	void MusicPlayer<T>::play(T track_id, bool loop)
	{
		play(getListenerPosition(), track_id, loop);
	}

	/// <summary>Play a pre-loaded music track</summary>
	/// <param name="pos">The position of the track's source</param>
	/// <param name="track_id">The music id associated with the desired track</param>
	/// <param name="loop">True to put the track on loop, false otherwise</param>
	/// <see cref="pause"/>
	/// <see cref="stop"/>
	/// <seealso cref="loadTrack"/>
	template <typename T>
	void MusicPlayer<T>::play(const sf::Vector2f& pos, T track_id, bool loop)
	{
		auto found = track_properties_.find(track_id);
		assert(found != track_properties_.end());

		if (music_.openFromFile(found->second.first)) {
			music_.setPosition(pos.x, -pos.y, 0.f);
			music_.setLoop(loop);
			music_.setVolume(global_volume_ * found->second.second.getVolume() / 100.f);
			music_.setAttenuation(found->second.second.getAttenuation());
			music_.setPitch(found->second.second.getPitch());
			music_.setMinDistance(found->second.second.getMinDistance3D());
			music_.setRelativeToListener(found->second.second.isRelativeToListener());
			music_.play();
		}
		else
			std::cout << "\nMusicPlayer::play - Failed to load " << found->second.first << std::endl;
	}

	/// <summary>(Un)Pause the current track</summary>
	/// <param name="flag">True to pause the track, false otherwise</param>
	/// <see cref="play"/>
	/// <see cref="stop"/>
	template <typename T>
	void MusicPlayer<T>::pause(bool flag)
	{
		flag ? music_.pause() : music_.play();
	}

	/// <summary>Stop the track that is currently playing</summary>
	/// <see cref="play"/>
	/// <see cref="pause"/>
	template <typename T>
	void MusicPlayer<T>::stop()
	{
		music_.stop();
	}

	/// <summary>Load in a music track</summary>
	/// <param name="filename">The music track's filepath</param>
	/// <param name="sound_properties">The sound properties associated with the track to be loaded in</param>
	/// <param name="track_id">An ID with which to associate the music track (enum value)</param>
	/// <see cref="play"/>
	template <typename T>
	void MusicPlayer<T>::loadTrack(const std::string& filename, const SoundProperties& sound_properties,
		                           T track_id)
	{
		track_properties_.insert(std::make_pair(track_id, std::make_pair(filename, sound_properties)));
	}

	/// <summary>Load in a music track</summary>
	/// <param name="filename">The music track's filepath</param>
	/// <param name="track_id">An ID with which to associate the music track (enum value)</param>
	/// <see cref="play"/>
	template <typename T>
	void MusicPlayer<T>::loadTrack(const std::string& filename, T track_id)
	{
		track_properties_.insert(std::make_pair(track_id, std::make_pair(filename, SoundProperties())));
	}

	/// <summary>Update the position of the current music track's source</summary>
	/// <param name="pos">The updated position of the music track's source</param>
	template <typename T>
	void MusicPlayer<T>::updateTrackPosition(const sf::Vector2f& pos)
	{
		music_.setPosition(pos.x, -pos.y, 0.f);
	}

	/// <summary>Set the position of the listener (i.e. the player position)</summary>
	/// <param name="pos">The listener's position</param>
	/// <see cref="getListenerPosition"/>
	template <typename T>
	void MusicPlayer<T>::setListenerPosition(const sf::Vector2f& pos)
	{
		sf::Listener::setPosition(pos.x, -pos.y, sf::Listener::getPosition().z);
	}

	/// <summary>Get the listener's position</summary>
	/// <returns>The listener's position</returns>
	/// <see cref="setListenerPosition"/>
	template <typename T>
	sf::Vector2f MusicPlayer<T>::getListenerPosition() const
	{
		sf::Vector3f pos(sf::Listener::getPosition());
		return sf::Vector2f(pos.x, -pos.y);
	}

	/// <summary>Check if the track that was playing has stopped</summary>
	/// <returns>True if it has stopped playing, false otherwise</returns>
	/// <see cref="isTrackPaused"/>
	template <typename T>
	bool MusicPlayer<T>::isTrackOver() const
	{
		return music_.getStatus() == sf::SoundSource::Status::Stopped;
	}

	/// <summary>Check if the track that was playing has paused</summary>
	/// <returns>True if it has paused, false otherwise</returns>
	/// <see cref="isTrackOver"/>
	template <typename T>
	bool MusicPlayer<T>::isTrackPaused() const
	{
		return music_.getStatus() == sf::SoundSource::Status::Paused;
	}

	/// <summary>
	/// Set the music player's global volume(0-100)<para/>
	/// A global volume of 50 will reduce the current music track's<para/>
	/// volume by half regardless of its own volume
	/// </summary>
	/// <param name="volume">The global volume</param>
	/// <see cref="getGlobalVolume"/>
	template <typename T>
	void MusicPlayer<T>::setGlobalVolume(float volume)
	{
		if (volume < 0.f)
			global_volume_ = 0.f;
		else if (volume > 100.f)
			global_volume_ = 100.f;
		else
			global_volume_ = volume;
	}

	/// <summary>Get the music player's global volume</summary>
	/// <returns>The global volume</returns>
	/// <see cref="setGlobalVolume"/>
	template <typename T>
	float MusicPlayer<T>::getGlobalVolume() const
	{
		return global_volume_;
	}
}