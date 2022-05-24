#pragma once
#include <string>

class ChessDevice;

class CecpProtocol
{
public:
    void begin(ChessDevice&);
    void onDeviceMove(const std::string& mv);
    void onMessage(const std::string& str);

private:
    void send(std::string str);
    static std::string getCmdParams(const std::string& cmd);
    static std::string getIllegalMove(const std::string& cmd);

    bool isForceMode;
    bool isForcedPromotion;
    ChessDevice* device;
};

extern CecpProtocol Protocol;