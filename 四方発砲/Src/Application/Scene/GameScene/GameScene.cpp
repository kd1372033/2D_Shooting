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

	m_countTex.Load("Texture/Game/Countdown.png");

	// プレイヤー
	std::shared_ptr<Player> player;
	player = std::make_shared<Player>();	//①インスタンスを生成
	player->Init();
	player->SetScore(m_score);
	player->SetOwner(this);
	m_objList.push_back(player);			//③リストへ追加

	m_state = State::Countdown;
	m_countdownTimer = 3.5f;
}

void GameScene::Update()
{
	// --- ① 予約リストの反映（敵を出現させるために必須！） ---
	if (!m_addList.empty()) {
		for (auto& newObj : m_addList) {
			m_objList.push_back(newObj);
		}
		m_addList.clear();
	}

	// --- ② カウントダウン中の処理 ---
	if (m_state == State::Countdown) {
		m_countdownTimer -= 1.0f / 60.0f;

		for (auto& obj : m_objList) {
			if (obj && obj->GetObjType() == BaseObject::ObjectType::Player) {
				auto player = std::static_pointer_cast<Player>(obj);
				player->SetCanControl(false);
				obj->Update(); // プレイヤーのみ更新
			}
		}

		if (m_countdownTimer <= 0) {
			m_state = State::Playing;

			// プレイヤーの操作を解禁
			for (auto& obj : m_objList) {
				if (obj->GetObjType() == BaseObject::ObjectType::Player) {
					std::static_pointer_cast<Player>(obj)->SetCanControl(true);
				}
			}

			// 最初の敵を3体予約
			for (int i = 0; i < 3; i++) {
				auto enemy = std::make_shared<Enemy>();
				enemy->Init();
				enemy->SetOwner(this);
				m_addList.push_back(enemy);
			}
		}

		// カウントダウン中も背景や行列の計算は必要
		backmat = Math::Matrix::CreateTranslation(m_backPos.x, m_backPos.y, 0.0f);
		countmat = Math::Matrix::CreateTranslation(0, 0, 0.0f); // 中央付近に

		return; // ★カウントダウン中のみ、ここで処理を抜ける
	}

	// --- ③ ここから下は Playing 状態の時にしか来ない ---

	m_spawnTimer++;
	if (m_spawnTimer >= m_spawnSpan)
	{
		auto enemy = std::make_shared<Enemy>();
		enemy->Init();
		enemy->SetOwner(this);
		m_addList.push_back(enemy);
		m_spawnTimer = 0;
	}

	// 全オブジェクトの更新（敵の移動もここで行われる）
	for (int i = 0; i < m_objList.size(); ++i)
	{
		m_objList[i]->Update();
	}

	// --- ④ 死んだオブジェクトの削除処理 ---
	auto it = m_objList.begin();
	while (it != m_objList.end())
	{
		if ((*it)->GetAliveFlg() == false)
		{
			if ((*it)->GetObjType() == BaseObject::ObjectType::Enemy)
			{
				m_score->Add(250);
			}
			it = m_objList.erase(it);
		}
		else
		{
			it++;
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

	if (m_state == State::Countdown) {
		int countIdx = (int)m_countdownTimer;

		int imgH = 72;
		int imgW = 202;

		int srcY = 202;
		if (countIdx == 3) srcY = imgH * 0;
		else if (countIdx == 2) srcY = imgH * 1;
		else if (countIdx == 1) srcY = imgH * 2;
		else srcY = imgH * 3;
		Math::Rectangle countrc = { 0, srcY, imgW, imgH };
		Math::Color countcolor = { 1.0f,1.0f,1.0f,1.0f };
		SHADER.m_spriteShader.SetMatrix(countmat);
		SHADER.m_spriteShader.DrawTex(&m_countTex, 0, 0, &countrc, &countcolor);
	}
	// 文字列表示
	//SHADER.m_spriteShader.DrawString(0, 0, "Game", Math::Vector4(1, 1, 0, 1));
}

void GameScene::Release()
{

}