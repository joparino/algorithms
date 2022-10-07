
#include <stdexcept>
#include <algorithm>
#include <limits>
#include "graph.h"

jp::Vertex::Vertex(const std::string& name) noexcept(false) :
	name_{ name }
{
}


std::string jp::Vertex::getName() const noexcept
{
	return name_;
}


bool jp::operator==(const Vertex& lhs, const Vertex& rhs) noexcept
{
	return lhs.name_ == rhs.name_;
}


bool jp::operator!=(const Vertex& lhs, const Vertex& rhs) noexcept
{
	return !(lhs == rhs);
}


jp::Vertex& jp::Graph::addVertex(const std::string& name) noexcept(false)
{
	auto vertex{ vertices_.insert(std::make_pair(Vertex{ name }, List{})) };
	return const_cast<Vertex&>(vertex.first->first);
}


jp::Edge::Edge(const Vertex& from, const Vertex& to, int weight) noexcept :
	from_{ from },
	to_{ to },
	weight_{ weight }
{}


void jp::Graph::addDirectedEdge(const Vertex& from, const Vertex& to, int weight) noexcept(false)
{
	auto& list{ findList(from) };
	list.push_back(Edge{ from, to, weight });
}


void jp::Graph::addEdge(const Vertex& from, const Vertex& to, int weight) noexcept(false)
{
	addDirectedEdge(from, to, weight);
	addDirectedEdge(to, from, weight);
}


std::list<jp::Vertex*> jp::Graph::dijkstra(Vertex& from, Vertex& to) const noexcept(false)
{
	std::unordered_map<Vertex, int> labels;
	std::unordered_map<Vertex, bool> visited;
	std::unordered_map<Vertex, Vertex*> previous;

	std::for_each(begin(vertices_), end(vertices_),
		[&](std::pair<const jp::Vertex, jp::Graph::List>& vertexAndList) {
			const auto& vertex{ vertexAndList.first };
			labels[vertex] = std::numeric_limits<int>::max();
			visited[vertex] = false;
			previous[vertex] = nullptr;
	});
	labels[from] = 0;

	Vertex* current = nullptr;
	while (true)
	{	
		current = nullptr;
		int min{ std::numeric_limits<int>::max() };
		std::for_each(begin(vertices_), end(vertices_),
			[&](std::pair<const jp::Vertex, jp::Graph::List>& vertexAndList) {
				const auto& vertex{ vertexAndList.first };
				if (labels[vertex] < min && !visited[vertex])
				{
					min = labels[vertex];
					current = const_cast<Vertex*>(&vertex);
				}
		});

		if (!current)
		{
			break;
		}

		std::for_each(begin(vertices_[*current]), end(vertices_[*current]),
			[&](Edge& edge) {
				auto sum{ labels[*current] + edge.weight_ };
				if (sum < labels[edge.to_])
				{
					labels[edge.to_] = sum;
					previous[edge.to_] = current;
				}
		});
		visited[*current] = true;
	}

	std::list<Vertex*> path;
	
	current = &to;
	while (*current != from)
	{
		path.push_front(current);
		current = previous[*current];
	}
	if (!path.empty())
	{
		path.push_front(&from);
	}

	return path;
}


jp::Graph::List& jp::Graph::findList(const Vertex& vertex) noexcept(false)
{
	auto list{ vertices_.find(vertex) };
	if (list == vertices_.end())
	{
		throw std::runtime_error{ "Vertex not found" };
	}
	return list->second;
}
