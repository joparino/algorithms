
#pragma once

#include <unordered_map>
#include <list>

namespace jp
{
	class Vertex
	{
		friend class Graph;

	public:
		Vertex(const std::string& name) noexcept(false);
		std::string getName() const noexcept;

	private:
		std::string name_;

		template<typename T>
		friend struct std::hash;

		friend bool operator==(const Vertex& lhs, const Vertex& rhs) noexcept;
		friend bool operator!=(const Vertex& lhs, const Vertex& rhs) noexcept;
	};


	class Edge
	{
		friend class Graph;

	public:
		Edge(const Vertex& from, const Vertex& to, int weight) noexcept;

	private:
		const Vertex& from_;
		const Vertex& to_;
		int weight_;
	};
	

	bool operator==(const Vertex& lhs, const Vertex& rhs) noexcept;
	bool operator!=(const Vertex& lhs, const Vertex& rhs) noexcept;
}

template<>
struct std::hash<jp::Vertex>
{
	std::size_t operator()(jp::Vertex const& vertex) const noexcept
	{
		auto h1{ std::hash<std::string>{}(vertex.name_) };
		//std::size_t h2 = std::hash<std::string>{}(s.last_name);
		//return h1 ^ (h2 << 1); // or use boost::hash_combine
		return h1;
	}
};

namespace jp
{
	class Graph
	{
	public:
		Vertex& addVertex(const std::string& name) noexcept(false);
		void addDirectedEdge(const Vertex& from, const Vertex& to, int weight) noexcept(false);
		void addEdge(const Vertex& from, const Vertex& to, int weight) noexcept(false);
		std::list<Vertex*> dijkstra(Vertex& from, Vertex& to) const noexcept(false);

	private:
		typedef std::list<Edge> List;

		List& findList(const Vertex& vertex) noexcept(false);

		mutable std::unordered_map<Vertex, List> vertices_;
	};
}
