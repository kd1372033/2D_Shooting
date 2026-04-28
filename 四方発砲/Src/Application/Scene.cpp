#include "main.h"
#include "Scene.h"
#include "Scene/SceneManager.h"

void Scene::Draw2D()
{
	SceneManager::Instance().Draw();
	// 文字列表示
	//SHADER.m_spriteShader.DrawString(0, 0, "Hello World", Math::Vector4(1, 1, 0, 1));
}

void Scene::PreUpdate()
{
	SceneManager::Instance().PreUpdate();
}

void Scene::Update()
{
	PreUpdate();

	SceneManager::Instance().Update();
}

void Scene::Init()
{

}

void Scene::Release()
{

}



void Scene::ImGuiUpdate()
{
	//return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
	}
	ImGui::End();
}
