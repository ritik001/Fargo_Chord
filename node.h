#ifndef NODE_H
#define NODE_H

#include "chord.h"
#include "finger.h"

using namespace std;
class Node {

public:
	ll identifier;
	pair<ll, string> successor; // <identifier, address(ip:port)>
	pair<ll, string> predecessor; // <identifier, address(ip:port)>
	vector<Finger> finger_table; // finger table for this node



	Node(ll identifier, pair<ll,string> successor, pair<ll,string> predecessor);
	Node();

	vector<Finger>& getFingerTable();

	void setFingerTable(vector<Finger>& fingerTable);

	ll getIdentifier();

	void setIdentifier(ll identifier);

	pair<ll, string>& getPredecessor();

	void setPredecessor(pair<ll, string>& predecessor);

	pair<ll, string>& getSuccessor();

	void setSuccessor(pair<ll, string>& successor);

	void print_fingers();

};

extern Node node;
#endif