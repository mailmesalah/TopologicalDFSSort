#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
/*
 * TopologicalSort.cpp
 *
 *  Created on: Apr 17, 2015
 *      Author: Sely
 */

//pi, d ,f arrays
int d[25];
int f[25];
int pi[25];
string topoNames[25];

static int count = 0;
static int nameIndex = 0;

struct Node;

//List for saving children nodes
struct List {
	Node *child;
	List *next;
};

class Node {

public:
	int index;
	int status;
	List *children;
	std::string name;

	static void depthFirstSearch(Node *root) {

		Node *node = root;
		if (node != 0 && node->status == 0) {
			count++;
			d[node->index] = count;
			List *list = node->children;
			while (list != 0) {
				depthFirstSearch(list->child);
				list = list->next;
			}
			//Post Order Output
			topoNames[nameIndex++] = node->name;
			node->status = 1;
			count++;
			f[node->index] = count;
		}
	}

};

int main() {

	std::cout << "\nEnter the number of nodes followed by node names\n";
	int limit;
	std::cin >> limit;
	int noOfNodes = limit;
	//Reading nodes
	int i = 0;
	std::string str;
	std::string names[25];
	//skips the new line
	getline(cin, str, '\n');

	while (i < limit) {
		getline(cin, str, '\n');
		//std::cin >> str;
		names[i] = str;
		//increment the index
		i++;
	}

	//Reading edges
	std::cout << "\nEnter the number of edges followed by edge information\n";
	std::cin >> limit;
	//skips the new line
	getline(cin, str, '\n');

	i = 0;
	int parentIndex[limit];
	int childIndex[limit];
	while (i < limit) {
		getline(cin, str, '\n');
		//std::cin >> str;
		parentIndex[i] = -1;
		childIndex[i] = -1;
		for (int j = 0; j < noOfNodes; j++) {
			unsigned pos = str.find(names[j]);
			//cout<<"\n"<<str<<"-"<<names[j]<<" "<<str.length();
			if (pos != std::string::npos) {
				if (pos == 0) {
					parentIndex[i] = j;
				} else {
					childIndex[i] = j;
				}
			}
		}

		if (parentIndex[i] == -1 || childIndex[i] == -1) {
			cout << "\nError : Possible wrong Inputs";
		}
		//increment the index
		i++;
	}

	//initializing all Nodes
	Node *nodeArray[noOfNodes];
	for (int j = 0; j < noOfNodes; j++) {
		Node *node = new Node;
		node->index = j;
		node->status = 0;
		node->children = 0;
		node->name = names[j];

		nodeArray[j] = node;
	}

	//Connecting Nodes as required
	for (int j = 0; j < limit; j++) {

		List *list = nodeArray[parentIndex[j]]->children;
		if (list != 0) {
			while (list->next != 0)
				list = list->next;

			List *mylist = new List;
			mylist->child = nodeArray[childIndex[j]];
			mylist->next = 0;
			//append to parent
			list->next = mylist;
		} else {
			//first list of the node
			List *mylist = new List;
			mylist->child = nodeArray[childIndex[j]];
			mylist->next = 0;
			//append to parent
			nodeArray[parentIndex[j]]->children = mylist;
		}

	}

	//First Node is taken as root node
	Node *rootNode = nodeArray[0];

	Node::depthFirstSearch(rootNode);

	//Printing outputs
	cout << "\n\nThe array d content:\n";
	for (int j = 0; j < noOfNodes; j++) {
		cout << "\nd[" << names[j] << "]=" << d[j];
	}

	cout << "\n\nThe array f content:\n";
	for (int j = 0; j < noOfNodes; j++) {
		cout << "\nf[" << names[j] << "]=" << f[j];
	}

	cout << "\n\nTopological Order:\n";
	for (int j = noOfNodes-1; j>=0  ; j--) {
		cout << "\n" << topoNames[j] ;
	}

}

