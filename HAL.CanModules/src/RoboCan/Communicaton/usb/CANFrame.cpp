// Project libraries.
#include <string.h>
#include "CANFrame.h"
#include <iostream>



#include <stdlib.h>

// Constructor
CANFrame::CANFrame()
{
    ID_ = 0;
    DLC_ = 0;
    RTR_ = false;
    IDE_ = STANDARD;
    //data_ = new Poco::UInt8[8];// { 0, 0, 0, 0, 0, 0, 0, 0 };
    memset(data_, 0, 8);
    byteOrder_ = MSB;
}

CANFrame::CANFrame(Poco::UInt32 id, Poco::UInt8 dlc)
{
    ID_ = id;
    if (dlc <= maxDLCSize_)
        DLC_ = dlc;
    else
        DLC_ = maxDLCSize_;
    RTR_ = false;
    IDE_ = STANDARD;
    //data_ = new Poco::UInt8[8];// { 0, 0, 0, 0, 0, 0, 0, 0 };
    memset(data_, 0, 8);
    byteOrder_ = MSB;
}

CANFrame::~CANFrame()
{
    //delete(data_);
}

void CANFrame::setData8(int index, Poco::UInt8 value)
{
    if (index < 0 || index >= 8)
        return;//throw new System.IndexOutOfRangeException();
    data_[index] = value;
}
void CANFrame::setData16(int index, Poco::UInt16 value)
{
    if (index < 0 || index >= 4)
        return;//throw new System.IndexOutOfRangeException();
    if (byteOrder_ == MSB)
    {
        data_[index * 2] = (Poco::UInt8)(value >> 8);
        data_[index * 2 + 1] = (Poco::UInt8)(value);
    }
    else
    {
        data_[index * 2] = (Poco::UInt8)(value);
        data_[index * 2 + 1] = (Poco::UInt8)(value >> 8);
    }
}
void CANFrame::setData32(int index, Poco::UInt32 value)
{
    if (index < 0 || index >= 2)
        return;//throw new System.IndexOutOfRangeException();
    if (byteOrder_ == MSB)
    {
        data_[index * 4] = (Poco::UInt8)(value >> 24);
        data_[index * 4 + 1] = (Poco::UInt8)(value >> 16);
        data_[index * 4 + 2] = (Poco::UInt8)(value >> 8);
        data_[index * 4 + 3] = (Poco::UInt8)(value);
    }
    else
    {
        data_[index * 4] = (Poco::UInt8)(value);
        data_[index * 4 + 1] = (Poco::UInt8)(value >> 8);
        data_[index * 4 + 2] = (Poco::UInt8)(value >> 16);
        data_[index * 4 + 3] = (Poco::UInt8)(value >> 24);
    }
}
Poco::UInt8 CANFrame::getData8(int index) const
{
    if (index < 0 || index >= 8)
        return 0;//throw new System.IndexOutOfRangeException();
    return data_[index];
}
Poco::UInt16 CANFrame::getData16(int index) const
{
    if (index < 0 || index >= 4)
        return 0;//throw new System.IndexOutOfRangeException();
    if (byteOrder_ == MSB)
    {
        return (Poco::UInt16)(((data_[index * 2]) << 8) | (data_[index * 2 + 1]));
    }
    else
    {
        return (Poco::UInt16)((data_[index * 2]) | ((data_[index * 2 + 1])<<8));
    }
}
Poco::UInt32 CANFrame::getData32(int index) const
{
    if (index < 0 || index >= 2)
        return 0;//throw new System.IndexOutOfRangeException();
    if (byteOrder_ == MSB)
    {
        return (Poco::UInt32)(((data_[index * 4]) << 24) | ((data_[index * 4 + 1]) << 16) | ((data_[index * 4 + 2]) << 8) | ((data_[index * 4 + 3])));
    }
    else
    {
        return (Poco::UInt32)(((data_[index * 4])) | ((data_[index * 4 + 1]) << 8) | ((data_[index * 4 + 2]) << 16) | (((data_[index * 4 + 3]) << 24)));
    }
}
/*
QString CANFrame::toString()
{
    QString s;
    s = QString("ID %1, DLC %2")
            .arg(ID_, 5)
            .arg(DLC_);

    if (DLC_ > 0) {
        s += ", Data: ";
        for (int i = 0; i < DLC_; i++)
        {
            if (i == 4)
                s+= " ";
            s += QString(" %1")
                    .arg(data_[i], 2, 16, QChar('0')).toUpper();;
        }
    }
    return s;
}
*/
bool CANFrame::compare(CANFrame::Ptr p)
{
    if (ID_ != p->ID())
        return false;
    if (IDE_ != p->IDE())
        return false;
    if (DLC_ != p->DLC())
        return false;
    if (RTR_ != p->RTR())
        return false;
    for (int i = 0; i < DLC_; i++)
    {
        if (data_[i] != p->getData8(i))
            return false;
    }
    return true;
}

//QByteArray * SocketCAN::toByteArray()
//{
//    QByteArray *buf = new QByteArray();
////    array = this->ID();

//    Poco::UInt32 id_mess = 0;
//    if (IDE_ == EXTENDED)
//    {
//        id_mess = maskIDE | (ID_ & maskID_Extended);
//    }
//    else
//    {
//        id_mess = ID_ & maskID_Standard;
//    }
//    if (RTR_)
//    {
//        id_mess |= maskRTR;
//    }

//    buf->append((Poco::UInt8)((id_mess & 0xFF000000) >> 24));
//    buf->append((Poco::UInt8)((id_mess & 0x00FF0000) >> 16));
//    buf->append((Poco::UInt8)((id_mess & 0x0000FF00) >> 8));
//    buf->append((Poco::UInt8)(id_mess & 0x000000FF));

//    buf->append((Poco::UInt8)(DLC_));

//    int i;
//    for (i = 0; i < DLC_; i++)
//    {
//        buf->append((Poco::UInt8)data_[i]);
//    }
//    for ( ; i < DLC_; i++)
//    {
//        buf->append((char)0);
//    }
//    return buf;
//}

Poco::UInt32 CANFrame::getFrameID() const{
	Poco::UInt32 id_mess = 0;
	if (IDE_ == EXTENDED)
	{
		id_mess = maskIDE | (ID_ & maskID_Extended);
	}
	else
	{
		id_mess = ID_ & maskID_Standard;
	}
	if (RTR_)
	{
		id_mess |= maskRTR;
	}
	return id_mess;

}

void CANFrame::initDataBuffer(unsigned char * buffer, int length){
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if (i < DLC_){
			buffer[i] = ((Poco::UInt8)data_[i]);
		} else {
			buffer[i] = ((unsigned char)0);
		}

	}
}

std::vector <Poco::UInt8> CANFrame::toByteArray()
{
	std::vector <Poco::UInt8> buf;
//    array = this->ID();

    Poco::UInt32 id_mess = 0;
    if (IDE_ == EXTENDED)
    {
        id_mess = maskIDE | (ID_ & maskID_Extended);
    }
    else
    {
        id_mess = ID_ & maskID_Standard;
    }
    if (RTR_)
    {
        id_mess |= maskRTR;
    }

    buf.push_back((Poco::UInt8)((id_mess & 0xFF000000) >> 24));
    buf.push_back((Poco::UInt8)((id_mess & 0x00FF0000) >> 16));
    buf.push_back((Poco::UInt8)((id_mess & 0x0000FF00) >> 8));
    buf.push_back((Poco::UInt8)(id_mess & 0x000000FF));

    buf.push_back((Poco::UInt8)(DLC_));

    int i;
    for (i = 0; i < DLC_; i++)
    {
        buf.push_back((Poco::UInt8)data_[i]);
    }
    for ( ; i < DLC_; i++)
    {
        buf.push_back((char)0);
    }
    return buf;
}

CANFrame::CANFrame(std::vector <Poco::UInt8> buf)
{
	std::cout << "dec:";
	for (int i = 0; i < buf.size(); i++){
		std::cout << "" << (int)buf[i] << " ";

	}
	std::cout << std::endl;
	std::cout << "hex:";
	for (int i = 0; i < buf.size(); i++){
		std::cout << "" << std::hex  << (int)buf[i] << " ";

	}
	std::cout << std::dec << std::endl;

    //data_ = new Poco::UInt8[8];// { 0, 0, 0, 0, 0, 0, 0, 0 };

    //Poco::UInt32 mess = (Poco::UInt32)((((Poco::UInt8)buf.at(0)) << 24) | (((Poco::UInt8)buf.at(1)) << 16) | (((Poco::UInt8)buf.at(2)) << 8) | (((Poco::UInt8)buf.at(3))));
    Poco::UInt32 mess = (Poco::UInt32)((((Poco::UInt8)buf.at(3)) << 24) | (((Poco::UInt8)buf.at(2)) << 16) | (((Poco::UInt8)buf.at(1)) << 8) | (((Poco::UInt8)buf.at(0))));

    if ((mess & maskIDE) == 0)
    {
        IDE_ = STANDARD;
        ID_ = mess & maskID_Standard;
    }
    else
    {
        IDE_ = EXTENDED;
        ID_ = mess & maskID_Extended;
    }

    if ((mess & maskRTR) == 0)
    {
        RTR_ = false;
    }
    else
    {
        RTR_ = true;
    }

    DLC_ = buf.at(4);
    if (DLC_ > maxDLCSize_) {
        DLC_ = maxDLCSize_;
    }


    int i;
    for (i = 0; i < DLC_; i++)
    {
        data_[i] = buf.at(5+i);
    }

    //buf->remove(0, 5+i); /* DLC + ID size */

    for (; i < 8; i++)
    {
        data_[i] = 0;
    }


}


//SocketCAN::SocketCAN(QByteArray buf)
//{
//    //data_ = new Poco::UInt8[8];// { 0, 0, 0, 0, 0, 0, 0, 0 };
//    byteOrder_ = MSB;

//    //qDebug() << "ID rozlozene: " << (hex) << (Poco::UInt8)buf.at(0) << "-" << (hex) << (Poco::UInt8)buf.at(1) << "-" <<  (hex) << (Poco::UInt8)buf.at(2) << "-" << (hex) << (Poco::UInt8)buf.at(3);

//    Poco::UInt32 mess = (Poco::UInt32)((((Poco::UInt8)buf.at(0)) << 24) | (((Poco::UInt8)buf.at(1)) << 16) | (((Poco::UInt8)buf.at(2)) << 8) | (((Poco::UInt8)buf.at(3))));

//    if ((mess & maskIDE) == 0)
//    {
//        IDE_ = STANDARD;
//        ID_ = mess & maskID_Standard;
//    }
//    else
//    {
//        IDE_ = EXTENDED;
//        ID_ = mess & maskID_Extended;
//    }
//    if ((mess & maskRTR) == 0)
//    {
//        RTR_ = false;
//    }
//    else
//    {
//        RTR_ = true;
//    }

//    DLC_ = buf.at(4);
//    int i;

//    for (i = 0; i < DLC_; i++)
//    {
//        data_[i] = buf.at(5+i);
//    }

//    buf.remove(0, 5+i); /* DLC + ID size */ -- nefunguje, neprojevi se

//    for (; i < 8; i++)
//    {
//        data_[i] = 0;
//    }
//}

void CANFrame::setCANAS(Poco::UInt8 id, Poco::UInt8 dataType, Poco::UInt8 serviceCode, Poco::UInt8 messageCode)
{
    data_[0] = id;
    data_[1] = dataType;
    data_[2] = serviceCode;
    data_[3] = messageCode;
}


Poco::UInt8 CANFrame::getCANASData8(unsigned int index)
{
    if (index >= 4)
        return 0;

    return data_[4+index];
}

Poco::UInt16 CANFrame::getCANASData16(unsigned int index)
{
    if (index >= 2)
        return 0;

    if (byteOrder_ == MSB)
    {
        return (Poco::UInt16)(((data_[4 + (index * 2)]) << 8) | (data_[4 + (index * 2) + 1]));
    }
    else
    {
        return (Poco::UInt16)((data_[4 + (index * 2)]) | ((data_[4 + (index * 2) + 1])<<8));
    }
}

Poco::UInt32 CANFrame::getCANASData32()
{
    if (byteOrder_ == MSB)
    {
        return (Poco::UInt32)(((data_[4]) << 24) | ((data_[5]) << 16) | ((data_[6]) << 8) | ((data_[7])));
    }
    else
    {
        return (Poco::UInt32)(((data_[4])) | ((data_[5]) << 8) | ((data_[6]) << 16) | (((data_[7]) << 24)));
    }
}

void CANFrame::setCANASData8(unsigned int index, Poco::UInt8 value)
{
    if (index >= 4)
        return;

    data_[4+index] = value;
    data_[5+index] = value;
    data_[6+index] = value;
    data_[7+index] = value;
}

void CANFrame::setCANASData16(unsigned int index, Poco::UInt16 value)
{
    if (index >= 2)
        return;

    if (byteOrder_ == MSB)
    {
        data_[4 + (index * 2)] = (Poco::UInt8)(value >> 8);
        data_[4 + (index * 2) + 1] = (Poco::UInt8)(value);
    }
    else
    {
        data_[4 + (index * 2)] = (Poco::UInt8)(value);
        data_[4 + (index * 2) + 1] = (Poco::UInt8)(value >> 8);
    }

}

void CANFrame::setCANASData32(Poco::UInt32 value)
{
    if (byteOrder_ == MSB)
    {
        data_[4] = (Poco::UInt8)(value >> 24);
        data_[5] = (Poco::UInt8)(value >> 16);
        data_[6] = (Poco::UInt8)(value >> 8);
        data_[7] = (Poco::UInt8)(value);
    }
    else
    {
        data_[4] = (Poco::UInt8)(value);
        data_[5] = (Poco::UInt8)(value >> 8);
        data_[6] = (Poco::UInt8)(value >> 16);
        data_[7] = (Poco::UInt8)(value >> 24);
    }
}

CANFrame::CANFrame(CANFrame::Ptr sc):
    ID_(sc->ID()),
    DLC_(sc->DLC()),
    RTR_(sc->RTR()),
    IDE_(sc->IDE()),
    byteOrder_(MSB)
{
    int i;
    if (DLC_ > maxDLCSize_)
    {
        DLC_ = maxDLCSize_;
    }
    for (i = 0; i < 8; i++) {
        data_[i] = sc->getData8(i) ;
    }
}


//--------------------------------------------UNUSED------------------------------------------------------
//CANFrame::ptr CANFrame::getFrame(QByteArray &buf)
//{
//    if (buf.size() < minimalSize)
//        return null;

//    CANFrame::ptr = new(CANFrame());

//    Poco::UInt32 mess = (Poco::UInt32)((((Poco::UInt8)buf->at(0)) << 24) | (((Poco::UInt8)buf->at(1)) << 16) | (((Poco::UInt8)buf->at(2)) << 8) | (((Poco::UInt8)buf->at(3))));
//    if ((mess & maskIDE) == 0)
//    {
//        IDE_ = STANDARD;
//        ID_ = mess & maskID_Standard;
//    }
//    else
//    {
//        IDE_ = EXTENDED;
//        ID_ = mess & maskID_Extended;
//    }

//    if ((mess & maskRTR) == 0)
//    {
//        RTR_ = false;
//    }
//    else
//    {
//        RTR_ = true;
//    }

//    DLC_ = buf->at(4);

//    int i;
//    for (i = 0; i < DLC_; i++)
//    {
//        data_[i] = buf->at(5+i);
//    }
//    for (; i < 8; i++)
//    {
//        data_[i] = 0;
//    }
//}
