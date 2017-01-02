namespace au
{
	namespace utils
	{
		/// <summary>Starting value constructor</summary>
		/// <param name="amount">Starting value</param>
		template <typename T>
		Resource<T>::Resource(T amount)
			: original(amount)
			, current(amount)
		{
		}
	}
}