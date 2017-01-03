#include <iostream>

#include "Text.h"

namespace au
{
	Text::Text()
		: shadow_(nullptr)
		, font_(nullptr)
	{
	}

	Text::Text(const Text& copy)
		: MaterialNode(copy)
		, text_(copy.text_)
		, shadow_(copy.shadow_ ? std::make_unique<sf::Text>(*copy.shadow_) : nullptr)
		, font_(nullptr)
	{
	}

	void Text::setString(const std::string& string)
	{
		text_.setString(string);
		if (shadow_)
			shadow_->setString(string);

		correctOriginFlagProperties();
	}

	void Text::setFont(const sf::Font& font)
	{
		text_.setFont(font);
		if (shadow_)
			shadow_->setFont(font);

		font_.reset();
		correctOriginFlagProperties();
	}

	void Text::loadFontFromFile(const std::string& filename)
	{
		font_ = std::make_unique<sf::Font>();
		if (font_->loadFromFile(filename)) {
			text_.setFont(*font_);
			if (shadow_)
				shadow_->setFont(*font_);

			correctOriginFlagProperties();
		}
		else
			std::cerr << "\nUnable to load font\"" << filename << "\"\n\n";
	}

	void Text::setCharacterSize(unsigned size)
	{
		text_.setCharacterSize(size);
		if (shadow_)
			shadow_->setCharacterSize(size);

		correctOriginFlagProperties();
	}

	void Text::setStyle(sf::Uint32 style)
	{
		text_.setStyle(style);
		if (shadow_)
			shadow_->setStyle(style);

		correctOriginFlagProperties();
	}

	void Text::setFillColor(const sf::Color& color)
	{
		text_.setFillColor(color);
	}

	void Text::setOutlineColor(const sf::Color& color)
	{
		text_.setOutlineColor(color);
	}

	void Text::setOutlineThickness(float thickness)
	{
		text_.setOutlineThickness(thickness);
	}

	sf::Vector2f Text::findCharacterPos(size_t index) const
	{
		return text_.findCharacterPos(index);
	}

	void Text::activateShadow(bool flag)
	{
		if (!shadow_ && flag)
			shadow_ = std::make_unique<sf::Text>(text_);
		else if (shadow_ && !flag)
			shadow_.reset();
	}

	void Text::setShadowOffset(float offset_x, float offset_y)
	{
		if (shadow_)
			shadow_->setPosition(offset_x, offset_y);
	}

	void Text::setShadowOffset(const sf::Vector2f& offset)
	{
		setShadowOffset(offset.x, offset.y);
	}

	void Text::setShadowColor(const sf::Color& color)
	{
		if (shadow_)
			shadow_->setFillColor(color);
	}

	sf::FloatRect Text::getLocalBounds() const
	{
		return text_.getLocalBounds();
	}

	void Text::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (shadow_)
			target.draw(*shadow_, states);
		target.draw(text_, states);
	}
}