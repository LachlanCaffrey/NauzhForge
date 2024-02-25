#include "Graphics/Animation.h"
#include "Game.h"
#include "Debug.h"
#include "Graphics/Texture.h"

Animation::Animation()
{
	m_TextureRef = nullptr;
	m_AnimParams = nullptr;
	m_CurrentFrame = 0;
	m_FrameTimer = 0.0f;
}

Animation::~Animation()
{
	if (m_AnimParams != nullptr) {
		delete m_AnimParams;
	}

	if (m_TextureRef != nullptr) {
		delete m_TextureRef;
	}

	Game::GetGame()->DestroyTexture(m_TextureRef);
}

bool Animation::CreateAnimation(const char* PathToFile, AnimationParams* Params)
{
	m_TextureRef = Game::GetGame()->ImportTexture(PathToFile);

	// If the import failed
	if (m_TextureRef == nullptr) {
		NF_LOG("Animation", "Animation failed to import texture: " << PathToFile);
		return false;
	}

	// Set the parameters
	m_AnimParams = Params;

	// If animation parameter were set:
	if (m_AnimParams != nullptr) {
		m_CurrentFrame = m_AnimParams->StartFrame;

		// Update the clip to start on the first frame
		m_TextureRef->SetClip(
			m_AnimParams->FrameWidth * 0,
			0,
			m_AnimParams->FrameWidth,
			m_AnimParams->FrameHeight
		);
	}

	return false;
}

void Animation::Update(float DeltaTime)
{
	if (m_AnimParams == nullptr || m_AnimParams->fps == 0.0f) {
		return;
	}

	// Increase the frame timer each frame to get time passed
	m_FrameTimer += DeltaTime;

	// Check if the frame timer has reached the time to update to the next frame
	if (m_FrameTimer >= 1.0f / m_AnimParams->fps) {
		m_CurrentFrame++;

		if (m_CurrentFrame > m_AnimParams->EndFrame) {
			m_CurrentFrame = 0;
		}

		// Update the clip to start on the next frame
		m_TextureRef->SetClip(
			m_AnimParams->FrameWidth * m_CurrentFrame,
			0,
			m_AnimParams->FrameWidth,
			m_AnimParams->FrameHeight
		);

		// Reset the frame timer
		m_FrameTimer = 0.0f;
	}
}

void Animation::SetPosition(int x, int y)
{
	if (m_TextureRef == nullptr) {
		return;
	}

	m_TextureRef->m_PosX = x;
	m_TextureRef->m_PosY = y;
}

void Animation::SetRotation(float Angle)
{
	if (m_TextureRef == nullptr) {
		return;
	}

	m_TextureRef->m_Angle = Angle;
}

void Animation::SetScale(float Scale)
{
	if (m_TextureRef == nullptr) {
		return;
	}

	m_TextureRef->m_Scale = Scale;
}
