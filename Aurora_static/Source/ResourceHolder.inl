#include <cassert>
#include <iostream>

namespace au
{
	/// <summary>Loads in a resource</summary>
	/// <param name="filename">String containing the resource file path</param>
	/// <param name="id">Enumeration value with which to link the resource</param>
	/// <see cref="unload"/>
	/// <seealso cref="get"/>
	template <typename ID, typename Res>
	void ResourceHolder<ID, Res>::load(const std::string& filename, ID id)
	{
		Res resource;
		if (!resource.loadFromFile(filename))
			std::cout << "\nResourceHolder::load - Failed to load " << filename << std::endl;
		else
			insertResource(std::move(resource), id);
	}

	/// <summary>Loads in a shader resource</summary>
	/// <param name="filename">String containing the resource file path</param>
	/// <param name="shaderParam">Extra parameter for shader loading</param>
	/// <param name="id">Enumeration value with which to link the resource</param>
	/// <see cref="unload"/>
	/// <seealso cref="get"/>
	template <typename ID, typename Res>
	template <typename ShaderParam>
	void ResourceHolder<ID, Res>::load(const std::string& filename, const ShaderParam& shaderParam, ID id)
	{
		Res resource;
		if (!resource.loadFromFile(filename, shaderParam))
			std::cout << "\nResourceHolder::load - Failed to load " << filename << std::endl;
		else
			insertResource(std::move(resource), id);
	}

	/// <summary>Unloads a resource</summary>
	/// <param name="id">ID of the resource to unload</param>
	/// <see cref="load"/>
	template <typename ID, typename Res>
	void ResourceHolder<ID, Res>::unload(ID id)
	{
		auto found = mResourceMap.find(id);
		assert(found != mResourceMap.end());

		mResourceMap.erase(found);
	}

	/// <summary>Retrieves a resource</summary>
	/// <param name="id">ID of the resource to retrieve</param>
	/// <returns>Resource of associated id</returns>
	/// <see cref="load"/>
	template <typename ID, typename Res>
	Res& ResourceHolder<ID, Res>::get(ID id)
	{
		auto found = mResourceMap.find(id);
		assert(found != mResourceMap.end());

		return found->second;
	}

	/// <summary>Retrieves a resource</summary>
	/// <param name="id">ID of the resource to retrieve</param>
	/// <returns>Resource of associated id</returns>
	/// <see cref="load"/>
	template <typename ID, typename Res>
	const Res& ResourceHolder<ID, Res>::get(ID id) const
	{
		auto found = mResourceMap.find(id);
		assert(found != mResourceMap.end());

		return found->second;
	}

	/// <summary>Insert resource into holder</summary>
	/// <param name="res">Resource to be added</param>
	/// <param name="id">Associated ID</param>
	template <typename ID, typename Res>
	void ResourceHolder<ID, Res>::insertResource(const Res& res, ID id)
	{
		auto inserted = mResourceMap.insert(std::make_pair(id, std::move(res)));
		assert(inserted.second);
	}
}