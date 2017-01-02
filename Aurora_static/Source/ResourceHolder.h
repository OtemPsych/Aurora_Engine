#ifndef Aurora_ResourceHolder_H_
#define Aurora_ResourceHolder_H_

#include <map>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

namespace au
{
	/// <summary>
	/// Stores SFML resources by providing a filename and an ID(enum value)<para/>
	/// Available typedefs: TextureHolder, ImageHolder, FontHolder and SoundBufferHolder<para/>
	/// Only an ID has to be provided if one of the available typedefs is used
	/// </summary>
	/// <param name="ID">Enumeration type</param>
	/// <param name="Res">SFML resource type (sf::Texture, sf::Font, sf::Image, etc.)</param>
	template <typename ID, typename Res>
	class ResourceHolder : private sf::NonCopyable
	{
	public:
		/// <summary>Loads in a resource</summary>
		/// <param name="filename">String containing the resource file path</param>
		/// <param name="id">Enumeration value with which to link the resource</param>
		/// <see cref="unload"/>
		/// <seealso cref="get"/>
		void load(const std::string& filename, ID id);
		/// <summary>Loads in a shader resource</summary>
		/// <param name="filename">String containing the resource file path</param>
		/// <param name="shaderParam">Extra parameter for shader loading</param>
		/// <param name="id">Enumeration value with which to link the resource</param>
		/// <see cref="unload"/>
		/// <seealso cref="get"/>
		template <typename ShaderParam>
		void load(const std::string& filename, const ShaderParam& shaderParam, ID id);
		/// <summary>Unloads a resource</summary>
		/// <param name="id">ID of the resource to unload</param>
		/// <see cref="load"/>
		void unload(ID id);
		/// <summary>Retrieves a resource</summary>
		/// <param name="id">ID of the resource to retrieve</param>
		/// <returns>Resource of associated id</returns>
		/// <see cref="load"/>
		Res& get(ID id);
		/// <summary>Retrieves a resource</summary>
		/// <param name="id">ID of the resource to retrieve</param>
		/// <returns>Resource of associated id</returns>
		/// <see cref="load"/>
		const Res& get(ID id) const;
	private:
		/// <summary>Insert resource into holder</summary>
		/// <param name="res">Resource to be added</param>
		/// <param name="id">Associated ID</param>
		void insertResource(const Res& res, ID id);

	private:
		std::map<ID, Res> mResourceMap;
	};

	template <typename ID>
	using TextureHolder = ResourceHolder<ID, sf::Texture>;
	template <typename ID>
	using ImageHolder = ResourceHolder<ID, sf::Image>;
	template <typename ID>
	using FontHolder = ResourceHolder<ID, sf::Font>;
	template <typename ID>
	using SoundBufferHolder = ResourceHolder<ID, sf::SoundBuffer>;
}
#include "ResourceHolder.inl"
#endif