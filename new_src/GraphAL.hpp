#ifndef GRAPH_AL
#define GRAPH_AL

#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <map>
#include <assert.h>
#include <stdexcept>

//typedef std::shared_ptr<IdType> IdPtr;
// template <typename IdType>
// typedef std::shared_ptr<NodeAL<IdType>> NodeALPtr;



using namespace std;

template <typename IdType>
class NodeAL;
template <typename IdType>
class GraphAL;

/************************* GraphAL Class ****************************/
template <typename IdType>
class GraphAL{
friend class NodeAL<IdType>;
public:
	/* Need to add more constructors such as list initialization here*/
	GraphAL(){
		next_unique_id = 0;
		cout << "created a graph\n";
	}

	// Function return the neighbours of the node
	// vector<shared_ptr<NodeAL<IdType>>>& neighbours(IdType& src){
	// 	Pointer<NodeAL> _src = id_map.find(src.id);
	// 	return _src->neighbours;
	// }

/* 	TODO: For these we need to decide what we do if the operation 
 *	is already true. ex. add_vertex when the vertex is already there.
 *	Exception? return false? */
	bool adjacent(IdType x, IdType y){
		return true;
	}
	bool add_vertex(IdType x){
		
		/* Check if the vertex is already in the graph */
		if(id_map.find(x) != id_map.end()){
			throw std::invalid_argument("vertex already added");
		}

		/* Create the wrapper and add it to adjacency list */
		shared_ptr<NodeAL<IdType>> vertex_sp(new NodeAL<IdType>(*this, x));
		int internal_id = vertex_sp->internal_id;

		//TODO: factor this out into a helper?
		if(internal_id == next_unique_id - 1){
			adjacency_list.push_back(vertex_sp);
		}else{
			adjacency_list[internal_id] = vertex_sp;
		}
		
		/* Add the new mapping into the map */
		id_map[x] = vertex_sp;
		assert(id_map.find(x)->second == vertex_sp); //ASSERT
		return true;
	}

	bool remove_vertex(IdType x){

		/* Check if the vertex is not in the graph */
		if(id_map.find(x) == id_map.end()){
			throw std::invalid_argument("vertex not in the graph");
		}

		/* Get the internal id of the wrapper of x */
		int internal_id = id_map.find(x)->second->internal_id;
		cout << internal_id << " HELLO\n";

		/* Remove all outgoing endes from the vertex */
		for(auto node_sp: adjacency_list[internal_id]->neighbours){
			node_sp.reset();
		}

		/* Destroy incoming edges */
		for(auto node_sp : adjacency_list){
			for(auto neighbour_sp : node_sp->neighbours){
				if(neighbour_sp == adjacency_list[internal_id])
					neighbour_sp.reset();
			}
		}

		/* Remove the vertex from the adjacency list */
		//TODO: Segfault happens here. Doing something wrong with sp.
		adjacency_list[internal_id].reset();

		/* Get the unique id back for id recycling */
		return_id(internal_id);
		return true;
	}
	bool add_edge(IdType x, IdType y){
		return true;
	}
	bool remove_edge(IdType x, IdType y){
		return true;
	}

	void print_graph() {
		for(auto node_sp : this->adjacency_list){
			cout << *(node_sp->user_id_p) << ": ";
			for(auto neighbour_sp : node_sp->neighbours){
				cout << *(neighbour_sp->user_id_p) << " ";
			}
			cout << endl;
		}
	}
/*	TODO: Not sure how these factor into our library
 *	get_vertex_value(G, x): returns the value associated with the vertex x;
 *	set_vertex_value(G, x, v): sets the value associated with the vertex x to v. */
private:
	
	/* Vector of smart pointers to wrappers. This allows direct access
	to the neighbours of the node from its wrapper. The penalty – vertex
	removal */
	vector<shared_ptr<NodeAL<IdType>>> adjacency_list;
	// Need this map to go from Node -> NodeAL
	map<IdType, shared_ptr<NodeAL<IdType>> > id_map;

	/* Same idea as for GraphAM here */
	long next_unique_id;
	vector<int> free_ids;

	/* Function hands out the new id when a vertex is added*/
	long get_new_id(){
		if(free_ids.empty()){
			return next_unique_id++;
		}else{
			int temp = free_ids.back();
			free_ids.pop_back();
			return temp;
		}
	}

	bool return_id(int internal_id){
		free_ids.push_back(internal_id);
	}

};

/************************* NodeAL Class ****************************/

/* Adjacency list implementation node wrapper */
//TODO: Need Comparable on ID type here
template <typename IdType>
class NodeAL{
friend class GraphAL<IdType>;
public:
	/* Need to think about other constructors here a little */
	/* Existance of NodeAL only makes sense in the context of a graph */
	NodeAL(GraphAL<IdType>& graph, IdType& user_id){
		/* Get the new internal id */
		internal_id = graph.get_new_id();
		
		/* No neighbours yet, so empty vector */
		neighbours = vector<shared_ptr<NodeAL<IdType>>>();

		user_id_p = &user_id;
	}

private:
	/* Necessary to distinguish the node within the graph*/
	long internal_id;
	/* This way, we avoid indexing into the adjacency list*/
	vector<shared_ptr<NodeAL<IdType>>> neighbours;
	
	/* Smart pointer to the user created object, my be comparable */
	IdType* user_id_p;

	bool operator==(const NodeAL& rhs){
		return (*(this->user_id_p))==(*(rhs.user_id_p));
	}
};


#endif
