#include <iostream>
#include <stdio.h>
#include <winsock2.h>
#pragma comment (lib,"ws2_32.lib")
using namespace std;

int main() {
	char a[63] = {0};
	int b;
	string s, command[] = {"stop"};
end:
	cout << "允许连接的IP：";
	cin >> a;
	cout << "端口号：";
	cin >> b;
	cout << "等待连接" << endl;
	//开启网络权限
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//创建socket IPV4:Af_INET IPV6:Af_INET6 TCP
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

	//指定端口号和IP地址
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(b);
	local.sin_addr.S_un.S_addr = inet_addr(a);

	//绑定socket,IP地址和端口号
	bind(sock, (struct sockaddr *)&local, sizeof(struct sockaddr_in));

	//监听socket
	listen(sock, 10);

	SOCKET sockfd = accept(sock, NULL, NULL);

	char buff[1024] = {1};
	send(sockfd, buff, strlen(buff), 0);//发送

	//连接完成
	cout << "连接成功" << endl;

	while (1) {
		memset(buff, 0, 1024);//清空
		printf("请输入：");
		scanf("%s", buff);
		s = (buff);
		if (s.find(command[0]) != string::npos) {
			cout << "连接已断开" << endl;
			send(sockfd, buff, strlen(buff), 0);//发送
			send(sockfd, buff, strlen(buff), 0);//发送
			goto end;
		}
		send(sockfd, buff, strlen(buff), 0);//发送
		printf("发送成功\n");
	}

	return 0;
}
