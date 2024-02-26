#include "Input.h"
#include <SDL2/SDL_events.h>
#include "Game.h"
#include "Math/Vector2.h"

void Input::ProcessInput()
{
	// Data type that reads the SDL input events for the window
	SDL_Event InputEvent;

	// Run through each input in that frame
	while (SDL_PollEvent(&InputEvent)) {
		// Was the input that was pressed a mouse button
		// and is it pressed down
		if (InputEvent.type == SDL_MOUSEBUTTONDOWN) {
			DetectMouseButtonState(InputEvent.button.button, true);
		}

		// Was the input that was pressed a mouse button
		// and was it released
		if (InputEvent.type == SDL_MOUSEBUTTONUP) {
			DetectMouseButtonState(InputEvent.button.button, false);
		}

		// If the cross button (exit button) is pressed on the window, close the app
		if (InputEvent.type == SDL_QUIT) {
			Game::GetGame()->QuitApp();
		}
	}
}

bool Input::IsKeyDown(NF_Key Key)
{
	const Uint8* KeyStates = SDL_GetKeyboardState(NULL);

	if (KeyStates == nullptr) {
		return false;
	}

	return KeyStates[Key];
}

bool Input::IsMouseButtonDown(NF_MouseButton Button)
{
	if (Button >= NF_NUM_BUTTONS) {
		return false;
	}
	return m_MouseState[Button];
}

Vector2 Input::GetMousePos() const 
{
	int x(0);
	int y(0);

	// This function will change our x and y variables to the location of the mouse
	SDL_GetMouseState(&x, &y);

	return Vector2((float)x, (float)y);
}

void Input::DetectMouseButtonState(unsigned int Event, bool Value)
{
	switch (Event) {
	case SDL_BUTTON_LEFT :
		m_MouseState[NF_MOUSE_LEFT] = Value;
		break;
	case SDL_BUTTON_MIDDLE :
		m_MouseState[NF_MOUSE_MIDDLE] = Value;
		break;
	case SDL_BUTTON_RIGHT : 
		m_MouseState[NF_MOUSE_RIGHT] = Value;
		break;
	default : 
		break;
	}
}
