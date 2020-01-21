#include "Etc/stdafx.h"
#include "Manager/keyManager.h"

keyManager::keyManager()
{
}


keyManager::~keyManager()
{
}

HRESULT keyManager::init()
{
	//Ű�� ���� �������� ���� ���·� �ʱ�ȭ����
	for (int i = 0; i < KEYMAX; i++)
	{
		_keyUp.set(i, false);
		_keyDown.set(i, false);
	}

	playerKey[P1_UP] = VK_NUMPAD5;
	playerKey[P1_DOWN] = VK_NUMPAD2;
	playerKey[P1_LEFT] = VK_NUMPAD1;
	playerKey[P1_RIGHT] = VK_NUMPAD3;
	playerKey[P1_EVENT] = VK_END;
	playerKey[P1_USEITEM] = VK_DELETE;
	

	playerKey[P2_UP] = 'R';
	playerKey[P2_DOWN] = 'F';
	playerKey[P2_LEFT] = 'D';
	playerKey[P2_RIGHT] = 'G';
	playerKey[P2_EVENT] = 'S';
	playerKey[P2_USEITEM] = 'A';

	playerKey[GAME_RECTMODE] = VK_F2;
	playerKey[GAME_DEBUGMODE] = VK_F3;
	playerKey[GAME_LMOUSE] = VK_LBUTTON;
	playerKey[GAME_RMOUSE] = VK_RBUTTON;

	return S_OK;
}

void keyManager::release()
{
}

bool keyManager::isOnceKeyDown(int key)
{
	//GetAsyncKeyState���� Ű�� ���¸� �˾ƿ��� �༮
	//Ű�� ������������ ���������� ȣ��
	//0x8000 �������� �������� ���� ȣ��������� ��������
	if (GetAsyncKeyState(playerKey[key]) & 0x8000)
	{
		if (!_keyDown[playerKey[key]])
		{
			_keyDown.set(playerKey[key], true);
			return true;
		}
	}
	else
	{
		_keyDown.set(playerKey[key], false);
	}
	return false;
}

bool keyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		_keyUp.set(playerKey[key],true);
	}
	else
	{
		if (_keyUp[playerKey[key]])
		{
			_keyUp.set(playerKey[key], false);
			return true;
		}
	}

	return false;
}

bool keyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(playerKey[key]) & 0x8000)return true;
	return false;
}

bool keyManager::isToggleKey(int key)
{

	//GetKeyState :���� Ű�� ��ۻ���
	//0x0001������ �������� �ְ� ȣ��������� �ȴ��� ����

	if (GetKeyState(playerKey[key]) & 0x0001)return true;
	return false;
}

void keyManager::setCustomKey(int dest, int userKey)
{
	playerKey[dest] = userKey;
}
