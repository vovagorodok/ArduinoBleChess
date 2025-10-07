#include "BleChessProtocol.h"
#include "ArduinoBleChess.h"
#include "BleChessPeripheral.h"
#include "BleChessConnection.h"
#include "BleChessData.h"

namespace
{
BleChessStringView getCmdParams(BleChessStringViewInternal cmd)
{
    auto found = cmd.find(' ');
    if (found == BleChessStringViewInternal::npos)
        return BleChessStringView();
    return cmd.substr(found + 1);
}

inline BleChessString join(BleChessStringView cmd, const BleChessString& params)
{
    BleChessString result;
#ifdef USE_NIM_BLE_ARDUINO_LIB
    result.reserve(cmd.size() + 1 + params.size());
    result.append(cmd.data(), cmd.size());
#else
    result.reserve(cmd.size() + 1 + params.length());
    result.concat(cmd.data(), cmd.size());
#endif
    result += ' ';
    result += params;
    return result;
}
}

BleChessProtocol::BleChessProtocol():
    handleAckMethod(&BleChessPeripheral::handleCentralUnexpectdAck),
    handlePromotedMethod(&BleChessPeripheral::handleCentralUnexpectdCommand)
{}

void BleChessProtocol::handleCentralCommand(BleChessStringViewInternal cmd)
{
    #ifdef BLE_CHESS_DEBUG_LOGS
    Serial.print("DBG: ble chess receive: ");
    Serial.println(cmd.data());
    #endif
    if (cmd.starts_with(BleChessCommand::Ok))
    {
        (bleChessConnection.peripheralForOnline().*handleAckMethod)(true);
        handleAckMethod = &BleChessPeripheral::handleCentralUnexpectdAck;
        handlePromotedMethod = &BleChessPeripheral::handleCentralUnexpectdCommand;
    }
    else if (cmd.starts_with(BleChessCommand::Nok))
    {
        (bleChessConnection.peripheralForOnline().*handleAckMethod)(false);
        handleAckMethod = &BleChessPeripheral::handleCentralUnexpectdAck;
        handlePromotedMethod = &BleChessPeripheral::handleCentralUnexpectdCommand;
    }
    else if (cmd.starts_with(BleChessCommand::Move))
    {
        bleChessConnection.peripheralForOnline().handleCentralMove(getCmdParams(cmd));
    }
    else if (cmd.starts_with(BleChessCommand::Begin))
    {
        handleAckMethod = &BleChessPeripheral::handleCentralUnexpectdAck;
        handlePromotedMethod = &BleChessPeripheral::handleCentralUnexpectdCommand;
        bleChessConnection.peripheralForOnline().handleCentralBegin(getCmdParams(cmd));
    }
    else if (cmd.starts_with(BleChessCommand::SetVariant))
    {
        bleChessConnection.peripheralForOnline().handleCentralSetVariant(getCmdParams(cmd));
    }
    else if (cmd.starts_with(BleChessCommand::Check))
    {
        bleChessConnection.peripheralForOnline().handleCentralCheck(getCmdParams(cmd));
    }
    else if (cmd.starts_with(BleChessCommand::End))
    {
        bleChessConnection.peripheralForOnline().handleCentralEnd(getCmdParams(cmd));
    }
    else if (cmd.starts_with(BleChessCommand::Promote))
    {
        (bleChessConnection.peripheralForOnline().*handlePromotedMethod)(getCmdParams(cmd));
        handleAckMethod = &BleChessPeripheral::handleCentralUnexpectdAck;
        handlePromotedMethod = &BleChessPeripheral::handleCentralUnexpectdCommand;
    }
    else if (cmd.starts_with(BleChessCommand::Feature))
    {
        bleChessConnection.peripheralForOnline().handleCentralFeature(getCmdParams(cmd));
    }
    else if (cmd.starts_with(BleChessCommand::Variant))
    {
        bleChessConnection.peripheralForOnline().handleCentralVariant(getCmdParams(cmd));
    }
    else if (cmd.starts_with(BleChessCommand::GetState))
    {
        bleChessConnection.peripheralForOnline().handleCentralGetState();
    }
    else if (cmd.starts_with(BleChessCommand::SetState))
    {
        bleChessConnection.peripheralForOnline().handleCentralSetState();
    }
    else if (cmd.starts_with(BleChessCommand::State))
    {
        bleChessConnection.peripheralForOnline().handleCentralState(getCmdParams(cmd));
    }
    else if (cmd.starts_with(BleChessCommand::LastMove))
    {
        bleChessConnection.peripheralForOnline().handleCentralLastMove(getCmdParams(cmd));
    }
    else if (cmd.starts_with(BleChessCommand::Msg))
    {
        bleChessConnection.peripheralForOnline().handleCentralMsg(getCmdParams(cmd));
    }
    else if (cmd.starts_with(BleChessCommand::UndoOffer))
    {
        bleChessConnection.peripheralForOnline().handleCentralUndoOffer();
    }
    else if (cmd.starts_with(BleChessCommand::Undo))
    {
        bleChessConnection.peripheralForOnline().handleCentralUndo(getCmdParams(cmd));
    }
    else if (cmd.starts_with(BleChessCommand::DrawOffer))
    {
        bleChessConnection.peripheralForOnline().handleCentralDrawOffer();
    }
    else if (cmd.starts_with(BleChessCommand::Side))
    {
        bleChessConnection.peripheralForOnline().handleCentralSide(getCmdParams(cmd));
    }
    else if (cmd.starts_with(BleChessCommand::Time))
    {
        bleChessConnection.peripheralForOnline().handleCentralTime(getCmdParams(cmd));
    }
    else if (cmd.starts_with(BleChessCommand::Score))
    {
        bleChessConnection.peripheralForOnline().handleCentralScore(getCmdParams(cmd));
    }
    else if (cmd.starts_with(BleChessCommand::OptionsBegin))
    {
        bleChessConnection.peripheralForOnline().handleCentralOptionsBegin();
    }
    else if (cmd.starts_with(BleChessCommand::OptionsReset))
    {
        bleChessConnection.peripheralForOnline().handleCentralOptionsReset();
    }
    else if (cmd.starts_with(BleChessCommand::SetOption))
    {
        bleChessConnection.peripheralForOnline().handleCentralSetOption(getCmdParams(cmd));
    }
    else
    {
        bleChessConnection.peripheralForOnline().handleCentralUnexpectdCommand(cmd);
    }
}

void BleChessProtocol::sendPeripheralState(const BleChessString& fen)
{
    send(join(BleChessCommand::State, fen));
}

void BleChessProtocol::sendPeripheralSync(const BleChessString& fen)
{
    send(join(BleChessCommand::Sync, fen));
}

void BleChessProtocol::sendPeripheralUnsync(const BleChessString& fen)
{
    send(join(BleChessCommand::Unsync, fen));
}

void BleChessProtocol::sendPeripheralMove(const BleChessString& mv)
{
    handleAckMethod = &BleChessPeripheral::handlePeripheralMoveAck;
    handlePromotedMethod = &BleChessPeripheral::handlePeripheralMovePromoted;
    send(join(BleChessCommand::Move, mv));
}

void BleChessProtocol::sendPeripheralAck(bool ack)
{
    send(ack ? BleChessCommand::Ok : BleChessCommand::Nok);
}

void BleChessProtocol::sendPeripheralErr(const BleChessString& err)
{
    send(join(BleChessCommand::Err, err));
}

void BleChessProtocol::sendPeripheralUnsyncSettable(const BleChessString& fen)
{
    send(join(BleChessCommand::UnsyncSettable, fen));
}

void BleChessProtocol::sendPeripheralMoved()
{
    send(BleChessCommand::Moved);
}

void BleChessProtocol::sendPeripheralMsg(const BleChessString& msg)
{
    send(join(BleChessCommand::Msg, msg));
}

void BleChessProtocol::sendPeripheralResign()
{
    send(BleChessCommand::Resign);
}

void BleChessProtocol::sendPeripheralUndoOffer()
{
    handleAckMethod = &BleChessPeripheral::handlePeripheralUndoOfferAck;
    send(BleChessCommand::UndoOffer);
}

void BleChessProtocol::sendPeripheralDrawOffer()
{
    handleAckMethod = &BleChessPeripheral::handlePeripheralDrawOfferAck;
    send(BleChessCommand::DrawOffer);
}

void BleChessProtocol::sendPeripheralOptionsEnd()
{
    send(BleChessCommand::OptionsEnd);
}

void BleChessProtocol::sendPeripheralOptionsReset()
{
    send(BleChessCommand::OptionsReset);
}

void BleChessProtocol::sendPeripheralOption(const BleChessString& option)
{
    send(join(BleChessCommand::Option, option));
}

void BleChessProtocol::sendPeripheralSetOption(const BleChessString& option)
{
    send(join(BleChessCommand::SetOption, option));
}

void BleChessProtocol::send(BleChessString str)
{
    #ifdef BLE_CHESS_DEBUG_LOGS
    Serial.print("DBG: ble chess send: ");
    Serial.println(str.c_str());
    #endif
    ArduinoBleChess.send(str);
}

BleChessProtocol chessProtocol{};