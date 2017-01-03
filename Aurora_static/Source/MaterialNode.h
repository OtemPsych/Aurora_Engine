#ifndef Aurora_MaterialNode_H_
#define Aurora_MaterialNode_H_

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "SceneNode.h"

namespace au
{
	/// <summary>SceneNode derivative providing functionality for transformations</summary>
	class MaterialNode : public SceneNode, public sf::Transformable
	{
	public:
		/// <summary>
		/// Origin flags are an automatic way to set the local origin of a material node<para/>
		/// All of the origin flags except the Center origin flag an be paired together
		/// </summary>
		/// <example>
		/// The following code will place the local origin of the node at the top middle point
		/// <code>
		/// setOriginFlags(OriginFlag::CenterX | OriginFlag::Top)
		/// </code>
		/// </example>
		enum OriginFlag {
			Center  = 0,
			CenterX = 1 << 0,
			CenterY = 1 << 1,
			Left    = 1 << 2,
			Right   = 1 << 3,
			Top     = 1 << 4,
			Bottom  = 1 << 5
		};

	public:
		/// <summary>
		/// Default constructor<para/>
		/// Origin set to Top Left and global bounding rect drawing set to false
		/// </summary>
		MaterialNode();
		/// <summary>Copy constructor</summary>
		/// <param name="copy">MaterialNode objec that will be copied</param>
		MaterialNode(const MaterialNode& copy);
		/// <summary>Virtual destructor</summary>
		virtual ~MaterialNode();
	public:
		/// <summary>Calculates and returns the world position of the node</summary>
		/// <returns>The node's world position</returns>
		/// <see cref="getWorldTransform"/>
		sf::Vector2f getWorldPosition() const;
		/// <summary>
		/// Calculates and returns the world transform of the node by multiplying<para/>
		/// every parent's transform until the root node is reached
		/// </summary>
		/// <returns>The node's world tranform</returns>
		/// <see cref="getWorldPosition"/>
		sf::Transform getWorldTransform() const;
		/// <summary>
		/// Origin flags are an automatic way to set the local origin of a material node<para/>
		/// All of the origin flags except the Center origin flag can be paired together
		/// </summary>
		/// <param name="origin_flags">The origin flags</param>
		/// <example>
		/// The following code will place the local origin of the node at the top middle point
		/// <code>
		/// setOriginFlags(OriginFlag::CenterX | OriginFlag::Top)
		/// </code>
		/// </example>
		/// <see cref="getOriginFlags"/>
		void setOriginFlags(sf::Uint16 origin_flags);
		/// <summary>
		/// Relatively align this node to another material node or one of its derivatives<para/>
		/// i.e. Centering text inside of a rectangle<para/>
		/// This method works best if the alignment target is the node's parent
		/// </summary>
		/// <param name="alignment_target">The material node that will be used as the alignment target</param>
		/// <param name="alignment_flags">Specifies where the material node will be placed</param>
		/// <param name="padding">The padding (the spacing from the edge of the alignment target)</param>
		void setRelativeAlignment(const MaterialNode& alignment_target,
			                      sf::Uint16 alignment_flags, float padding);
		/// <summary>Returns the local bounds transformed by the world transform</summary>
		/// <returns>The node's global bounds</returns>
		/// <see cref="getLocalBounds"/>
		sf::FloatRect getGlobalBounds() const;
		/// <summary>
		/// Returns the local bounds of the node<para/>
		/// This method is defined by the user
		/// </summary>
		/// <returns>The node's local bounds</returns>
		/// <see cref="getGlobalBounds"/>
		virtual sf::FloatRect getLocalBounds() const;
		/// <summary>Returns the origin flags</summary>
		/// <returns>The node's origin flags</returns>
		/// <see cref="setOriginFlags"/>
		inline sf::Uint16 getOriginFlags() const { return origin_flags_; }
		/// <summary>
		/// Activate global bounding rect drawing (used for debugging purposes)<para/>
		/// Deactivated by default
		/// </summary>
		/// <param name="flag">True to activate, false otherwise</param>
		/// <see cref="drawGlobalBoundingRect"/>
		inline void activateGlobalBoundingRect(bool flag) { drawing_global_bounding_rect_ = flag; }
	protected:
		/// <summary>Recalculates the origin position based on the origin flags</summary>
		/// <see cref="setOriginFlags"/>
		void correctOriginFlagProperties();
	private:
		/// <summary>Draws the global bounding rect of the node for debugging purposes</summary>
		/// <param name="target">Render target (window, render texture)</param>
		/// <param name="states">Render states (transform, texture)</param>
		/// <see cref="activateGlobalBoundingRect"/>
		/// <seealso cref="getGlobalBounds"/>
		void drawGlobalBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const;
		/// <summary>Multiplies the states transform by its own transform and then draws all nodes</summary>
		/// <param name="target">Render target (window, render texture)</param>
		/// <param name="states">Render states (transform, texture)</param>
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

	private:
		sf::Uint16 origin_flags_;
		bool       drawing_global_bounding_rect_;
	};
}
#endif