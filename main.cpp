#include<iostream>
#include "finger.h"
#include "chord.h"
#include "node.h"
using namespace std;

int main(){

	Node *nd = new Node(7,make_pair(0,""),make_pair(0,""));

	nd->print_fingers();
}
