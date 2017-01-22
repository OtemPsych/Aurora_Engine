#include <cassert>

#include "StateStack.h"
#include "Application.h"

namespace au
{
	StateStack::PendingChange::PendingChange(Action action, StateID::ID state_id)
		: action(action)
		, state_id(state_id)
	{
	}

	StateStack::StateStack(Application* app, sf::RenderWindow* window)
		: app_(app)
		, window_(window)
	{
	}

	void StateStack::handleEvent(const sf::Event& event)
	{
		for (auto itr = stack_.rbegin(); itr != stack_.rend(); ++itr)
			if (!(*itr).second->handleEvent(event))
				break;

		applyPendingChanges();
	}

	void StateStack::update(sf::Time dt)
	{
		for (auto itr = stack_.rbegin(); itr != stack_.rend(); ++itr)
			if (!(*itr).second->update(dt))
				break;

		applyPendingChanges();
	}

	void StateStack::draw()
	{
		for (const auto& state : stack_)
			state.second->draw();
	}

	void StateStack::pushState(StateID::ID state_id)
	{
		pending_list_.emplace_back(Action::Push, state_id);
	}

	void StateStack::popState()
	{
		pending_list_.emplace_back(Action::Pop);
	}

	void StateStack::removeState(StateID::ID state_id)
	{
		pending_list_.emplace_back(Action::Remove, state_id);
	}

	void StateStack::clearStates()
	{
		pending_list_.emplace_back(Action::Clear);
	}

	const State* StateStack::getState(StateID::ID state_id)
	{
		for (const auto& state : stack_)
			if (state.first == state_id)
				return state.second.get();

		return nullptr;
	}

	void StateStack::setFpsCap(unsigned fps_cap)
	{ 
		app_->setFpsCap(fps_cap); 
	}

	unsigned StateStack::getFps() const
	{
		return app_->getFps();
	}

	void StateStack::setClearColor(const sf::Color& color)
	{
		app_->setClearColor(color);
	}

	const sf::Color& StateStack::getClearColor() const
	{
		return app_->getClearColor();
	}

	StateStack::StatePtr StateStack::createState(StateID::ID state_id)
	{
		auto found = factories_.find(state_id);
		assert(found != factories_.end());

		return found->second();
	}

	void StateStack::applyPendingChanges()
	{
		for (const auto& change : pending_list_)
			switch (change.action)
			{
			case Action::Push:
				stack_.emplace_back(change.state_id, createState(change.state_id));
				break;
			case Action::Pop:
				stack_.pop_back();
				break;
			case Action::Remove:
				std::remove_if(stack_.begin(), stack_.end(), [&change](const std::pair<StateID::ID, StatePtr>& state) {
					return state.first == change.state_id;
				});
				break;
			case Action::Clear:
				stack_.clear();
			}

		pending_list_.clear();
	}
}