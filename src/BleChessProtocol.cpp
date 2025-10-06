#include "BleChessProtocol.h"
#include "ArduinoBleChess.h"
#include "BleChessPeripheral.h"
#include "BleChessConnection.h"
#include "BleChessData.h"

namespace
{
BleChessString getCmdParams(const BleChessString& cmd)
{
    return substring(cmd, indexOf(cmd, ' ') + 1);
}
}

BleChessProtocol::BleChessProtocol() :
    handleAckMethod(&BleChessPeripheral::handleCentralUnexpectdAck),
    handlePromotedMethod(&BleChessPeripheral::handleCentralUnexpectdCommand)
{}

void BleChessProtocol::handleCentralCommand(const BleChessString& cmd)
{
    #ifdef BLE_CHESS_DEBUG_LOGS
    Serial.print("DBG: ble chess receive: ");
    Serial.println(cmd.c_str());
    #endif
    if (startsWith(cmd, BleChessCommand::Ok))
    {
        (bleChessConnection.peripheralForOnline().*handleAckMethod)(true);
        handleAckMethod = &BleChessPeripheral::handleCentralUnexpectdAck;
        handlePromotedMethod = &BleChessPeripheral::handleCentralUnexpectdCommand;
    }
    else if (startsWith(cmd, BleChessCommand::Nok))
    {
        (bleChessConnection.peripheralForOnline().*handleAckMethod)(false);
        handleAckMethod = &BleChessPeripheral::handleCentralUnexpectdAck;
        handlePromotedMethod = &BleChessPeripheral::handleCentralUnexpectdCommand;
    }
    else if (startsWith(cmd, BleChessCommand::Move))
    {
        bleChessConnection.peripheralForOnline().handleCentralMove(getCmdParams(cmd));
    }
    else if (startsWith(cmd, BleChessCommand::Begin))
    {
        handleAckMethod = &BleChessPeripheral::handleCentralUnexpectdAck;
        handlePromotedMethod = &BleChessPeripheral::handleCentralUnexpectdCommand;
        bleChessConnection.peripheralForOnline().handleCentralBegin(getCmdParams(cmd));
    }
    else if (startsWith(cmd, BleChessCommand::SetVariant))
    {
        bleChessConnection.peripheralForOnline().handleCentralSetVariant(getCmdParams(cmd));
    }
    else if (startsWith(cmd, BleChessCommand::Check))
    {
        bleChessConnection.peripheralForOnline().handleCentralCheck(getCmdParams(cmd));
    }
    else if (startsWith(cmd, BleChessCommand::End))
    {
        bleChessConnection.peripheralForOnline().handleCentralEnd(getCmdParams(cmd));
    }
    else if (startsWith(cmd, BleChessCommand::Promote))
    {
        (bleChessConnection.peripheralForOnline().*handlePromotedMethod)(getCmdParams(cmd));
        handleAckMethod = &BleChessPeripheral::handleCentralUnexpectdAck;
        handlePromotedMethod = &BleChessPeripheral::handleCentralUnexpectdCommand;
    }
    else if (startsWith(cmd, BleChessCommand::Feature))
    {
        bleChessConnection.peripheralForOnline().handleCentralFeature(getCmdParams(cmd));
    }
    else if (startsWith(cmd, BleChessCommand::Variant))
    {
        bleChessConnection.peripheralForOnline().handleCentralVariant(getCmdParams(cmd));
    }
    else if (startsWith(cmd, BleChessCommand::GetState))
    {
        bleChessConnection.peripheralForOnline().handleCentralGetState();
    }
    else if (startsWith(cmd, BleChessCommand::SetState))
    {
        bleChessConnection.peripheralForOnline().handleCentralSetState();
    }
    else if (startsWith(cmd, BleChessCommand::State))
    {
        bleChessConnection.peripheralForOnline().handleCentralState(getCmdParams(cmd));
    }
    else if (startsWith(cmd, BleChessCommand::LastMove))
    {
        bleChessConnection.peripheralForOnline().handleCentralLastMove(getCmdParams(cmd));
    }
    else if (startsWith(cmd, BleChessCommand::Msg))
    {
        bleChessConnection.peripheralForOnline().handleCentralMsg(getCmdParams(cmd));
    }
    else if (startsWith(cmd, BleChessCommand::UndoOffer))
    {
        bleChessConnection.peripheralForOnline().handleCentralUndoOffer();
    }
    else if (startsWith(cmd, BleChessCommand::Undo))
    {
        bleChessConnection.peripheralForOnline().handleCentralUndo(getCmdParams(cmd));
    }
    else if (startsWith(cmd, BleChessCommand::DrawOffer))
    {
        bleChessConnection.peripheralForOnline().handleCentralDrawOffer();
    }
    else if (startsWith(cmd, BleChessCommand::Side))
    {
        bleChessConnection.peripheralForOnline().handleCentralSide(getCmdParams(cmd));
    }
    else if (startsWith(cmd, BleChessCommand::Time))
    {
        bleChessConnection.peripheralForOnline().handleCentralTime(getCmdParams(cmd));
    }
    else if (startsWith(cmd, BleChessCommand::Score))
    {
        bleChessConnection.peripheralForOnline().handleCentralScore(getCmdParams(cmd));
    }
    else if (startsWith(cmd, BleChessCommand::OptionsBegin))
    {
        bleChessConnection.peripheralForOnline().handleCentralOptionsBegin();
    }
    else if (startsWith(cmd, BleChessCommand::OptionsReset))
    {
        bleChessConnection.peripheralForOnline().handleCentralOptionsReset();
    }
    else if (startsWith(cmd, BleChessCommand::SetOption))
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