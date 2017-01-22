#include "Button.h"
#include <iostream>

namespace au
{
	namespace gui
	{
		Button::Button(sf::RenderWindow* window)
			: text_(nullptr)
			, current_state_(State::Idle)
			, window_(window)
		{
			for (size_t i = 0; i < State::StateCount; i++) {
				auto state(std::make_unique<VertexNode>());
				states_[i] = state.get();
				attachChild(std::move(state));
			}
			activateCurrentState();
		}

		Button::Button(const sf::Vector2f& size, sf::RenderWindow* window)
			: text_(nullptr)
			, current_state_(State::Idle)
			, window_(window)
		{
			for (size_t i = 0; i < State::StateCount; i++) {
				auto state(std::make_unique<VertexNode>(size));
				states_[i] = state.get();
				attachChild(std::move(state));
			}
			activateCurrentState();
		}

		Button::Button(const Button& copy)
			: MaterialNode(copy)
			, text_(nullptr)
			, current_state_(copy.current_state_ == State::Disabled ? State::Disabled : State::Idle)
			, window_(copy.window_)
		{
			for (size_t i = 0; i < State::StateCount; i++) {
				auto state(std::make_unique<VertexNode>(*copy.states_[i]));
				states_[i] = state.get();
				attachChild(std::move(state));
			}
			activateCurrentState();

			if (copy.text_) {
				auto text(std::make_unique<Text>(*copy.text_));
				text_ = text.get();
				attachChild(std::move(text));
			}
		}

		Button::~Button()
		{
		}

		void Button::activate(bool flag)
		{
			if (current_state_ == State::Disabled && flag) {
				current_state_ = State::Idle;
				activateCurrentState();
			}
			else if (current_state_ != State::Disabled && !flag) {
				current_state_ = State::Disabled;
				activateCurrentState();
			}
		}

		void Button::activateText(bool flag)
		{
			if (!text_ && flag) {
				auto text(std::make_unique<Text>());
				text_ = text.get();
				attachChild(std::move(text));
				alignText(OriginFlag::Center, 0.f);
			}
			else if (text_ && !flag) {
				detachChild(*text_);
				text_ = nullptr;
			}
		}

		void Button::alignText(sf::Uint16 origin_flags, float padding)
		{
			if (text_) {
				text_->setOriginFlags(origin_flags);
				text_->setRelativeAlignment(*this, origin_flags, padding);
			}
		}

		sf::FloatRect Button::getLocalBounds() const
		{
			au::VertexNode* current_state = states_[current_state_];
			return current_state->getTransform().transformRect(current_state->getLocalBounds());
		}

		bool Button::isHoveredOver() const
		{
			return getGlobalBounds().contains(window_->mapPixelToCoords(sf::Mouse::getPosition(*window_)));
		}

		void Button::handleEventCurrent(const sf::Event& event)
		{
			if (current_state_ != State::Disabled && event.mouseButton.button == sf::Mouse::Left) {
				if (current_state_ == State::HoveredOver && event.type == sf::Event::MouseButtonPressed) {
					current_state_ = State::HeldDown;
					activateCurrentState();
				}
				else if ((current_state_ == State::HeldDown || current_state_ == State::Clicked) && event.type == sf::Event::MouseButtonReleased) {
					current_state_ = isHoveredOver() ? State::Clicked : State::Idle;
					activateCurrentState();
				}
			}
		}

		void Button::updateCurrent(sf::Time dt)
		{
			if (current_state_ != State::Disabled) {
				if (current_state_ == State::Idle && isHoveredOver()) {
					current_state_ = State::HoveredOver;
					activateCurrentState();
				}
				else if (current_state_ == State::HoveredOver && !isHoveredOver()) {
					current_state_ = State::Idle;
					activateCurrentState();
				}
			}
		}

		void Button::activateCurrentState()
		{
			for (size_t i = 0; i < State::StateCount; i++) {
				bool flag = static_cast<State>(i) == current_state_;
				states_[i]->activateEventHandling(ActivationTarget::All, flag);
				states_[i]->activateUpdating(ActivationTarget::All, flag);
				states_[i]->activateDrawing(ActivationTarget::All, flag);
			}
			correctOriginFlagProperties();
			alignText(OriginFlag::Center, 0.f);
		}
	}
}