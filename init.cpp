#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <thread>

#include "init.h"
#include "connection.h"
#include "chordfunctions.h"
#include "util.h"
#include "nodedetails.h"
#include "chord.h"

using namespace std;

void initialize(){
	
	NodeDetails nodeDetails = NodeDetails();

	/* open a socket to listen to other nodes */
	nodeDetails.sp.specifyPortServer();

	cout<<"Started at port number: "<<nodeDetails.sp.getPortNumber()<<endl;

	cout<<"Type help to know more\n";

	string command;

	while(1){
		cout<<"> ";
		getline(cin,command);

		/* find space in command and seperate arguments*/
		Utility util = Utility();
		vector<string> arguments = util.splitCommand(command);

		string arg = arguments[0];
		if(arguments.size() == 1){

			/* creates */
			if(arg == "create"){
				if(nodeDetails.getStatus() == true){
					cout<<"Could not initialize new ring. This node is already on the ring.\n";
				}
				else{
					thread first(create,ref(nodeDetails));
					first.detach();
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
				return;
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

		else if(arguments.size() == 2){

			/* */
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

		else if(arguments.size() == 3){

			/* */
			if(arg == "join"){
				if(nodeDetails.getStatus() == true){
					cout<<"This node is already on the ring.\n";
				}
				else
					join(nodeDetails,arguments[1],arguments[2]);
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

		else{
			cout<<"Invalid Command\n";
		}
	}
	
}