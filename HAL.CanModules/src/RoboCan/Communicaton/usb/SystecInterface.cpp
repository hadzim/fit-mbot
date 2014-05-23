#include <stdexcept>
#include <iostream>
#include <sstream>
// ONLY FOR WIN32 PLATFORM!
#if 1

// Project libraries.
#include "SystecInterface.h"

// Namespaces.

SystecInterface * SystecInterface::instance = NULL;

// Local defines
//#define TIMING_OUTPUT // Printout time consupmtion of sending processes.
//#define DEBUG

// Constructor.
SystecInterface::SystecInterface(int speed) {
	tUcanHandle UcanHandle;
	int ret = UcanInitHardware(&UcanHandle, USBCAN_ANY_MODULE, callback);

	this->canHandle_ = UcanHandle; //&SystecInterface::UcanCallbackFkt);

	if (ret != USBCAN_SUCCESSFUL) {
		std::cout << "SystecInterface::connect - error during UcanInitHardware"
				<< (std::hex) << ret << std::endl;
		throw std::runtime_error(" error during UcanInitHardware");
	}

	int speed_value = 0;
	switch (speed) {
	case 10:
		speed_value = USBCAN_BAUD_10kBit;
		break;
	case 20:
		speed_value = USBCAN_BAUD_20kBit;
		break;
	case 50:
		speed_value = USBCAN_BAUD_50kBit;
		break;
	case 100:
		speed_value = USBCAN_BAUD_100kBit;
		break;
	case 125:
		speed_value = USBCAN_BAUD_125kBit;
		break;
	case 250:
		speed_value = USBCAN_BAUD_250kBit;
		break;
	case 500:
		speed_value = USBCAN_BAUD_500kBit;
		break;
	case 1000:
		speed_value = USBCAN_BAUD_1MBit;
		break;
	default:
		std::cout << "SystecInterface::connect - unknown CAN speed" << ret
				<< std::endl;
		throw std::runtime_error("unknown speed");
		break;
	}
	ret = UcanInitCan(canHandle_, HIBYTE (speed_value), // BTR0
			LOBYTE (speed_value), // BTR1
			0xFFFFFFFF, // AMR: all messages received
			0x00000000); // ACR

	if (ret != USBCAN_SUCCESSFUL) {
		UcanDeinitHardware(canHandle_);
		throw std::runtime_error("init error");
	}

	instance = this;

}

// Desctructor.
SystecInterface::~SystecInterface() {
	UcanDeinitCan(canHandle_);
	UcanDeinitHardware(canHandle_);

	instance = NULL;
}

// Return version of USB-CAN dongle.
std::string SystecInterface::getVestion() {
	int version = UcanGetVersionEx(kVerTypeUserDll);
	std::stringstream s;
	s << USBCAN_MAJOR_VER(version) << "." << USBCAN_MINOR_VER(version) << "."
			<< USBCAN_RELEASE_VER(version);
	return s.str();
	/*return QString("Major version: %1, Minor verion: %2, Version: %3").arg(
	 USBCAN_MAJOR_VER(version)).arg(USBCAN_MINOR_VER(version)).arg(
	 USBCAN_RELEASE_VER(version));*/
}

// Send CAN message from App to CAN-BUS.
void SystecInterface::sendFrame(CANFrame::Ptr frame) {

	tCanMsgStruct tx;

	tx.m_dwID = frame->ID();
	tx.m_bFF = 0;
	tx.m_bDLC = frame->DLC();
	for (int i = 0; i < 8; i++) {
		tx.m_bData[i] = frame->getData8(i);
	}
	int ret = UcanWriteCanMsg(this->canHandle_, &tx);

	if (ret != 0) {
		std::cerr << "SystecInterface::LANtoCANmessage - wrong return value:"
				<< ret << std::endl;
		throw std::runtime_error("sending failed - wrong return");
	}
}


// Get message from USB-CAN dongle.
bool SystecInterface::getMessage(CANFrame::Ptr frame) {

	tCanMsgStruct rx;
	int ret = UcanReadCanMsg(this->canHandle_, &rx);

	if (ret == USBCAN_SUCCESSFUL) {
		frame->setID(rx.m_dwID);
		if (rx.m_bFF & 0x80) {
			frame->setIDE(frame->EXTENDED);
		} else {
			frame->setIDE(frame->STANDARD);
		}
		frame->setDLC(rx.m_bDLC);
		int i;
		for (i = 0; i < rx.m_bDLC; i++) {
			frame->setData8(i, rx.m_bData[i]);
		}
		for (i; i < 8; i++) {
			frame->setData8(i, 0);
		}
		return TRUE;
	}

	return false;
}

// Send CAN message from CAN-BUS to Application.
void SystecInterface::emitMessage() {
	while (true){
		CANFrame::Ptr frame(new CANFrame());
		if (this->getMessage(frame) == false) {
			return;
		}

		FrameReady.notify(this, frame);
	}
}

// Callback from CAN dongle. Primary read CAN message from dongle and emit signal with message.
void PUBLIC SystecInterface::callback(tUcanHandle UcanHandle_p, BYTE bEvent_p) {
	//std::cout << "callback" << std::endl;
	switch (bEvent_p) {
	// CAN message received
	case USBCAN_EVENT_RECEIVE:
		//qDebug() << "USBCAN_EVENT_RECEIVE";
		//TODO
		if (instance){
			instance->emitMessage();
		}
		//SystecInterface::getInstance().emitMessageFromCAN();
		break;

		// changes error status
	case USBCAN_EVENT_STATUS:
		std::cout << "USBCAN_EVENT_STATUS" << std::endl;
		break;
	default:
		std::cout << "USBCAN_OTHER_STATUS" << std::endl;
		break;
	}
}

//----------------------------------UNUSED-------------------------------
//    if (autoreply_) {
//        if (checkAutoReplyID(frame->ID())) {
//            replyToMessage(frame);
//        }
//    }
//-----------------------------------------------------------------------
//
// Fast reply to message (Same message, just CAN_ID = CAN_ID + 1).
//void SystecInterface::replyToMessage(rce::net::can::CANFrame::ptr frame)
//{
//#ifdef TIMING_OUTPUT
//    QDateTime time = QDateTime::currentDateTime();
//#endif
//    if (connected_) {
//        tCanMsgStruct tx;
//
//        tx.m_dwID = frame->ID()+1;
//        tx.m_bFF = 0;
//        tx.m_bDLC = frame->DLC();
//        for (int i = 0; i < 8; i++) {
//            tx.m_bData[i] = frame->getData8(i);
//        }
//        int ret = UcanWriteCanMsg(this->canHandle_, &tx);
//#ifdef TIMING_OUTPUT
//        qDebug() << time.toString("mm:ss.zzz") << "\t" << "rep! " << frame->toString();
//#endif
//        if (ret != 0) {
//            qDebug() << "SystecInterface::replyToMessage - wrong return value:" << ret;
//        }
//    }
//}
//-----------------------------------------------------------------------
//bool SystecInterface::sendMessage(rce::net::can::CANFrame::ptr frame)
//{
//    if (connected_) {
//        tCanMsgStruct tx;

//        tx.m_dwID = frame->ID();
//        tx.m_bFF = 0;
//        tx.m_bDLC = frame->DLC();
//        for (int i = 0; i < 8; i++) {
//            tx.m_bData[i] = frame->getData8(i);
//        }
//        int ret = UcanWriteCanMsg(this->canHandle_, &tx);

//        if (ret != 0) {
//            qDebug() << "SystecInterface::sendPacket - wrong return value:" << ret;
//        }
//    }
//    return false;
//}
#endif
