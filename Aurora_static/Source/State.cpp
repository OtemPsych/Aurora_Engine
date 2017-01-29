#include "State.h"
#include "StateStack.h"

namespace au
{
	State::State(StateStack* stack, sf::RenderWindow* window)
		: stack_(stack)
		, window_(window)
		, window_bounds_(0, 0, window->getSize().x, window->getSize().y)
	{
	}

	State::~State()
	{
	}

	void State::reinitializeWindowBounds()
	{
		window_bounds_.width = window_->getSize().x;
		window_bounds_.height = window_->getSize().y;
	}

	bool State::handleEvent(const sf::Event& event)
	{
		scene_graph_.handleEvent(event);
		return true;
	}

	bool State::update(sf::Time dt)
	{
		scene_graph_.update(dt);
		return true;
	}

	void State::draw()
	{
		window_->draw(scene_graph_);
	}

	void State::buildScene()
	{
	}

	void State::setupResources()
	{
	}
}