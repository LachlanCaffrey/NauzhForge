#include "Game.h"
#include <iostream>
#include "SDL2/SDL.h"
#include "Debug.h"
#include "Graphics/Texture.h"

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

Game::Game()
{
	printf("The game has been created.\n");

	m_IsGameOpen = true;
	m_WindowRef = nullptr;	
	m_RendererRef = nullptr;

	// DEBUG VARIABLES
	m_TestTexture1 = nullptr;
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
	m_TestTexture1 = new Texture(m_RendererRef);
	
	if (!m_TestTexture1->ImportTexture("Content/Letters/D.png")) {
		m_TestTexture1->Cleanup();
		delete m_TestTexture1;
		m_TestTexture1 = nullptr;
	}
	else{
		m_TestTexture1->m_PosX = 100.0f;
		m_TestTexture1->m_PosY = 200.0f;
		m_TestTexture1->m_Angle = 45.0f;
	}

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
	if (m_TestTexture1 != nullptr) {
		m_TestTexture1->Cleanup();
		delete m_TestTexture1;
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
	// TODO: Udpate game logic
	static float Angle = 0.0f;

	if (m_TestTexture1 != nullptr) {
		m_TestTexture1->m_Angle = Angle;
	};

	Angle += 0.1f;
}

void Game::Render()
{
	// Telling the renderer what colours we want to use next
	SDL_SetRenderDrawColor(m_RendererRef, 227, 195, 215, 255);

	// Use the colour just stated to clear the previous frame and fill with that colour
	SDL_RenderClear(m_RendererRef);

	// TODO: Render custom graphics
	if (m_TestTexture1 != nullptr) {
		m_TestTexture1->Draw();
	}
	// Present the graphics to the renderer
	SDL_RenderPresent(m_RendererRef);
}

void Game::CollectGarbage()
{
	// TODO: Delete objects at the end of each frame
}
