#include "Game.h"
#include <iostream>
#include "SDL2/SDL.h"
#include "Debug.h"
#include "Graphics/Texture.h"
#include "Graphics/Animation.h"

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
	int TexturesFound = 0;

	// Loop through all of the textures
	for (Texture* TexRef : m_TextureStack) {
		if (TexRef == nullptr) {
			continue;
		}
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

Game::Game()
{
	printf("The game has been created.\n");

	m_IsGameOpen = true;
	m_WindowRef = nullptr;	
	m_RendererRef = nullptr;

	// DEBUG VARIABLES
	m_TestAnim1 = nullptr;
	m_TestAnim2 = nullptr;
	m_TestAnim3 = nullptr;
	m_TestAnim4 = nullptr;
	m_TestAnim5 = nullptr;
	m_TestAnim6 = nullptr;
	m_TestAnim7 = nullptr;
	m_TestAnim8 = nullptr;
	m_TestAnim9 = nullptr;

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

	// DEBUG
	AnimationParams AnimParams;
	AnimParams.fps = 24.0f;
	AnimParams.MaxFrames = 12;
	AnimParams.EndFrame = 11;
	AnimParams.FrameWidth = 64;
	AnimParams.FrameHeight = 64;

	m_TestAnim1 = new Animation();
	m_TestAnim1->CreateAnimation("Content/Sprites/Main Ship/Main Ship - Shields/PNGs/Main Ship - Shields - Round Shield.png",
		&AnimParams);

	m_TestAnim1->SetPosition(640.0f, 360.0f);
	m_TestAnim1->SetScale(2.0f);

	m_TestAnim2 = new Animation();
	m_TestAnim2->CreateAnimation("Content/Sprites/Main Ship/Main Ship - Shields/PNGs/Main Ship - Shields - Front and Side Shield.png",
		&AnimParams);

	m_TestAnim2->SetPosition(64.0f, 64.0f);
	m_TestAnim2->SetScale(2.0f);

	m_TestAnim3 = new Animation();
	m_TestAnim3->CreateAnimation("Content/Sprites/Main Ship/Main Ship - Shields/PNGs/Main Ship - Shields - Front Shield.png",
		&AnimParams);

	m_TestAnim3->SetPosition(1200.0f, 64.0f);
	m_TestAnim3->SetScale(2.0f);

	m_TestAnim4 = new Animation();
	m_TestAnim4->CreateAnimation("Content/Sprites/Main Ship/Main Ship - Shields/PNGs/Main Ship - Shields - Invincibility Shield.png",
		&AnimParams);

	m_TestAnim4->SetPosition(1200.0f, 640.0f);
	m_TestAnim4->SetScale(2.0f);

	m_TestAnim5 = new Animation();
	m_TestAnim5->CreateAnimation("Content/Sprites/Kla'ed/Shield/PNGs/Kla'ed - Bomber - Shield.png",
		&AnimParams);
	
	m_TestAnim5->SetPosition(64.0f, 640.0f);
	m_TestAnim5->SetScale(2.0f);
	
	m_TestAnim6 = new Animation();
	m_TestAnim6->CreateAnimation("Content/Sprites/Kla'ed/Destruction/PNGs/Kla'ed - Bomber - Destruction.png",
		&AnimParams);

	m_TestAnim6->SetPosition(640.0f, 64.0f);
	m_TestAnim6->SetScale(2.0f);
	
	m_TestAnim7 = new Animation();
	m_TestAnim7->CreateAnimation("Content/Sprites/Kla'ed/Destruction/PNGs/Kla'ed - Frigate - Destruction.png",
		&AnimParams);

	m_TestAnim7->SetPosition(640.0f, 640.0f);
	m_TestAnim7->SetScale(2.0f);

	m_TestAnim8 = new Animation();
	m_TestAnim8->CreateAnimation("Content/Sprites/Kla'ed/Engine/PNGs/Kla'ed - Bomber - Engine.png",
		&AnimParams);

	m_TestAnim8->SetPosition(64.0f, 320.0f);
	m_TestAnim8->SetScale(2.0f);

	m_TestAnim9 = new Animation();
	m_TestAnim9->CreateAnimation("Content/Sprites/Kla'ed/Weapons/PNGs/Kla'ed - Torpedo Ship - Weapons.png",
		&AnimParams);

	m_TestAnim9->SetPosition(1200.0f, 320.0f);
	m_TestAnim9->SetScale(2.0f);

	GameLoop();
}

void Game::GameLoop()
{
	// While IsGameOpen is true keep game running
	while (m_IsGameOpen) {
		ProcessInput();

		Update();

		Render();

		CollectGarbage();
	}
	Cleanup();
}

void Game::Cleanup()
{
	// Clean up and remove all textures from the texture stack
	for (int i = m_TextureStack.size() - 1; i > -1; --i) {
		if (m_TextureStack[i] != nullptr) {
			DestroyTexture(m_TextureStack[i]);
		}
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

void Game::ProcessInput()
{
	// Data type that reads the SDL input events for the window
	SDL_Event InputEvent;

	// Run through each input in that frame
	while (SDL_PollEvent(&InputEvent)) {
		// If the cross button (exit button) is pressed on the window, close the app
		if (InputEvent.type == SDL_QUIT) {
			QuitApp();
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

	// TODO: Udpate game logic
	if (m_TestAnim1 != nullptr) {
		m_TestAnim1->Update((float)DeltaTime);
	}
	if (m_TestAnim2 != nullptr) {
		m_TestAnim2->Update((float)DeltaTime);
	}
	if (m_TestAnim3 != nullptr) {
		m_TestAnim3->Update((float)DeltaTime);
	}
	if (m_TestAnim4 != nullptr) {
		m_TestAnim4->Update((float)DeltaTime);
	}
	if (m_TestAnim5 != nullptr) {
		m_TestAnim5->Update((float)DeltaTime);
	}
	if (m_TestAnim6 != nullptr) {
		m_TestAnim6->Update((float)DeltaTime);
	}
	if (m_TestAnim7 != nullptr) {
		m_TestAnim7->Update((float)DeltaTime);
	}
	if (m_TestAnim8 != nullptr) {
		m_TestAnim8->Update((float)DeltaTime);
	}
	if (m_TestAnim9 != nullptr) {
		m_TestAnim9->Update((float)DeltaTime);
	}
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
}
