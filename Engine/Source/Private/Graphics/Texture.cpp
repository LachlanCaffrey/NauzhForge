#include "Graphics/Texture.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Debug.h"

Texture::Texture(SDL_Renderer* Renderer)
{
	m_RendererRef = Renderer;
	m_Angle = 0.0f;
	m_Path = "";
	m_PosX = m_PosY = 0;
	m_SurfaceData = nullptr;
	m_TextureRef = nullptr;
	m_Scale = 1.0f;
	m_ClipRect = nullptr;
}

Texture::~Texture()
{
	if (m_ClipRect != nullptr) {
		delete m_ClipRect;
	}
}

bool Texture::ImportTexture(const char* PathToFile)
{
	// Store the path to the file
	m_Path = PathToFile;

	// Import the image and convert it to a surface
	// Fill in the object with the data for the image
	m_SurfaceData = IMG_Load(PathToFile);

	// Did the import fail
	if (m_SurfaceData == nullptr) {
		NF_LOG("Texture", "Image failed to import: " << SDL_GetError());
	
		return false;
	}

	// Create the texture from the surface
	m_TextureRef = SDL_CreateTextureFromSurface(m_RendererRef, m_SurfaceData);
	
	// Did the conversion fail
	if (m_TextureRef == nullptr) {
		NF_LOG("Texture", "Image failed to convert to texture: " << SDL_GetError());
	
		Cleanup();
		return false;
	}

	NF_LOG("Texture", "Successfully imported texture: " << m_Path);

	return true;
}

void Texture::CopyTexture(Texture* CopyTexture)
{
	m_Path = CopyTexture->m_Path;
	m_SurfaceData = CopyTexture->m_SurfaceData;
	m_TextureRef = CopyTexture->m_TextureRef;
}

void Texture::Draw()
{
	float ImageWidth = (float)m_SurfaceData->w;
	float ImageHeight = (float)m_SurfaceData->h;

	SDL_FRect DestRect = {
		(float)m_PosX, (float)m_PosY,
		ImageWidth * m_Scale, ImageHeight * m_Scale
	};

	// If we have a set clip then update the width and height of the texture
	if (m_ClipRect != nullptr) {
		DestRect.w = m_ClipRect->w * m_Scale;
		DestRect.h = m_ClipRect->h * m_Scale;
	}

	// Move the texture to be centered at the middle point of the image
	DestRect.x -= DestRect.w / 2;
	DestRect.y -= DestRect.h / 2;

	SDL_FPoint Center{
		DestRect.w / 2,
		DestRect.h / 2
	};

	SDL_RenderCopyExF(
		m_RendererRef, // Renderer to draw to
		m_TextureRef, // The texture to draw to the renderer
		m_ClipRect, // SRC/Clip rect
		&DestRect, // Position and scale on screen
		m_Angle, // Rotation of texture
		&Center, // Center point of rotation
		SDL_FLIP_NONE); // Flip texture vertical or horizontal
}

void Texture::Cleanup()
{
	// Clean up the surface
	if (m_SurfaceData != nullptr) {
		SDL_FreeSurface(m_SurfaceData);
	}

	// Clean up the texture
	if (m_TextureRef != nullptr) {
		SDL_DestroyTexture(m_TextureRef);
	}
	
	NF_LOG("Texture", "Successfully destroyed image: " << m_Path);
}

void Texture::SetClip(int x, int y, int w, int h)
{
	if (m_ClipRect == nullptr) {
		// Create the sdl rect object
		m_ClipRect = new SDL_Rect();
	}

	// Set the rect values
	m_ClipRect->x = x;
	m_ClipRect->y = y;
	m_ClipRect->w = w;
	m_ClipRect->h = h;
}
