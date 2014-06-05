#ifndef SYSTECINTERFACE_H
#define SYSTECINTERFACE_H

// ONLY FOR WIN32 PLATFORM!
#ifdef _WIN32

// Project libraries.
#include <windows.h>
#include "USBCAN32.h"

// C++ libraries.
#include <queue>
#include <memory>
#include <Poco/BasicEvent.h>
#include <RoboCan/Communicaton/usb/CANFrame.h>
#include <RoboCan/Communicaton/usb/ICanWorker.h>


namespace can {

class SystecInterface : public ICanWorker {

public:
	//! Constructor is defined later.
	//! Destructor.
	SystecInterface(int speed);
	~SystecInterface();

	//! Return version of USB-CAN dongle.
	std::string getVestion();

	//! Callback from CAN dongle. Primary read CAN message from dongle and emit signal with message.
	static void PUBLIC callback(tUcanHandle UcanHandle_p, BYTE bEvent_p);

	//! Return system handle for USB-CAN dongle.
	tUcanHandle *getCanHandle() {
		return &canHandle_;
	}

	virtual void sendFrame(CANFrame::Ptr frame);

private:
	void emitMessage();
	//! Get message from USB-CAN dongle.
	bool getMessage(CANFrame::Ptr frame);

	//public slots:
	//! Send CAN message from App to CAN-BUS.


	// Singelton
public:
	/*
	 //! Return instance of object.
	 static SystecInterface& getInstance()
	 {
	 static SystecInterface instance;
	 return instance;
	 }
	 */
private:
	tUcanHandle canHandle_;         //! USB-CAN dongle handler.

private:


public:
	static SystecInterface * instance;
};

}

#endif
#endif // SYSTECINTERFACE_H
