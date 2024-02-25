#pragma once
#include "EngineTypes.h"

// Forward declaration
struct SDL_Window;
struct SDL_Renderer;
class Texture;

// DEBUG
class Animation;

class Game {
public:
	// Get the game singleton or create one if it doesn't exist
	static Game* GetGame();

	// Deallocate the game from memory (do not use to exit game, 
	// should only be used inside source)
	static void DestroyGame();

	// Run the game
	void Run() { Initialise(); }

	// Exit the app
	void QuitApp() { m_IsGameOpen = false; }

	// Importing a texture to the game
	Texture* ImportTexture(const char* PathToFile);

	// Safe destroy the texture
	void DestroyTexture(Texture* TextureToDestroy);

private:
	// Constructor runs when the class is created
	// It is also needed to create a new object
	Game();
	// Destructor runs when the class is destroyed/deleted
	~Game();

	// Core Game Functions:
 
	// Initialise the dependencies/external libraries
	// and will exit the game if any fail
	void Initialise();

	// This will run the post-initialise functions relying on dependencies
	// loading the window or any start game functions
	void Start();

	// Run the game loop functions of the game until the app closes
	void GameLoop();

	// Deallocates memoryu after game loops has been exited
	void Cleanup();
	
	// Game Loop: 

	// Listen for and process user input
	void ProcessInput();

	// Update game logic based on player input
	// No rendering here, logic should updte first, then display results
	void Update();

	// Display results and render graphics to screen based on logic
	void Render();

	// Any objects marked for delete will be deallocated from memory here
	void CollectGarbage();

private:
	// Flag that decides when the game loop ends
	bool m_IsGameOpen;

	// Stores the window for the app/game in a pointer
	SDL_Window* m_WindowRef;

	// Stores the renderer for the SDL window in a pointer
	SDL_Renderer* m_RendererRef;

	// Going to store all textures in the game
	TArray<Texture*> m_TextureStack;

	// DEBUG TESTING VARIABLES
	Animation* m_TestAnim1;
	Animation* m_TestAnim2;
	Animation* m_TestAnim3;
	Animation* m_TestAnim4;
	Animation* m_TestAnim5;
	Animation* m_TestAnim6;
	Animation* m_TestAnim7;
	Animation* m_TestAnim8;
	Animation* m_TestAnim9;
};