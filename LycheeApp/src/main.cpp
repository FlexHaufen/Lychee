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

// *** INCLUDES ***
#include "LycheeApp.h"


// *** MAIN ***
int main(int argc, char **argv) {

	Lychee::LycheeApp* ly_app = new Lychee::LycheeApp();
	ly_app->Run();
	delete ly_app;
	
	return 0;
}