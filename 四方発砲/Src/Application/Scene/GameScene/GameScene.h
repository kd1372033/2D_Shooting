#pragma once
#include "../BaseScene.h"

class BaseObject;
class Player;
class Score;

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

	// スコアアクセス
	//std::shared_ptr<Score> GetScore() { return m_score; }
	//void SetScore(std::shared_ptr<Score> _score) { m_score = _score; }

private:
	std::shared_ptr<Player> m_player;
	std::shared_ptr<Score> m_score;
	std::vector<std::shared_ptr<BaseObject>> m_objList;
	std::vector<std::shared_ptr<BaseObject>> m_addList;

	int m_spawnTimer = 0;           // 出現用タイマー
	const int m_spawnSpan = 90;

	KdTexture m_backTex;
	Math::Vector2 m_backPos;
	Math::Matrix backmat;

};