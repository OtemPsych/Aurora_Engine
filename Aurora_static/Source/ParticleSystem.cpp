#include <iostream>

#include <SFML/Graphics/RenderTarget.hpp>

#include "ParticleSystem.h"

namespace au
{
	ParticleSystem::ParticleSystem(sf::PrimitiveType prim_type, size_t max_particles,
		const sf::Texture* texture)
		: max_particles_(max_particles)
		, vertex_array_(prim_type)
		, texture_(texture)
		, emitter_active_(false)
		, emitter_pos_()
		, original_particle_lifetime_(sf::Time::Zero)
		, initializer_(nullptr)
		, affector_(nullptr)
	{
	}

	ParticleSystem::ParticleSystem(const ParticleSystem& copy)
		: max_particles_(copy.max_particles_)
		, vertex_array_(copy.vertex_array_)
		, texture_(copy.texture_)
		, emitter_active_(copy.emitter_active_)
		, emitter_pos_(copy.emitter_pos_)
		, original_particle_lifetime_(copy.original_particle_lifetime_)
		, initializer_(copy.initializer_ ? std::make_unique<std::function<Particle()>>(*copy.initializer_) : nullptr)
		, affector_(copy.affector_ ? std::make_unique<std::function<void(Particle&, sf::Time)>>(*copy.affector_) : nullptr)
	{
	}

	void ParticleSystem::setInitializer(const std::function<Particle()>& initializer)
	{
		initializer_ = std::make_unique<std::function<Particle()>>(std::move(initializer));
		original_particle_lifetime_ = (*initializer_)().lifetime;
	}

	void ParticleSystem::setAffector(const std::function<void(Particle&, sf::Time)>& affector)
	{
		affector_ = std::make_unique<std::function<void(Particle&, sf::Time)>>(std::move(affector));
	}

	void ParticleSystem::computeVertices() const
	{
		if (original_particle_lifetime_ != sf::Time::Zero && !particles_.empty())
		{
			sf::Vector2f size(particles_.front().size);
			sf::Vector2f half = size / 2.f;

			vertex_array_.clear();

			for (const Particle& particle : particles_)
			{
				sf::Vector2f pos = particle.position;
				sf::Color c = particle.color;
				float ratio = particle.lifetime.asSeconds() / original_particle_lifetime_.asSeconds();
				c.a = static_cast<sf::Uint8>(255 * std::max(ratio, 0.f));

				sf::Vector2u textureSize(texture_ ? texture_->getSize() : sf::Vector2u(0, 0));
				addVertex(pos.x - half.x, pos.y - half.y, 0, 0, c);
				addVertex(pos.x + half.x, pos.y - half.y, textureSize.x, 0, c);
				addVertex(pos.x + half.x, pos.y + half.y, textureSize.x, textureSize.y, c);
				addVertex(pos.x - half.x, pos.y + half.y, 0, textureSize.y, c);
			}
		}
		else
			std::cout << "\n\nA particle's lifetime can't be set at 0\n\n";
	}

	void ParticleSystem::addParticle()
	{
		particles_.push_back(std::move((*initializer_)()));
		particles_.back().position = emitter_pos_;
		particles_.back().originalLifetime = &original_particle_lifetime_;
	}

	void ParticleSystem::addVertex(float x, float y, unsigned tu, unsigned tv, const sf::Color& color) const
	{
		vertex_array_.append(sf::Vertex(sf::Vector2f(x, y), color, sf::Vector2f((float)tu, (float)tv)));
	}

	void ParticleSystem::updateCurrent(sf::Time dt)
	{
		if (emitter_active_ && initializer_ && affector_)
		{
			if (particles_.size() < max_particles_ || max_particles_ == 0)
				addParticle();

			for (auto& particle : particles_) {
				(*affector_)(particle, dt);
				particle.lifetime -= dt;
			}
			if (!particles_.empty() && particles_.front().lifetime <= sf::Time::Zero) {
				particles_.erase(particles_.begin());
			}

			computeVertices();
		}
		else
			std::cout << "\n\nUnable to update ParticleSystem\n"
				      << "3 possible causes:\n"
				      << "  - The Emitter hasn't been activated\n"
				      << "  - The Initializer hasn't been set\n"
				      << "  - The Affector hasn't been set\n\n";
	}

	void ParticleSystem::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.texture = texture_;
		target.draw(vertex_array_, states);
	}
}