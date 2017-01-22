#include <SFML/Window/Event.hpp>

#include "Application.h"

namespace au
{
	Application::Application(sf::VideoMode vmode, const std::string& title, sf::Uint32 style,
		const sf::ContextSettings& settings)
		: window_(vmode, title, style, settings)
		, state_stack_(this, &window_)
		, time_per_frame_(sf::seconds(1.f / 60.f))
		, current_fps_(60)
		, clear_color_(sf::Color::Black)
	{
		window_.setFramerateLimit(60);
	}

	void Application::run()
	{
		sf::Clock clock;
		sf::Time time_since_last_update(sf::Time::Zero);
		sf::Time time_counter(sf::Time::Zero);
		unsigned fps = 0;
		while (window_.isOpen()) {
			processEvents();
			sf::Time time_passed(clock.restart());

			// FPS Counter
			if ((time_counter += time_passed) >= sf::seconds(1.f)) {
				time_counter = sf::Time::Zero;
				current_fps_ = fps;
				fps = 0;
			}
			else
				fps++;

			time_since_last_update += time_passed;
			while (time_since_last_update > time_per_frame_) {
				time_since_last_update -= time_per_frame_;
				processEvents();
				update();
			}
			render();
		}
	}

	void Application::pushState(StateID::ID state_id)
	{
		state_stack_.pushState(state_id);
	}

	void Application::setFpsCap(unsigned fps_cap)
	{
		time_per_frame_ = sf::seconds(1.f / fps_cap);
		window_.setFramerateLimit(fps_cap);
	}

	void Application::processEvents()
	{
		sf::Event event;
		while (window_.pollEvent(event)) {
			state_stack_.handleEvent(event);
			if (state_stack_.isEmpty())
				window_.close();
			if (event.type == sf::Event::Closed)
				state_stack_.clearStates();
		}
	}

	void Application::update()
	{
		state_stack_.update(time_per_frame_);
	}

	void Application::render()
	{
		window_.clear(clear_color_);
		state_stack_.draw();
		window_.display();
	}
}