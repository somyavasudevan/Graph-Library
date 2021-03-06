/// \file
/// \brief functions to create a graph are defined

#ifndef GRAPH_CREATE
#define GRAPH_CREATE

#include <memory>
#include "graph_concepts.h"
#include "graph_lib_header_helper.h"

template<typename G, typename F>
requires Vertex_numeric_id<typename G::element_type::vertex_type>
int get_unique_id(G g, F f)
{
	int max_id = 0;
	int sum_id = 0;
	int count_id = 0;
	if (num_vertices(g) == 0) {
		return 0;
	}
	vector<int> curr_vertices_ids = f(g);
	for (auto curr_id : curr_vertices_ids) {
		sum_id = sum_id + curr_id;
		if (curr_id > max_id) {
			max_id = curr_id;
		}
		count_id++;
	}
	int ideal_sum = (count_id * (count_id + 1)) / 2;
	if (count_id == max_id - 1 && ideal_sum == sum_id) {
		return 0;
	}
	if (ideal_sum == sum_id) {
		return max_id + 1;
	} else {
		return ideal_sum - sum_id;
	}
}

template<typename G>
requires Graph<G> && Vertex_numeric_id<typename G::element_type::vertex_type>
shared_ptr<typename G::element_type::vertex_type> create_vertex(G g)
{
	typedef typename G::element_type::vertex_type vertex_type;
	int unique_id = get_unique_id(g, [](G g) { return get_vertices_ids(g); });
	shared_ptr<vertex_type> new_vertex = make_shared<vertex_type>();
	new_vertex->set_key(unique_id);
	return new_vertex;
}

template<typename G, typename V>
requires Graph<G> && Vertex_ptr<V>
shared_ptr<typename G::element_type::edge_type> create_edge(G g, V x, V y)
{
	typedef typename G::element_type::edge_type edge_type;
	shared_ptr<edge_type> new_edge = make_shared<edge_type>(); 
	new_edge->v1 = *x;
	new_edge->v2 = *y;
	new_edge->cost = 1;
	return new_edge;
}

template<typename G, typename V, typename C>
requires Graph<G> && Vertex_ptr<V> && Numeric<C>
shared_ptr<typename G::element_type::edge_type> create_edge(G g, V x, V y, C c)
{
	typedef typename G::element_type::edge_type edge_type;
	shared_ptr<edge_type> new_edge = make_shared<edge_type>();
	new_edge->v1 = *x;
	new_edge->v2 = *y;
	new_edge->cost = c;
	return new_edge;
}

#endif
