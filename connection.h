#ifndef connection_h
#define connection_h

#include <iostream>
#include <netinet/in.h>
#include "chord.h"
using namespace std;

class SocketAndPort{
	private:
		int portNoServer;
		int sock;
		struct sockaddr_in current;

	public:
		void assignAndBindToIpAndPort();
		void changePortNumber(int portNo);
		void closeSocket();
		bool isPortInUse(int portNo);
		string getIpAddress();
		int getPortNumber();
		int getSocketFd();
};

#endif