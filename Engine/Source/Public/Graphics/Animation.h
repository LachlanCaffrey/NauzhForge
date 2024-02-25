#pragma once

class Texture;

struct AnimationParams {
	AnimationParams() {
		FrameWidth = FrameHeight = 0;
		fps = 0.0f;
		StartFrame = EndFrame = 0;
		MaxFrames = 0;
	}

	// Width and height of each frame
	unsigned int FrameWidth, FrameHeight;

	// Frames per second
	float fps;

	//Stat and end frame that the animation will play
	unsigned int StartFrame, EndFrame;

	// Total frame count of sprite
	unsigned int MaxFrames;
};

class Animation {
public:
	Animation();
	~Animation();

	// Imports the animation and adds animations parameters
	bool CreateAnimation(const char* PathToFile, AnimationParams* Params = nullptr);

	// Update the animation logic each frame
	void Update(float DeltaTime);

	void SetPosition(int x, int y);

	void SetRotation(float Angle);

	void SetScale(float Scale);

private:
	// Stores the texture to render
	Texture* m_TextureRef;

	// Store the animation data
	AnimationParams* m_AnimParams;

	// The current playing frame of the animation
	unsigned int m_CurrentFrame;
	
	// How much time has passed since the last animation frame
	float m_FrameTimer;
};