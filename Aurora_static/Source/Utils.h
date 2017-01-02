#ifndef Aurora_Utils_H_
#define Aurora_Utils_H_

#include <SFML/System/Utf.hpp>

namespace au
{
	namespace utils
	{
		/// <summary>
		/// Provides the same functionality as a std::pair<para/>
		/// Interchanges the first and second attributes by original and current
		/// </summary>
		/// <param name="T">A numeric value</param>
		template <typename T>
		struct Resource
		{
			/// <summary>Default constructor</summary>
			Resource() = default;
			/// <summary>Starting value constructor</summary>
			/// <param name="amount">Starting value</param>
			Resource(T amount);

			T original, current;
		};
	}
}

#include "Utils.inl"
#endif