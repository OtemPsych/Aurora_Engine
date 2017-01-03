#include "SpriteNode.h"

namespace au
{
	SpriteNode::SpriteNode(const SpriteNode& copy)
		: MaterialNode(copy)
		, sprite_(copy.sprite_)
	{
	}

	SpriteNode::SpriteNode(const sf::Texture& texture)
		: sprite_(texture)
	{
	}

	SpriteNode::SpriteNode(const sf::Texture& texture, const sf::FloatRect& rect)
		: sprite_(texture, static_cast<sf::IntRect>(rect))
	{
	}

	SpriteNode::~SpriteNode()
	{
	}

	void SpriteNode::setTexture(const sf::Texture& texture)
	{
		sprite_.setTexture(texture);
	}

	void SpriteNode::setTextureRect(const sf::FloatRect& rect)
	{
		sprite_.setTextureRect(static_cast<sf::IntRect>(rect));
	}

	sf::FloatRect SpriteNode::getLocalBounds() const
	{
		return sprite_.getLocalBounds();
	}

	void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite_, states);
	}
}