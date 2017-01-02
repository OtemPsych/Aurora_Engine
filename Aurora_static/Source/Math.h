#ifndef Aurora_Math_H_
#define Aurora_Math_H_

#define Math_PI 3.14159265f

#include <cmath>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Vector2.hpp>

namespace au
{
	/// <summary>Static utility class for a number of math functions</summary>
	class Math : private sf::NonCopyable
	{
	private:
		/// <summary>Disabled default constructor, no instance of this class may be created</summary>
		Math() = default;
	public:
		/// <summary>Converts radians to degrees</summary>
		/// <param name="radians">Value in radians</param>
		/// <returns>Value in degrees</returns>
		/// <see cref="toRadians"/>
		static float toDegrees(float radians);
		/// <summary>Converts degrees to radians</summary>
		/// <param name="degrees">Value in degrees</param>
		/// <returns>Value in radians</returns>
		/// <see cref="toDegrees"/>
		static float toRadians(float degrees);
		/// <summary>Calculates the hypotenuse of a vector</summary>
		/// <param name="vec">The vector from which the hypotenuse will be calculated</param>
		/// <returns>Length of the hypotenuse</returns>
		static float calculateHypotenuse(const sf::Vector2f& vec);
		/// <summary>
		/// Normalizes a vector<para/>
		/// (Provides a direction by reducing the vector's length to 1)
		/// </summary>
		/// <param name="vec">The vector that will be normalized</param>
		/// <returns>Normalized vector</returns>
		static sf::Vector2f normalizeVector(const sf::Vector2f& vec);
	};
}
#endif