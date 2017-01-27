#ifndef Aurora_Animation_H_
#define Aurora_Animation_H_

#include "SpriteNode.h"

namespace au
{
	/// <summary>Class that facilitates animation handling using a json file</summary>
	class Animation : public SceneNode
	{
	public:
		/// <summary>Struct for an individual animation frame</summary>
		struct Frame {
			sf::FloatRect texture_rect;
			sf::Vector2f  origin;
			sf::Time      duration;
		};
		/// <summary>Struct for an entire animation</summary>
		struct Data {
			std::vector<Frame> frames;
			sf::Time           total_duration;
			bool               repeat;
			bool               loopback;
		};
	public:
		/// <summary>Constructs the animation by providing the animation data and the sprite node</summary>
		/// <param name="data">The animation data</param>
		/// <param name="node">The node to be animated</param>
		Animation(Data* data, SpriteNode* node);
		/// <summary>Constructs the animation by providing the json data, animation data and the sprite node</summary>
		/// <param name="data_file">JSON data filepath</param>
		/// <param name="sprite_file">The sprites' filename (w/o the file extension)</param>
		/// <param name="data">The animation data</param>
		/// <param name="node">The node to be animated</param>
		Animation(const std::string& data_file, const std::string& sprite_file,
			      Data* data, SpriteNode* node);
	public:
		/// <summary>Starts the animation (no effect if animation is already ongoing)</summary>
		/// <see cref="stop"/>
		/// <see cref="restart"/>
		void start();
		/// <summary>Stops the animation</summary>
		/// <see cref="start"/>
		/// <see cref="restart"/>
		void stop();
		/// <summary>Restarts the animation</summary>
		/// <see cref="start"/>
		/// <see cref="stop"/>
		void restart();
		/// <summary>Parses json animation file and inserts the data as frames</summary>
		/// <param name="data_file">JSON data filepath</param>
		/// <param name="sprite_file">The sprites' filename (w/o the file extension)</param>
		/// <example>
		/// <code>
		/// parseJsonFile("Assets/TextureData/KnightData.json", "Knight_Walk");
		/// </code>
		/// </example>
		void parseJsonFile(const std::string& data_file, const std::string& sprite_file);
		/// <summary>Checks if the animation is ongoing</summary>
		/// <returns>True if it's ongoing, false otherwise</returns>
		inline bool isOngoing() const { return animation_ongoing_; }
	private:
		/// <summary>Updates the node's properties (texture rect and origin)</summary>
		void updateNodeProperties();
		/// <summary>Adds in frames if the animation loops back and calculates the time per frame</summary>
		void finalizeAnimationSetup();
		/// <summary>Updates the node's animation</summary>
		virtual void updateCurrent(sf::Time dt) override;

	private:
		Data*       data_;
		SpriteNode* node_;

		unsigned    current_rect_;
		sf::Time    elapsed_time_;
		bool        animation_ongoing_;
	};
}
#endif