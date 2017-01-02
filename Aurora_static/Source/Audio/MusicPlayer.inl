#include <cassert>
#include <iostream>

#include <SFML/Audio/Listener.hpp>

namespace au
{
	/// <summary>
	/// Default constructor<para/>
	/// The listener's position is set to (0, 0, 300)
	/// </summary>
	template <typename MusicID>
	MusicPlayer<MusicID>::MusicPlayer()
	{
		sf::Listener::setPosition(0.f, 0.f, 300.f);
	}

	/// <summary>Play a pre-loaded music track</summary>
	/// <param name="trackID">The music id associated with the desired track</param>
	/// <param name="loop">True to put the track on loop, false otherwise</param>
	/// <see cref="stop"/>
	/// <see cref="pause"/>
	/// <seealso cref="loadTrack"/>
	template <typename MusicID>
	void MusicPlayer<MusicID>::play(MusicID trackID, bool loop)
	{
		play(getListenerPosition(), trackID, loop);
	}

	/// <summary>Play a pre-loaded music track</summary>
	/// <param name="pos">The position of the track's source</param>
	/// <param name="trackID">The music id associated with the desired track</param>
	/// <param name="loop">True to put the track on loop, false otherwise</param>
	/// <see cref="pause"/>
	/// <see cref="stop"/>
	/// <seealso cref="loadTrack"/>
	template <typename MusicID>
	void MusicPlayer<MusicID>::play(const sf::Vector2f& pos, MusicID trackID, bool loop)
	{
		auto found = mTrackProperties.find(trackID);
		assert(found != mTrackProperties.end());

		if (mMusic.openFromFile(found->second.first)) {
			mMusic.setPosition(pos.x, -pos.y, 0.f);
			mMusic.setLoop(loop);
			mMusic.setVolume(found->second.second.getVolume());
			mMusic.setAttenuation(found->second.second.getAttenuation());
			mMusic.setPitch(found->second.second.getPitch());
			mMusic.setMinDistance(found->second.second.getMinDistance3D());
			mMusic.setRelativeToListener(found->second.second.isRelativeToListener());
			mMusic.play();
		}
		else
			std::cout << "\nMusicPlayer::play - Failed to load " << found->second.first << std::endl;
	}

	/// <summary>(Un)Pause the current track</summary>
	/// <param name="flag">True to pause the track, false otherwise</param>
	/// <see cref="play"/>
	/// <see cref="stop"/>
	template <typename MusicID>
	void MusicPlayer<MusicID>::pause(bool flag)
	{
		flag ? mMusic.pause() : mMusic.play();
	}

	/// <summary>Stop the track that is currently playing</summary>
	/// <see cref="play"/>
	/// <see cref="pause"/>
	template <typename MusicID>
	void MusicPlayer<MusicID>::stop()
	{
		mMusic.stop();
	}

	/// <summary>Load in a music track</summary>
	/// <param name="filename">The music track's filepath</param>
	/// <param name="soundProperties">The sound properties associated with the track to be loaded in</param>
	/// <param name="trackID">An ID with which to associate the music track (enum value)</param>
	/// <see cref="play"/>
	template <typename MusicID>
	void MusicPlayer<MusicID>::loadTrack(const std::string& filename, const SoundProperties& soundProperties,
		                                 MusicID trackID)
	{
		mTrackProperties.insert(std::make_pair(trackID, std::make_pair(filename, soundProperties)));
	}

	/// <summary>Load in a music track</summary>
	/// <param name="filename">The music track's filepath</param>
	/// <param name="trackID">An ID with which to associate the music track (enum value)</param>
	/// <see cref="play"/>
	template <typename MusicID>
	void MusicPlayer<MusicID>::loadTrack(const std::string& filename, MusicID trackID)
	{
		mTrackProperties.insert(std::make_pair(trackID, std::make_pair(filename, SoundProperties())));
	}

	/// <summary>Update the position of the current music track's source</summary>
	/// <param name="pos">The updated position of the music track's source</param>
	template <typename MusicID>
	void MusicPlayer<MusicID>::updateTrackPosition(const sf::Vector2f& pos)
	{
		mMusic.setPosition(pos.x, -pos.y, 0.f);
	}

	/// <summary>Set the position of the listener (i.e. the player position)</summary>
	/// <param name="pos">The listener's position</param>
	/// <see cref="getListenerPosition"/>
	template <typename MusicID>
	void MusicPlayer<MusicID>::setListenerPosition(const sf::Vector2f& pos)
	{
		sf::Listener::setPosition(pos.x, -pos.y, sf::Listener::getPosition().z);
	}

	/// <summary>Get the listener's position</summary>
	/// <returns>The listener's position</returns>
	/// <see cref="setListenerPosition"/>
	template <typename MusicID>
	sf::Vector2f MusicPlayer<MusicID>::getListenerPosition() const
	{
		sf::Vector3f pos(sf::Listener::getPosition());
		return sf::Vector2f(pos.x, -pos.y);
	}

	/// <summary>Check if the track that was playing has stopped</summary>
	/// <returns>True if it has stopped playing, false otherwise</returns>
	/// <see cref="isTrackPaused"/>
	template <typename MusicID>
	bool MusicPlayer<MusicID>::isTrackOver() const
	{
		return mMusic.getStatus() == sf::SoundSource::Status::Stopped;
	}

	/// <summary>Check if the track that was playing has paused</summary>
	/// <returns>True if it has paused, false otherwise</returns>
	/// <see cref="isTrackOver"/>
	template <typename MusicID>
	bool MusicPlayer<MusicID>::isTrackPaused() const
	{
		return mMusic.getStatus() == sf::SoundSource::Status::Paused;
	}
}