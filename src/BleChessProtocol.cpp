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
    onAckMethod(&BleChessPeripheral::onCentralUnexpectdAck),
    onPromotedMethod(&BleChessPeripheral::onCentralUnexpectdCommand)
{}

void BleChessProtocol::onCentralCommand(const BleChessString& cmd)
{
    #ifdef BLE_CHESS_DEBUG_LOGS
    Serial.print("DBG: ble chess receive: ");
    Serial.println(cmd.c_str());
    #endif
    if (startsWith(cmd, BleChessCommand::Ok))
    {
        (bleChessConnection.peripheralForOnline().*onAckMethod)(true);
        onAckMethod = &BleChessPeripheral::onCentralUnexpectdAck;
        onPromotedMethod = &BleChessPeripheral::onCentralUnexpectdCommand;
    }
    else if (startsWith(cmd, BleChessCommand::Nok))
    {
        (bleChessConnection.peripheralForOnline().*onAckMethod)(false);
        onAckMethod = &BleChessPeripheral::onCentralUnexpectdAck;
        onPromotedMethod = &BleChessPeripheral::onCentralUnexpectdCommand;
    }
    else if (startsWith(cmd, BleChessCommand::Move))
    {
        bleChessConnection.peripheralForOnline().onCentralMove(getCmdParams(cmd));
    }
    else if (startsWith(cmd, BleChessCommand::Begin))
    {
        onAckMethod = &BleChessPeripheral::onCentralUnexpectdAck;
        onPromotedMethod = &BleChessPeripheral::onCentralUnexpectdCommand;
        bleChessConnection.peripheralForOnline().onCentralBegin(getCmdParams(cmd));
    }
    else if (startsWith(cmd, BleChessCommand::SetVariant))
    {
        bleChessConnection.peripheralForOnline().onCentralSetVariant(getCmdParams(cmd));
    }
    else if (startsWith(cmd, BleChessCommand::Check))
    {
        bleChessConnection.peripheralForOnline().onCentralCheck(getCmdParams(cmd));
    }
    else if (startsWith(cmd, BleChessCommand::End))
    {
        bleChessConnection.peripheralForOnline().onCentralEnd(getCmdParams(cmd));
    }
    else if (startsWith(cmd, BleChessCommand::Promote))
    {
        (bleChessConnection.peripheralForOnline().*onPromotedMethod)(getCmdParams(cmd));
        onAckMethod = &BleChessPeripheral::onCentralUnexpectdAck;
        onPromotedMethod = &BleChessPeripheral::onCentralUnexpectdCommand;
    }
    else if (startsWith(cmd, BleChessCommand::Feature))
    {
        bleChessConnection.peripheralForOnline().onCentralFeature(getCmdParams(cmd));
    }
    else if (startsWith(cmd, BleChessCommand::Variant))
    {
        bleChessConnection.peripheralForOnline().onCentralVariant(getCmdParams(cmd));
    }
    else if (startsWith(cmd, BleChessCommand::GetState))
    {
        bleChessConnection.peripheralForOnline().onCentralGetState();
    }
    else if (startsWith(cmd, BleChessCommand::SetState))
    {
        bleChessConnection.peripheralForOnline().onCentralSetState();
    }
    else if (startsWith(cmd, BleChessCommand::State))
    {
        bleChessConnection.peripheralForOnline().onCentralState(getCmdParams(cmd));
    }
    else if (startsWith(cmd, BleChessCommand::LastMove))
    {
        bleChessConnection.peripheralForOnline().onCentralLastMove(getCmdParams(cmd));
    }
    else if (startsWith(cmd, BleChessCommand::Msg))
    {
        bleChessConnection.peripheralForOnline().onCentralMsg(getCmdParams(cmd));
    }
    else if (startsWith(cmd, BleChessCommand::UndoOffer))
    {
        bleChessConnection.peripheralForOnline().onCentralUndoOffer();
    }
    else if (startsWith(cmd, BleChessCommand::Undo))
    {
        bleChessConnection.peripheralForOnline().onCentralUndo(getCmdParams(cmd));
    }
    else if (startsWith(cmd, BleChessCommand::DrawOffer))
    {
        bleChessConnection.peripheralForOnline().onCentralDrawOffer();
    }
    else if (startsWith(cmd, BleChessCommand::Side))
    {
        bleChessConnection.peripheralForOnline().onCentralSide(getCmdParams(cmd));
    }
    else if (startsWith(cmd, BleChessCommand::Time))
    {
        bleChessConnection.peripheralForOnline().onCentralTime(getCmdParams(cmd));
    }
    else if (startsWith(cmd, BleChessCommand::Score))
    {
        bleChessConnection.peripheralForOnline().onCentralScore(getCmdParams(cmd));
    }
    else if (startsWith(cmd, BleChessCommand::OptionsBegin))
    {
        bleChessConnection.peripheralForOnline().onCentralOptionsBegin();
    }
    else if (startsWith(cmd, BleChessCommand::OptionsReset))
    {
        bleChessConnection.peripheralForOnline().onCentralOptionsReset();
    }
    else if (startsWith(cmd, BleChessCommand::SetOption))
    {
        bleChessConnection.peripheralForOnline().onCentralSetOption(getCmdParams(cmd));
    }
    else
    {
        bleChessConnection.peripheralForOnline().onCentralUnexpectdCommand(cmd);
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
    onAckMethod = &BleChessPeripheral::onPeripheralMoveAck;
    onPromotedMethod = &BleChessPeripheral::onPeripheralMovePromoted;
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

void BleChessProtocol::sendPeripheralUnsyncSetible(const BleChessString& fen)
{
    send(join(BleChessCommand::UnsyncSetible, fen));
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
    onAckMethod = &BleChessPeripheral::onPeripheralUndoOfferAck;
    send(BleChessCommand::UndoOffer);
}

void BleChessProtocol::sendPeripheralDrawOffer()
{
    onAckMethod = &BleChessPeripheral::onPeripheralDrawOfferAck;
    send(BleChessCommand::DrawOffer);
}

void BleChessProtocol::sendPeripheralOptionsEnd()
{
    send(BleChessCommand::OptionsEnd);
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