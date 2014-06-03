#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <iostream>
#include <Poco/NumberParser.h>
#include <Poco/Delegate.h>
#include "HAL/API/RemoteSvc_Json.h"

#include <SDL/SDL.h>

using namespace cv;
using namespace std;

double curSpeedL = 0;
double curSpeedR = 0;

HAL::Remote::Json::Client::Ptr client;

class SDLLoop {
public:
	SDLLoop() {
		std::cout << "construct" << std::endl;
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
			throw Poco::Exception("no SDL");
		}
	}
	~SDLLoop() {
		SDL_QuitSubSystem(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
	}

	void run() {
		bool done = false;
		SDL_Event event;
		while (!done) {
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_KEYDOWN:
					if (event.key.keysym.sym != SDLK_ESCAPE) {
						//std::cout << "key" << std::endl;
						break;
					}
					// Fall through to signal quit
				case SDL_QUIT:
					std::cout << "quit" << std::endl;
					done = 1;
					break;
				default:
					//std::cout << "default event " << (int)event.type << std::endl;
					break;
				}
			}
		}
	}
};

class Joystick: private Poco::Runnable {
public:

	struct Coord {
		double x;
		double y;
	};

	Poco::BasicEvent<Coord> CoordUpdate;

	Joystick(int number) :
			done(false) {
		c.x = 0;
		c.y = 0;
		joystick = SDL_JoystickOpen(number);
		if (joystick == NULL) {
			throw Poco::Exception("no joystick");
		} else {
			std::cout << "joystick ok" << std::endl;
		}

		const char * name = SDL_JoystickName(SDL_JoystickIndex(joystick));
		printf("Watching joystick %d: (%s)\n", SDL_JoystickIndex(joystick),
				name ? name : "Unknown Joystick");
		printf("Joystick has %d axes, %d hats, %d balls, and %d buttons\n",
				SDL_JoystickNumAxes(joystick), SDL_JoystickNumHats(joystick),
				SDL_JoystickNumBalls(joystick),
				SDL_JoystickNumButtons(joystick));

		t.start(*this);

	}

	~Joystick() {
		std::cout << "destruct" << std::endl;
		done = true;
		t.join();
		SDL_JoystickClose(joystick);

	}

	double normalizeTo1(int val) {
		int stepDown = 3000;
		if (val < 0 && val > -stepDown)
			val = 0;
		if (val > 0 && val < stepDown)
			val = 0;
		double v = val * 1.0 / (32000.0);
		if (v > 1)
			v = 1;
		if (v < -1)
			v = -1;
		return v;
	}

	void iteration() {
		int x = (((int) SDL_JoystickGetAxis(joystick, 0)));
		int y = (((int) SDL_JoystickGetAxis(joystick, 1)));
		Coord tmp;
		{
			Poco::Mutex::ScopedLock l(m);
			tmp.x = normalizeTo1(x);
			tmp.y = normalizeTo1(-y);
			c = tmp;
		}
		CoordUpdate(this, tmp);
	}
	void run() {
		std::cout << "start bg" << std::endl;
		//SDL_Event event;
		//int x, y, draw;
		//SDL_Rect axis_area[2];

		while (!done) {
			for (int i = 0; i < 20; i++) {
				iteration();
				Poco::Thread::sleep(100);
			}
		}
		std::cout << "finish bg" << std::endl;
	}
	void read(double & x, double & y) {
		Poco::Mutex::ScopedLock l(m);
		x = c.x;
		y = c.y;
	}
private:
	bool done;
	SDL_Joystick * joystick;
	Poco::Thread t;
	Poco::Mutex m;

	Coord c;
};

void onJoystick(Joystick::Coord & c) {
	try {

			double speed = c.y;
			double speedLeft = speed;
			double speedRight = speed;

			double turn = c.x;
			double turnAbs = 1.0 - std::abs(turn);
			if (turn > 0){
				speedLeft *= turnAbs;
			}
			if (turn < 0){
				speedRight *= turnAbs;
			}

			std::cout << "speed: " << speed << " turn: " << turn << std::endl;

			client->Movement().Move(speedLeft, speedRight);
		} catch (Poco::Exception & e){
			std::cerr << "Exception: " << e.displayText() << std::endl;
		} catch (std::exception & e){
			std::cerr << "Exception: " << e.what() << std::endl;
		}
}

int main(int argc, char** argv) {
	try {
		client = new HAL::Remote::Json::Client(TBS::Services::JsonClientChannel("192.168.0.1", 8181));
		{
			SDLLoop loop;
			{
				Joystick j(0);
				j.CoordUpdate += Poco::delegate(&onJoystick);
				loop.run();
				j.CoordUpdate -= Poco::delegate(&onJoystick);
			}
		}
	} catch (Poco::Exception & e) {
		std::cerr << "Exception: " << e.displayText() << std::endl;
	} catch (std::exception & e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}
	return 0;
}
