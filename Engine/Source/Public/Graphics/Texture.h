#pragma once

struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Surface;

class Texture {
public:
	Texture(SDL_Renderer* Renderer);
	~Texture() = default;

	// Import and create a texture
	bool ImportTexture(const char* PathToFile);

	// Draw the texture to the renderer
	void Draw();

	// Deallocate memory
	void Cleanup();


	//Get the oringal image path
	const char* GetPath() const { return m_Path; }

public:
	// Position x & y to render to
	int m_PosX, m_PosY;

	// Rotation of the image
	float m_Angle;

	// Scale of the image
	float m_Scale;

private:
	// Texture that SDL understands
	SDL_Texture* m_TextureRef;

	// Store assigned renderer
	SDL_Renderer* m_RendererRef;

	// Surface data for the original image
	SDL_Surface* m_SurfaceData;

	// Path to the orignial image
	const char* m_Path;
};