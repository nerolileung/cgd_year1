#include "GLUTCallbacks.h"
#include "Source.h"

namespace GLUTCallbacks {
	namespace { //anonymous namespace cannot be accessed by external namespaces
		source * testVar = nullptr;
	}
	void Init(source * gl) {
		testVar = gl;
	}
	void Display() {
		if (testVar != nullptr)	testVar->Display();
	}
	void Timer(int preferredRefresh) {
		if (testVar != nullptr) {
			int updateTime = glutGet(GLUT_ELAPSED_TIME); // need to compensate fps for time taken for update() to run
			testVar->Update();
			updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
			glutTimerFunc(preferredRefresh - updateTime, GLUTCallbacks::Timer, preferredRefresh);  //makes sure timer continues to run
		}
	}
	void Keyboard(unsigned char key, int x, int y) {
		if (testVar != nullptr)	testVar->Keyboard(key, x, y);
	}
}