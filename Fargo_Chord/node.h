#ifndef NODE_H
#define NODE_H

#include "chord.h"
#include "finger.h"

using namespace std;
class Node {

public:
	ll identifier;
	pair<ll, pair<string,int>> successor; // <identifier, address(ip:port)>
	pair<ll, pair<string,int>> predecessor; // <identifier, address(ip:port)>
	vector<Finger> finger_table; // finger table for this node
	bool isInRing;
	string ip;
	int port;

	map<ll,string> keys; // responsible for these keys <key_identifier,address(ip:port)>



	Node(ll identifier, pair<ll, pair<string,int>>  successor, pair<ll, pair<string,int>>  predecessor);
	Node();

	vector<Finger>& getFingerTable();

	void setFingerTable();

	ll getIdentifier();

	void setIdentifier(ll identifier);

	pair<ll, pair<string,int>> getPredecessor();

	void setPredecessor(pair<ll, pair<string,int>> predecessor);

	pair<ll, pair<string,int>> getSuccessor();

	void setSuccessor(pair<ll, pair<string,int>> successor);

	void print_fingers();

	string getIp();
	void setIp(string ip);

	int getPort();
	void setPort(int port);

	bool checkInRing();


};

extern Node node;
#endif
