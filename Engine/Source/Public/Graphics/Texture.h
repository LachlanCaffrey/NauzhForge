#pragma once

struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Surface;
struct SDL_Rect;

class Texture {
public:
	Texture(SDL_Renderer* Renderer);
	~Texture();

	// Import and create a texture
	bool ImportTexture(const char* PathToFile);

	// Copy the texture
	void CopyTexture(Texture* CopyTexture);

	// Draw the texture to the renderer
	void Draw();

	// Deallocate memory
	void Cleanup();

	//Get the oringal image path
	const char* GetPath() const { return m_Path; }

	// Set the clip for the texture
	void SetClip(int x, int y, int w, int h);

public:
	// Position x & y to render to
	int m_PosX, m_PosY;

	// Rotation of the image
	float m_Angle;

	// Scale of the image
	float m_ScaleX, m_ScaleY;

	// Determine whether or not to render the texture
	bool m_IsVisible;

private:
	// Texture that SDL understands
	SDL_Texture* m_TextureRef;

	// Store assigned renderer
	SDL_Renderer* m_RendererRef;

	// Surface data for the original image
	SDL_Surface* m_SurfaceData;

	// Path to the orignial image
	const char* m_Path;

	// Store the clip for the texture
	SDL_Rect* m_ClipRect;
};