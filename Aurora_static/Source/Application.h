#ifndef Aurora_Application_H_
#define Aurora_Application_H_

#include "StateStack.h"

namespace au
{
	/// <summary>Class that controls the entire application</summary>
	class Application : private sf::NonCopyable
	{
	public:
		/// <summary>Constructs the application by providing sf::Window parameters</summary>
		/// <param name="vmode">Video mode to use (defines the width, height and depth of the rendering area of the window)</param>
		/// <param name="title">Title of the window</param>
		/// <param name="style">Window style (Resizable, Fullscreen, etc.)</param>
		/// <param name="settings">Additional settings for the underlying OpenGL context</param>
		Application(sf::VideoMode vmode, const std::string& title, sf::Uint32 style = sf::Style::Default,
			        const sf::ContextSettings& settings = sf::ContextSettings());
	public:
		/// <summary>Launches the application</summary>
		void run();
		/// <summary>Pushes in a registered state</summary>
		/// <param name="state_id">The state id associated with a certain state</param>
		/// <see cref="registerState"/>
		void pushState(StateID::ID state_id);
		/// <summary>Registers a new state</summary>
		/// <param name="state_id">The state id associated with a certain state</param>
		template <typename T>
		void registerState(StateID::ID state_id);
		/// <summary>Sets an fps cap</summary>
		/// <param name="fps_cap">The fps cap</param>
		void setFpsCap(unsigned fps_cap);
		/// <summary>Returns the current fps</summary>
		/// <returns>Current fps</returns>
		inline unsigned getFps() const { return current_fps_; }
		/// <summary>Sets the window clear color</summary>
		/// <param name="color">The window's clear color</param>
		inline void setClearColor(const sf::Color& color) { clear_color_ = color; }
		/// <summary>Returns the window's clear color</summary>
		/// <returns>The window's clear color</returns>
		inline const sf::Color& getClearColor() const { return clear_color_; }
	private:
		/// <summary>Processes all polled events and sends them down the state stack</summary>
		void processEvents();
		/// <summary>Updates the state stack</summary>
		void update();
		/// <summary>Renders the state stack</summary>
		void render();

	private:
		sf::RenderWindow window_;
		StateStack       state_stack_;
		sf::Time         time_per_frame_;

		unsigned         current_fps_;
		sf::Color        clear_color_;
	};

	template <typename T>
	void Application::registerState(StateID::ID id)
	{
		state_stack_.registerState<T>(id);
	}
}
#endif