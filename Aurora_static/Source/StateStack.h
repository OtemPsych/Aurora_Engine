#ifndef Aurora_StateStack_H_
#define Aurora_StateStack_H_

#include <memory>
#include <map>
#include <functional>

#include "StateIdentifiers.h"
#include "State.h"

namespace au
{
	class Application;

	/// <summary>Class that manages all game states</summary>
	class StateStack : private sf::NonCopyable
	{
	public:
		enum Action { Push, Pop, Remove, Clear };
	private:
		using StatePtr = std::unique_ptr<State>;
		struct PendingChange {
			explicit PendingChange(Action action, StateID::ID state_id = StateID::None);

			Action      action;
			StateID::ID state_id;
		};

	public:
		/// <summary>Constructs the state stack by providing the application and the active window</summary>
		/// <param name="app">The application</param>
		/// <param name="window">The active window</param>
		StateStack(Application* app, sf::RenderWindow* window);
	public:
		/// <summary>Sends event to all states</summary>
		/// <param name="event">Polled input event</param>
		void handleEvent(const sf::Event& event);
		/// <summary>Updates all states</summary>
		/// <param name="dt">Time passed for current frame</param>
		void update(sf::Time dt);
		/// <summary>Draws all states</summary>
		void draw();
		/// <summary>Places a state push command in the pending list</summary>
		/// <param name="state_id">The state id associated with a certain state</param>
		void pushState(StateID::ID state_id);
		/// <summary>Places a state pop command in the pending list</summary>
		void popState();
		/// <summary>Places a state removal command in the pending list</summary>
		/// <param name="state_id">The state id associated with a certain state</param>
		void removeState(StateID::ID state_id);
		/// <summary>Places a command to clear all states in the pending list</summary>
		void clearStates();
		/// <summary>Gets the state specified</summary>
		/// <param name="state_id">The state id associated with a certain state</param>
		/// <returns>The state specified</returns>
		const State* getState(StateID::ID state_id);
		/// <summary>
		/// Registers a new state<para/>
		/// A state must be registered before being pushed
		/// </summary>
		/// <param name="state_id">The state id associated with a certain state</param>
		template <typename T>
		void registerState(StateID::ID state_id);
		/// <summary>Sets an fps cap</summary>
		/// <param name="fps_cap">The fps cap</param>
		void setFpsCap(unsigned fps_cap);
		/// <summary>Returns the current fps</summary>
		/// <returns>Current fps</returns>
		unsigned getFps() const;
		/// <summary>Sets the window clear color</summary>
		/// <param name="color">The window's clear color</param>
		void setClearColor(const sf::Color& color);
		/// <summary>Returns the window's clear color</summary>
		/// <returns>The window's clear color</returns>
		const sf::Color& getClearColor() const;
		/// <summary>Checks if the state stack is empty</summary>
		/// <returns>True if it's empty, false otherwise</returns>
		inline bool isEmpty() const { return stack_.empty(); }
		/// <summary>Gets the total amount of active states</summary>
		/// <returns>Amount of active states</returns>
		inline size_t getSize() const { return stack_.size(); }
	private:
		/// <summary>Creates the state specified if it has been registered</summary>
		/// <param name="state_id">The state id associated with a certain state</param>
		/// <returns>State to be added in the stack</returns>
		StatePtr createState(StateID::ID state_id);
		/// <summary>Applies all the pending commands</summary>
		void applyPendingChanges();

	private:
		std::vector<std::pair<StateID::ID, StatePtr>>    stack_;
		std::vector<PendingChange>                       pending_list_;
		std::map<StateID::ID, std::function<StatePtr()>> factories_;
		Application*                                     app_;
		sf::RenderWindow*                                window_;
	};
}
#include "StateStack.inl"
#endif