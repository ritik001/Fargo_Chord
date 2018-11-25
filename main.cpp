#include <iostream>
#include <vector>
#include "init.h"
#include "connection.h"
#include "chordfunctions.h"
#include "util.h"
#include "nodedetails.h"
#include "chord.h"

using namespace std;
void processOneLengthCommands(NodeDetails &nodeDetails,string arg,vector<string> &arguments);
void processTwoLengthCommands(NodeDetails &nodeDetails,string arg,vector<string> &arguments);
void processThreeLengthCommands(NodeDetails &nodeDetails,string arg,vector<string> &arguments);

int main(){

	NodeDetails nodeDetails;
	
	/* */
	initialize(nodeDetails);  //init.cpp start listening thread
	
	string command;

	while(1){
		cout<<"> ";
		getline(cin,command);

		/* find space in command and seperate arguments*/
		Utility util = Utility();
		vector<string> arguments = util.split_string(command);

		string arg = arguments[0];
		if(arguments.size() == 1){

			/* creates */
			processOneLengthCommands(nodeDetails,arg,arguments);
		}

		else if(arguments.size() == 2){

			/* */
			processTwoLengthCommands(nodeDetails,arg,arguments);
			cout <<" executed command\n";
		}

		else if(arguments.size() == 3){

			/* */
			processThreeLengthCommands(nodeDetails,arg,arguments);
		}

		else{
			cout<<"Invalid Command\n";
		}
	}

	return 0;
}

void processOneLengthCommands(NodeDetails &nodeDetails,string arg,vector<string> &arguments){
		if(arg == "create"){
				if(nodeDetails.getStatus() == true){
					cout<<"Could not initialize new ring. This node is already on the ring.\n";
				}
				else{
					thread first(create,ref(nodeDetails));
					first.detach();
/* 					create(nodeDetails); */
				}
			}

			/* prints */
			else if(arg == "printstate"){
				if(nodeDetails.getStatus() == false){
					cout<<"This node is not in the ring.\n";
				}
				else
					printState(nodeDetails);
			}

			/* leaves */
			else if(arg == "leave"){
				leave(nodeDetails);
				nodeDetails.sp.closeSocket();
				exit(0);
			}

			/* print current port number */
			else if(arg == "port"){
				cout<<nodeDetails.sp.getPortNumber()<<endl;
			}

			/* print keys present in this node */
			else if(arg == "print"){
				if(nodeDetails.getStatus() == false){
					cout<<"This node is not in the ring.\n";
				}
				else
					nodeDetails.printKeys();
			}

			else if(arg == "help"){
				showHelp();
			}

			else{
				cout<<"Invalid Command\n";
			}
	}

	void processTwoLengthCommands(NodeDetails &nodeDetails,string arg,vector<string> &arguments){
		if(arg == "port"){
				if(nodeDetails.getStatus() == true){
					cout<<"You can't change port number.\n";
				}
				else{
					int newPortNo = atoi(arguments[1].c_str());
					nodeDetails.sp.changePortNumber(newPortNo);
				}
			}

			/* */
			else if(arg == "get"){
				if(nodeDetails.getStatus() == false){
					cout<<"This node is not in the ring.\n";
				}
				else
					get(arguments[1],nodeDetails);
			}

			else{
				cout<<"Invalid Command\n";
			}
	}

	void processThreeLengthCommands(NodeDetails &nodeDetails,string arg,vector<string> &arguments){
		if(arg == "join"){
				if(nodeDetails.getStatus() == true){
					cout<<"This node is already on the ring.\n";
				}
				else{
					join(ref(nodeDetails),arguments[1],arguments[2]);
/* 					thread one(join,ref(nodeDetails),arguments[1],arguments[2]);
					one.detach(); */
				}

			}

			/* puts the entered key and it's value to the necessary node*/
			else if(arg == "put"){
				if(nodeDetails.getStatus() == false){
					cout<<"This node is not in the ring.\n";
				}
				else
					put(arguments[1],arguments[2],nodeDetails);
			}

			else{
				cout<<"Invalid Command\n";
			}
	}
