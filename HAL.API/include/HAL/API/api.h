/*
 * Proxy.h
 *
 *  Created on: Jun 16, 2014
 *      Author: dron
 */

#ifndef PROXY_H_
#define PROXY_H_

namespace HAL {
namespace API {

class Communication {
public:
	static const int MovementPort = 9191;
	static const int BioRadarPort = 9192;
	static const int CameraPort = 9193;
};

}
}

#endif /* PROXY_H_ */
