#include "CecpProtocol.h"
#include "ArduinoBleChess.h"
#include "ChessDevice.h"
#include <regex>

namespace
{
#if __cpp_lib_starts_ends_with
#error "std::string::starts_with() already implemented"
#else
bool startsWith(const std::string& str, const std::string& start)
{
    return str.size() >= start.size() and
           str.substr(0, start.size()) == start;
}
#endif

static const std::regex uci("[a-h,A-H][1-8][a-h,A-H][1-8][nbrqNBRQ]{0,1}");
}

void CecpProtocol::begin(ChessDevice& device)
{
    this->device = &device;
}

void CecpProtocol::onMessage(const std::string& cmd)
{
    if (startsWith(cmd, "protover"))
    {
        send("feature setboard=1");
    }
    else if (startsWith(cmd, "new"))
    {
        isForceMode = false;
        device->askDeviceStopMove();
    }
    else if (startsWith(cmd, "setboard"))
    {
        auto fen = getCmdParams(cmd);
        device->onNewGame(fen);
    }
    else if (startsWith(cmd, "go"))
    {
        isForceMode = false;
        device->askDeviceMakeMove();
    }
    else if (startsWith(cmd, "force"))
    {
        isForceMode = true;
        device->askDeviceStopMove();
    }
    else if (startsWith(cmd, "Illegal move (without promotion)"))
    {
        isForcedPromotion = true;
    }
    else if (startsWith(cmd, "Illegal move"))
    {
        device->onDeviceMoveRejected(getIllegalMove(cmd));
        device->askDeviceMakeMove();
    }
    else if (std::regex_match(cmd, uci))
    {
        if (not isForcedPromotion)
            device->onMove(cmd);

        if (not isForceMode)
            device->askDeviceMakeMove();

        isForcedPromotion = false;
    }
}

void CecpProtocol::onDeviceMove(const std::string& mv)
{
    send("move " + mv);
}

void CecpProtocol::send(std::string str)
{
    ArduinoBleChess.send(str);
}

std::string CecpProtocol::getCmdParams(const std::string& cmd)
{
    return cmd.substr(cmd.find(' ') + 1);
}

std::string CecpProtocol::getIllegalMove(const std::string& cmd)
{
    return cmd.substr(cmd.find(": ") + 2);
}

CecpProtocol Protocol{};