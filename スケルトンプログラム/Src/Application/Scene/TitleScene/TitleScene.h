#pragma once
#include "../BaseScene/BaseScene.h"

class TitleScene : public BaseScene
{
public:
	TitleScene(){}
	~TitleScene(){}

	void Init()		override;
	void Update()	override;
	void Draw()		override;
	void Release()	override;

private:

};