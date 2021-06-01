#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <deque>

#define DEBUG

class Node {
    int _id;

public:
    Node(int id) {
        _id = id;
    }

    int getId() {
        return _id;
    }

    std::vector<std::pair<Node*,int>> adjacents;
};

typedef std::deque<Node*> Graph;

int shortestPath(Graph* graph, Node* start, Node* end) {
    int shortest = 0;
    std::set<Node*> visited;
    std::map<Node*,int> distance;

    for (auto v : *graph) {
        distance.insert(std::make_pair(v, INT32_MAX));

#ifdef DEBUG
        std::cout << "Initializing distance for node " << v->getId() << std::endl;
#endif
    }

    distance[start] = 0;
    while (!graph->empty()) {
        auto curr = graph->front();
        graph->pop_front();

        visited.insert(curr);

        std::cout << "Visiting node " << curr->getId() << std::endl;

        for (auto n : curr->adjacents) {
            if (visited.find(n.first) == visited.end()) {
#ifdef DEBUG
                std::cout << "Visiting adjacent " << n.first->getId() << std::endl;
#endif

                if (distance[n.first] == INT32_MAX || distance[n.first] > (n.second + distance[curr])) {
#ifdef DEBUG
                    std::cout << "Updating shortest distance for node " << n.first->getId()
                        << " distance " << n.second + distance[curr] << std::endl;
#endif

                    distance[n.first] = distance[curr] + n.second;
                }
            }
        }
    }

    return distance[end];
}

int main(int argc, char* argv[]) {

    auto node1 = new Node(1);
    auto node2 = new Node(2);
    auto node3 = new Node(3);
    auto node4 = new Node(4);
    auto node5 = new Node(5);

    node1->adjacents.push_back(std::make_pair(node1, 0));
    node1->adjacents.push_back(std::make_pair(node2, 5));
    node1->adjacents.push_back(std::make_pair(node3, 10));
    node1->adjacents.push_back(std::make_pair(node4, 200));
    node2->adjacents.push_back(std::make_pair(node4, 150));
    node2->adjacents.push_back(std::make_pair(node5, 200));
    node3->adjacents.push_back(std::make_pair(node4, 100));
    node4->adjacents.push_back(std::make_pair(node5, 94));

    auto graph = new Graph();
    graph->push_back(node1);
    graph->push_back(node2);
    graph->push_back(node3);
    graph->push_back(node4);
    graph->push_back(node5);

    auto s = shortestPath(graph, node1, node5);

    std::cout << "Shortest path is " << s << std::endl;

    delete node1;
    delete node2;
    delete node3;
    delete node4;

    return 0;
}