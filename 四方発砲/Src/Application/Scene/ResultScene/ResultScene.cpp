#include "ResultScene.h"
#include "../SceneManager.h"
#include "../../Object/Score/Score.h"

void ResultScene::Init()
{
	m_backTex.Load("Texture/Result/Back.png");
	m_scoreTex.Load("Texture/Result/score.png");
	m_highscoreTex.Load("Texture/Result/highscore.png");
	m_starttex.Load("Texture/Result/start.png");

	scorePos = { -150,150 };
	highscorePos = { -200 ,-50 };
	m_startPos = { 0,-200 };
	m_alpha = 0.0f;
	m_delta = 0.001f;

	m_score = SceneManager::Instance().GetScore();
	m_score->Init();
	m_score->Save();
	m_score->Load();


}

void ResultScene::Update()
{
	m_alpha += m_delta;
	if (m_alpha <= 0.05) { m_delta = 0.01f; }
	else if (m_alpha >= 1) { m_delta = -0.01f; }

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		// ビジーウエイト
		while (GetAsyncKeyState(VK_RETURN) & 0x8000) {
			// 何もしない
		}
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);
		m_score->Reset();
	}
	backmat = Math::Matrix::CreateTranslation(m_backPos.x, m_backPos.y, 0.0f);

	scoremat = Math::Matrix::CreateTranslation(scorePos.x, scorePos.y, 0.0);
	highscoremat = Math::Matrix::CreateTranslation(highscorePos.x, highscorePos.y, 0.0);
	startmat = Math::Matrix::CreateTranslation(m_startPos.x, m_startPos.y, 0.0f);

}

void ResultScene::Draw()
{
	SHADER.m_spriteShader.SetMatrix(backmat);
	Math::Rectangle backrc = { 0, 0, 1280, 720 };
	Math::Color backcolor = { 1.0f,1.0f,1.0f,1.0f };
	SHADER.m_spriteShader.DrawTex(&m_backTex, 0, 0, &backrc, &backcolor);

	m_score->Draw();

	SHADER.m_spriteShader.SetMatrix(scoremat);
	Math::Rectangle scorerc = { 0, 0, 151, 46 };
	Math::Color scorecolor = { 1.0f,1.0f,1.0f,1.0f };
	SHADER.m_spriteShader.DrawTex(&m_scoreTex, 0, 0, &scorerc, &scorecolor);

	SHADER.m_spriteShader.SetMatrix(highscoremat);
	Math::Rectangle highscorerc = { 0, 0, 260, 46 };
	Math::Color highscorecolor = { 1.0f,1.0f,1.0f,1.0f };
	SHADER.m_spriteShader.DrawTex(&m_highscoreTex, 0, 0, &highscorerc, &highscorecolor);

	Math::Rectangle startrc = { 0,0,284,91 };
	Math::Color startcolor = { 1, 1, 1, m_alpha };
	SHADER.m_spriteShader.SetMatrix(startmat);
	SHADER.m_spriteShader.DrawTex(&m_starttex, 0, 0, &startrc, &startcolor);

}

void ResultScene::Release()
{
}