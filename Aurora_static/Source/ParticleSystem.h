#ifndef Aurora_ParticleSystem_H_
#define Aurora_ParticleSystem_H_

#include <functional>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "SceneNode.h"

namespace au
{
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

	class ParticleSystem : public SceneNode
	{
	public:
		explicit ParticleSystem(sf::PrimitiveType prim_type = sf::Quads, size_t max_particles = 0,
			                    const sf::Texture* texture = nullptr);
		ParticleSystem(const ParticleSystem& copy);
	public:
		void setInitializer(const std::function<Particle()>& initializer);
		void setAffector(const std::function<void(Particle&, sf::Time)>& affector);

		inline void setMaxParticles(size_t max = 0) { max_particles_ = max; }
		inline void setTexture(const sf::Texture* texture) { texture_ = texture; }
		inline void activateEmitter(bool state = true) { emitter_active_ = state; }
		inline void setEmitterPosition(sf::Vector2f pos) { emitter_pos_ = pos; }

		inline size_t getMaxParticles() const { return max_particles_; }
		inline sf::Vector2f getEmitterPosition() const { return emitter_pos_; }
	private:
		void computeVertices() const;
		void addParticle();
		void addVertex(float x, float y, unsigned tu, unsigned tv, const sf::Color& color) const;
		virtual void updateCurrent(sf::Time dt) override;
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