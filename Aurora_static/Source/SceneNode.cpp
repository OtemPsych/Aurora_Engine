#include <cassert>
#include <functional>

#include "SceneNode.h"

namespace au
{
	SceneNode::SceneNode()
		: parent_(nullptr)
		, event_handling_current_(true)
		, event_handling_children_(true)
		, updating_current_(true)
		, updating_children_(true)
		, drawing_current_(true)
		, drawing_children_(true)
	{
	}

	SceneNode::SceneNode(const SceneNode& copy)
		: parent_(copy.parent_)
		, event_handling_current_(copy.event_handling_current_)
		, event_handling_children_(copy.event_handling_children_)
		, updating_current_(copy.updating_current_)
		, updating_children_(copy.updating_children_)
		, drawing_current_(copy.drawing_current_)
		, drawing_children_(copy.drawing_children_)
	{
		for (const auto& child : copy.children_)
			children_.emplace_back(std::make_unique<SceneNode>(*child));
	}

	SceneNode::~SceneNode()
	{
	}

	void SceneNode::attachChild(NodePtr child)
	{
		child->parent_ = this;
		children_.push_back(std::move(child));
	}

	SceneNode::NodePtr SceneNode::detachChild(const SceneNode& child)
	{
		auto found = std::find_if(children_.begin(), children_.end(), [&child](NodePtr& p) {
			return p.get() == &child;
		});
		assert(found != children_.end());

		NodePtr result = std::move(*found);
		result->parent_ = nullptr;
		children_.erase(found);

		return std::move(result);
	}

	void SceneNode::handleEvent(const sf::Event& event)
	{
		if (event_handling_current_) handleEventCurrent(event);
		if (event_handling_children_) handleEventChildren(event);
	}

	void SceneNode::update(sf::Time dt)
	{
		removeChildrenMarkedForRemoval();

		if (updating_current_) updateCurrent(dt);
		if (updating_children_) updateChildren(dt);
	}

	void SceneNode::activateEventHandling(SceneNode::ActivationTarget target, bool flag)
	{
		switch (target) {
		case ActivationTarget::Current:
			event_handling_current_ = flag;
			break;
		case ActivationTarget::Children:
			event_handling_children_ = flag;
			break;
		case ActivationTarget::All:
			event_handling_current_ = flag;
			event_handling_children_ = flag;
		}
	}

	void SceneNode::activateUpdating(SceneNode::ActivationTarget target, bool flag)
	{
		switch (target) {
		case ActivationTarget::Current:
			updating_current_ = flag;
			break;
		case ActivationTarget::Children:
			updating_children_ = flag;
			break;
		case ActivationTarget::All:
			updating_current_ = flag;
			updating_children_ = flag;
		}
	}

	void SceneNode::activateDrawing(SceneNode::ActivationTarget target, bool flag)
	{
		switch (target) {
		case ActivationTarget::Current:
			drawing_current_ = flag;
			break;
		case ActivationTarget::Children:
			drawing_children_ = flag;
			break;
		case ActivationTarget::All:
			drawing_current_ = flag;
			drawing_children_ = flag;
		}
	}

	bool SceneNode::isMarkedForRemoval() const
	{
		return isDestroyed();
	}

	bool SceneNode::isDestroyed() const
	{
		return parent_ != nullptr;
	}

	void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (drawing_current_) drawCurrent(target, states);
		if (drawing_children_) drawChildren(target, states);
	}

	void SceneNode::removeChildrenMarkedForRemoval()
	{
		std::remove_if(children_.begin(), children_.end(), [](NodePtr& child) {
			return child->isMarkedForRemoval();
		});
	}

	void SceneNode::handleEventChildren(const sf::Event& event)
	{
		for (NodePtr& child : children_)
			child->handleEvent(event);
	}

	void SceneNode::handleEventCurrent(const sf::Event& event)
	{
	}

	void SceneNode::updateChildren(sf::Time dt)
	{
		for (NodePtr& child : children_)
			child->update(dt);
	}

	void SceneNode::updateCurrent(sf::Time dt)
	{
	}

	void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (const auto& child : children_)
			child->draw(target, states);
	}

	void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
	{
	}
}