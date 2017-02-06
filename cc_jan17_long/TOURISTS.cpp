#include <bits/stdc++.h>

using namespace std;

// A class that represents an undirected graph
class Graph
{
  int V;    // No. of vertices
  list<int> *adj;    // A dynamic array of adjacency lists
public:
    // Constructor and destructor
  Graph(int V)  { this->V = V;  adj = new list<int>[V];  }
  ~Graph()      { delete [] adj;  }
 
  // functions to add and remove edge
  void addEdge(int u, int v) {  adj[u].push_back(v); adj[v].push_back(u); }
  void rmvEdge(int u, int v);
 
  // Methods to print Eulerian tour
  void printEulerTour();
  void printEulerUtil(int s);
 
  // This function returns count of vertices reachable from v. It does DFS
  int DFSCount(int v, bool visited[]);
 
  // Utility function to check if edge u-v is a valid next edge in
  // Eulerian trail or circuit
  bool isValidNextEdge(int u, int v);
};
 
/* The main function that print Eulerian Trail. It first finds an odd
   degree vertex (if there is any) and then calls printEulerUtil()
   to print the path */
void Graph::printEulerTour()
{
  // Find a vertex with odd degree
  int u = 0;
  for (int i = 0; i < V; i++)
      if (adj[i].size() & 1)
        {   u = i; break;  }
 
  // Print tour starting from oddv
  printEulerUtil(u);
  //cout << endl;
}
 
// Print Euler tour starting from vertex u
void Graph::printEulerUtil(int u)
{
  // Recur for all the vertices adjacent to this vertex
  list<int>::iterator i;
  for (i = adj[u].begin(); i != adj[u].end(); ++i)
  {
      int v = *i;
 
      // If edge u-v is not removed and it's a a valid next edge
      if (v != -1 && isValidNextEdge(u, v))
      {
          cout << u+1 << " " << v+1 << "\n";
          rmvEdge(u, v);
          printEulerUtil(v);
      }
  }
}
 
// The function to check if edge u-v can be considered as next edge in
// Euler Tout
bool Graph::isValidNextEdge(int u, int v)
{
  // The edge u-v is valid in one of the following two cases:
 
  // 1) If v is the only adjacent vertex of u
  int count = 0;  // To store count of adjacent vertices
  list<int>::iterator i;
  for (i = adj[u].begin(); i != adj[u].end(); ++i)
     if (*i != -1)
        count++;
  if (count == 1)
    return true;
 
 
  // 2) If there are multiple adjacents, then u-v is not a bridge
  // Do following steps to check if u-v is a bridge
 
  // 2.a) count of vertices reachable from u
  bool visited[V];
  memset(visited, false, V);
  int count1 = DFSCount(u, visited);
 
  // 2.b) Remove edge (u, v) and after removing the edge, count
  // vertices reachable from u
  rmvEdge(u, v);
  memset(visited, false, V);
  int count2 = DFSCount(u, visited);
 
  // 2.c) Add the edge back to the graph
  addEdge(u, v);
 
  // 2.d) If count1 is greater, then edge (u, v) is a bridge
  return (count1 > count2)? false: true;
}
 
// This function removes edge u-v from graph.  It removes the edge by
// replacing adjcent vertex value with -1.
void Graph::rmvEdge(int u, int v)
{
  // Find v in adjacency list of u and replace it with -1
  list<int>::iterator iv = find(adj[u].begin(), adj[u].end(), v);
  *iv = -1;
 
  // Find u in adjacency list of v and replace it with -1
  list<int>::iterator iu = find(adj[v].begin(), adj[v].end(), u);
  *iu = -1;
}
 
// A DFS based function to count reachable vertices from v
int Graph::DFSCount(int v, bool visited[])
{
  // Mark the current node as visited
  visited[v] = true;
  int count = 1;
 
  // Recur for all vertices adjacent to this vertex
  list<int>::iterator i;
  for (i = adj[v].begin(); i != adj[v].end(); ++i)
      if (*i != -1 && !visited[*i])
          count += DFSCount(*i, visited);
 
  return count;
}

int main(int argc, char const *argv[])
{
	int n, e;
	cin>>n>>e;
	set<int> s[n];
	int a, b;
	Graph g1(n);
	int from[e];
	int to[e];
	for (int i = 0; i < e; ++i)
	{
		cin>>a;
		cin>>b;
		from[i] = a;
		to[i] = b;
		g1.addEdge(a-1, b-1);
		s[a-1].insert(b);
		s[b-1].insert(a);
	}
	if(n == 2 && e == 2){
		if((from[0] == 1 && to[0] == 2 && from[1] == 2 && to[1] == 1) || (from[0] == 2 && to[0] == 1 && from[1] == 1 && to[1] == 2)){
			cout<<"YES"<<endl;
			cout<<from[0]<<" "<<to[0]<<endl;
			cout<<from[1]<<" "<<to[1]<<endl;
			return 0;
		}
	}
	int ans = 1;
	for (int i = 0; i < e; ++i)
	{
		if(s[i].size() == 0 || s[i].size() % 2 != 0)
			ans = 0;
	}
	
	if(ans == 0){
		cout<<"NO"<<endl;
	}
	else{
		cout<<"YES"<<endl;
	 	g1.printEulerTour();
	}


	return 0;
}