#pragma once
#include "../BaseScene/BaseScene.h"

class ResultScene : public BaseScene
{
public:
	ResultScene(){}
	~ResultScene(){}

	void Init()		override;
	void Update()	override;
	void Draw()		override;
	void Release()	override;

private:

};