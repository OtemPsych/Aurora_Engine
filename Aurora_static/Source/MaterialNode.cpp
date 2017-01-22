#include "MaterialNode.h"

namespace au
{
	MaterialNode::MaterialNode()
		: origin_flags_(OriginFlag::Left | OriginFlag::Top)
		, drawing_global_bounding_rect_(false)
	{
	}

	MaterialNode::MaterialNode(const MaterialNode& copy)
		: SceneNode(copy)
		, origin_flags_(copy.origin_flags_)
		, drawing_global_bounding_rect_(copy.drawing_global_bounding_rect_)
	{
		setOrigin(copy.getOrigin());
		setPosition(copy.getPosition());
		setScale(copy.getScale());
		setRotation(copy.getRotation());
	}

	MaterialNode::~MaterialNode()
	{
	}

	sf::Vector2f MaterialNode::getWorldPosition() const
	{
		return getWorldTransform() * sf::Vector2f();
	}

	sf::Transform MaterialNode::getWorldTransform() const
	{
		sf::Transform transform;
		for (const MaterialNode* node = this; node != nullptr; node = dynamic_cast<MaterialNode*>(parent_))
			transform *= node->getTransform();

		return transform;
	}

	void MaterialNode::setOriginFlags(sf::Uint16 origin_flags)
	{
		const sf::FloatRect lbounds(getLocalBounds());
		if (origin_flags == OriginFlag::Center)
			setOrigin(lbounds.left + lbounds.width / 2.f, lbounds.top + lbounds.height / 2.f);
		else {
			sf::Vector2f newOrigin(lbounds.left, lbounds.top);
			if (origin_flags & OriginFlag::CenterX)
				newOrigin.x = lbounds.left + lbounds.width / 2.f;
			else if (origin_flags & OriginFlag::Right)
				newOrigin.x = lbounds.left + lbounds.width;

			if (origin_flags & OriginFlag::CenterY)
				newOrigin.y = lbounds.top + lbounds.height / 2.f;
			else if (origin_flags & OriginFlag::Bottom)
				newOrigin.y = lbounds.top + lbounds.height;

			setOrigin(newOrigin);
		}

		origin_flags_ = origin_flags;
	}

	void MaterialNode::setRelativeAlignment(const MaterialNode& alignment_target,
		                                    sf::Uint16 alignment_flags, float padding)
	{
		const sf::FloatRect target_lbounds(alignment_target.getLocalBounds());
		if (alignment_flags == OriginFlag::Center)
			setPosition(target_lbounds.left + target_lbounds.width / 2.f,
				        target_lbounds.top + target_lbounds.height / 2.f);
		else {
			sf::Vector2f new_pos(target_lbounds.left + padding, target_lbounds.top + padding);
			if (alignment_flags & OriginFlag::CenterX)
				new_pos.x = target_lbounds.left + target_lbounds.width / 2.f;
			else if (alignment_flags & OriginFlag::Right)
				new_pos.x = target_lbounds.left + target_lbounds.width - padding;

			if (alignment_flags & OriginFlag::CenterY)
				new_pos.y = target_lbounds.top + target_lbounds.height / 2.f;
			else if (alignment_flags & OriginFlag::Bottom)
				new_pos.y = target_lbounds.top + target_lbounds.height - padding;

			setPosition(new_pos);
		}
	}

	sf::FloatRect MaterialNode::getGlobalBounds() const
	{
		return getWorldTransform().transformRect(getLocalBounds());
	}

	sf::FloatRect MaterialNode::getLocalBounds() const
	{
		return sf::FloatRect();
	}

	void MaterialNode::correctOriginFlagProperties()
	{
		setOriginFlags(origin_flags_);
	}

	void MaterialNode::drawGlobalBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const
	{
		const sf::FloatRect rect(getGlobalBounds());

		sf::RectangleShape shape(sf::Vector2f(rect.width, rect.height));
		shape.setPosition(rect.left, rect.top);
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineColor(sf::Color::Green);
		shape.setOutlineThickness(1.f);

		target.draw(shape);
	}

	void MaterialNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		SceneNode::draw(target, states);

		if (drawing_global_bounding_rect_)
			drawGlobalBoundingRect(target, states);
	}
}