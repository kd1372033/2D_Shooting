#pragma once

class UI
{
public:
	UI() {}
	~UI() { Release(); }

	void Update();
	void Draw();
	void Init();
private:
	void Release();

	Math::Vector2 Cnt;

	static const int uiNum = 9;
	KdTexture m_tex;
	KdTexture m_controlTex;
	Math::Matrix mat[uiNum];
	Math::Matrix controlMat;
	Math::Vector2 m_pos[uiNum];
	Math::Vector2 m_controlPos;

	float m_alpha = 0.0f;
	float m_controlslpha = 0.0f;
};