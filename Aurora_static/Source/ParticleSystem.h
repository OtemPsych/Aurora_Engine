#ifndef Aurora_ParticleSystem_H_
#define Aurora_ParticleSystem_H_

#include <functional>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "SceneNode.h"

namespace au
{
	/// <summary>Struct that describes a particle</summary>
	struct Particle
	{
		sf::Vector2f position;
		sf::Vector2f size;
		sf::Vector2f velocity;
		sf::Vector2f acceleration;
		sf::Color	 color;
		sf::Time	 lifetime;
		sf::Time*    originalLifetime;
	};

	/// <summary>Class that manages particle creation and emission</summary>
	class ParticleSystem : public SceneNode
	{
	public:
		/// <summary>Constructs the particle system</summary>
		/// <param name="prim_type">The particles' primitive type</param>
		/// <param name="max_particles">The max particles that can be emitted</param>
		/// <param name="texture">The particles' texture</param>
		explicit ParticleSystem(sf::PrimitiveType prim_type = sf::Quads, size_t max_particles = 0,
			                    const sf::Texture* texture = nullptr);
		/// <summary>Copy constructor</summary>
		/// <param name="copy">The particle system that will be copied</param>
		ParticleSystem(const ParticleSystem& copy);
	public:
		/// <summary>Sets the particles' initializer</summary>
		/// <param name="initializer">An std::function that returns a Particle</param>
		void setInitializer(const std::function<Particle()>& initializer);
		/// <summary>Sets the particles' affector</summary>
		/// <param name="affector">An std::function that takes in a particle and an sf::Time</param>
		void setAffector(const std::function<void(Particle&, sf::Time)>& affector);
		/// <summary>Sets the max particles that can be emitted</summary>
		/// <param name="max">The max particles</param>
		/// <see cref="getMaxParticles"/>
		inline void setMaxParticles(size_t max = 0) { max_particles_ = max; }
		/// <summary>Returns the max particles that can be emitted</summary>
		/// <returns>The max particles</returns>
		/// <see cref="setMaxParticles"/>
		inline size_t getMaxParticles() const { return max_particles_; }
		/// <summary>Sets the particles' texture</summary>
		/// <param name="texture">The particles' texture</param>
		inline void setTexture(const sf::Texture* texture) { texture_ = texture; }
		/// <summary>(De)Activates the emitter</summary>
		/// <param name="flag">True to activate the emitter, false otherwise</param>
		inline void activateEmitter(bool flag = true) { emitter_active_ = flag; }
		/// <summary>Sets the emitter's position</summary>
		/// <param name="pos">The emitter's position</param>
		inline void setEmitterPosition(sf::Vector2f pos) { emitter_pos_ = pos; }
		/// <summary>Returns the emitter's position</summary>
		/// <returns>The emitter's position</returns>
		inline sf::Vector2f getEmitterPosition() const { return emitter_pos_; }
	private:
		/// <summary>Recomputes the vertices' positions and transparency ratios</summary>
		void computeVertices() const;
		/// <summary>Adds in a new particle</summary>
		void addParticle();
		/// <summary>Helper method to facilitate vertex insertion</summary>
		/// <param name="x">The position along the x axis</param>
		/// <param name="y">The position along the y axis</param>
		/// <param name="tu">The texture rect position along the x axis</param>
		/// <param name="tv">The texture rect position along the y axis</param>
		/// <param name="color">The vertex's color</param>
		void addVertex(float x, float y, unsigned tu, unsigned tv, const sf::Color& color) const;
		/// <summary>Updates the particles (reduces particle lifetime, recomputes vertices)</summary>
		/// <param name="dt">Time passed in current frame</param>
		virtual void updateCurrent(sf::Time dt) override;
		/// <summary>Draws all the vertices</summary>
		/// <param name="target">Render target (window, render texture)</param>
		/// <param name="states">Render states (transform, texture)</param>
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		std::vector<Particle>                                     particles_;
		size_t								                      max_particles_;
		mutable sf::VertexArray					                  vertex_array_;
		const sf::Texture*						                  texture_;

		bool									                  emitter_active_;
		sf::Vector2f                                              emitter_pos_;

		sf::Time                                                  original_particle_lifetime_;
		std::unique_ptr<std::function<Particle()>>                initializer_;
		std::unique_ptr<std::function<void(Particle&, sf::Time)>> affector_;
	};
}
#endif