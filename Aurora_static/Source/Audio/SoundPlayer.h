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
	template <typename SoundID>
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
		/// <param name="effectID">The sound id associated with the desired sound effect</param>
		/// <see cref="loadEffect"/>
		void play(SoundID effectID);
		/// <summary>Play a pre-loaded sound effect</summary>
		/// <param name="pos">The position of the sound's source</param>
		/// <param name="effectID">The sound id associated with the desired sound effect</param>
		/// <see cref="loadEffect"/>
		void play(const sf::Vector2f& pos, SoundID effectID);
		/// <summary>Load in a sound effect</summary>
		/// <param name="filename">The sound effect's filepath</param>
		/// <param name="soundProperties">The sound properties associated with the sound to be loaded in</param>
		/// <param name="effectID">An ID with which to associate the sound effect (enum value)</param>
		void loadEffect(const std::string& filename, const SoundProperties& soundProperties,
			            SoundID effectID);
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
	private:
		/// <summary>Remove all stopped sounds</summary>
		void removeStoppedSounds();

	private:
		SoundBufferHolder<SoundID>         mSoundBuffers;
		std::map<SoundID, SoundProperties> mSoundProperties;
		std::list<sf::Sound>               mSounds;
	};
}
#include "SoundPlayer.inl"
#endif