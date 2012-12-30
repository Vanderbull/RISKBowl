#ifndef INPUT_H
#define INPUT_H

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

class CInput
{
private:

public:

	CInput();
	~CInput() {};

	void KeyPressed();
};
#endif