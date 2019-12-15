#include "DirectedGraph.h"
#include <iostream>
#include <algorithm>
DirectedGraph::DirectedGraph(Edge *edges, int size) {
    for (int i = 0; i < size; i++) {
        int src = edges[i].src, dest = edges[i].dest;
        if (nodes.count(src) == 0) {
            nodes[src] = new SingleLinkedList<int>();
        }
        nodes[src]->add(dest);
        if (nodes.count(dest) == 0) {
            nodes[dest] = new SingleLinkedList<int>();
        }
    }
}

DirectedGraph::~DirectedGraph() {
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        delete (*it).second;
    }
}

void DirectedGraph::printGraph() {
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        printf("node(%d) has edges: ", (*it).first);
        for (auto itl = (*it).second->begin(); itl != (*it).second->end(); itl++) {
            printf("%d ", (*itl));
        }
        printf("\n");
    }
}


bool DirectedGraph::contains(set<int> & search_set, int val) {
    set<int>::iterator set_iterator;
    for (set_iterator = search_set.begin(); set_iterator != search_set.end(); ++set_iterator) {
        if (*set_iterator == val) {
            return true;
        }
    }
    return false;
}
vector<int> *DirectedGraph::topologySort() {
	// homework
	// the return here is a placeholder. replace with your own code

	LinkedStack<int> ordered;
	set<int> temp_set;

	map<int, SingleLinkedList<int> *>::iterator it;
	for( it = nodes.begin(); it != nodes.end(); ++it) {
	    if(!contains(temp_set, it->first)){
	        topologySort(it->first, ordered, temp_set);
	    }
	}

	while(!ordered.isEmpty()){
	    this->orderedNodes.push_back(ordered.peek());
	    //std::cout << ordered.peek() << " ,";
	    ordered.pop();
	}
	//std::cout << endl;

	bool setReverse = false;
	for(int i = 0; i < this->nodes.size(); i++){
	    vector<int> temp = this->nodes[i]->toVector();
	    for(int j = 0; j < temp.size(); j++){
	        if(this->orderedNodes[0] == temp[j]){
	            setReverse = true;
	        }
	    }
	}
    if(setReverse){
        std::reverse(this->orderedNodes.begin(), this->orderedNodes.end());
    }

	return new vector<int>;
}



void DirectedGraph::topologySort(int val, LinkedStack<int> & ordered, set<int> & temp_set){
    temp_set.insert(val);

    map<int, SingleLinkedList<int> *>::iterator stick;
    for (stick = nodes.begin(); stick != nodes.end(); ++stick){
        if (!contains(temp_set, stick->first)) {
            topologySort(stick->first, ordered, temp_set);
        }
    }

    ordered.push(val);

}

