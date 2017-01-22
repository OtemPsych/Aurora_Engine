#ifndef Aurora_Audio_SoundPlayer_H_
#define Aurora_Audio_SoundPlayer_H_

#include <list>

#include <SFML/System/Vector2.hpp>
#include <SFML/Audio/Sound.hpp>

#include "../ResourceHolder.h"
#include "SoundProperties.h"

namespace au
{
	/// <summary>Class that facilitates loading in sound effects and playing them</summary>
	template <typename T>
	class SoundPlayer : private sf::NonCopyable
	{
	public:
		/// <summary>
		/// Default constructor<para/>
		/// The listener's position is set to (0, 0, 300)
		/// </summary>
		SoundPlayer();
	public:
		/// <summary>Play a pre-loaded sound effect</summary>
		/// <param name="effect_id">The sound id associated with the desired sound effect</param>
		/// <see cref="loadEffect"/>
		void play(T effect_id);
		/// <summary>Play a pre-loaded sound effect</summary>
		/// <param name="pos">The position of the sound's source</param>
		/// <param name="effect_id">The sound id associated with the desired sound effect</param>
		/// <see cref="loadEffect"/>
		void play(const sf::Vector2f& pos, T effect_id);
		/// <summary>Load in a sound effect</summary>
		/// <param name="filename">The sound effect's filepath</param>
		/// <param name="sound_properties">The sound properties associated with the sound to be loaded in</param>
		/// <param name="effect_id">An ID with which to associate the sound effect (enum value)</param>
		void loadEffect(const std::string& filename, const SoundProperties& sound_properties,
			            T effect_id);
		/// <summary>Pause all active sounds</summary>
		/// <param name="flag">True to pause, false to unpause</param>
		/// <see cref="stopSounds"/>
		void pauseSounds(bool flag);
		/// <summary>Stop all active sounds (sounds will be removed)</summary>
		/// <see cref="pauseSounds"/>
		void stopSounds();
		/// <summary>Set the position of the listener (i.e. the player position)</summary>
		/// <param name="pos">The listener's position</param>
		/// <see cref="getListenerPosition"/>
		void setListenerPosition(const sf::Vector2f& pos);
		/// <summary>Get the listener's position</summary>
		/// <returns>The listener's position</returns>
		/// <see cref="setListenerPosition"/>
		sf::Vector2f getListenerPosition() const;
		/// <summary>
		/// Set the sound player's global volume(0-100)<para/>
		/// A global volume of 50 will reduce the sound effects'<para/>
		/// volume by half regardless of their own volume
		/// </summary>
		/// <param name="volume">The global volume</param>
		/// <see cref="getGlobalVolume"/>
		void setGlobalVolume(float volume);
		/// <summary>Get the sound player's global volume</summary>
		/// <returns>The global volume</returns>
		/// <see cref="setGlobalVolume"/>
		float getGlobalVolume() const;
	private:
		/// <summary>Remove all stopped sounds</summary>
		void removeStoppedSounds();

	private:
		SoundBufferHolder<T>         sound_buffers_;
		std::map<T, SoundProperties> sound_properties_;
		std::list<sf::Sound>         sounds_;
		float                        global_volume_;
	};
}
#include "SoundPlayer.inl"
#endif