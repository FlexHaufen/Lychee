/**
 * @file main.cpp
 * @author flexhaufen
 * @brief main
 * @version 0.1
 * @date 2022-08-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//*** INCLUDES ***
#include "Lychee/Lychee.h"


//*** MAIN ***
int main(int argc, char **argv) {
	Lychee::Application* ly_app = new Lychee::Application();
	
	ly_app->Run();

	delete ly_app;

	return 0;
}