#pragma once
#include "Vector2.h"
#include <vector>



namespace nu {
	class Input {
	public:
		enum MouseButton {
			LEFT = 1,
			MIDDLE,
			RIGHT
		};
	public:
		bool Initialize();
		void Shutdown();

		void Update();

		bool GetKeyDown(int key) const { return m_keyStates[key]; }
		bool GetPrevKeyDown(int key) const { return m_prevKeyStates[key]; }
		bool GetKeyPressed(int key) const { return !m_prevKeyStates[key] && m_keyStates[key]; }
		bool GetKeyReleased(int key) const { return m_prevKeyStates[key] && !m_keyStates[key]; }

		Vector2 GetMousePosition() { return m_mousePosition; }
		bool GetMouseDown(MouseButton button) const { return false; }

	private:
		// Keyboard Stuff
		std::vector<bool> m_keyStates;
		std::vector<bool> m_prevKeyStates;

		// Mouse Stuff
		uint32_t m_buttonStates = 0;
		uint32_t m_prevButtonStates = 0;

		Vector2 m_mousePosition{0,0};

	};
}