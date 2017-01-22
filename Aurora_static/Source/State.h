#ifndef Aurora_State_H_
#define Aurora_State_H_

#include <SFML/Graphics/RenderWindow.hpp>

#include "SceneNode.h"

namespace au
{
	class StateStack;

	/// <summary>Class that facilitates game state representation (main menu, settings, pause, etc.)</summary>
	class State : private sf::NonCopyable
	{
	public:
		/// <summary>Constructs the state by providing the state stack and the active window</summary>
		/// <param name="stack">The state stack</param>
		/// <param name="window">The active window</param>
		State(StateStack* stack, sf::RenderWindow* window);
		/// <summary>Virtual destructor</summary>
		virtual ~State();
	public:
		/// <summary>Reinitializes the window bounds (for when the window is recreated)</summary>
		void reinitializeWindowBounds();
		/// <summary>
		/// Handles the polled input event<para/>
		/// Defined by the user
		/// </summary>
		/// <param name="event">Polled input event</param>
		/// <returns>True if the event should be passed to the other states, false otherwise</returns>
		/// <see cref="update"/>
		/// <see cref="draw"/>
		virtual bool handleEvent(const sf::Event& event) = 0;
		/// <summary>
		/// Updates the state<para/>
		/// Defined by the user
		/// </summary>
		/// <param name="dt">Time passed for current frame</param>
		/// <returns>True if the other states should be updated, false otherwise</returns>
		/// <see cref="handleEvent"/>
		/// <see cref="draw"/>
		virtual bool update(sf::Time dt) = 0;
		/// <summary>
		/// Draws the state<para/>
		/// Defined by the user
		/// </summary>
		/// <see cref="handleEvent"/>
		/// <see cref="update"/>
		virtual void draw() = 0;
	private:
		/// <summary>
		/// Initializes all the scene layers and the scene nodes<para/>
		/// Defined by the user
		/// </summary>
		virtual void buildScene() = 0;
		/// <summary>
		/// Setups all resources (textures, music/sound files, fonts, etc.)<para/>
		/// Defined by the user
		/// </summary>
		virtual void setupResources() = 0;

	protected:
		StateStack*             stack_;
		sf::RenderWindow*       window_;

		SceneNode               scene_graph_;
		std::vector<SceneNode*> scene_layers_;
		sf::IntRect             window_bounds_;
	};
}
#endif