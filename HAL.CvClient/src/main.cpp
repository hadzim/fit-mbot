#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <iostream>
#include <Poco/NumberParser.h>
#include <Poco/Delegate.h>
#include "HAL/API/MovementClient.h"
#include "HAL/API/BioRadarSvc_Json.h"
#include "HAL/API/BioRadar.h"
#include "HAL/API/CameraSvc_Json.h"
#include "HAL/API/ManipulatorSvc_Json.h"
#include "HAL/API/api.h"

#include "TBS/Log.h"

using namespace cv;
using namespace std;

double curSpeedL = 0;
double curSpeedR = 0;

HAL::API::MovementClient::Ptr client;
HAL::API::BioRadar::Json::Client::Ptr bioRadarClient;
HAL::API::Camera::Json::Client::Ptr cameraClient;
HAL::API::Manipulator::Json::Client::Ptr manipulatorClient;

static void onMouse(int event, int x, int y, int, void*) {
	try {
		if (event != CV_EVENT_LBUTTONDOWN)
			return;

		Point seed = Point(x, y);
		double speed = -((-100 + y) * 1.0 / 100.0);
		double speedLeft = speed;
		double speedRight = speed;

		double turn = (-100 + x) * 1.0 / 100.0;
		double turnAbs = 1.0 - std::abs(turn);
		if (turn > 0) {
			speedLeft *= turnAbs;
		}
		if (turn < 0) {
			speedRight *= turnAbs;
		}

		std::cout << "speed: " << speed << " turn: " << turn << std::endl;

		client->Movement().Move(speedLeft, speedRight);
	} catch (Poco::Exception & e) {
		std::cerr << "Exception: " << e.displayText() << std::endl;
	} catch (std::exception & e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}

static void onMouse2(int event, int x, int y, int, void*) {
	try {
		//if( event != CV_EVENT_LBUTTONDOWN )
		//	return;

		double speed = -((-100 + y) * 1.0);

		std::cout << "bio radar speed: " << speed << std::endl;

		bioRadarClient->BioRadar().GoRelBase(speed);
	} catch (Poco::Exception & e) {
		std::cerr << "Exception: " << e.displayText() << std::endl;
	} catch (std::exception & e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}
	//Poco::Thread::sleep(50);
}

void updateSpeed(HAL::API::Movement::IMovement::StatusChangedArg & arg) {
	curSpeedL = arg.speedLeft;
	curSpeedR = arg.speedRight;
}
void drawSpeed(Mat & img) {
	std::stringstream l;
	l << "L: " << curSpeedL;
	std::stringstream r;
	r << "R: " << curSpeedR;
	//draw text

	int fontFace = FONT_HERSHEY_PLAIN;
	double fontScale = 1.1;
	int thickness = 1;

	// center the text
	Point textOrgL(20, 20);
	Point textOrgR(20, 45);

	// then put the text itself
	putText(img, l.str(), textOrgL, fontFace, fontScale, Scalar::all(255), thickness, 8);
	putText(img, r.str(), textOrgR, fontFace, fontScale, Scalar::all(255), thickness, 8);
}

int main(int argc, char** argv) {

	int maxManSpeed = 30000;

	try {

		TBS::initLogs("cvclient", 8);

		std::cout << "HAL Client Starts" << std::endl;
		Mat image(200, 200, CV_8UC3);
		Mat imageRadar(50, 200, CV_8UC3);

		cv::line(image, cv::Point(0, 100), cv::Point(200, 100), cv::Scalar(255, 0, 0), 1);
		cv::line(image, cv::Point(100, 0), cv::Point(100, 200), cv::Scalar(255, 0, 0), 1);

		namedWindow("movement", 0);
		setMouseCallback("movement", onMouse, 0);

		namedWindow("bioradar", 0);
		setMouseCallback("bioradar", onMouse2, 0);

		TBS::Services::JsonClientParams bp("localhost", HAL::API::Communication::BioRadarPort, TBS::Services::JsonClientParams::JsonHttp);
		bioRadarClient = new HAL::API::BioRadar::Json::Client(bp);

		TBS::Services::JsonClientParams cp("localhost", HAL::API::Communication::CameraPort, TBS::Services::JsonClientParams::JsonHttp);
		cameraClient = new HAL::API::Camera::Json::Client(cp);

		TBS::Services::JsonClientParams mc("localhost", HAL::API::Communication::ManipulatorPort, TBS::Services::JsonClientParams::JsonHttp);
		manipulatorClient = new HAL::API::Manipulator::Json::Client(mc);

		client = new HAL::API::MovementClient();
		client->Movement().StatusChanged += Poco::delegate(&updateSpeed);
		for (;;) {

			cv::Mat cpy = image.clone();
			drawSpeed(cpy);
			imshow("movement", cpy);
			imshow("bioradar", cpy);

			int c = waitKey(100);
			if ((c & 255) == 27) {
				cout << "Exiting ...\n";
				break;
			}

			try {
				static int speed = 0;
				static Poco::Timestamp tst;
				static int lastInRow = 0;
				if ((c & 255) == 'q') {
					lastInRow++;
					speed = 50;
					bioRadarClient->BioRadar().GoRelBase(speed);
				} else if ((c & 255) == 'a') {
					speed = -50;
					lastInRow++;
					bioRadarClient->BioRadar().GoRelBase(speed);
				} else {
					speed = 0;
					if (lastInRow > 1) {
						bioRadarClient->BioRadar().GoRelBase(speed);
					}
					lastInRow = 0;
				}
				//std::cout << "tst " << tst.elapsed() / 1000 << "ms - speed: " << speed << std::endl;
				tst.update();
			} catch (Poco::Exception & e) {

			}

			try {
				static int speed = 0;
				static Poco::Timestamp tst;
				static int lastInRow = 0;
				if ((c & 255) == 'w') {
					lastInRow++;
					speed = 20;
					bioRadarClient->BioRadar().GoRelAntenna(speed);
				} else if ((c & 255) == 's') {
					speed = -20;
					lastInRow++;
					bioRadarClient->BioRadar().GoRelAntenna(speed);
				} else {
					speed = 0;
					if (lastInRow > 1) {
						bioRadarClient->BioRadar().GoRelAntenna(speed);
					}
					lastInRow = 0;
				}
				//std::cout << "tst " << tst.elapsed() / 1000 << "ms - speed: " << speed << std::endl;
				tst.update();
			} catch (Poco::Exception & e) {

			}

			try {
				if ((c & 255) == 'e') {
					bioRadarClient->BioRadar().Enable();
				} else if ((c & 255) == 'd') {
					bioRadarClient->BioRadar().Disable();
				}
			} catch (Poco::Exception & e) {

			}

			try {
				if ((c & 255) == 'r') {

					HAL::API::BioRadar::MotorInfo base;
					HAL::API::BioRadar::MotorInfo antena;
					std::vector<HAL::API::BioRadar::TouchInfo> touchInfo;

					bioRadarClient->BioRadar().GetStatus(base, antena, touchInfo);

					std::cout << "Antena touch min: " << (antena.touchMin ? 1 : 0) << std::endl;
					std::cout << "Antena touch max: " << (antena.touchMax ? 1 : 0) << std::endl;
					std::cout << "Antena position: " << (antena.position) << std::endl;
					std::cout << "Antena error: " << (antena.positionError ? 1 : 0) << std::endl;
				}
			} catch (Poco::Exception & e) {

			}

			try {
				if ((c & 255) == '{') {
					cameraClient->Camera().Enable();
				} else if ((c & 255) == '}') {
					cameraClient->Camera().Disable();
				}
			} catch (Poco::Exception & e) {

			}

			try {
				static int speed = 0;
				static int lastInRow = 0;
				if ((c & 255) == '+') {
					lastInRow++;
					speed = 100;
					cameraClient->Camera().GoRelEngine(speed);
				} else if ((c & 255) == '-') {
					speed = -100;
					lastInRow++;
					cameraClient->Camera().GoRelEngine(speed);
				} else {
					speed = 0;
					if (lastInRow > 1) {
						cameraClient->Camera().GoRelEngine(0);
					}
					lastInRow = 0;
				}
			} catch (Poco::Exception & e) {

			}

			try {
				static int speed = 0;
				static int lastInRow = 0;
				if ((c & 255) == '4') {
					lastInRow++;
					speed = 100;
					cameraClient->Camera().GoRelServo1(speed);
				} else if ((c & 255) == '6') {
					speed = -100;
					lastInRow++;
					cameraClient->Camera().GoRelServo1(speed);
				} else {
					speed = 0;
					if (lastInRow > 1) {
						cameraClient->Camera().GoRelServo1(0);
					}
					lastInRow = 0;
				}
			} catch (Poco::Exception & e) {

			}

			try {
				static int speed = 0;
				static int lastInRow = 0;
				if ((c & 255) == '8') {
					lastInRow++;
					speed = 100;
					cameraClient->Camera().GoRelServo2(speed);
				} else if ((c & 255) == '2') {
					speed = -100;
					lastInRow++;
					cameraClient->Camera().GoRelServo2(speed);
				} else {
					speed = 0;
					if (lastInRow > 1) {
						cameraClient->Camera().GoRelServo2(0);
					}
					lastInRow = 0;
				}
			} catch (Poco::Exception & e) {

			}

			try {
				if ((c & 255) == 'x') {
					manipulatorClient->Manipulator().Enable();
				} else if ((c & 255) == 'c') {
					manipulatorClient->Manipulator().Disable();
				}
			} catch (Poco::Exception & e) {

			}

			try {
				static int speed = 0;
				static int lastInRow = 0;
				if ((c & 255) == 'v') {
					lastInRow++;
					speed = 50;
					manipulatorClient->Manipulator().StartRotation(speed);
				} else if ((c & 255) == 'b') {
					speed = -50;
					lastInRow++;
					manipulatorClient->Manipulator().StartRotation(speed);
				} else if ((c & 255) == 'n') {
					lastInRow++;
					speed = 50;
					manipulatorClient->Manipulator().StartRotationTo(speed, 1450);
				} else if ((c & 255) == 'm') {
					speed = -50;
					lastInRow++;
					manipulatorClient->Manipulator().StartRotationTo(speed, 1450);
				} else {
					speed = 0;
					if (lastInRow > 1) {
						manipulatorClient->Manipulator().StopRotation();
					}
					lastInRow = 0;
				}
			} catch (Poco::Exception & e) {

			}
/*
			try {
				static int speed = 0;
				static int lastInRow = 0;
				if ((c & 255) == 'n') {
					lastInRow++;
					speed = 50;
					manipulatorClient->Manipulator().StartHolder(speed);
				} else if ((c & 255) == 'm') {
					speed = -50;
					lastInRow++;
					manipulatorClient->Manipulator().StartHolder(speed);
				} else {
					speed = 0;
					if (lastInRow > 1) {
						manipulatorClient->Manipulator().StopHolder();
					}
					lastInRow = 0;
				}
			} catch (Poco::Exception & e) {

			}
*/
			try {
				static int speed = 0;
				static int lastInRow = 0;
				if ((c & 255) == 'j') {
					lastInRow++;
					speed = maxManSpeed;
					manipulatorClient->Manipulator().StartJoint1(speed);
				} else if ((c & 255) == 'k') {
					speed = -maxManSpeed;
					lastInRow++;
					manipulatorClient->Manipulator().StartJoint1(speed);
				} else if ((c & 255) == 'g') {
					lastInRow++;
					speed = maxManSpeed;
					manipulatorClient->Manipulator().StartJoint1To(speed, 3900);
				} else if ((c & 255) == 'h') {
					speed = -maxManSpeed;
					lastInRow++;
					manipulatorClient->Manipulator().StartJoint1To(speed, 3900);
				} else {
					speed = 0;
					if (lastInRow > 1) {
						manipulatorClient->Manipulator().StopJoint1();
					}
					lastInRow = 0;
				}
			} catch (Poco::Exception & e) {

			}

			try {
				static int speed = 0;
				static int lastInRow = 0;
				if ((c & 255) == 'u') {
					lastInRow++;
					speed = maxManSpeed;
					manipulatorClient->Manipulator().StartJoint2(speed);
				} else if ((c & 255) == 'i') {
					speed = -maxManSpeed;
					lastInRow++;
					manipulatorClient->Manipulator().StartJoint2(speed);
				} else if ((c & 255) == 'o') {
					lastInRow++;
					speed = maxManSpeed;
					manipulatorClient->Manipulator().StartJoint2To(speed, 1100);
				} else if ((c & 255) == 'p') {
					speed = -maxManSpeed;
					lastInRow++;
					manipulatorClient->Manipulator().StartJoint2To(speed, 1100);
				} else {
					speed = 0;
					if (lastInRow > 1) {
						manipulatorClient->Manipulator().StopJoint2();
					}
					lastInRow = 0;
				}
			} catch (Poco::Exception & e) {

			}



			try {
				if ((c & 255) == ',') {
					manipulatorClient->Manipulator().LightOn();
				} else if ((c & 255) == '.') {
					manipulatorClient->Manipulator().LightOff();
				}
			} catch (Poco::Exception & e) {

			}

		}
		client->Movement().StatusChanged -= Poco::delegate(&updateSpeed);
	} catch (Poco::Exception & e) {
		std::cerr << "Exception: " << e.displayText() << std::endl;
	} catch (std::exception & e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}
	return 0;
}
