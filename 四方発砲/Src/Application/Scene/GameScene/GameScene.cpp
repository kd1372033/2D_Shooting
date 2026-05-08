#include "GameScene.h"
#include "../SceneManager.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Enemy/Enemy.h"
#include "../../Object/Bullet/Bullet.h"
#include "../../Object/Score/Score.h"

void GameScene::Init()
{
	m_score = SceneManager::Instance().GetScore();
	m_backTex.Load("Texture/Game/Back.png");
	// プレイヤー
	std::shared_ptr<Player> player;
	player = std::make_shared<Player>();	//①インスタンスを生成
	player->Init();
	player->SetScore(m_score);
	player->SetOwner(this);
	m_objList.push_back(player);			//③リストへ追加

	// エネミー
	std::shared_ptr<Enemy> enemy;	//forの外で宣言すればOK
	for (int i = 0; i < 3; i++)
	{
		enemy = std::make_shared<Enemy>();
		enemy->Init();
		enemy->SetTarget(player);
		enemy->SetOwner(this);
		m_objList.push_back(enemy);
	}
}

void GameScene::Update()
{

	if (!m_addList.empty()) {
		for (auto& newObj : m_addList) {
			m_objList.push_back(newObj);
		}
		m_addList.clear(); // 予約リストを空にする
	}

	m_spawnTimer++; // 毎フレームカウントアップ
	if (m_spawnTimer >= m_spawnSpan)
	{
		auto enemy = std::make_shared<Enemy>();
		enemy->Init();
		enemy->SetOwner(this);
		// enemy->SetTarget(m_player); 
		m_addList.push_back(enemy);

		m_spawnTimer = 0; // タイマーをリセットして次の3秒を待つ
	}

	for (int i = 0; i < m_objList.size(); ++i)
	{
		m_objList[i]->Update();
	}

	auto it = m_objList.begin();

	while (it != m_objList.end())	// end() は 最後の要素の1個後ろを返す
	{
		// オブジェクトの有効チェック
		if ((*it)->GetAliveFlg() == false)
		{
			// 削除する前に、今指している要素 (*it) が Enemy かどうかを判定する
			// ※ ObjectType:: の部分でエラーが出る場合は ObjectType::Enemy を確認
			if ((*it)->GetObjType() == BaseObject::ObjectType::Enemy)
			{
				m_score->Add(100); // 敵を倒した時だけ加算
			}

			// リストから削除して、次の要素のイテレータを受け取る
			it = m_objList.erase(it);
		}
		else
		{
			it++;	// 次の要素へイテレータを進める
		}
	}

	if (GetAsyncKeyState('R') & 0x8000)
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Result);
	}

	backmat = Math::Matrix::CreateTranslation(m_backPos.x, m_backPos.y, 0.0f);
}

void GameScene::Draw()
{
	SHADER.m_spriteShader.SetMatrix(backmat);
	Math::Rectangle backrc = { 0, 0, 1280, 720 };
	Math::Color backcolor = { 1.0f,1.0f,1.0f,1.0f };
	SHADER.m_spriteShader.DrawTex(&m_backTex, 0, 0, &backrc, &backcolor);

	for (int i = 0; i < m_objList.size(); ++i)
	{
		m_objList[i]->Draw();
	}
	// 文字列表示
	//SHADER.m_spriteShader.DrawString(0, 0, "Game", Math::Vector4(1, 1, 0, 1));
}

void GameScene::Release()
{

}