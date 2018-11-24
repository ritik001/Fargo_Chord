#include "chord.h"
#include "node.h"
#include "helper.h"
#include "create.h"

/* listen to any contacting node */
void listenTo(){
    struct sockaddr_in client;
    socklen_t l = sizeof(client);

    struct sockaddr_in myaddr;
    socklen_t mylen = sizeof(myaddr);

    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = inet_addr(node.ip.c_str());
    myaddr.sin_port = htons(node.port);

    int my_sock_id = socket(AF_INET,SOCK_DGRAM,0);

    /* wait for any client to connect and create a new thread as soon as one connects */
//    while(1){
//        char charNodeId[40];
//        int len = recvfrom(my_sock_id, charNodeId, 1024, 0, (struct sockaddr *) &client, &l);
//        charNodeId[len] = '\0';
//        string nodeIdString = charNodeId;
//
//        /* launch a thread that will perform diff tasks acc to received msg */
//        thread f(doTask,ref(nodeInfo),sock,client,nodeIdString);
//        f.detach();
//    }
}

/* create a new ring */
void create_ring(){

    string ip = node.getIp();
    int port = node.getPort();
    Helper helper;
    /* key to be hashed for a node is ip:port */
    string key = ip+":"+(to_string(port));

    ll hash = helper.getHash(key);

    /* setting id, successor , successor list , predecessor ,finger table and status of node */
    node.setIdentifier(hash);

    pair<ll,pair<string,int>> successor=make_pair(hash,make_pair(ip,port));
    node.setSuccessor(successor);
    //nodeInfo.setSuccessorList(ip,port,hash);

    //set predecessor
    pair<ll,pair<string,int>> predecessor = make_pair(-1,make_pair("",-1));
    node.setPredecessor(predecessor);

    //set dummy values in the finger table initially
    node.setFingerTable();

    // node is now in the ring, set TRUE.
    node.isInRing=true;

    /* launch threads,one thread will listen to request from other nodes,one will do stabilization */
    thread second(listenTo);
    second.detach();

    //thread fifth(doStabilize);
    //fifth.detach();

}


