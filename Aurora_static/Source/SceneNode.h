#ifndef Aurora_SceneNode_H_
#define Aurora_SceneNode_H_

#include <memory>
#include <vector>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Drawable.hpp>

namespace au
{
	/// <summary>
	/// Base class for scene graph architecture<para/>
	/// Provides functionality for attaching/detaching children nodes,<para/>
	/// event handling, updating and drawing the current node and its children.<para/>
	/// The majority (if not all) of user-defined classes will derive from this class<para/>
	/// or one of its derivatives<para/>
	/// Use a MaterialNode instead of a SceneNode if the node has a physical body
	/// </summary>
	class SceneNode : public sf::Drawable
	{
	public:
		/// <summary>Used to (de)activate event handling, updating or drawing</summary>
		enum class ActivationTarget { Current, Children, All };
	private:
		using NodePtr = std::unique_ptr<SceneNode>;

	public:
		/// <summary>
		/// Default constructor<para/>
		/// Event handling, updating and drawing are active by default on all nodes
		/// </summary>
		SceneNode();
		/// <summary>Copy constructor</summary>
		/// <param name="copy">SceneNode object that will be copied</param>
		SceneNode(const SceneNode& copy);
		/// <summary>Virtual destructor</summary>
		virtual ~SceneNode();
	public:
		/// <summary>Attaches a child node to this node</summary>
		/// <param name="child">SceneNode (or SceneNode derivative) unique_ptr created before calling this method</param>
		/// <see cref="detachChild"/>
		void attachChild(NodePtr child);
		/// <summary>Detaches a child node and returns it, detached node will by destroyed if not retrieved</summary>
		/// <param name="child">Stored child node</param>
		/// <returns>Detached child node</returns>
		/// <see cref="attachChild"/>
		NodePtr detachChild(const SceneNode& child);
		/// <summary>Sends event to current node and all of its children nodes</summary>
		/// <param name="event">Polled input event</param>
		/// <see cref="update"/>
		/// <see cref="draw"/>
		/// <seealso cref="handleEventChildren"/>
		/// <seealso cref="handleEventCurrent"/>
		void handleEvent(const sf::Event& event);
		/// <summary>Updates the current node and all of its children nodes</summary>
		/// <param name="dt">Time passed for current frame</param>
		/// <see cref="handleEvent"/>
		/// <see cref="draw"/>
		/// <seealso cref="updateChildren"/>
		/// <seealso cref="updateCurrent"/>
		void update(sf::Time dt);
		/// <summary>(De)Activates event handling for the current node, its children or all of them</summary>
		/// <param name="target">(De)Activate current node, its children or all of them</param>
		/// <param name="flag">True to activate, false to deactivate</param>
		/// <see cref="activateUpdating"/>
		/// <see cref="activateDrawing"/>
		void activateEventHandling(ActivationTarget target, bool flag);
		/// <summary>(De)Activates updating for the current node, its children or all of them</summary>
		/// <param name="target">(De)Activate current node, its children or all of them</param>
		/// <param name="flag">True to activate, false to deactivate</param>
		/// <see cref="activateEventHandling"/>
		/// <see cref="activateDrawing"/>
		void activateUpdating(ActivationTarget target, bool flag);
		/// <summary>(De)Activates drawing for the current node, its children or all of them</summary>
		/// <param name="target">(De)Activate current node, its children or all of them</param>
		/// <param name="flag">True to activate, false to deactivate</param>
		/// <see cref="activateEventHandling"/>
		/// <see cref="activateUpdating"/>
		void activateDrawing(ActivationTarget target, bool flag);
		/// <summary>
		/// Informs the user if the node must be removed from the scene<para/>
		/// Removal condition is defined by the user<para/>
		/// Nodes that are marked for removal are automatically removed from the scene
		/// </summary>
		/// <returns>True if the node will be removed, false otherwise</returns>
		/// <see cref="isDestroyed"/>
		virtual bool isMarkedForRemoval() const;
		/// <summary>
		/// Informs the user if the node is destroyed<para/>
		/// Destruction condition is defined by the user<para/>
		/// This can be useful when for example, a spaceship was destroyed but an<para/>
		/// explosion animation still needs to be played out before removing the node
		/// </summary>
		/// <returns>True if the node is destroyed, false otherwise</returns>
		/// <see cref="isMarkedForRemoval"/>
		virtual bool isDestroyed() const;
	protected:
		/// <summary>Draws the current node and all of its children nodes</summary>
		/// <param name="target">Render target (window, render texture)</param>
		/// <param name="states">Render states (transform, texture)</param>
		/// <see cref="handleEvent"/>
		/// <see cref="update"/>
		/// <seealso cref="drawChildren"/>
		/// <seealso cref="drawCurrent"/>
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	private:
		/// <summary>Remove all children nodes that are marked for removal</summary>
		/// <see cref="isMarkedForRemoval"/>
		void removeChildrenMarkedForRemoval();
		/// <summary>Sends event to all children nodes</summary>
		/// <param name="event">Polled input event</param>
		/// <see cref="handleEvent"/>
		/// <see cref="handleEventCurrent"/>
		void handleEventChildren(const sf::Event& event);
		/// <summary>
		/// Sends event to current node<para/>
		/// Method is defined by the user
		/// </summary>
		/// <param name="event">Polled input event</param>
		/// <see cref="handleEvent"/>
		/// <see cref="handleEventChildren"/>
		virtual void handleEventCurrent(const sf::Event& event);
		/// <summary>Updates all children nodes</summary>
		/// <param name="dt">Time passed for current frame</param>
		/// <see cref="update"/>
		/// <see cref="updateCurrent"/>
		void updateChildren(sf::Time dt);
		/// <summary>
		/// Updates current node<para/>
		/// Method is defined by the user
		/// </summary>
		/// <param name="dt">Time passed for current frame</param>
		/// <see cref="update"/>
		/// <see cref="updateChildren"/>
		virtual void updateCurrent(sf::Time dt);
		/// <summary>Draws all children nodes</summary>
		/// <param name="target">Render target (window, render texture)</param>
		/// <param name="states">Render states (transform, texture)</param>
		/// <see cref="draw"/>
		/// <see cref="drawCurrent"/>
		void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
		/// <summary>
		/// Draws current node<para/>
		/// Method is defined by the user
		/// </summary>
		/// <param name="target">Render target (window, render texture)</param>
		/// <param name="states">Render states (transform, texture)</param>
		/// <see cref="draw"/>
		/// <see cref="drawChildren"/>
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:
		SceneNode*           parent_;
	private:
		std::vector<NodePtr> children_;
		bool                 event_handling_current_;
		bool                 event_handling_children_;
		bool                 updating_current_;
		bool                 updating_children_;
		bool                 drawing_current_;
		bool                 drawing_children_;
	};
}
#endif