#ifndef Aurora_GUI_Textbox_H_
#define Aurora_GUI_Textbox_H_

#include <SFML/Graphics/RenderTexture.hpp>

#include "Button.h"
#include "../SpriteNode.h"
#include "../Utils.h"

namespace au
{
	namespace gui
	{
		/// <summary>Class that provides gui textbox functionalities</summary>
		class Textbox : public Button
		{
		public:
			/// <summary>Constructs textbox by providing the active window</summary>
			/// <param name="window">The active window</param>
			explicit Textbox(sf::RenderWindow* window);
			/// <summary>Constructs textbox by providing a size and the active window</summary>
			/// <param name="size">The textbox's size</param>
			/// <param name="window">The active window</param>
			Textbox(const sf::Vector2f& size, sf::RenderWindow* window);
			/// <summary>Copy constructor</summary>
			Textbox(const Textbox& copy);
		public:
			/// <summary>Sets the caret's color</summary>
			/// <param name="color">The caret's color</param>
			void setCaretColor(const sf::Color& color);
			/// <summary>Corrects the caret's properties (height, position, alignment)</summary>
			void correctCaretProperties();
			/// <summary>Checks if the Enter key was pressed while the textbox was selected</summary>
			/// <returns>True if the Enter key was pressed, false otherwise</returns>
			bool wasActionConfirmed();
			/// <summary>Aligns the text and the caret inside the textbox</summary>
			/// <param name="origin_flags">The origin flags to indicate the text's position inside the textbox</param>
			/// <param name="padding">The padding from the edges of the textbox</param>
			virtual void alignText(sf::Uint16 origin_flags, float padding) override;
		private:
			/// <summary>Modifies the caret's height</summary>
			/// <param name="height">The caret's modified height</param>
			void modifyCaretHeight(float height);
			/// <summary>Calculates where a new character's position will be if added to the text</summary>
			/// <param name="str">The new character</param>
			/// <returns>The new character's position in the text</returns>
			sf::Vector2f calculateNewCharacterPos(const std::string& str);
			/// <summary>Updates the textbox</summary>
			/// <param name="dt">Time passed for current frame</param>
			virtual void updateCurrent(sf::Time dt) override;
			/// <summary>Handles event received</summary>
			/// <param name="event">Polled input event</param>
			virtual void handleEventCurrent(const sf::Event& event) override;

		private:
			bool                      action_confirmed_;
			VertexNode*               caret_;
			utils::Resource<sf::Time> caret_timer_;
		};
	}
}
#endif