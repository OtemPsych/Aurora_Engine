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
		Res res;
		if (!res.loadFromFile(filename))
			std::cout << "\nResourceHolder::load - Failed to load " << filename << std::endl;
		else
			insertResource(std::move(res), id);
	}

	/// <summary>Loads in a shader resource</summary>
	/// <param name="filename">String containing the resource file path</param>
	/// <param name="t">Extra parameter for shader loading</param>
	/// <param name="id">Enumeration value with which to link the resource</param>
	/// <see cref="unload"/>
	/// <seealso cref="get"/>
	template <typename ID, typename Res>
	template <typename T>
	void ResourceHolder<ID, Res>::load(const std::string& filename, const T& t, ID id)
	{
		Res res;
		if (!res.loadFromFile(filename, t))
			std::cout << "\nResourceHolder::load - Failed to load " << filename << std::endl;
		else
			insertResource(std::move(res), id);
	}

	/// <summary>Unloads a resource</summary>
	/// <param name="id">ID of the resource to unload</param>
	/// <see cref="load"/>
	template <typename ID, typename Res>
	void ResourceHolder<ID, Res>::unload(ID id)
	{
		auto found = resource_map_.find(id);
		assert(found != resource_map_.end());

		resource_map_.erase(found);
	}

	/// <summary>Retrieves a resource</summary>
	/// <param name="id">ID of the resource to retrieve</param>
	/// <returns>Resource of associated id</returns>
	/// <see cref="load"/>
	template <typename ID, typename Res>
	Res& ResourceHolder<ID, Res>::get(ID id)
	{
		auto found = resource_map_.find(id);
		assert(found != resource_map_.end());

		return found->second;
	}

	/// <summary>Retrieves a resource</summary>
	/// <param name="id">ID of the resource to retrieve</param>
	/// <returns>Resource of associated id</returns>
	/// <see cref="load"/>
	template <typename ID, typename Res>
	const Res& ResourceHolder<ID, Res>::get(ID id) const
	{
		auto found = resource_map_.find(id);
		assert(found != resource_map_.end());

		return found->second;
	}

	/// <summary>Insert resource into holder</summary>
	/// <param name="res">Resource to be added</param>
	/// <param name="id">Associated ID</param>
	template <typename ID, typename Res>
	void ResourceHolder<ID, Res>::insertResource(const Res& res, ID id)
	{
		auto inserted = resource_map_.insert(std::make_pair(id, std::move(res)));
		assert(inserted.second);
	}
}