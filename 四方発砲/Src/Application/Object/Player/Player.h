#pragma once
#include "../BaseObject.h"

class Player :public BaseObject
{
public:
	Player() {}
	~Player()override { Release(); }

	void Update()override;
	void Draw()override;
	void Init()override;
private:

	void Release()override;
	Math::Matrix transmat;
	Math::Matrix scalemat;
	Math::Matrix mat;

	int m_animCnt;	//アニメーションカウンタ
	

};