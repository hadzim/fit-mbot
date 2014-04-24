#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <iostream>
#include <Poco/NumberParser.h>
#include <Poco/Delegate.h>
#include "HAL/API/MovementSvc_DBus.h"

using namespace cv;
using namespace std;

double curSpeedL = 0;
double curSpeedR = 0;

HAL::API::DBus::Client::Ptr client;

static void onMouse( int event, int x, int y, int, void* )
{
	try {
		if( event != CV_EVENT_LBUTTONDOWN )
			return;

		Point seed = Point(x,y);
		double speed = -((-100 + y) * 1.0 / 100.0);
		double speedLeft = speed;
		double speedRight = speed;

		double turn = (-100 + x) * 1.0 / 100.0;
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

void updateSpeed(HAL::API::IMovement::StatusChangedArg & arg){
	curSpeedL = arg.speedLeft;
	curSpeedR = arg.speedRight;
}
void drawSpeed(Mat & img){
	std::stringstream l;
	l << "L: " << curSpeedL;
	std::stringstream r;
	r << "R: " << curSpeedR;
	//draw text

	int fontFace = FONT_HERSHEY_PLAIN;
	double fontScale = 1.1;
	int thickness = 1;


	// center the text
	Point textOrgL(20,20);
	Point textOrgR(20,45);

	// then put the text itself
	putText(img, l.str(), textOrgL, fontFace, fontScale, Scalar::all(255), thickness, 8);
	putText(img, r.str(), textOrgR, fontFace, fontScale, Scalar::all(255), thickness, 8);
}

int main( int argc, char** argv )
{
	try {
		std::cout << "HAL Client Starts" << std::endl;
		Mat image(200, 200, CV_8UC3);

		cv::line(image, cv::Point(0, 100), cv::Point(200,100), cv::Scalar(255,0,0), 1);
		cv::line(image, cv::Point(100, 0), cv::Point(100,200), cv::Scalar(255,0,0), 1);

		namedWindow( "image", 0 );
		setMouseCallback( "image", onMouse, 0 );

		client = new HAL::API::DBus::Client();
		client->Movement().StatusChanged += Poco::delegate(&updateSpeed);
		for(;;)
		{

			cv::Mat cpy = image.clone();
			drawSpeed(cpy);
			imshow("image", cpy);

			int c = waitKey(100);
			if( (c & 255) == 27 )
			{
				cout << "Exiting ...\n";
				break;
			}

		}
		client->Movement().StatusChanged -= Poco::delegate(&updateSpeed);
	} catch (Poco::Exception & e){
		std::cerr << "Exception: " << e.displayText() << std::endl;
	} catch (std::exception & e){
		std::cerr << "Exception: " << e.what() << std::endl;
	}
    return 0;
}
