
void connect_to_server(string ip,int port)
{
struct sockaddr_in serverToConnectTo;
socklen_t l = sizeof(serverToConnectTo);
util.setServerDetails(serverToConnectTo,ip,port);
int sock = socket(AF_INET,SOCK_STREAM,0);

if(sock < 0){
    perror("error");
    exit(-1);
}

int ret = connect(sock, (struct sockaddr *)&serverToConnectTo, sizeof(serverToConnectTo));
if (ret < 0)
{
    printf("Error In Connection.\n");
    exit(1);
}
else
    printf("Connected\n");
}