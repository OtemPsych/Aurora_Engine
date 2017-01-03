#ifndef Aurora_Text_H_
#define Aurora_Text_H_

#include <SFML/Graphics/Text.hpp>

#include "MaterialNode.h"

namespace au
{
	/// <summary>
	/// Functions like a sf::Text but derives from MaterialNode and adds in an optional shadow<para/>
	/// to the text and the ability to load in a font directly from the object<para/>
	/// This functionality can be useful for a font that is only used once (i.e. title on the main menu)
	/// </summary>
	class Text : public MaterialNode
	{
	public:
		/// <summary>
		/// Default constructor<para/>
		/// No font is loaded in nor a shadow
		/// </summary>
		Text();
		/// <summary>Copy constructor</summary>
		/// <param name="copy">Text object that will be copied</param>
		Text(const Text& copy);
	public:
		/// <summary>Sets a string for the text (and shadow if active)</summary>
		/// <param name="string">String to use</param>
		/// <see cref="getString"/>
		void setString(const std::string& string);
		/// <summary>Sets a font for the text (and shadow if active)</summary>
		/// <param name="font">Font to use</param>
		/// <see cref="loadFontFromFile"/>
		/// <seealso cref="getFont"/>
		void setFont(const sf::Font& font);
		/// <summary>
		/// Loads in a font from a file for this Text object<para/>
		/// Can be useful for a font that is only used once (i.e. title on the main menu)
		/// </summary>
		/// <param name="filename">String containing the resource file path</param>
		/// <see cref="setFont"/>
		/// <seealso cref="getFont"/>
		void loadFontFromFile(const std::string& filename);
		/// <summary>Sets a character size for the text (and shadow if active)</summary>
		/// <param name="size">Character size</param>
		/// <see cref="getCharacterSize"/>
		void setCharacterSize(unsigned size);
		/// <summary>Sets a style for the text (and shadow if active)</summary>
		/// <param name="style">SFML text style properties</param>
		/// <see cref="getStyle"/>
		void setStyle(sf::Uint32 style);
		/// <summary>Sets the fill color for the text</summary>
		/// <param name="color">Fill color</param>
		/// <see cref="setOutlineColor"/>
		/// <seealso cref="getFillColor"/>
		void setFillColor(const sf::Color& color);
		/// <summary>Sets the outline color for the text</summary>
		/// <param name="color">Outline color</param>
		/// <see cref="setOutlineThickness"/>
		/// <see cref="setFillColor"/>
		/// <seealso cref="getOutlineColor"/>
		void setOutlineColor(const sf::Color& color);
		/// <summary>Sets the outline thickness for the text</summary>
		/// <param name="thickness">Outline thickness</param>
		/// <see cref="setOutlineColor"/>
		/// <seealso cref="getOutlineThickness"/>
		void setOutlineThickness(float thickness);
		/// <summary>Finds the position of a character in the text</summary>
		/// <param name="index">The character's index to search for</param>
		/// <returns>The position of the character specified</returns>
		sf::Vector2f findCharacterPos(size_t index) const;
		/// <summary>
		/// Activates a shadow for the text<para/>
		/// All of the text's properties will be copied into the shadow when activated
		/// </summary>
		/// <param name="flag">True to activate, false to deactivate</param>
		/// <see cref="isShadowActive"/>
		void activateShadow(bool flag);
		/// <summary>
		/// Sets the shadow's offset from the main text<para/>
		/// The shadow must be activated
		/// </summary>
		/// <param name="offset_x">The horizontal offset</param>
		/// <param name="offset_y">The vertical offset</param>
		/// <see cref="activateShadow"/>
		/// <see cref="isShadowActive"/>
		/// <seealso cref="getShadowOffset"/>
		void setShadowOffset(float offset_x, float offset_y);
		/// <summary>
		/// Sets the shadow's offset from the main text<para/>
		/// The shadow must be activated
		/// </summary>
		/// <param name="offset">The offset</param>
		/// <see cref="activateShadow"/>
		/// <see cref="isShadowActive"/>
		/// <seealso cref="getShadowOffset"/>
		void setShadowOffset(const sf::Vector2f& offset);
		/// <summary>
		/// Sets the shadow's color<para/>
		/// The shadow must be activated
		/// </summary>
		/// <param name="color">The shadow's color</param>
		/// <see cref="activateShadow"/>
		/// <see cref="isShadowActive"/>
		/// <seealso cref="getShadowColor"/>
		void setShadowColor(const sf::Color& color);
		/// <summary>Returns the text's local bounds without taking into account the shadow</summary>
		/// <returns>The text's local bounds</returns>
		virtual sf::FloatRect getLocalBounds() const override;
		/// <summary>Gets the font that is currenly being used by the text</summary>
		/// <returns>The text's font</returns>
		/// <see cref="setFont"/>
		/// <see cref="loadFontFromFile"/>
		inline const sf::Font* getFont() const { return text_.getFont(); }
		/// <summary>Gets the text's string</summary>
		/// <returns>The text's string</returns>
		/// <see cref="setString"/>
		inline const sf::String& getString() const { return text_.getString(); }
		/// <summary>Gets the text's character size</summary>
		/// <returns>The text's character size</returns>
		/// <see cref="setCharacterSize"/>
		inline unsigned getCharacterSize() const { return text_.getCharacterSize(); }
		/// <summary>Gets the text's sfml style properties</summary>
		/// <returns>The text's sfml style properties</returns>
		/// <see cref="setStyle"/>
		inline sf::Uint32 getStyle() const { return text_.getStyle(); }
		/// <summary>Gets the text's fill color</summary>
		/// <returns>The text's fill color</returns>
		/// <see cref="setFillColor"/>
		inline const sf::Color& getFillColor() const { return text_.getFillColor(); }
		/// <summary>Gets the text's outline color</summary>
		/// <returns>The text's outline color</returns>
		/// <see cref="setOutlineColor"/>
		inline const sf::Color& getOutlineColor() const { return text_.getOutlineColor(); }
		/// <summary>Gets the text's outline thickness</summary>
		/// <returns>The text's outline thickness</returns>
		/// <see cref="setOutlineThickness"/>
		inline float getOutlineThickness() const { return text_.getOutlineThickness(); }
		/// <summary>Check if the shadow is active</summary>
		/// <returns>True if active, false otherwise</returns>
		/// <see cref="activateShadow"/>
		inline bool isShadowActive() const { return shadow_ != nullptr; }
		/// <summary>Gets the shadow's offset from the main text</summary>
		/// <returns>The shadow's position (if active)</returns>
		/// <see cref="setShadowOffset"/>
		inline const sf::Vector2f* getShadowOffset() const { return shadow_ ? &shadow_->getPosition() : nullptr; }
		/// <summary>Gets the shadow's fill color</summary>
		/// <returns>The shadow's fill color (if active)</returns>
		/// <see cref="setShadowColor"/>
		inline const sf::Color* getShadowColor() const { return shadow_ ? &shadow_->getFillColor() : nullptr; }
	private:
		/// <summary>Draws the text (and shadow if active)</summary>
		/// <param name="target">Render target (window, render texture)</param>
		/// <param name="states">Render states (transform, texture)</param>
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Text                  text_;
		std::unique_ptr<sf::Text> shadow_;
		std::unique_ptr<sf::Font> font_;
	};
}
#endif