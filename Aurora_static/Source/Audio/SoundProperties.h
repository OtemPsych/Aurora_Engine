#ifndef Aurora_Audio_SoundProperties_H_
#define Aurora_Audio_SoundProperties_H_

namespace au
{
	/// <summary>Container for sound properties (volume, attenuation, pitch, ...)</summary>
	class SoundProperties
	{
	public:
		/// <summary>Constructor</summary>
		/// <param name="volume">
		/// The volume is a value between 0 (mute) and 100 (full volume).<para/>
		/// The default value for the volume is 100.
		/// </param>
		/// <param name="attenuation">
		/// The attenuation is a multiplicative factor which makes<para/>
		/// the sound more or less loud according to its distance<para/>
		/// from the listener. An attenuation of 0 will produce a<para/>
		/// non-attenuated sound, i.e. its volume will always be the same<para/>
		/// whether it is heard from near or from far. On the other hand,<para/>
		/// an attenuation value such as 100 will make the sound fade out<para/>
		/// very quickly as it gets further from the listener.<para/>
		/// The default value of the attenuation is 1.
		/// </param>
		/// <param name="pitch">
		/// The pitch represents the perceived fundamental frequency<para/>
		/// of a sound; thus you can make a sound more acute or grave<para/>
		/// by changing its pitch. A side effect of changing the pitch<para/>
		/// is to modify the playing speed of the sound as well.<para/>
		/// The default value for the pitch is 1.
		/// </param>
		/// <param name="minDistance2D">
		/// The "minimum distance" of a sound is the maximum<para/>
		/// distance at which it is heard at its maximum volume. Further<para/>
		/// than the minimum distance, it will start to fade out according<para/>
		/// to its attenuation factor. A value of 0 ("inside the head<para/>
		/// of the listener") is an invalid value and is forbidden.<para/>
		/// The default value of the minimum distance is 1.
		/// </param>
		/// <param name="relativeToListener">
		/// Making a sound relative to the listener will ensure that it will always<para/>
		/// be played the same way regardless of the position of the listener.<para/>
		/// This can be useful for non-spatialized sounds, sounds that are<para/>
		/// produced by the listener, or sounds attached to it.<para/>
		/// The default value is false (position is absolute).
		/// </param>
		SoundProperties(float volume = 100.f, float attenuation = 1.f, float pitch = 1.f,
			            float minDistance2D = 1.f, bool relativeToListener = false);
	public:
		/// <summary>
		/// Set the volume to a value between 0 (mute) and 100 (full volume).<para/>
		/// The default value for the volume is 100.
		/// </summary>
		/// <param name="volume">The new volume value</param>
		/// <see cref="getVolume"/>
		/// <seealso cref="setAttenuation"/>
		/// <seealso cref="setPitch"/>
		/// <seealso cref="setMinDistance2D"/>
		/// <seealso cref="setRelativeToListener"/>
		void setVolume(float volume);
		/// <summary>
		/// The "minimum distance" of a sound is the maximum<para/>
		/// distance at which it is heard at its maximum volume. Further<para/>
		/// than the minimum distance, it will start to fade out according<para/>
		/// to its attenuation factor. A value of 0 ("inside the head<para/>
		/// of the listener") is an invalid value and is forbidden.<para/>
		/// The default value of the minimum distance is 1.
		/// </summary>
		/// <param name="minDistance2D">The new minimum distance</param>
		/// <see cref="getMinDistance2D"/>
		/// <seealso cref="setVolume"/>
		/// <seealso cref="setAttenuation"/>
		/// <seealso cref="setPitch"/>
		/// <seealso cref="setRelativeToListener"/>
		void setMinDistance2D(float minDistance2D);
		/// <summary>
		/// The attenuation is a multiplicative factor which makes<para/>
		/// the sound more or less loud according to its distance<para/>
		/// from the listener. An attenuation of 0 will produce a<para/>
		/// non-attenuated sound, i.e. its volume will always be the same<para/>
		/// whether it is heard from near or from far. On the other hand,<para/>
		/// an attenuation value such as 100 will make the sound fade out<para/>
		/// very quickly as it gets further from the listener.<para/>
		/// The default value of the attenuation is 1.
		/// </summary>
		/// <param name="attenuation">The new attenuation factor</param>
		/// <see cref="getAttenuation"/>
		/// <seealso cref="setVolume"/>
		/// <seealso cref="setPitch"/>
		/// <seealso cref="setMinDistance2D"/>
		/// <seealso cref="setRelativeToListener"/>
		inline void setAttenuation(float attenuation) { mAttenuation = attenuation; }
		/// <summary>
		/// The pitch represents the perceived fundamental frequency<para/>
		/// of a sound; thus you can make a sound more acute or grave<para/>
		/// by changing its pitch. A side effect of changing the pitch<para/>
		/// is to modify the playing speed of the sound as well.<para/>
		/// The default value for the pitch is 1.
		/// </summary>
		/// <param name="pitch">The new pitch frequency</param>
		/// <see cref="getPitch"/>
		/// <seealso cref="setVolume"/>
		/// <seealso cref="setAttenuation"/>
		/// <seealso cref="setMinDistance2D"/>
		/// <seealso cref="setRelativeToListener"/>
		inline void setPitch(float pitch) { mPitch = pitch; }
		/// <summary>
		/// Making a sound relative to the listener will ensure that it will always<para/>
		/// be played the same way regardless of the position of the listener.<para/>
		/// This can be useful for non-spatialized sounds, sounds that are<para/>
		/// produced by the listener, or sounds attached to it.<para/>
		/// The default value is false (position is absolute).
		/// </summary>
		/// <param name="relativeToListener">True to make the sound relative to the listener, false otherwise</param>
		/// <see cref="isRelativeToListener"/>
		/// <seealso cref="setVolume"/>
		/// <seealso cref="setAttenuation"/>
		/// <seealso cref="setPitch"/>
		/// <seealso cref="setMinDistance2D"/>
		inline void setRelativeToListener(bool relativeToListener) { mRelativeToListener = relativeToListener; }
		/// <summary>Get the volume value</summary>
		/// <returns>The volume value</returns>
		/// <see cref="setVolume"/>
		inline float getVolume() const { return mVolume; }
		/// <summary>Get the minimum 2d distance</summary>
		/// <returns>The minimum 2d distance</returns>
		/// <see cref="setMinDistance2D"/>
		inline float getMinDistance2D() const { return mMinDistance2D; }
		/// <summary>Get the minimum 3d distance</summary>
		/// <returns>The minimum 3d distance</returns>
		inline float getMinDistance3D() const { return mMinDistance3D; }
		/// <summary>Get the attenuation factor</summary>
		/// <returns>The attenuation factor</returns>
		/// <see cref="setAttenuation"/>
		inline float getAttenuation() const { return mAttenuation; }
		/// <summary>Get the pitch frequency</summary>
		/// <returns>The pitch frequency</returns>
		/// <see cref="setPitch"/>
		inline float getPitch() const { return mPitch; }
		/// <summary>Is the sound relative to the listener</summary>
		/// <returns>True if the sound is relative to the listener, false otherwise</returns>
		/// <see cref="setRelativeToListener"/>
		inline bool isRelativeToListener() const { return mRelativeToListener; }

		private:
			float mVolume;
			float mAttenuation;
			float mPitch;
			float mMinDistance2D;
			float mMinDistance3D;
			bool  mRelativeToListener;
	};
}
#endif