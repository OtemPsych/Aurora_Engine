#ifndef Aurora_Audio_MusicPlayer_H_
#define Aurora_Audio_MusicPlayer_H_

#include <map>

#include <SFML/System/Vector2.hpp>
#include <SFML/Audio/Music.hpp>

#include "SoundProperties.h"

namespace au
{
	/// <summary>Class that facilitates loading in music and playing it</summary>
	template <typename T>
	class MusicPlayer : private sf::NonCopyable
	{
	public:
		/// <summary>
		/// Default constructor<para/>
		/// The listener's position is set to (0, 0, 300)
		/// </summary>
		MusicPlayer();
	public:
		/// <summary>Play a pre-loaded music track</summary>
		/// <param name="track_id">The music id associated with the desired track</param>
		/// <param name="loop">True to put the track on loop, false otherwise</param>
		/// <see cref="stop"/>
		/// <see cref="pause"/>
		/// <seealso cref="loadTrack"/>
		void play(T track_id, bool loop);
		/// <summary>Play a pre-loaded music track</summary>
		/// <param name="pos">The position of the track's source</param>
		/// <param name="track_id">The music id associated with the desired track</param>
		/// <param name="loop">True to put the track on loop, false otherwise</param>
		/// <see cref="pause"/>
		/// <see cref="stop"/>
		/// <seealso cref="loadTrack"/>
		void play(const sf::Vector2f& pos, T track_id, bool loop);
		/// <summary>(Un)Pause the current track</summary>
		/// <param name="flag">True to pause the track, false otherwise</param>
		/// <see cref="play"/>
		/// <see cref="stop"/>
		void pause(bool flag);
		/// <summary>Stop the track that is currently playing</summary>
		/// <see cref="play"/>
		/// <see cref="pause"/>
		void stop();
		/// <summary>Load in a music track</summary>
		/// <param name="filename">The music track's filepath</param>
		/// <param name="sound_properties">The sound properties associated with the track to be loaded in</param>
		/// <param name="track_id">An ID with which to associate the music track (enum value)</param>
		/// <see cref="play"/>
		void loadTrack(const std::string& filename, const SoundProperties& sound_properties,
			           T track_id);
		/// <summary>Load in a music track</summary>
		/// <param name="filename">The music track's filepath</param>
		/// <param name="track_id">An ID with which to associate the music track (enum value)</param>
		/// <see cref="play"/>
		void loadTrack(const std::string& filename, T track_id);
		/// <summary>Update the position of the current music track's source</summary>
		/// <param name="pos">The updated position of the music track's source</param>
		void updateTrackPosition(const sf::Vector2f& pos);
		/// <summary>Set the position of the listener (i.e. the player position)</summary>
		/// <param name="pos">The listener's position</param>
		/// <see cref="getListenerPosition"/>
		void setListenerPosition(const sf::Vector2f& pos);
		/// <summary>Get the listener's position</summary>
		/// <returns>The listener's position</returns>
		/// <see cref="setListenerPosition"/>
		sf::Vector2f getListenerPosition() const;
		/// <summary>Check if the track that was playing has stopped</summary>
		/// <returns>True if it has stopped playing, false otherwise</returns>
		/// <see cref="isTrackPaused"/>
		bool isTrackOver() const;
		/// <summary>Check if the track that was playing has paused</summary>
		/// <returns>True if it has paused, false otherwise</returns>
		/// <see cref="isTrackOver"/>
		bool isTrackPaused() const;

	private:
		std::map<T, std::pair<std::string, SoundProperties>> track_properties_;
		sf::Music                                            music_;
	};
}
#include "MusicPlayer.inl"
#endif