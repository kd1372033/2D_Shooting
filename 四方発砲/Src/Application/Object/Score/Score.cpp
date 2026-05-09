#include "Score.h"

void Score::Save()
{
	// 現在のスコアをファイルに追記
	FILE* fp;
	if (fopen_s(&fp, "Data/score.txt", "a") == 0) {
		fprintf(fp, "%d\n", m_value);
		fclose(fp);
	}

	// 保存した後に再読み込みして、最新のハイスコアを saveScore 配列に反映させる
	Load();
}

void Score::Load() {
	FILE* fp;
	int count = 0;

	// 配列をゼロで初期化（古いデータが残らないように）
	for (int k = 0; k < saveNum; k++) saveScore[k] = 0;

	if (fopen_s(&fp, "Data/score.txt", "r") == 0) {
		// 配列のサイズ（saveNum）を超えないように読み込む
		while (count < saveNum && fscanf_s(fp, "%d", &saveScore[count]) != EOF) {
			count++;
		}
		fclose(fp);
	}

	// ソート処理（実際に読み込んだ count 分だけ回すのが安全）
	for (int i = 0; i < count - 1; i++) {
		for (int j = i + 1; j < count; j++) {
			if (saveScore[i] < saveScore[j]) {
				int w = saveScore[i];
				saveScore[i] = saveScore[j];
				saveScore[j] = w;
			}
		}
	}
}

void Score::DrawNumber(float x, float y, int value)
{
	std::string str = std::to_string(value);
	float charW = (float)m_fontTex.GetInfo().Width / 10.0f;
	float charH = (float)m_fontTex.GetInfo().Height;

	// --- 1. 倍率を設定 (例: 2.0f で 2倍の大きさ) ---
	float scale = 2.0f;

	for (int i = 0; i < (int)str.length(); i++) {
		int num = str[i] - '0';

		// --- 2. 行列を「拡大」してから「移動」させる ---
		// Scale * Translation の順番が重要です
		Math::Matrix mat = Math::Matrix::CreateScale(scale, scale, 1.0f) * Math::Matrix::CreateTranslation(x + (i * charW * scale * 1.2f), y, 0);

		SHADER.m_spriteShader.SetMatrix(mat);

		Math::Rectangle src = {
			(long)(num * charW),
			0,
			(long)charW,
			(long)charH
		};

		SHADER.m_spriteShader.DrawTex(&m_fontTex, src, 1.0f);
	}
}

void Score::Draw()
{
	DrawNumber(150, 100, m_value);

	// 2. ハイスコア（保存されている中で1番高いもの）を表示
	// 読み込み済みの saveScore[0] を使用
	DrawNumber(150, -50, saveScore[0]);
}

void Score::Init()
{
	m_fontTex.Load("Texture/Result/number.png"); // 画像の読み込み
}
