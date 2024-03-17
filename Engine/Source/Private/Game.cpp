#include "Game.h"
#include <iostream>
#include "SDL2/SDL.h"
#include "Debug.h"
#include "Graphics/Texture.h"
#include "Input.h"
#include "GameObjects/GameObject.h"

// DEBUG
#include "GameObjects/Player.h"
#include "GameObjects/Enemy.h"

Game* Game::GetGame()
{
	// Static means only run initialisation once
	// meaning this line will only run once
	// this is completely thread safe
	static Game* GameSingleton = new Game();

	return GameSingleton;
}

void Game::DestroyGame()
{
	delete GetGame();
}

Texture* Game::ImportTexture(const char* PathToFile)
{
	Texture* NewTexture = new Texture(m_RendererRef);

	// Loop through all of the textures in the game
	for (Texture* TexRef : m_TextureStack) {
		// Check if the texture has already been imported
		if (std::strcmp(TexRef->GetPath(), PathToFile) == 0) {
			// If there was a mtaching path:
			NewTexture->CopyTexture(TexRef);
			// Add it to the texture stack
			m_TextureStack.push_back(NewTexture);

			return NewTexture;
		}
	}

	// Attempt to import the texture
	if (!NewTexture->ImportTexture(PathToFile)) {
		//if it failed the delete and update new texture to nullptr
		delete NewTexture;
		NewTexture = nullptr;
	}
	else {
		// If the import was successfull
		m_TextureStack.push_back(NewTexture);
	}

	return NewTexture;
}

void Game::DestroyTexture(Texture* TextureToDestroy)
{
	if (TextureToDestroy == nullptr) {
		return;
	}

	int TexturesFound = 0;

	// Loop through all of the textures
	for (Texture* TexRef : m_TextureStack) {
		// If the texture has a matching path:
		if (std::strcmp(TextureToDestroy->GetPath(), TexRef->GetPath()) == 0) {
			++TexturesFound;

			if (TexturesFound > 1) {
				break;
			}
		}
	}
	if (TexturesFound <= 1) {
		TextureToDestroy->Cleanup();
	}

	// Find the texture in the array
	auto it = std::find(m_TextureStack.begin(), m_TextureStack.end(), TextureToDestroy);
	// If we find the texture:
	if (it != m_TextureStack.end()) {
		m_TextureStack.erase(it);
	}

	// Remove texture object from memory;
	delete TextureToDestroy;
	TextureToDestroy = nullptr;

	NF_LOG("Game", "Texture has been destroyed.");
}

template<typename T>
T* Game::AddGameObject()
{
	// Create the game object
	T* NewObject = new T();

	// Add the object to our pending spawn array
	m_GameObjectPendingSpawn.push_back(NewObject);

	return NewObject;
}

Game::Game()
{
	printf("The game has been created.\n");

	m_IsGameOpen = true;
	m_WindowRef = nullptr;	
	m_RendererRef = nullptr;
	m_GameInput = nullptr;
}

Game::~Game()
{
	printf("The game has been deleted.\n");
}

void Game::Initialise()
{
	// TODO: Run intialisation of dependencies
	// Initialise SDL and end the game if it fails
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		NF_LOG("Game", "SDL failed to init: " << SDL_GetError());

		return;
	}

	NF_LOG("Game", "Successfully initialised all libraries");

	Start();
}

void Game::Start()
{
	// TODO: Launch the game window

	// Create a window and check if it failed
	m_WindowRef = SDL_CreateWindow("Nauzh Forge", // Title of the window
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, // Starting position on the screen
		1280, 720, // Resolution of the window
		0); // Special flags to change the window settings

	// Did the window fail
	if (m_WindowRef == nullptr) {
		NF_LOG("Game", "SDL window failed to create: " << SDL_GetError());
	
		// Deallocate all which has been allocated prior to this point
		Cleanup();
		return;
	}

	// Create renderer and check if it failed
	m_RendererRef = SDL_CreateRenderer(m_WindowRef, -1, 0);

	// Did the render fail
	if (m_RendererRef == nullptr) {
		NF_LOG("Game", "SDL renderer failed to create: " << SDL_GetError());

		Cleanup();
		return;
	}

	// Create the game input
	m_GameInput = new Input();

	// DEBUG
	AddGameObject<Player>();
	AddGameObject<Enemy>();
	AddGameObject<Enemy>();

	GameLoop();
}

void Game::GameLoop()
{
	// While IsGameOpen is true keep game running
	while (m_IsGameOpen) {
		PreLoop();

		ProcessInput();

		Update();

		Render();

		CollectGarbage();
	}
	Cleanup();
}

void Game::Cleanup()
{
	// Destroy any objects pending spawn
	for (auto GO : m_GameObjectPendingSpawn) {
		GO->Cleanup();
		delete GO;
		GO = nullptr;
	}

	// Destroy any remaining game objects
	for (auto GO : m_GameObjectStack) {
		GO->Cleanup();
		delete GO;
		GO = nullptr;
	}
	
	// Clean up and remove all textures from the texture stack
	for (int i = m_TextureStack.size() - 1; i > -1; --i) {
		DestroyTexture(m_TextureStack[i]);
	}

	// Does the renderer exist
	if (m_RendererRef != nullptr) {
		// Deallocate the renderer memory
		SDL_DestroyRenderer(m_RendererRef);
	}

	// Does the window exist
	if (m_WindowRef != nullptr) {
		// Deallocates the window from memory
		SDL_DestroyWindow(m_WindowRef);
	}

	SDL_Quit();

	NF_LOG("Game", "All memory has been deallocated.");
}

void Game::PreLoop()
{
	// Add all game objects pending spawn to the game object stack
	for (auto GO : m_GameObjectPendingSpawn) {
		m_GameObjectStack.push_back(GO);
		GO->Start();
	}

	// resize array to 0
	m_GameObjectPendingSpawn.clear();
}

void Game::ProcessInput()
{
	// Process the inputs for the game
	m_GameInput->ProcessInput();

	// Run the input listener function for all game objects
	for (auto GO : m_GameObjectStack) {
		if (GO != nullptr) {
			GO->ProcessInput(m_GameInput);
		}
	}
}

void Game::Update()
{
	// Record the previous frame time
	static double LastTickTime = 0.0;
	// Record the current frame time
	double CurrentTickTime = (double)SDL_GetTicks64();
	// Get the delta time - how much time has passed since the last frame
	double LongDelta = CurrentTickTime - LastTickTime;
	// Convert from milliseconds to seconds
	double DeltaTime = LongDelta / 1000.0;
	// Set the last tick time
	LastTickTime = CurrentTickTime;

	// Run the update logic for all game objects
	for (auto GO : m_GameObjectStack) {
		if (GO != nullptr) {
			GO->Update((float)DeltaTime);
			GO->PostUpdate((float)DeltaTime);
		}
	}

	// Caps the frame rate
	int FrameDuration = 1000 / 240;

	if ((double)FrameDuration > LongDelta) {
		FrameDuration = (int)LongDelta;
	}
	// If the frame rate is greater than 240fps, delay the frame
	SDL_Delay((Uint32)FrameDuration);
}

void Game::Render()
{
	// Telling the renderer what colours we want to use next
	SDL_SetRenderDrawColor(m_RendererRef, 227, 195, 215, 255);

	// Use the colour just stated to clear the previous frame and fill with that colour
	SDL_RenderClear(m_RendererRef);

	// TODO: Render custom graphics
	for (Texture* TexRef : m_TextureStack) {
		if (TexRef != nullptr) {
			TexRef->Draw();
		}
	}

	// Present the graphics to the renderer
	SDL_RenderPresent(m_RendererRef);
}

void Game::CollectGarbage()
{
	// TODO: Delete objects at the end of each frame
	for (int i = m_GameObjectStack.size() - 1; i >= 0; --i) {
		if (!m_GameObjectStack[i]->IsPendingDestroy()) {
			continue;
		}

		// Make sure the game object isn't nullptr
		if (m_GameObjectStack[i] != nullptr) {
			m_GameObjectStack[i]->Cleanup();
			delete m_GameObjectStack[i];
		}

		// Remove from and resize the array
		m_GameObjectStack.erase(m_GameObjectStack.begin() + i);
	}
}
