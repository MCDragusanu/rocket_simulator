
#include "Application.h"

int main() {
	Application app;
	app.init();

	while (app.isRunning()) {
		app.update();
	}
	//app.release();
}