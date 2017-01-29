#ifndef Aurora_VertexNode_H_
#define Aurora_VertexNode_H_

#include <SFML/Graphics/VertexArray.hpp>

#include "MaterialNode.h"

namespace au
{
	/// <summary>MaterialNode derivative that possesses a sf::VertexArray</summary>
	class VertexNode : public MaterialNode
	{
	public:
		/// <summary>Default constructor</summary>
		VertexNode();
		/// <summary>Copy constructor</summary>
		/// <param name="copy">VertexNode object that will be copied</param>
		VertexNode(const VertexNode& copy);
		/// <summary>Constructs node by providing a size</summary>
		/// <param name="size">Size of the node</param>
		explicit VertexNode(const sf::Vector2f& size);
		/// <summary>Constructs node by providing a texture</summary>
		/// <param name="texture">Texture</param>
		explicit VertexNode(const sf::Texture& texture);
		/// <summary>Constructs node by proving a texture and a texture rect</summary>
		/// <param name="texture">Texture</param>
		/// <param name="rect">Texture rect to use of the texture provided</param>
		VertexNode(const sf::Texture& texture, const sf::FloatRect& rect);
		/// <summary>Constructs node by providing a primitive type and a vertex count</summary>
		/// <param name="prim_type">Primitive type of the vertex array</param>
		/// <param name="vertex_count">Total amount of vertices</param>
		VertexNode(sf::PrimitiveType prim_type, size_t vertex_count);
		/// <summary>Virtual destructor</summary>
		virtual ~VertexNode();
	public:
		/// <summary>Set the color of all the vertices</summary>
		/// <param name="color">Desired color</param>
		void setFillColor(const sf::Color& color);
		/// <summary>
		/// Modify the node's size<para/>
		/// If a vertex is currently situated at a middle point in the node<para/>
		/// then its position will increase and still remain at the middle<para/>
		/// This method can't be used to modify the size of a node that has a size of (0,0)
		/// </summary>
		/// <param name="size">Modified size of node</param>
		/// <see cref="getSize"/>
		void modifySize(const sf::Vector2f& size);
		/// <summary>Set the node's texture</summary>
		/// <param name="texture">Texture</param>
		/// <see cref="getTexture"/>
		/// <seealso cref="setTextureRect"/>
		void setTexture(const sf::Texture& texture);
		/// <summary>Set the node's texture rect</summary>
		/// <param name="rect">Texture rect</param>
		/// <see cref="getTextureRect"/>
		/// <seealso cref="setTexture"/>
		void setTextureRect(const sf::FloatRect& rect);
		/// <summary>Calculate the size of the node based on every vertex's position</summary>
		/// <returns>The size of the node</returns>
		/// <see cref="modifySize"/>
		sf::Vector2f getSize() const;
		/// <summary>Get the node's texture (if set)</summary>
		/// <returns>Pointer to texture if one has been set, nullptr otherwise</returns>
		/// <see cref="setTexture"/>
		inline const sf::Texture* getTexture() const { return texture_; }
		/// <summary>Get the node's texture rect</summary>
		/// <returns>Texture rect</returns>
		/// <see cref="setTextureRect"/>
		inline sf::FloatRect getTextureRect() const { return texture_rect_; }
		/// <summary>Access the vertices of the node using the [] operator</summary>
		/// <param name="index">Index of the vertex</param>
		/// <returns>The vertex found at index specified</returns>
		inline sf::Vertex& operator[](size_t index) { return vertices_[index]; }
		/// <summary>Get the node's local bounds</summary>
		/// <returns>The node's local bounds</returns>
		virtual sf::FloatRect getLocalBounds() const override;
	protected:
		/// <summary>Draws the node's vertices</summary>
		/// <param name="target">Render target (window, render texture)</param>
		/// <param name="states">Render states (transform, texture)</param>
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	public:
		sf::VertexArray    vertices_;
	private:
		const sf::Texture* texture_;
		sf::FloatRect      texture_rect_;
	};
}
#endif