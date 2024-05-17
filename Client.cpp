#include <iostream>
#include <stdio.h>
#include <winsock2.h>
#pragma comment (lib,"ws2_32.lib")
using namespace std;

int main() {
	char buff[1024] = {0}, a[15] = {0};
	int b;
	string s, command[] = {"stop"};
end1:
	cout << "服务端IP地址：";
	cin >> a;
	cout << "端口号：";
	cin >> b;
	cout << "等待连接" << endl;
end:
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

	connect(sock, (struct sockaddr *)&local, sizeof(struct sockaddr_in));

	recv(sock, buff, 1024, 0);//接收
	for (int i = 0; i < 1024; i++) {
		if (buff[i] == 0) {
			goto end;
		} else {
			break;
		}
	}

	cout << "连接成功" << endl;

	//连接成功
	while (1) {
		memset(buff, 0, 1024);//清空
		recv(sock, buff, 1024, 0);//接收
		s = (buff);
		if (s.find(command[0]) != string::npos) {
			cout << "连接已断开" << endl;
			goto end1;
		}
		printf("%s\n", buff);
	}

	return 0;
}