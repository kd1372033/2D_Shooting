#include "TitleScene.h"
#include "../SceneManager.h"

void TitleScene::Init()
{
	m_logoTex.Load("Texture/Title/Title.png");
	m_backTex.Load("Texture/Title/Back.png");
	m_playerTex.Load("Texture/Title/Player.png");
	m_starttex.Load("Texture/Title/start.png");


	m_logoPos = { -320,175 };
	m_playerPos = { -800,0 };
	m_startPos = { 0,-200 };
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

	m_alpha += m_delta;
	if (m_alpha <= 0.05) { m_delta = 0.01f; }
	else if (m_alpha >= 1) { m_delta = -0.01f; }

	m_playerPos.x += 3;
	playerdeg -= 2;
	if (m_playerPos.x >= 800)
	{
		m_playerPos.x = -800;
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
	SHADER.m_spriteShader.DrawTex(&m_starttex, 0, 0, &startrc, &startcolor);

}

void TitleScene::Release()
{
}