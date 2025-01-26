
#include "app/TestApplication.h"


int main() {
	TestApplication app;
	
	app.start();
	while (app.is_running()) {
		app.run();
	}
	
	
	std::cout << "App has been closed successfully!";
}