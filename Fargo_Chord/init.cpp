#include "chord.h"
#include "node.h"
#include "helper.h"
#include "create.h"
void initialize() {

	/* open a socket to listen to other nodes */
	Helper helper;
	helper.assignIpAndPortToNode(); // this node binds to a randomly generated port and ip 127.0.0.1

	cout << "Listening at port: " << node.getPort() << endl;

	string command;

	while(1){
			cout<<"> ";
			getline(cin,command);

			/* find space in command and seperate arguments*/

			vector<string> arguments = helper.splitCommand(command);

			string arg = arguments[0];
			if(arguments.size() == 1){

				/* creates */
				if(arg == "create"){
					if(node.checkInRing() == true){
						cout<<"Sorry but this node is already on the ring\n";
					}
					else{
						thread first(create_ring);
						first.detach();
					}
				}

				/* prints */
				else if(arg == "printstate"){
//					if(nodeInfo.getStatus() == false){
//						cout<<"Sorry this node is not in the ring\n";
//					}
//					else
//						printState(nodeInfo);
				}

				/* leaves */
				else if(arg == "leave"){
//					leave(nodeInfo);
//					nodeInfo.sp.closeSocket();
//					return;
				}

				/* print current port number */
				else if(arg == "port"){
					//cout<<nodeInfo.sp.getPortNumber()<<endl;
				}

				/* print keys present in this node */
				else if(arg == "print"){
//					if(nodeInfo.getStatus() == false){
//						cout<<"Sorry this node is not in the ring\n";
//					}
//					else
//						nodeInfo.printKeys();
				}

				else if(arg == "help"){
					//showHelp();
				}

				else{
					cout<<"Invalid Command\n";
				}
			}

			else if(arguments.size() == 2){

				/* */
				if(arg == "port"){
//					if(nodeInfo.getStatus() == true){
//						cout<<"Sorry you can't change port number now\n";
//					}
//					else{
//						int newPortNo = atoi(arguments[1].c_str());
//						nodeInfo.sp.changePortNumber(newPortNo);
//					}
				}

				/* */
				else if(arg == "get"){
//					if(nodeInfo.getStatus() == false){
//						cout<<"Sorry this node is not in the ring\n";
//					}
//					else
//						get(arguments[1],nodeInfo);
				}

				else{
					cout<<"Invalid Command\n";
				}
			}

			else if(arguments.size() == 3){

				/* */
				if(arg == "join"){
//					if(nodeInfo.getStatus() == true){
//						cout<<"Sorry but this node is already on the ring\n";
//					}
//					else
//						join(nodeInfo,arguments[1],arguments[2]);
				}

				/* puts the entered key and it's value to the necessary node*/
				else if(arg == "put"){
//					if(nodeInfo.getStatus() == false){
//						cout<<"Sorry this node is not in the ring\n";
//					}
//					else
//						put(arguments[1],arguments[2],nodeInfo);
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
