#ifndef CANFRAME_H
#define CANFRAME_H

#include <memory>
#include <Poco/SharedPtr.h>

#include <Poco/Types.h>
#include <vector>



class CANFrame
{
public:
    typedef Poco::SharedPtr<CANFrame> Ptr;
    typedef std::vector <Ptr> PtrList;

    enum Identifier
    {
        STANDARD,
        EXTENDED
    };
    enum ByteOrder
    {
        LSB,
        MSB
    };

    void setBO(ByteOrder bo) {
        byteOrder_ = bo;
    }

    ByteOrder BO() const
    {
        return byteOrder_;
    }

    Poco::UInt32 ID() const
    {
        return ID_;
    }
    void setID(Poco::UInt32 value)
    {
        ID_ = value;
    }

    Poco::UInt8 DLC() const
    {
        return DLC_;
    }
    void setDLC(Poco::UInt32 value)
    {
        if (value > 8) {
            DLC_ = 8;
        }
        else {
            DLC_ = value;
        }
    }

    bool RTR() const
    {
        return RTR_;
    }
    void setRTR(bool value)
    {
        RTR_ = value;
    }

    Identifier IDE() const
    {
        return IDE_;
    }
    void setIDE(Identifier value)
    {
        IDE_ = value;
    }

public:
    CANFrame();
    CANFrame(Poco::UInt32 id, Poco::UInt8 dlc);
    ~CANFrame();

    Poco::UInt32 getFrameID() const;

    void initDataBuffer(unsigned char * buffer, int length);

    void setData8(int index, Poco::UInt8 value);
    void setData16(int index, Poco::UInt16 value);
    void setData32(int index, Poco::UInt32 value);
    Poco::UInt8 getData8(int index) const;
    Poco::UInt16 getData16(int index) const;
    Poco::UInt32 getData32(int index) const;
    bool compare(CANFrame::Ptr p);

    CANFrame(CANFrame::Ptr sc);
    CANFrame(std::vector <Poco::UInt8> buf);
    //SocketCAN(QByteArray buf);
    //QByteArray *toByteArray();
    std::vector <Poco::UInt8> toByteArray();

    void setCANAS(Poco::UInt8 id, Poco::UInt8 dataType, Poco::UInt8 serviceCode, Poco::UInt8 messageCode);
    Poco::UInt8 getCANASData8(unsigned int index);
    Poco::UInt16 getCANASData16(unsigned int index);
    Poco::UInt32 getCANASData32();
    void setCANASData8(unsigned int index, Poco::UInt8 value);
    void setCANASData16(unsigned int index, Poco::UInt16 value);
    void setCANASData32(Poco::UInt32 value);





public:
    static const Poco::UInt32 maskID_Standard = 0x000007FF;
    static const Poco::UInt32 maskID_Extended = 0x1FFFFFFF;
    static const Poco::UInt32 maskIDE = 0x80000000;
    static const Poco::UInt32 maskRTR = 0x40000000;
    static const Poco::UInt32 maskERR = 0x20000000;

protected:
    Poco::UInt32 ID_;
    Poco::UInt8 DLC_;
    bool RTR_;
    Identifier IDE_;
    Poco::UInt8 data_[8];
    ByteOrder byteOrder_;

    static const int minimalSize = 5;
    static const Poco::UInt8 maxDLCSize_ = 8;
};

#endif // CANFRAME_H
