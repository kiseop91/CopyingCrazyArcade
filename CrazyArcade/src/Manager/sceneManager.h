#pragma once
#include "Common/singletonBase.h"


class gameNode;
class sceneManager :  public singletonBase<sceneManager>
{
private:

	typedef map<string, gameNode*> mSceneList;
	typedef map<string, gameNode*>::iterator miSceneList;

private:
	//�����
	static gameNode* _currentScene;
	//���
	mSceneList _mSceneList;

public:
	sceneManager();
	~sceneManager();

	HRESULT init();
	void release();
	void update(float deltaTime);
	void render();
	void afterRender();
	void debugRender();
	
	//���߰��ϱ�
	gameNode* addScene(string sceneName, gameNode* scene);
	HRESULT changeScene(string sceneName);
};

