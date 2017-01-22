#include "Textbox.h"
#include <iostream>

namespace au
{
	namespace gui
	{
		Textbox::Textbox(sf::RenderWindow* window)
			: Button(window)
			, action_confirmed_(false)
			, caret_(nullptr)
			, caret_timer_(sf::seconds(0.5f))
		{
			auto caret(std::make_unique<VertexNode>(sf::Vector2f(2.f, 30.f)));
			caret->setFillColor(sf::Color::Black);
			caret_ = caret.get();
			attachChild(std::move(caret));

			activateText(true);
		}

		Textbox::Textbox(const sf::Vector2f& size, sf::RenderWindow* window)
			: Button(size, window)
			, action_confirmed_(false)
			, caret_(nullptr)
			, caret_timer_(sf::seconds(0.5f))
		{
			auto caret(std::make_unique<VertexNode>(sf::Vector2f(2.f, 30.f)));
			caret->setPosition(size / 2.f);
			caret->setFillColor(sf::Color::Black);
			caret_ = caret.get();
			attachChild(std::move(caret));

			activateText(true);
		}

		Textbox::Textbox(const Textbox& copy)
			: Button(copy)
			, action_confirmed_(copy.action_confirmed_)
			, caret_(nullptr)
			, caret_timer_(copy.caret_timer_)
		{
			auto caret(std::make_unique<VertexNode>(*copy.caret_));
			caret_ = caret.get();
			attachChild(std::move(caret));

			activateText(true);
		}

		void Textbox::setCaretColor(const sf::Color& color)
		{
			caret_->setFillColor(color);
		}

		void Textbox::correctCaretProperties()
		{
			caret_timer_.current = caret_timer_.original;

			const sf::Color& color = (*caret_)[0].color;
			caret_->setFillColor(sf::Color(color.r, color.g, color.b, 255));

			modifyCaretHeight(static_cast<float>(text_->getCharacterSize()));
			if (text_->getString().isEmpty())
				caret_->setPosition(text_->getPosition());
			else {
				const sf::String& text_str = text_->getString();
				sf::Vector2f caret_pos(calculateNewCharacterPos(text_str.substring(text_str.getSize() - 1)));
				caret_->setPosition(caret_pos.x + 1.5f, caret_pos.y + text_->getLocalBounds().top - 1.f);
			}
		}

		bool Textbox::wasActionConfirmed()
		{
			bool confirmation = action_confirmed_;
			action_confirmed_ = false;

			return confirmation;
		}

		void Textbox::alignText(sf::Uint16 origin_flags, float padding)
		{
			if (text_) {
				text_->setOriginFlags(origin_flags);
				text_->setRelativeAlignment(*this, origin_flags, padding);
				caret_->setPosition(text_->getPosition());
			}
			correctCaretProperties();
		}

		void Textbox::modifyCaretHeight(float height)
		{
			caret_->modifySize(sf::Vector2f(caret_->getSize().x, height));
		}

		sf::Vector2f Textbox::calculateNewCharacterPos(const std::string& str)
		{
			sf::String text_str(text_->getString());
			sf::Vector2f last_char_pos(text_->findCharacterPos(text_str.getSize() - 1));
			text_->setString(text_str + str);
			float char_width = text_->findCharacterPos(text_->getString().getSize() - 1).x - last_char_pos.x;
			text_->setString(text_str);

			sf::Vector2f transformed_char_pos(text_->getTransform().transformPoint(last_char_pos));
			return sf::Vector2f(transformed_char_pos.x + char_width, transformed_char_pos.y);
		}

		void Textbox::updateCurrent(sf::Time dt)
		{
			Button::updateCurrent(dt);
			if (current_state_ == State::Clicked && (caret_timer_.current -= dt) <= sf::Time::Zero) {
				caret_timer_.current = caret_timer_.original;

				const sf::Color& color = (*caret_)[0].color;
				caret_->setFillColor(sf::Color(color.r, color.g, color.b, color.a == 0 ? 255 : 0));
			}
		}

		void Textbox::handleEventCurrent(const sf::Event& event)
		{
			State prev_state = current_state_;
			Button::handleEventCurrent(event);
			if (prev_state == State::Clicked && prev_state != current_state_) {
				caret_timer_.current = caret_timer_.original;

				const sf::Color& color = (*caret_)[0].color;
				caret_->setFillColor(sf::Color(color.r, color.g, color.b, 0));
			}

			if (current_state_ == State::Clicked && event.type == sf::Event::TextEntered) {
				std::string text_str(text_->getString());
				sf::FloatRect text_lbounds(text_->getLocalBounds());

				if (event.text.unicode >= 32 && event.text.unicode <= 127) {
					std::string new_char;
					new_char.push_back(static_cast<char>(event.text.unicode));
					sf::Vector2f char_pos(calculateNewCharacterPos(new_char));

					if (char_pos.x + 20.f < getLocalBounds().width)
						text_->setString(text_str + new_char);
					else if (text_lbounds.height + text_->getCharacterSize() + 5.f < getLocalBounds().height)
						text_->setString(text_str + "\n" + new_char);

					correctCaretProperties();
				}
				else if (event.text.unicode == 8 && !text_str.empty()) {
					text_str.pop_back();
					text_->setString(text_str);
					correctCaretProperties();
				}
			}
			else if (current_state_ == State::Clicked && event.type == sf::Event::KeyPressed
			  && event.key.code == sf::Keyboard::Return)
				action_confirmed_ = true;
		}
	}
}