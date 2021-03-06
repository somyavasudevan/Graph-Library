#include <iostream>
#include <cassert>
#include <vector>
#include "user_data_structures.h"
#include "../src/graph_lib.h"

using namespace std;

int main(int argc, char *argv[])
{
	assert(__cpp_concepts >= 201500);
	assert(__cplusplus >= 201500);

	using namespace graph_std_lib;

	city my_c("NYC", 1);
	city my_c2("NYC", 1);
	vector<city> vec;
	vec.push_back(my_c);
	vec.push_back(my_c2);
	my_c.set_name("jon");
	cout << vec[0].get_name() << '\n';
	cout << my_c.get_name() << '\n';
	shared_ptr<matrix_graph<city, road>> my_graph = make_shared<matrix_graph<city, road>>(10);
	auto v0 = create_vertex(my_graph);
	v0->set_name("New York");
	v0->set_population(8406000);
	add(my_graph, v0);
	cout << "NYC is 0\n";
	auto v1 = create_vertex(my_graph);
	v1->set_name("Los Angeles");
	v1->set_population(3808000);
	add(my_graph, v1);
	cout << "Los Angeles is 1\n";
	auto v2 = create_vertex(my_graph);
	v2->set_name("Chicago");
	v2->set_population(2719000);
	add(my_graph, v2);
	cout << "Chicago is 2\n";
	auto v3 = create_vertex(my_graph);
	v3->set_name("Austin");
	v3->set_population(885000);
	add(my_graph, v3);
	cout << "Austin is 3\n";
	auto v4 = create_vertex(my_graph);
	v4->set_name("Cleveland");
	v4->set_population(350000);
	add(my_graph, v4);
	cout << "Cleveland is 4\n";
	auto v5 = create_vertex(my_graph);
	v5->set_name("Atlanta");
	v5->set_population(3999);
	add(my_graph, v5);
	cout << "Atlanta is 5\n";
	auto v6 = create_vertex(my_graph);
	v6->set_name("Dallas");
	v6->set_population(3999);
	add(my_graph, v6);
	cout << "Dallas is 6\n";
	auto v7 = create_vertex(my_graph);
	v7->set_name("San Francisco");
	v7->set_population(700000);
	add(my_graph, v7);
	cout << "SF is 7\n";
	auto v8 = create_vertex(my_graph);
	v8->set_name("Dallas");
	v8->set_population(3333999);
	add(my_graph, v8);
	cout << "Dallas is 8\n";

	auto e1 = create_edge(my_graph, v0, v2);
	e1->cost = 1000;
	add_edge(my_graph, e1);

	auto e2 = create_edge(my_graph, v2, v0);
	e2->cost = 1000;
	add_edge(my_graph, e2);

	auto e3 = create_edge(my_graph, v2, v1);
	e3->cost = 1000;
	add_edge(my_graph, e3);

	auto e4 = create_edge(my_graph, v1, v2);
	e4->cost = 1000;
	add_edge(my_graph, e4);

	auto e5 = create_edge(my_graph, v2, v4);
	e5->cost = 1000;
	add_edge(my_graph, e5);

	auto e6 = create_edge(my_graph, v4, v2);
	e6->cost = 1000;
	add_edge(my_graph, e6);

	auto e7 = create_edge(my_graph, v1, v3);
	e7->cost = 1000;
	add_edge(my_graph, e7);

	auto e8 = create_edge(my_graph, v3, v1);
	e8->cost = 1;
	add_edge(my_graph, e8);

	auto e10 = create_edge(my_graph, v0, v5);
	e10->cost = 10;
	add_edge(my_graph, e10);

	auto e11 = create_edge(my_graph, v5, v3);
	e11->cost = 10;
	add_edge(my_graph, e11);

	auto e12 = create_edge(my_graph, v3, v8);
	e12->cost = 10;
	add_edge(my_graph, e12);

	/*
	auto edges = get_edges(my_graph);
	for (auto& e : edges) {
		//cout << e.v1.get_name() << "->" << e.v2.get_name() << '\n';
	}
	*/
	auto path_v0_v1 = find_path_dfs(my_graph, v0, v1);
	cout << "dfs: \n";
	for (auto& p : path_v0_v1->path_v) {
		cout << p.get_name() << ", ";
	}
	cout << "cost " << path_v0_v1->cost << '\n';
	path_v0_v1 = find_path_bfs(my_graph, v0, v1);
	cout << "bfs: \n";
	for (auto& p : path_v0_v1->path_v) {
		cout << p.get_name() << ", ";
	}
	cout << "cost " << path_v0_v1->cost << '\n';
	path_v0_v1 = find_path_ucs(my_graph, v0, v1);
	auto vector_of_vertices = path_v0_v1->path_v;
	cout << path_v0_v1->to_string() << '\n';
	for (auto s : path_v0_v1->path_v) {
		cout << s.to_string() << '\n';
	}
	cout << "ucs: \n";
	for (auto& p : path_v0_v1->path_v) {
		cout << p.get_name() << ", ";
	}
	cout << "cost " << path_v0_v1->cost << '\n';
	cout << '\n';
	path_v0_v1 = find_path_ast(my_graph, v0, v1);
	cout << "ast: \n";
	for (auto& p : path_v0_v1->path_v) {
		cout << p.get_name() << ", ";
	}
	cout << "cost " << path_v0_v1->cost << '\n';
	cout << '\n';
	cout << "path from chicago to Austin?\n";
	auto path_ex = path_exists(my_graph, v2, v3);
	cout << path_ex << '\n';
	cout << "path from dallas to Austin?\n";
	path_ex = path_exists(my_graph, v8, v3);
	cout << path_ex << '\n';
	cout << "cycle exists\n";
	auto cycle_ex = cycle_exists(my_graph);
	cout << cycle_ex << '\n';
	cout << "cycle exists for dallas\n";
	cycle_ex = cycle_exists(my_graph, v8);
	cout << cycle_ex << '\n';
	cout << "cycle exists for nyc\n";
	cycle_ex = cycle_exists(my_graph, v0);
	cout << cycle_ex << '\n';
	return 0;
}

