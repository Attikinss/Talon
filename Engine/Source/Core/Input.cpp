#include "Input.h"
#include "Logger.h"
#include "Window.h"

#include <unordered_map>
#include <GLFW/glfw3.h>

namespace Talon
{
	static std::unordered_map<KeyCode, bool> s_KeyMap;
	static std::unordered_map<MouseButton, bool> s_MouseMap;
	static glm::vec2 s_LastMousePosition;

	static bool s_CalculatingDelta = false;

	void Input::Initialise()
	{
		// NOTE: This initialisation/reset process isn't very efficient as there are
		//       values in between each enum that have been added to the input map

		// Reset all key presses
		for (int32_t code = (int32_t)KeyCode::Space; code < (int32_t)KeyCode::Count; code++)
			s_KeyMap[static_cast<KeyCode>(code)] = false;

		// Reset all button presses
		for (int32_t button = (int32_t)MouseButton::Button_0; button < (int32_t)MouseButton::Count; button++)
			s_MouseMap[static_cast<MouseButton>(button)] = false;

        Logger::Trace("Input Initialised...");
	}

	void Input::Update()
	{
		if (!s_CalculatingDelta)
			s_LastMousePosition = GetMousePos();
		else
			s_CalculatingDelta = false;
	}

	void Input::SetCursorVisibility(CursorMode mode)
	{
		s_Visibility = mode;

		// Retrieve window
		GLFWwindow* window = static_cast<GLFWwindow*>(Window::Get().GetWindowHandle());

		switch (s_Visibility)
		{
			case Talon::CursorMode::Hidden:
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
				break;

			case Talon::CursorMode::Visible:
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				break;

			default: break;
		}
	}

	void Input::SetCursorLock(LockState state)
	{
		s_LockState = state;

		// Retrieve window
		GLFWwindow* window = static_cast<GLFWwindow*>(Window::Get().GetWindowHandle());

		switch (s_LockState)
		{
			case Talon::LockState::Locked:
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				break;

			case Talon::LockState::Unlocked:
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				break;

			default: break;
		}
	}

    bool Input::GetKey(KeyCode keycode)
    {
        // Retrieve window
        GLFWwindow* window = static_cast<GLFWwindow*>(Window::Get().GetWindowHandle());

        // Get value of enum
        int key = static_cast<int>(keycode);

        // Check key status
        bool keyDown = glfwGetKey(window, key) == GLFW_PRESS || glfwGetKey(window, key) == GLFW_REPEAT;
        return keyDown;
    }

    bool Input::GetKeyDown(KeyCode keycode)
    {
        // Retrieve window
        GLFWwindow* window = static_cast<GLFWwindow*>(Window::Get().GetWindowHandle());

        // Get value of enum
        int key = static_cast<int>(keycode);

        // Check key status
        bool keyDown = glfwGetKey(window, key) == GLFW_PRESS;

        // Check if key was already down
        bool keyAlreadyDown = s_KeyMap[keycode];
        if (keyDown == keyAlreadyDown)
            return false;

        // Assign value
        s_KeyMap[keycode] = keyDown;
        return keyDown;
    }

    bool Input::GetKeyUp(KeyCode keycode)
    {
        // Retrieve window
        GLFWwindow* window = static_cast<GLFWwindow*>(Window::Get().GetWindowHandle());

        // Get value of enum
        int key = static_cast<int>(keycode);

        // Check key status
        bool keyUp = glfwGetKey(window, key) == GLFW_RELEASE;

        // Check if key was already up
        bool keyAlreadyUp = s_KeyMap[keycode];
        if (keyUp == keyAlreadyUp)
            return false;

        // Assign value
        s_KeyMap[keycode] = keyUp;
        return keyUp;
    }

    bool Input::GetMouseButton(MouseButton buttonCode)
    {
        // Retrieve window
        GLFWwindow* window = static_cast<GLFWwindow*>(Window::Get().GetWindowHandle());

        // Get value of enum
        int button = static_cast<int>(buttonCode);

        // Check key status
        bool buttonDown = glfwGetMouseButton(window, button) == GLFW_PRESS;
        return buttonDown;
    }

    bool Input::GetMouseButtonDown(MouseButton buttonCode)
    {
        // Retrieve window
        GLFWwindow* window = static_cast<GLFWwindow*>(Window::Get().GetWindowHandle());

        // Get value of enum
        int button = static_cast<int>(buttonCode);

        // Check key status
        bool buttonDown = glfwGetMouseButton(window, button) == GLFW_PRESS;

        // Check if button was already down
        bool buttonAlreadyDown = s_MouseMap[buttonCode];
        if (buttonDown == buttonAlreadyDown)
            return false;

        // Assign value
        s_MouseMap[buttonCode] = buttonDown;
        return buttonDown;
    }

    bool Input::GetMouseButtonUp(MouseButton buttonCode)
    {
        // Retrieve window
        GLFWwindow* window = static_cast<GLFWwindow*>(Window::Get().GetWindowHandle());

        // Get value of enum
        int button = static_cast<int>(buttonCode);

        // Check key status
        bool buttonUp = glfwGetMouseButton(window, button) == GLFW_RELEASE;

        // Check if button was already up
        bool buttonAlreadyUp = s_MouseMap[buttonCode];
        if (buttonUp == buttonAlreadyUp)
            return false;

        // Assign value
        s_MouseMap[buttonCode] = buttonUp;
        return buttonUp;
    }

    float Input::GetMouseX(bool screenSpace)
    {
        // Get mouse position
        glm::vec2 mousePos = GetMousePos();

        if (screenSpace)
        {
            // Convert to screen space
            glm::vec2 screenSpace = ToScreenSpace(mousePos);
            return screenSpace.x;
        }

        return mousePos.x;
    }

    float Input::GetMouseY(bool screenSpace)
    {
        // Get mouse position
        glm::vec2 mousePos = GetMousePos();

        if (screenSpace)
        {
            // Convert to screen space
            glm::vec2 screenSpace = ToScreenSpace(mousePos);
            return screenSpace.y;
        }

        return mousePos.y;
    }

    glm::vec2 Input::GetMousePos()
    {
        // Retrieve window
        GLFWwindow* window = static_cast<GLFWwindow*>(Window::Get().GetWindowHandle());

        // Retrieve mouse position
        double x, y;
        glfwGetCursorPos(window, &x, &y);

        return { (float)x, (float)y };
    }

    glm::vec2 Input::GetMouseDelta()
    {
        s_CalculatingDelta = true;

        glm::vec2 currentPos = GetMousePos();
        glm::vec2 delta = currentPos - s_LastMousePosition;
        s_LastMousePosition = currentPos;

        return delta;
    }

    glm::vec2 Input::ToScreenSpace(const glm::vec2& position)
    {
        // Get window dimensions
        auto [x, y] = Window::Get().GetSize();
        float aspectRatio = (float)x / y;

        // Wacky math time!
        return { aspectRatio * (position.x / ((float)x / 2.0f) - 1.0f), -(position.y / ((float)y / 2.0f) - 1.0f) };
    }
}