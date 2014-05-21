/*
 * main.cpp
 *
 *  Created on: 20.3.2014
 *      Author: JV
 */

#include "HALRemote.h"

int main(int argc, char **argv) {

	HAL::RemoteProvider app;
	return app.run(argc, argv);

}
