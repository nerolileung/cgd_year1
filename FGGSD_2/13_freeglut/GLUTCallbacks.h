#pragma once

class source; //forward declare class to avoid circular dependency

namespace GLUTCallbacks {
	void Init(source * gl);
	void Display();
	void Timer(int preferredRefresh);
	void Keyboard(unsigned char key, int x, int y);
}