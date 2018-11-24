#include "helper.h"
#include "node.h"
using namespace std;

void Helper::setServerDetails(struct sockaddr_in &server, string ip, int port){ // @suppress("Member declaration not found")
	 server.sin_family = AF_INET;
	 server.sin_addr.s_addr = inet_addr(ip.c_str());
	 server.sin_port = htons(port);

}
ll Helper::getHash(string key){
    unsigned char obuf[41];
    char finalHash[41];
    string keyHash = "";
    unsigned char unsigned_key[key.length()+1];
    int i;
    for(i=0;i<key.length();i++){
        unsigned_key[i] = key[i];
    }
    unsigned_key[i] = '\0';
    SHA1(unsigned_key,sizeof(unsigned_key),obuf);
    for (i = 0; i < SHA_DIGEST_LENGTH/4; i++) {
        sprintf(finalHash,"%d",obuf[i]);
        keyHash += finalHash;
    }

    ll modulo = pow(2,M);
    cout<<"Key hash: "<<keyHash<<endl;
    ll hash = fmod(stoll(keyHash),modulo);
    cout<<"sha hash generated is "<<hash<<"\n";
    return hash;
}

void Helper::assignIpAndPortToNode(){

	/* generating a port number between 1024 and 65535 */
	srand(time(0));
	int port_number = rand() % 65536;
	if(port_number < 1024)
		port_number += 1024;
	sockaddr_in sockaddr;
	socklen_t len = sizeof(struct sockaddr);

	int sock = socket(AF_INET,SOCK_DGRAM,0);
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(port_number);
	sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	node.setIp("127.0.0.1");
	node.setPort(port_number);

	if( bind(sock,(struct sockaddr *)&sockaddr,len) < 0){
		perror("error");
		exit(-1);
	}

}


vector<string> Helper::splitCommand(string command){
	vector<string> arguments;
	int pos = 0;
	do {
		pos = command.find(' ');
		string arg = command.substr(0, pos);
		arguments.push_back(arg);
		command = command.substr(pos + 1);
	} while (pos != -1);
	return arguments;
}

void Helper::serveRequest(int sock_id, struct sockaddr_in client, string nodeIdString){

	/* predecessor of this node has left the ring and has sent all it's keys to this node(it's successor) */
	    if(nodeIdString.find("storeKeys") != -1){
	        //help.storeAllKeys(nodeInfo,nodeIdString);
	    }

	    /* check if the sent msg is in form of key:val, if yes then store it in current node (for put ) */
	    else if(isKeyValue(nodeIdString)){
	        pair< lli , string > keyAndVal = help.getKeyAndVal(nodeIdString);
	        nodeInfo.storeKey(keyAndVal.first , keyAndVal.second);
	    }

	    else if(nodeIdString.find("alive") != -1){
	        help.sendAcknowledgement(newSock,client);
	    }

	    /* contacting node wants successor list of this node */
	    else if(nodeIdString.find("sendSuccList") != -1){
	        help.sendSuccessorList(nodeInfo,newSock,client);
	    }

	    /* contacting node has just joined the ring and is asking for keys that belongs to it now */
	    else if(nodeIdString.find("getKeys") != -1){
	        help.sendNeccessaryKeys(nodeInfo,newSock,client,nodeIdString);
	    }

	    /* contacting node has run get command so send value of key it requires */
	    else if(nodeIdString.find("k") != -1){
	        help.sendValToNode(nodeInfo,newSock,client,nodeIdString);
	    }

	    /* contacting node wants the predecessor of this node */
	    else if(nodeIdString.find("p") != -1){
	        help.sendPredecessor(nodeInfo,newSock,client);

	        /* p1 in msg means that notify the current node about this contacting node */
	        if(nodeIdString.find("p1") != -1){
	            callNotify(nodeInfo,nodeIdString);
	        }
	    }

	    /* contacting node wants successor Id of this node for help in finger table */
	    else if(nodeIdString.find("finger") != -1){
	        help.sendSuccessorId(nodeInfo,newSock,client);
	    }

	    /* contacting node wants current node to find successor for it */
	    else{
	        help.sendSuccessor(nodeInfo,nodeIdString,newSock,client);
	    }
}

pair<string,int> Helper::getIpAndPort(string address){
	int ind=address.find(":");
    string ip=address.substr(0,ind);
    int port=stoi(address.substr(ind+1));
    pair<string,int> ip_port;
    ip_port.first=ip;
    ip_port.second=port;
    return ip_port;
}

//int getConnectionSocket(string ip, int port){
////	struct sockaddr_in server;
////	socklen_t addr_len = sizeof(server);
////
////	server.sin_family = AF_INET;
////	server.sin_addr.s_addr = inet_addr(ip.c_str());
////	server.sin_port = htons(port);
////
////	int sock_id = socket(AF_INET,SOCK_DGRAM,0);
////	if(sock_id < 0){
////	   perror("error");
////	   exit(-1);
////	}
////
////	sendto(__fd, __buf, __n, __flags, __addr, __addr_len)
////
////	return sock_id;
//}
