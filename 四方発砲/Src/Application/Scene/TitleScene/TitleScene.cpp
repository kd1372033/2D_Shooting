#include "TitleScene.h"
#include "../SceneManager.h"

void TitleScene::Init()
{
	m_logoTex.Load("Texture/Title/Title.png");
	m_backTex.Load("Texture/Title/Back.png");
	m_playerTex.Load("Texture/Title/Player.png");
	m_startTex.Load("Texture/Title/start.png");
	m_enemyTex.Load("Texture/Title/Enemy.png");

	for (int i = 0; i < 6; i++) {
		EnemyData e;
		e.pos = { -1100.0f - (i * 200.0f), (rand() % 201) - 100.0f }; // 重ならないようにX軸をずらす
		e.speed = 3.0f;    // 個別にスピードを変えると自然
		e.animCnt = 0;
		m_enemies.push_back(e);
	}

	m_logoPos = { -320,175 };
	m_playerPos = { -800,0 };
	//m_enemyPos = { -1000,0 };
	m_startPos = { 0,-250 };
	m_animCnt = 0;
	m_playerScale = { 0.5,0.5 };
	playerdeg = 0.0f;
	m_alpha = 0.0f;
	m_delta = 0.001f;
}

void TitleScene::Update()
{
	std::vector<int> patterns = { 0, 1, 2, 1 };
	static int timer = 0;
	static int index = 0; // 配列のどこを指すか

	if (++timer > 10) {
		index = (index + 1) % patterns.size(); // 0, 1, 2, 3, 0... と繰り返す
		m_animCnt = patterns[index];           // 現在の番号を代入
		timer = 0;
	}

	std::vector<int> epatterns = { 0, 1 };

	static int etimer = 0;
	static int eindex = 0; // 配列のどこを指すか

	if (++etimer > 10) {
		eindex = (eindex + 1) % epatterns.size();
		m_enemies[eindex].animCnt = epatterns[eindex];
		etimer = 0;
	}

	m_alpha += m_delta;
	if (m_alpha <= 0.1) { m_delta = 0.01f; }
	else if (m_alpha >= 1) { m_delta = -0.01f; }

	m_playerPos.x += 3;
	playerdeg -= 2;

	if (m_playerPos.x >= 750) {
		m_playerPos.x = -800;
	}

	for (auto& e : m_enemies) {
		e.pos.x += e.speed;

		// 画面外に行ったら左に戻す
		if (e.pos.x >= 672) {
			e.pos.x = -875;
			e.pos.y = (rand() % 201) - 100.0f;
		}
		e.mat = Math::Matrix::CreateTranslation(e.pos.x, e.pos.y, 0);
	}

	if (GetAsyncKeyState('R') & 0x8000)
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Result);
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
	}
	logomat = Math::Matrix::CreateTranslation(m_logoPos.x, m_logoPos.y, 0.0f);
	backmat = Math::Matrix::CreateTranslation(m_backPos.x, m_backPos.y, 0.0f);
	startmat = Math::Matrix::CreateTranslation(m_startPos.x, m_startPos.y, 0.0f);

	Math::Matrix transmat = Math::Matrix::CreateTranslation(m_playerPos.x, m_playerPos.y, 0.0f);
	Math::Matrix scalemat = Math::Matrix::CreateScale(m_playerScale.x, m_playerScale.y, 1.0f);
	Math::Matrix rotatemat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(playerdeg));
	playermat = scalemat * rotatemat * transmat;

}

void TitleScene::Draw()
{
	SHADER.m_spriteShader.SetMatrix(backmat);
	Math::Rectangle backrc = { 0, 0, 1280, 720 };
	Math::Color backcolor = { 0.0f,rand() / 32767.0f,rand() / 32767.0f,1.0f };
	SHADER.m_spriteShader.DrawTex(&m_backTex, 0, 0, &backrc, &backcolor);

	Math::Rectangle playerrc = { 640 * m_animCnt, 0, 640, 640 };
	Math::Color playercolor = { 1.0f, 1.0f, 1.0f, 1.0f };
	SHADER.m_spriteShader.SetMatrix(playermat);
	SHADER.m_spriteShader.DrawTex(&m_playerTex, 0, 0, &playerrc, &playercolor);

	Math::Rectangle logorc = { 0, 0, 512, 128 };
	Math::Color logocolor = { 1.0f, 1.0f, 1.0f, 1.0f };
	SHADER.m_spriteShader.SetMatrix(logomat);
	SHADER.m_spriteShader.DrawTex(&m_logoTex, 0, 0, &logorc, &logocolor);

	Math::Rectangle startrc = { 0,0,284,91 };
	Math::Color startcolor = { 1, 1, 1, m_alpha };
	SHADER.m_spriteShader.SetMatrix(startmat);
	SHADER.m_spriteShader.DrawTex(&m_startTex, 0, 0, &startrc, &startcolor);

	for (auto& e : m_enemies) {
		SHADER.m_spriteShader.SetMatrix(e.mat);
		// アニメーションは共通の eindex を使っても、個別に持たせてもOK
		SHADER.m_spriteShader.DrawTex(&m_enemyTex, Math::Rectangle(64 * e.animCnt, 0, 64, 64), 1.0f);
	}
}

void TitleScene::Release()
{
}