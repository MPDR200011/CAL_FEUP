/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <set>
#include <map>

using namespace std;

template<class T>
class Edge;

template<class T>
class Graph;

template<class T>
class Vertex;


/****************** Provided structures  ********************/

template<class T>
class Vertex {
    T info;                // contents
    vector<Edge<T> > adj;  // list of outgoing edges
    bool visited;          // auxiliary field used by dfs and bfs
    int indegree;          // auxiliary field used by topsort
    bool processing;       // auxiliary field used by isDAG

    void addEdge(Vertex<T> *dest, double w);

    bool removeEdgeTo(Vertex<T> *d);

public:
    Vertex(T in);

    friend class Graph<T>;
};

template<class T>
class Edge {
    Vertex<T> *dest;      // destination vertex
    double weight;         // edge weight
public:
    Edge(Vertex<T> *d, double w);

    friend class Graph<T>;

    friend class Vertex<T>;
};

template<class T>
class Graph {
    vector<Vertex<T> *> vertexSet;    // vertex set

    void dfsVisit(Vertex<T> *v, vector<T> &res) const;

    Vertex<T> *findVertex(const T &in) const;

    bool dfsIsDAG(Vertex<T> *v) const;

public:
    int getNumVertex() const;

    bool addVertex(const T &in);

    bool removeVertex(const T &in);

    bool addEdge(const T &sourc, const T &dest, double w);

    bool removeEdge(const T &sourc, const T &dest);

    vector<T> dfs() const;

    vector<T> bfs(const T &source) const;

    vector<T> topsort() const;

    int maxNewChildren(const T &source, T &inf) const;

    bool isDAG() const;
};

/****************** Provided constructors and functions ********************/

template<class T>
Vertex<T>::Vertex(T in): info(in) {this->indegree = 0;}

template<class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


template<class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template<class T>
Vertex<T> *Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

/****************** 1a) addVertex ********************/

/*
 *  Adds a vertex with a given content/info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template<class T>
bool Graph<T>::addVertex(const T &in) {
    if (findVertex(in) != nullptr) {
        return false;
    }
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

/****************** 1b) addEdge ********************/

/*
 * Adds an edge to a graph (this), given the contents of the source (sourc) and
 * destination (dest) vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template<class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    Vertex<T> *source = findVertex(sourc);
    Vertex<T> *d = findVertex(dest);
    if (source == nullptr || d == nullptr) {
        return false;
    }
    source->addEdge(d, w);
    return true;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template<class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    d->indegree++;
    adj.push_back(Edge<T>(d, w));
}


/****************** 1c) removeEdge ********************/

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template<class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    Vertex<T> *v;
    Vertex<T> *d;
    if ((v = findVertex(sourc)) == nullptr ||
        (d = findVertex(dest)) == nullptr) {
        return false;
    }

    return v->removeEdgeTo(d);
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template<class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
    auto it = adj.begin();
    for (; it < adj.end(); it++) {
        if ((*it).dest == d) {
            break;
        }
    }

    if (it == adj.end()) {
        return false;
    } else {
        d->indegree--;
        adj.erase(it);
        return true;
    }
}


/****************** 1d) removeVertex ********************/

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template<class T>
bool Graph<T>::removeVertex(const T &in) {
    auto it = vertexSet.begin();
    for (; it < vertexSet.end(); it++) {
        if ((*it)->info == in) {
            break;
        }
    }

    if (it == vertexSet.end()) {
        return false;
    }

    for (Vertex<T> *v: vertexSet) {
        v->removeEdgeTo(*it);
    }

    delete (*it);
    vertexSet.erase(it);

    return true;
}


/****************** 2a) dfs ********************/

/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template<class T>
vector<T> Graph<T>::dfs() const {
    for (Vertex<T> *v: vertexSet) {
        v->visited = false;
    }
    vector<T> res;
    if (vertexSet.size() == 0) {
        return res;
    }
    dfsVisit(vertexSet[0], res);
    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template<class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> &res) const {
    if (v->visited) {
        return;
    }
    res.push_back(v->info);
    v->visited = true;
    for (const Edge<T> &e: v->adj) {
        dfsVisit(e.dest, res);
    }
}

/****************** 2b) bfs ********************/

/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template<class T>
vector<T> Graph<T>::bfs(const T &source) const {
    for (Vertex<T> *v: vertexSet) {
        v->visited = false;
    }
    vector<T> res;
    if (vertexSet.size() == 0) {
        return res;
    }
    queue<Vertex<T> *> searchQueue;
    searchQueue.push(vertexSet[0]);
    while (searchQueue.size()) {
        Vertex<T> *current = searchQueue.front();
        searchQueue.pop();
        if (current->visited) {
            continue;
        }
        res.push_back(current->info);
        current->visited = true;
        for (const Edge<T> &e : current->adj) {
            searchQueue.push(e.dest);
        }
    }
    return res;
}

/****************** 2c) toposort ********************/

/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */

template<class T>
vector<T> Graph<T>::topsort() const {
    vector<T> res;

    //Fail if the graph is not a DAG
    if (!isDAG()) {
        return res;
    }

    //This map is to temporarily store the indegrees of every vertex
    //so they can be restored after the algorithm is done running
    map<Vertex<T> *, int> degreeMap;
    for (Vertex<T> *v: vertexSet) {
        degreeMap.insert(pair<Vertex<T> *, int>(v, v->indegree));
    }

    //Copy of the vertexSet
    vector<Vertex<T>*> vertexes(vertexSet.begin(), vertexSet.end());
    while (vertexes.size()) {
        //Look for vertex with indegree == 0
        typename vector<Vertex<T>*>::iterator it = vertexes.begin();
        for (; it <vertexes.end(); it++) {
            if ((*it)->indegree == 0) {
                break;
            }
        }

        //Check if it was found
        if (it == vertexes.end()){
            cout << "no vertexes with indregree == 0" << endl;
            //Restore indegrees
            for (const pair<Vertex<T> *, int> &pair: degreeMap) {
                pair.first->indegree = pair.second;
            }
            return vector<T>();
        }

        //Add it to the result vector
        res.push_back((*it)->info);

        //Reduce the indegree of every destination of its outgoing edges
        for (const Edge<T> &e: (*it)->adj) {
            e.dest->indegree-=1;
        }

        //Remove vertex from set
        vertexes.erase(it);
    }

    //Restore indegrees
    for (const pair<Vertex<T> *, int> &pair: degreeMap) {
        pair.first->indegree = pair.second;
    }

    return res;
}

/****************** 3a) maxNewChildren (HOME WORK)  ********************/

/*
 * Performs a breadth-first search in a graph (this), starting
 * from the vertex with the given source contents (source).
 * During the search, determines the vertex that has a maximum number
 * of new children (adjacent not previously visited), and returns the
 * contents of that vertex (inf) and the number of new children (return value).
 */

template<class T>
int Graph<T>::maxNewChildren(const T &source, T &inf) const {
    if (vertexSet.size() == 0) {
        return 0;
    }

    Vertex<T> * s = findVertex(source);
    if (s == nullptr) {
        return 0;
    }

    for (Vertex<T> *v: vertexSet) {
        v->visited = false;
    }

    queue<Vertex<T> *> searchQueue;
    searchQueue.push(s);
    int maxChildren = 0;
    Vertex<T>* biggestV;
    while (searchQueue.size()) {
        Vertex<T> *current = searchQueue.front();
        searchQueue.pop();
        if (current->visited) {
            continue;
        }
        current->visited = true;
        int i =0;
        for (const Edge<T> &e : current->adj) {
            if (!e.dest->visited) {
                i++;
            }
            searchQueue.push(e.dest);
        }
        if (i > maxChildren) {
            maxChildren = i;
            biggestV = current;
        }
    }
    inf = biggestV->info;
    return maxChildren;
}

/****************** 3b) isDAG   (HOME WORK)  ********************/

/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

template<class T>
bool Graph<T>::isDAG() const {
    for (Vertex<T> *v:vertexSet) {
        v->processing = false;
        v->visited = false;
    }
    for (Vertex<T> *v:vertexSet) {
        if (!v->visited) {
            if (!dfsIsDAG(v)) {
                return false;
            }
        }
    }
    return true;
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
template<class T>
bool Graph<T>::dfsIsDAG(Vertex<T> *v) const {
    if (v->processing) {
        return false;
    }
    v->visited = true;
    v->processing = true;
    for (const Edge<T> &e: v->adj) {
        if (!dfsIsDAG(e.dest)) {
            return false;
        }
    }
    v->processing = false;
    return true;
}

#endif /* GRAPH_H_ */
