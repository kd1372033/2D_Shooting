#pragma once
#include "State.h"
#include "Title.h"
#include "Game.h"
#include "Result.h"

class SceneMenager
{
public:

	static SceneMenager& GetInstance()
	{
		static SceneMenager instance;
		return instance;
	}

	void ChangState(State* newState)
	{
		delete currentState;//←これにしてると安全 deleteにするとすべて消える
		currentState = newState;

		Init();
	}

	void Init()
	{
		currentState->Init();
		/*bgmvol = 0.10f; //BGMのボリューム設定
		//BGM切り替える
		if (currentState->GetTag() == Stage::Title)
		{
			if (soundflg)
			{
				if (skybgmInst->IsPlay())
				{
					skybgmInst->Stop();
				}
			}
			titlebgm = std::make_shared<KdSoundEffect>();
			titlebgm->Load("Sound/BGM.wav");
			titlebgmInst = titlebgm->CreateInstance(false);
			titlebgmInst->SetVolume(bgmvol);
			titlebgmInst->Play(true);
		}
		*/
	}

	void Update()
	{
		currentState->Update();
	}

	void Draw()
	{
		currentState->Draw();
	}

	//追加処理
	int SkyScore;
	bool stageClear;
	bool skyClear;

private:
	//追加処理
	SceneMenager() {
		SkyScore = 0;
		stageClear = false;
		skyClear = false;
	}

	State* currentState = nullptr;

	//BGM変数用意
	float bgmvol;//BGNのボリューム
	std::shared_ptr<KdSoundInstance>	titlebgmInst;//BGMのインスタンス
	std::shared_ptr<KdSoundInstance>	skybgmInst;//BGMのインスタンス
	std::shared_ptr<KdSoundEffect>		titlebgm;
	std::shared_ptr<KdSoundEffect>		skybgm;
	bool soundflg = false;

	int waitFrame = 0;
};

#define SCENEMANAGER SceneMenager::GetInstance()
