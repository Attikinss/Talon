#pragma once
#include <glm/glm.hpp>

namespace Talon
{
	enum class CursorMode { Hidden, Visible };
	enum class LockState { Locked, Unlocked };
	enum class KeyCode
	{
		Space = 32,
		Apostrophe = 39,
		Comma = 44,
		Minus = 45,
		Period = 46,
		Slash = 47,
		Alpha_0 = 48,
		Alpha_1 = 49,
		Alpha_2 = 50,
		Alpha_3 = 51,
		Alpha_4 = 52,
		Alpha_5 = 53,
		Alpha_6 = 54,
		Alpha_7 = 55,
		Alpha_8 = 56,
		Alpha_9 = 57,
		Semicolon = 59,
		Equal = 61,
		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,
		Left_Bracket = 91,
		Backslash = 92,
		Right_Bracket = 93,
		Grave = 96,
		WORLD_1 = 161, // ??
		WORLD_2 = 162, // ??
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		Page_Up = 266,
		Page_Down = 267,
		Home = 268,
		End = 269,
		Caps_Lock = 280,
		Scroll_Lock = 281,
		Num_Lock = 282,
		Print_Screen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,
		KP_0 = 320,
		KP_1 = 321,
		KP_2 = 322,
		KP_3 = 323,
		KP_4 = 324,
		KP_5 = 325,
		KP_6 = 326,
		KP_7 = 327,
		KP_8 = 328,
		KP_9 = 329,
		KP_Decimal = 330,
		KP_Divide = 331,
		KP_Multiply = 332,
		KP_Subtract = 333,
		KP_Add = 334,
		KP_Enter = 335,
		KP_Equal = 336,
		Left_Shift = 340,
		Left_Control = 341,
		Left_Alt = 342,
		Left_Super = 343,
		Right_Shift = 344,
		Right_Control = 345,
		Right_Alt = 346,
		Right_Super = 347,
		Menu = 348,

		Count = Menu
	};
	enum class MouseButton
	{
		Button_0 = 0,
		Button_1 = 1,
		Button_2 = 2,
		Button_3 = 3,
		Button_4 = 4,
		Button_5 = 5,
		Button_6 = 6,
		Button_7 = 7,
		Button_Last = Button_7,
		Button_Left = Button_0,
		Button_Right = Button_1,
		Button_Middle = Button_2,
		Count = Button_Middle,
	};

	class Input
	{
	public:
		static void Initialise();
		static void Update();
		static void SetCursorVisibility(CursorMode mode);
		static void SetCursorLock(LockState state);
		static bool GetKey(KeyCode keycode);
		static bool GetKeyDown(KeyCode keycode);
		static bool GetKeyUp(KeyCode keycode);
		static bool GetMouseButton(MouseButton buttonCode);
		static bool GetMouseButtonDown(MouseButton buttonCode);
		static bool GetMouseButtonUp(MouseButton buttonCode);
		static float GetMouseX(bool screenSpace = false);
		static float GetMouseY(bool screenSpace = false);
		static glm::vec2 GetMousePos();
		static glm::vec2 GetMouseDelta();

	private:
		static glm::vec2 ToScreenSpace(const glm::vec2& position);

	private:
		inline static LockState s_LockState = LockState::Unlocked;
		inline static CursorMode s_Visibility = CursorMode::Visible;
	};
}