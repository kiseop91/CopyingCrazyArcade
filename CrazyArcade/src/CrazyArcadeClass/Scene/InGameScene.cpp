#include "Etc/stdafx.h"
#include "InGameScene.h"
#include "Manager/SoundManager.h"

InGameScene::InGameScene()
{
}


InGameScene::~InGameScene()
{
}

HRESULT InGameScene::init()
{
	//=============== inGameScene image settup ======================//

	//map
	IMAGEMANAGER->addImage		("�ΰ��Ӿ����", "images/map.bmp",					WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	//character
	IMAGEMANAGER->addImage		("�÷��̾�",	"images/bazziReadyCharacter.bmp",	54, 63, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("�����̵�",	"images/BazziMove.bmp",				560, 320, 7, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("����ǳ����",	"images/bazziBubble.bmp",			960, 65, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("��������",	"images/bazziDie.bmp",				770, 110, 11, 1, true, RGB(255, 0, 255));

	//block
	IMAGEMANAGER->addImage		("�ϵ���",	"images/house.bmp",					180, 90, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage		("����Ʈ���",	"images/box.bmp",					180, 67, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage		("Ÿ��",		"images/Tile.bmp",					300, 60);

	//bomb
	IMAGEMANAGER->addFrameImage	("����ź",		"images/bomb_already.bmp",			222, 75, 4, 1, true, RGB(255, 0, 255));

	//boom
	IMAGEMANAGER->addFrameImage	("�������ʳ�",	"images/bomb_top.bmp",				540, 60, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("��������",	"images/bomb_top_ex.bmp",			540, 60, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("���߾Ʒ��ʳ�","images/bomb_bottom.bmp",			540, 60, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("���߾Ʒ���",	"images/bomb_bottom_ex.bmp",		540, 60, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("���߿����ʳ�","images/bomb_right.bmp",			540, 60, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("���߿�����",	"images/bomb_right_ex.bmp",			540, 60, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("���߿��ʳ�",	"images/bomb_left.bmp",				540, 60, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("���߿���",	"images/bomb_left_ex.bmp",			540, 60, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("���߼���",	"images/bomb_center.bmp",			540, 60, 9, 1, true, RGB(255, 0, 255));

	//item
	IMAGEMANAGER->addFrameImage	("������",		"images/item.bmp", 160, 234, 3, 4, true, RGB(255, 0, 255));

	GET_SINGLE(SoundManager)->addSound("����", "music/Boomhill.mp3");
	//============================================================//

	//InGameScene manager init
	GET_SINGLE(BlockManager)->init();
	GET_SINGLE(CharacterManager)->init();
	GET_SINGLE(BombManager)->init();
	GET_SINGLE(ItemManager)->init();

	//for debugMode
	sprintf(str, "DEBUG ENABLED A : speed up S : limit up D : range up");
	len = strlen(str);

	GET_SINGLE(SoundManager)->playeSound("����", 0);
	return S_OK;
}

void InGameScene::release()
{
	RELEASE_SINGLE(BlockManager);
	RELEASE_SINGLE(CharacterManager);
	RELEASE_SINGLE(BombManager);
	RELEASE_SINGLE(ItemManager);
}

void InGameScene::update(float deltaTime)
{
	if (KEYMANAGER->isOnceKeyDown(VK_F4))
		m_debugMode = !m_debugMode;

	GET_SINGLE(BlockManager)->update(deltaTime);
	GET_SINGLE(BombManager)->update(deltaTime);
	GET_SINGLE(CharacterManager)->update(deltaTime);
	GET_SINGLE(ItemManager)->update(deltaTime);
}

void InGameScene::render()
{
	DrawColorRect(getMemDC(), IRECT(0, 0, WINSIZEX, WINSIZEY), RGB(95, 95, 95));
	IMAGEMANAGER->render("�ΰ��Ӿ����", getMemDC(), 0, 0);

	GET_SINGLE(BlockManager)->render(getMemDC());
	GET_SINGLE(BombManager)->render(getMemDC());
	GET_SINGLE(ItemManager)->render(getMemDC());
	GET_SINGLE(CharacterManager)->render(getMemDC());

	if (m_debugMode) {
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 0, 0));
		TextOut(getMemDC(), 100, 20, str, len);
	}
}

void InGameScene::afterRender()
{
	GET_SINGLE(BlockManager)->afterRender(getMemDC());
}

void InGameScene::debugRender()
{
	GET_SINGLE(BlockManager)->debugRender(getMemDC());
	GET_SINGLE(CharacterManager)->debugRender(getMemDC());
	GET_SINGLE(BombManager)->debugRender(getMemDC());
	GET_SINGLE(ItemManager)->debugRender(getMemDC());

}
