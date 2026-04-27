#include "main.h"
#include "Scene.h"
#include "Scene/TitleScene/TitleScene.h"
#include "Scene/GameScene/GameScene.h"
#include "Scene/ResultScene/ResultScene.h"

void Scene::Draw2D()
{
	m_nowscene->Draw();
	// 文字列表示
	//SHADER.m_spriteShader.DrawString(0, 0, "Hello World", Math::Vector4(1, 1, 0, 1));
}

void Scene::Update()
{
	m_nowscene->Update();
}

void Scene::Init()
{
	m_nowscene = std::make_shared<GameScene>();
	m_nowscene->Init();
}

void Scene::Release()
{
	m_nowscene->Release();
}

void Scene::ImGuiUpdate()
{
	return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
	}
	ImGui::End();
}
