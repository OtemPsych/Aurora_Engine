namespace au
{
	/// <summary>
	/// Registers a new state<para/>
	/// A state must be registered before being pushed
	/// </summary>
	/// <param name="state_id">The state id associated with a certain state</param>
	template <typename T>
	void StateStack::registerState(StateID::ID state_id)
	{
		factories_[state_id] = [this] {
			return StatePtr(std::make_unique<T>(this, window_));
		};
	}
}