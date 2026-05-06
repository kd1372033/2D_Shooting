#pragma once
#include "../BaseScene.h"

class BaseObject;
class Player;

class GameScene : public BaseScene
{
public:
	GameScene() {}
	~GameScene()override {}

	void Init()		override;
	void Update()	override;
	void Draw()		override;
	void Release()	override;

	//全オブジェクトリストを取得
	std::vector<std::shared_ptr<BaseObject>> GetObjList()
	{
		return m_objList;
	}

	void AddObject(std::shared_ptr<BaseObject> _obj)
	{
		// リストの末尾に引数で渡された１要素を追加
		m_objList.push_back(_obj);
	}

private:
	std::shared_ptr<Player> m_player;
	std::vector<std::shared_ptr<BaseObject>> m_objList;
	std::vector<std::shared_ptr<BaseObject>> m_addList;

	int m_spawnTimer = 0;           // 出現用タイマー
	const int m_spawnSpan = 180;    // 3秒（60fps × 3秒 = 180フレーム）
};