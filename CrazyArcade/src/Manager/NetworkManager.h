#pragma once
#include "Etc/stdafx.h"
#include "Network/MemoryStream.h"

//data size =  6 BYTE
struct blockData{
	char posX, posY;
	//Block Position ����
	char type;			//0, softbloc, 1. hardblock, 2. tree, 3, none 4, bush	
	char tileIndex;		//for tile image render
	char blockIndex;	//for block image render
	char innerItem;		//0, range 1.speed 2, bomb drop limit up 3,
};

//data size =  15 * 13 * 6 + 8 = 1178 BYTE
struct InitiationData {
	vector<blockData> block; // 15 * 13���� ���� �����͸� ���´�.

	//1�� 1���� �����Ұű� ������ 2���� ���´�.
	char clientID[2];
	char clientPosX[2];
	char clientPosY[2];
	char clientCharacter[2];		// 0 bazzi, 1 dao

	void Write(OutputMemoryStream& outStream)
	{
		outStream.Write(block);
		outStream.Write(clientID);
		outStream.Write(clientPosY);
		outStream.Write(clientCharacter);
	}

	void Read(InputMemoryStream& inStream)
	{
		inStream.Read(block);
		inStream.Read(clientID);
		inStream.Read(clientPosY);
		inStream.Read(clientCharacter);
	}
};

//data size = 2 BYTE
struct MoveData {
	
	char clientID;
	char playerMoveDir;			//0, up 1, down 2, right 3, left;

	void Write(OutputMemoryStream& outStream)
	{
		outStream.Write(clientID);
		outStream.Write(playerMoveDir);
	}
	void Read(InputMemoryStream& inStream)
	{
		inStream.Read(clientID);
		inStream.Read(playerMoveDir);
	}
};

class NetworkManager
{
	//Scene�ܿ��� ������ ip�� �Ѱܹ޾� init�Ѵ�. 
	void init(string _ip);
	
	//Ŭ�� ��Ʈ��ũ �޴������� 
	void sendMoveData(char _clientID, char _playerMoveDir);
	MoveData recvMoveData();
	InitiationData recvInitData();

private:
	string server_ip;
	TCPSocketPtr clientSock;

	const int moveDataSize = 2;
	const int initDataSize = 1178;

private:
	DECLARE_SINGLE(NetworkManager)
};
