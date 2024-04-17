/**********************************************************************************************
 * NIU CSCI 340 Section 0003                                                                  *
 * Assignment 10                                                                               *
 * Phoenix Chheav - Z1966108 - phoenixchh                                                     *
 *                                                                                            *
 *   I certify that everything I am submitting is either provided by the professor for use in *
 * the assignment, or work done by me personally. I understand that if I am caught submitting *
 * the work of others (including StackOverflow or ChatGPT) as my own is an act of Academic    *
 * Misconduct and will be punished as such.                                                   *
 *                                                                                            *
 **********************************************************************************************/
#ifndef NIU_CSCI340_GRAPH_H
#define NIU_CSCI340_GRAPH_H

// This is the file where the student should do their work.

#include "graph.decl.h"
#include <queue>
#include <functional>
#include <stack>
#include <iostream>

/**
 * @brief this function will return the number of vertices in the graph stored.
 * 
 * @return number of vertices in the graph stored.
 */
size_t Graph::nvertices() const {
  return vertices.size();
}

/**
 * @brief this function will return number of edges in the graph stored.
 * 
 * @return number of edges in graph stored. 
 */
size_t Graph::nedges() const { 
  return edges.size(); 
}

/**
 * @brief This function removes any data currently stored in the `Graph`,
 *        and replaces it with the graph described by the vertex vector, 
 *        `vertices`, and edge list vector, `edges`, passed in.
 * 
 * @param vertices a `std::vector` of strings containing labels for the vertices in the graph.
 * @param edges a `std::vector` of strings containing labels for the vertices in the graph.
 */
void Graph::assign(const std::vector<std::string> & vertices, const std::vector<GraphEdge> & edges) {
 this->vertices = vertices;
 this->v_lut.clear();
 for(size_t i = 0; i < nvertices(); ++i){
  v_lut[vertices[i]] = i;
 }
 this->edges = edges;
}

/**
 * @brief This function will be used to check if there is any edge exist in the graph
 * 
 * @param origin the index of the vertex the edge starts from
 * @param destination the index of the vertex the edge goes to
 * @return true if edge exists going from `origin` to `destination`
 * @return false if not
 */
bool Graph::edge_exists(size_t origin, size_t destination) const {
  for(const auto& edge : edges){
    if(edge.origin == origin && edge.destination == destination){
      return true;
    }
  }
  return false; 
}

/**
 * @brief This function will be used to check if the weight of edges in the graph
 * 
 * @param origin the index of the vertex the edge starts from
 * @param destination the index of the vertex the edge goes to
 * @return return the wieght of edges
 */
double Graph::edge_weight(size_t origin, size_t destination) const {
  if(edge_exists(origin, destination)){
    for(const auto& edge : edges){
      if(edge.origin == origin && edge.destination == destination){
        return edge.weight;
      }
    }
  }
  return INFINITY;
}

/**
 * @brief undirected adjacency
 * 
 * @param vertex index of the vertex whose adjacency list we want
 * @return vector containing an `AjdListEdge`
 */
std::vector<AdjListEdge> Graph::undirected_adjacency_list(size_t vertex) const {
  std::vector<AdjListEdge> v;
  for(const auto& edge : edges){
    if(edge.origin == vertex){
      v.push_back({edge.destination, edge.weight});
    }else if(edge.destination == vertex){
      v.push_back({edge.origin, edge.weight});
    }
  }
  return v;
}

/**
 * @brief in adjacency
 * 
 * @param vertex index of the vertex whose adjacency list we want
 * @return vector containing an `AjdListEdge`
 */
std::vector<AdjListEdge> Graph::in_adjacency_list(size_t vertex) const {
  std::vector<AdjListEdge> in_l;

  for(const auto& edge : edges){
    if(edge.destination == vertex){
      in_l.push_back({edge.origin, edge.weight});
    }
  }

  return in_l;
}

/**
 * @brief out adjacency
 * 
 * @param vertex index of the vertex whose adjacency list we want
 * @return vector containing an `AjdListEdge`
 */
std::vector<AdjListEdge> Graph::out_adjacency_list(size_t vertex) const {
  std::vector<AdjListEdge> out_l;

  for(const auto& edge : edges){
    if(edge.origin == vertex){
      out_l.push_back({edge.destination, edge.weight});
    }
  }
  return out_l;
}

/**
 * @brief This function returns the  weighted adjacency list in row major order.
 * 
 * @return weighted adjacency list
 */
std::vector <double> Graph::weighted_adjacency_matrix() const {
  std::vector<double> weighted_adj_matrix(nvertices() * nvertices(), INFINITY);

  for(const auto& edge : edges){
    // Retrieve index of origin
    size_t start = v_lut.at(vertices[edge.origin]);

    // Retrieve index of destination
    size_t end = v_lut.at(vertices[edge.destination]);

    //Assume that it is a directed graph
    weighted_adj_matrix[start * nvertices() + end] = edge.weight;
  }  
  return weighted_adj_matrix;
}

/**
 * @brief This function returns the unweighted adjacency list in row major order.
 * 
 * @return std::vector <bool> 
 */
std::vector <bool> Graph::unweighted_adjacency_matrix() const {
    // Initialize the adjacency matrix with false values
    std::vector<std::vector<bool>> unweighted_adj_matrix(nvertices(), std::vector<bool>(nvertices(), false));

  // Populate the adjacency matrix based on the given edges
  for (const auto& edge : edges) {
      int start_vertex = edge.origin;
      int end_vertex = edge.destination;
      // Mark the entry as true to represent the existence of an edge
      unweighted_adj_matrix[start_vertex][end_vertex] = true;
  }

  std::vector<bool> matrix;
  for(const auto& row : unweighted_adj_matrix){
    matrix.insert(matrix.end(), row.begin(), row.end());
  }

  return matrix;
}

/**
 * @brief This function returns the string label for the vertex index passed in.
 * 
 * @param vertex representing the index of the vertex to look up.
 * @return string label for the vertex index passed in.
 */
std::string Graph::v_label(size_t vertex) const {
  size_t size = nvertices();
  if(vertex < size){
    return vertices[vertex];
  }
  return "";
}

/**
 * @brief This function returns the index of the vertex whose label matches `label`.
 * 
 * @param label the `string` label of the vertex whose index you would like.
 * @return index of the vertex whose label matches `label`.
 */
ssize_t Graph::v_index(const std::string &label) const {
  auto i = v_lut.find(label);
  if(i != v_lut.end()){
    return i->second;
  }
  return -1; 
}

/**
 * @brief This funtion perform breadth first traversal of the graph starting from the vertex whose index is passed in as `start`.
 * 
 * @tparam FN 
 * @param start index of the vertex to start the traversal from
 * @param visitfn the function (or function-like object) to call when visiting
 * @param connected_only controls whether vertices to which not path from the `start` vertex exists are traversed separately.
 */
template <typename FN>
void Graph::breadth_first(size_t start, FN visitfn, bool connected_only) {
  std::vector<bool> visited(nvertices(), false);
  // Mark visited vertices to avoid processing them multiple times
  visited[start] = true;

  // Queue for BFS traversal
  std::queue<size_t> q;

  // Start queue
  q.push(start);
  //visited.insert(start);

  while(!q.empty()){
    // Dequeue a vertex from the queue and visit it
    size_t cur_vertex = q.front();
    q.pop();

    // Start visit opeation on cur_vertex
    visitfn(cur_vertex);

    for(const auto& edge : edges){
      if(edge.origin == cur_vertex && !visited[edge.destination]){
        // Mark the neighbor as visited and enqueue it
        visited[edge.destination] = true;
        q.push(edge.destination);
        // visited.insert(neighbor);
      }else if(!connected_only && edge.destination == cur_vertex && !visited[edge.origin]){
        // if not connect_only, also visit neighbors in the reverse direction
        visited[edge.origin] = true;
        q.push(edge.origin);
      }
    }
  }

  if(!connected_only){
    // Traverse
    for(size_t i = 0; i < nvertices(); ++i){
      if(!visited[i]){
        visitfn(i);
      }
    }
  }
}

/**
 * @brief Performs a depth first traversal of the graph starting from the vertex whose index is passed in as `start`.
 * 
 * @tparam FN 
 * @param start index of the vertex to start the traversal from
 * @param visitfn the function (or function-like object) to call when visiting
 * @param connected_only controls whether vertices to which not path from the `start` vertex exists are traversed separately.
 */
template <typename FN>
void Graph::depth_first(size_t start, FN visitfn, bool connected_only) {
  std::vector<bool> visited(nvertices(), false);

  std::function<void(size_t)> DFS;
  DFS = [&](size_t v){
    visited[v] = true;

    for(const auto& edge : edges){
      if(edge.origin == v){
        size_t end = edge.destination;
        if(!visited[end]){
          visitfn(end);
          DFS(end);
        }
      }
    }
  };

  if(!connected_only){
    for(size_t vertex = 0; vertex < nvertices(); ++vertex){
      if(!visited[vertex]){
        visitfn(vertex);
        DFS(vertex);
      }
    }
  }else{
    visitfn(start);
    DFS(start);
  }
}

/**
 * @brief Performs the Topological Sort algorithm on the graph. Returns a `std::vector` containing the index of each vertex in the order determined by the algorithm.
 * 
 * @return return only the vertices whose order was determined before the cycle.
 */
std::vector<size_t> Graph::toposort() const {
  std::vector<size_t> topo_order;
  std::queue<size_t> q;

  // Initialize in-degrees for each vertex
  std::vector<size_t> in_d(nvertices(), 0);
  for (const auto& edge : edges) {
    in_d.at(v_lut.at(vertices[edge.destination]))++;
  }

  // Initialize the queue with vertices having in_d of 0
  for (size_t vertex = 0; vertex < nvertices(); ++vertex) {
    if (in_d.at(vertex) == 0) {
      q.push(vertex);
    }
  }

  size_t count = 0;

  // Perform topological sort
  while (!q.empty()) {
    size_t v = q.front();
    q.pop();

    // Increment the count and assign it as the topological number for v
    topo_order.push_back(count++);

    // Update in_ds and enqueue adjacent vertices with in_d 0
    for (const auto& edge : edges) {
      if (v_lut.at(vertices[edge.origin]) == v) { 
        size_t w = v_lut.at(vertices[edge.destination]);
        in_d.at(w)--;
        if (in_d.at(w) == 0) {
          q.push(w);
        }
      }
    }
  }
  return topo_order;
}
    
/**
 * @brief Use Dijkstra's Shortest Path algorithm to find the shortest path to every vertex from the source vertex whose index is passed in as `start`.
 * 
 * @param start the index of the source vertex, from which all of the shortest paths will be found.
 * @return the table used by the algorithm in its final state, as a `std::vector` containing a `dijkstra_row` for every vertex in the graph.
 */
std::vector<dijkstra_row> Graph::dijkstra(size_t start) const {
    // Check for negative edge weights
    for (const auto& edge : edges) {
        if (edge.weight < 0) {
          std::cout << "Error: Dijkstra's algorithm does not support graphs with negative edge weights.\n";
          return {};
        }
    }

    // Initialize the distance vector
    std::vector<dijkstra_row> distance(nvertices());
    for (size_t i = 0; i < nvertices(); ++i) {
        distance[i].vertex = i;
        distance[i].visited = false;
        distance[i].shortest_known = INFINITY;
        distance[i].came_from = -1;
    }

    // Set the distance for the starting vertex
    distance[start].shortest_known = 0;

    // Dijkstra's algorithm
    for (size_t count = 0; count < nvertices() - 1; ++count) {
      size_t u = 0;
      double min_distance = INFINITY;

      // Choose the vertex with the minimum distance
      for (size_t v = 0; v < nvertices(); ++v) {
        if (!distance[v].visited && distance[v].shortest_known <= min_distance) {
          min_distance = distance[v].shortest_known;
          // Mark the selected vertex as visited
          u = v;
        }
      }

      distance[u].visited = true;

      // Update the distances of the adjacent vertices
      for (const auto& edge : edges) {
        if (edge.origin == u && !distance[edge.destination].visited) {
          double new_distance = distance[u].shortest_known + edge.weight;
          if (new_distance < distance[edge.destination].shortest_known) {
            distance[edge.destination].shortest_known = new_distance;
            distance[edge.destination].came_from = u;
          }
        }
      }
    }

  return distance;
}


#endif /* NIU_CSCI340_GRAPH_H */

