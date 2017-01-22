#ifndef Aurora_GUI_Button_H_
#define Aurora_GUI_Button_H_

#include <array>

#include <SFML/Graphics/RenderWindow.hpp>

#include "../VertexNode.h"
#include "../Text.h"

namespace au
{
	namespace gui
	{
		/// <summary>
		/// Class that provides gui button functionalities<para/>
		/// The Button class contains the different states(idle, clicked, hovered over, etc.)
		/// </summary>
		class Button : public MaterialNode
		{
		public:
			/// <summary>The different button states available</summary>
			enum State { Idle, Disabled, Clicked, HoveredOver, HeldDown, StateCount };

		public:
			/// <summary>Constructs button by providing the active window</summary>
			/// <param name="window">The active window</param>
			explicit Button(sf::RenderWindow* window);
			/// <summary>Constructs button by providing a size and the active window</summary>
			/// <param name="size">The button's size</param>
			/// <param name="window">The active window</param>
			Button(const sf::Vector2f& size, sf::RenderWindow* window);
			/// <summary>Copy constructor</summary>
			Button(const Button& copy);
			/// <summary>Virtual destructor</summary>
			virtual ~Button();
		public:
			/// <summary>(De)Activate the button (set to idle or disabled)</summary>
			/// <param name="flag">True to activate, false otherwise</param>
			void activate(bool flag);
			/// <summary>(De)Activate the button's text</summary>
			/// <param name="flag">True to activate, false otherwise</param>
			void activateText(bool flag);
			/// <summary>Aligns the text inside the button</summary>
			/// <param name="origin_flags">The origin flags to indicate the text's position inside the button</param>
			/// <param name="padding">The padding from the edges of the button</param>
			virtual void alignText(sf::Uint16 origin_flags, float padding);
			/// <summary>Returns the local bounds of the current state</summary>
			/// <returns>The current state's local bounds</returns>
			virtual sf::FloatRect getLocalBounds() const override;
			/// <summary>Checks if the text has been activated</summary>
			/// <returns>True if it's activated, false otherwise</returns>
			inline bool isTextActive() const { return text_ != nullptr; }
			/// <summary>Gets the text</summary>
			/// <returns>The text</returns>
			inline Text* getText() const { return text_; }
			/// <summary>Gets the current button state</summary>
			/// <returns>The current button state</returns>
			inline State getCurrentState() const { return current_state_; }
			/// <summary>Gets a button state to modify it for when it's activated</summary>
			/// <param name="state">The button state to return</param>
			/// <returns>The button state specified</returns>
			inline VertexNode& getState(State state) const { return *states_[state]; }
		protected:
			/// <summary>Checks if the button is currently being hovered over</summary>
			/// <returns>True if it's being hovered over, false otherwise</returns>
			bool isHoveredOver() const;
			/// <summary>Handles the polled input event</summary>
			/// <param name="event">Polled input event</param>
			virtual void handleEventCurrent(const sf::Event& event) override;
			/// <summary>Updates the button</summary>
			/// <param name="dt">Time passed for current frame</param>
			virtual void updateCurrent(sf::Time dt) override;
		private:
			/// <summary>Activates the current button state and deactivates the others</summary>
			void activateCurrentState();

		protected:
			Text*                                      text_;
			State                                      current_state_;
		private:
			sf::RenderWindow*                          window_;
			std::array<VertexNode*, State::StateCount> states_;
		};
	}
}
#endif