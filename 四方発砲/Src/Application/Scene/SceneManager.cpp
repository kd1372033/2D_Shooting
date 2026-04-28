#include "SceneManager.h"

#include "TitleScene/TitleScene.h"
#include "GameScene/GameScene.h"
#include "ResultScene/ResultScene.h"

void SceneManager::PreUpdate()
{
	// シーン切り替え
	if (m_currentSceneType != m_nextSceneType)
	{
		ChangeScene(m_nextSceneType);
	}
}

void SceneManager::Update()
{
	m_currentScene->Update();
}

void SceneManager::Draw()
{
	m_currentScene->Draw();
}

void SceneManager::Init()
{
	ChangeScene(m_currentSceneType);
}

void SceneManager::Release()
{

}

void SceneManager::ChangeScene(SceneType _sceneType)
{
	// ①次のシーンを作成②シーン管理フラグ更新
	// ①
	switch (_sceneType)
	{
	case SceneManager::Title:
		m_currentScene = std::make_shared<TitleScene>();
		break;
	case SceneManager::Game:
		m_currentScene = std::make_shared<GameScene>();
		break;
	case SceneManager::Result:
		m_currentScene = std::make_shared<ResultScene>();
		break;
	default:
		break;
	}

	// Init関数を呼ぶ場合はここで呼ぶ
	m_currentScene->Init();

	// ②シーン管理フラグ更新
	m_currentSceneType = _sceneType;

}
