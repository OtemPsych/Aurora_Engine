#include <SFML/Graphics/Texture.hpp>

#include "VertexNode.h"

namespace au
{
	VertexNode::VertexNode()
		: texture_(nullptr)
		, texture_rect_(0.f, 0.f, 0.f, 0.f)
	{
	}

	VertexNode::VertexNode(const VertexNode& copy)
		: MaterialNode(copy)
		, vertices_(copy.vertices_)
		, texture_(copy.texture_)
		, texture_rect_(copy.texture_rect_)
	{
	}

	VertexNode::VertexNode(const sf::Vector2f& size)
		: vertices_(sf::Quads)
		, texture_(nullptr)
		, texture_rect_(0.f, 0.f, 0.f, 0.f)
	{
		vertices_.append(sf::Vertex(sf::Vector2f(0.f,    0.f)));
		vertices_.append(sf::Vertex(sf::Vector2f(size.x, 0.f)));
		vertices_.append(sf::Vertex(sf::Vector2f(size.x, size.y)));
		vertices_.append(sf::Vertex(sf::Vector2f(0.f,    size.y)));
	}

	VertexNode::VertexNode(const sf::Texture& texture)
		: vertices_(sf::Quads, 4U)
		, texture_(&texture)
	{
		const sf::Vector2f texture_size(texture.getSize());
		setTextureRect(sf::FloatRect(0.f, 0.f, texture_size.x, texture_size.y));
	}

	VertexNode::VertexNode(const sf::Texture& texture, const sf::FloatRect& rect)
		: vertices_(sf::Quads, 4U)
		, texture_(&texture)
	{
		setTextureRect(rect);
	}

	VertexNode::VertexNode(sf::PrimitiveType prim_type, size_t vertex_count)
		: vertices_(prim_type, vertex_count)
		, texture_(nullptr)
		, texture_rect_(0.f, 0.f, 0.f, 0.f)
	{
	}

	VertexNode::~VertexNode()
	{
	}

	void VertexNode::setFillColor(const sf::Color& color)
	{
		for (size_t i = 0; i < vertices_.getVertexCount(); i++)
			vertices_[i].color = color;
	}

	void VertexNode::modifySize(const sf::Vector2f& size)
	{
		const sf::Vector2f current_size(getSize());
		for (size_t i = 0; i < vertices_.getVertexCount(); i++) {
			vertices_[i].position.x = size.x * vertices_[i].position.x / current_size.x;
			vertices_[i].position.y = size.y * vertices_[i].position.y / current_size.y;
		}
	}

	void VertexNode::setTexture(const sf::Texture& texture)
	{
		texture_ = &texture;

		const sf::Vector2f texture_size(texture.getSize());
		setTextureRect(sf::FloatRect(0.f, 0.f, texture_size.x, texture_size.y));
	}

	void VertexNode::setTextureRect(const sf::FloatRect& rect)
	{
		const float rect_right = rect.left + rect.width;
		const float rect_bottom = rect.top + rect.height;
		const sf::Vector2f node_size(getSize());

		texture_rect_ = rect;

		for (size_t i = 0; i < vertices_.getVertexCount(); i++) {
			vertices_[i].texCoords.x = vertices_[i].position.x * (rect_right - rect.left) / node_size.x;
			vertices_[i].texCoords.y = vertices_[i].position.y * (rect_bottom - rect.top) / node_size.y;
		}
	}

	sf::Vector2f VertexNode::getSize() const
	{
		sf::Vector2f size;
		for (size_t i = 0; i < vertices_.getVertexCount(); i++) {
			if (vertices_[i].position.x > size.x)
				size.x = vertices_[i].position.x;

			if (vertices_[i].position.y > size.y)
				size.y = vertices_[i].position.y;
		}

		return size;
	}

	sf::FloatRect VertexNode::getLocalBounds() const
	{
		return vertices_.getBounds();
	}

	void VertexNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.texture = texture_;
		target.draw(vertices_, states);
	}
}