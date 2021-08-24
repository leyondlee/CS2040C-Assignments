#include "Graph.h"
//uncomment this to include your own "heap.h"
//we will assume that you use the same code in your previous assignment
#include "heap.h"

std::ostream &operator<<(std::ostream &os, nodeWeightPair const &n) {
	return os << " (idx:" << n._node << " w:" << n._weight << ")";
}

Graph::Graph(int n) {
	_al = new List<nodeWeightPair>[n];
	_nv = n;
}

int Graph::shortestDistance(int s, int d) {
	Heap<nodeWeightPair> heap;
	nodeWeightPair firstNode(s, 0);
	heap.insert(firstNode);

	int *weight = new int[_nv];
	int *pathUnion = new int[_nv];
	for (int i = 0; i < _nv; i += 1) {
		weight[i] = -1;
		pathUnion[i] = -1;
	}
	pathUnion[s] = s;

	while (!heap.empty()) {
		nodeWeightPair extractedNode = heap.extractMax(); // Extract lowest distance vertex

		int index = extractedNode.nodeIndex();
		if (index == d) { // Check if vertex is what we are looking for
			// Trace steps
			int i = d;
			List<int> path;
			while (i != s) {
				path.insertHead(i);
				i = pathUnion[i];
			}
			path.insertHead(s);

			cout << "Path:";
			for (path.start(); !path.end(); path.next()) {
				cout << " " << path.current();
			}
			cout << endl;

			// Cleanup
			delete[] weight;
			delete[] pathUnion;

			return -extractedNode.weight();
		}

		for (_al[index].start(); !_al[index].end(); _al[index].next()) { // Loop through neighbors
			nodeWeightPair currentNode = _al[index].current();
			int currentIndex = currentNode.nodeIndex();
			int currentWeight = currentNode.weight() + -extractedNode.weight();
			nodeWeightPair node(currentIndex, -currentWeight); // Negate weight as we are using max heap

			if (weight[currentIndex] == -1) { // Check if is in heap
				// Not in heap; So we add it in and update the weight and path
				heap.insert(node);
				weight[currentIndex] = currentWeight;
				pathUnion[currentIndex] = index;
			} else {
				// In heap
				if (currentWeight < weight[currentIndex]) { // Check if shorter distance (weight) found
					// Replace node in heap
					nodeWeightPair oldNode(currentIndex, weight[currentIndex]);
					heap.deleteItem(oldNode);
					heap.insert(node);

					// Update weight and path
					weight[currentIndex] = currentWeight;
					pathUnion[currentIndex] = index;
				}
			}
		}
	}

	// Cleanup
	delete[] weight;
	delete[] pathUnion;

	// No path
	return -1;
}

void Graph::addEdge(int s, int d, int w) {
	_al[s].insertHead(nodeWeightPair(d, w));
}

void Graph::printGraph() {
	for (int i = 0; i < _nv; i++) {
		cout << "Node " << i << ": ";
		for (_al[i].start(); !_al[i].end(); _al[i].next())
			cout << " (" << _al[i].current().nodeIndex() << "," << _al[i].current().weight() << ")";
		cout << endl;

	}
}

Graph::~Graph() {

	delete[] _al;

}