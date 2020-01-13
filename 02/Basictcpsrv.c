#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 9001

int main()
{
    int srvSd, clntSd;
    struct sockaddr_in srvAddr, clntAddr;   
    int clntAddrLen, readLen;
    char rBuff[BUFSIZ];
    char wBuff[BUFSIZ] = "I am 20 years old.";

    srvSd = socket(PF_INET, SOCK_STREAM, 0);
    if(srvSd == -1)
    {
        printf("Socket Creation Error");
        return -1;
    }
    printf("===== server program ===== \n");
    memset(&srvAddr, 0, sizeof(srvAddr));
    srvAddr.sin_family = AF_INET;
    srvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    srvAddr.sin_port = htons(PORT);
    if(bind(srvSd, (struct sockaddr*)&srvAddr, sizeof(srvAddr)) == -1)
    {
        printf("Bind Error");
        return -1;
    }
    if(listen(srvSd, 5) == -1)
    {
        printf("Listen Error");
        return -1;
    }

    clntAddrLen = sizeof(clntAddr); //클라이언트 addrd을 대체 어디서 받아오는것임 ?
 
    //이곳에서 홀딩.
    clntSd = accept(srvSd, (struct sockaddr*)&clntAddr, &clntAddrLen);
    if(clntSd== -1)
    {
        printf("Accept Error");
        return -1;
    }

    readLen = (clntSd, rBuff, sizeof(rBuff));
    if(readLen == -1)
    {
        printf("Read Error");
        return -1;
    }
    rBuff[readLen] = '\0';
    printf("Client: %s \n", rBuff);

    write(clntSd, wBuff, sizeof(wBuff));
    printf("Server:%s \n", wBuff);

    close(clntSd);
    close(srvSd);

    return 0;
}