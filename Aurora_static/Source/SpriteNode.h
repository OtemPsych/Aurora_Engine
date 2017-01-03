#ifndef Aurora_SpriteNode_H_
#define Aurora_SpriteNode_H_

#include <SFML/Graphics/Sprite.hpp>

#include "MaterialNode.h"

namespace au
{
	/// <summary>MaterialNode derivative that possesses a sf::Sprite</summary>
	class SpriteNode : public MaterialNode
	{
	public:
		/// <summary>Default constructor</summary>
		SpriteNode() = default;
		/// <summary>Copy constructor</summary>
		/// <param name="copy">SpriteNode object that will be copied</param>
		SpriteNode(const SpriteNode& copy);
		/// <summary>Constructs node by providing a texture</summary>
		/// <param name="texture">Texture</param>
		explicit SpriteNode(const sf::Texture& texture);
		/// <summary>Constructs node by providing a texture and a texture rect</summary>
		/// <param name="texture">Texture</param>
		/// <param name="rect">Texture rect to use of the texture provided</param>
		SpriteNode(const sf::Texture& texture, const sf::FloatRect& rect);
		/// <summary>Virtual destructor</summary>
		virtual ~SpriteNode();
	public:
		/// <summary>Set the node's texture</summary>
		/// <param name="texture">Texture</param>
		/// <see cref="setTextureRect"/>
		void setTexture(const sf::Texture& texture);
		/// <summary>Set the node's texture rect</summary>
		/// <param name="rect">Texture rect</param>
		/// <see cref="setTexture"/>
		void setTextureRect(const sf::FloatRect& rect);
		/// <summary>Returns the node's local bounds</summary>
		/// <returns>The node's local bounds</returns>
		virtual sf::FloatRect getLocalBounds() const override;
	protected:
		/// <summary>Draws the node's sprite</summary>
		/// <param name="target">Render target (window, render texture)</param>
		/// <param name="states">Render states (transform, texture)</param>
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Sprite sprite_;
	};
}
#endif