#pragma once

class FPS {
	static const float sec;
	static const int FPS_N;
	static int indexFPS;
	static float FPS_Moy[];

public:

	static float getFPS(const float delta) {
		FPS_Moy[indexFPS] = delta;
		indexFPS = (indexFPS + 1) % FPS_N;

		float fps = 0;
		for (int i = 0; i < FPS_N; i++) {
			fps += FPS_Moy[i];
		}
		return sec / (fps / (float)FPS_N);
	}
};
const float FPS::sec = 1000;
const int FPS::FPS_N = 5;
int FPS::indexFPS = 0;
float FPS::FPS_Moy[FPS_N]{ 60 };