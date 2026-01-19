#include "BleChessProtocol.h"
#include "ArduinoBleChess.h"
#include "BleChessPeripheral.h"
#include "BleChessConnection.h"
#include "BleChessData.h"
#include "BleChessLogger.h"

namespace
{
#define TAG "Protocol"

BleChessStringView getParams(BleChessStringViewInternal cmd)
{
    auto found = cmd.find(' ');
    if (found == BleChessStringViewInternal::npos)
        return BleChessStringView();
    return cmd.substr(found + 1);
}

inline BleChessString join(BleChessStringView cmd, const BleChessString& params)
{
    BleChessString result;
#ifdef BLE_CHESS_BLE_LIB_ARDUINO_BLE
    result.reserve(cmd.size() + 1 + params.length());
    result.concat(cmd.data(), cmd.size());
#else
    result.reserve(cmd.size() + 1 + params.size());
    result.append(cmd.data(), cmd.size());
#endif
    result += ' ';
    result += params;
    return result;
}
}

BleChessProtocol::BleChessProtocol():
    _handleAckMethod(&BleChessPeripheral::handleCentralUnexpectdAck),
    _handlePromotedMethod(&BleChessPeripheral::handleCentralUnexpectdCommand)
{}

void BleChessProtocol::handleCentralCommand(BleChessStringViewInternal cmd)
{
    BLE_CHESS_LOG(TAG, "Receive: %s", cmd.data());

    if (cmd.starts_with(BleChessCommand::Ok))
    {
        (bleChessConnection.getPeripheralForOnline().*_handleAckMethod)(true);
        _handleAckMethod = &BleChessPeripheral::handleCentralUnexpectdAck;
        _handlePromotedMethod = &BleChessPeripheral::handleCentralUnexpectdCommand;
    }
    else if (cmd.starts_with(BleChessCommand::Nok))
    {
        (bleChessConnection.getPeripheralForOnline().*_handleAckMethod)(false);
        _handleAckMethod = &BleChessPeripheral::handleCentralUnexpectdAck;
        _handlePromotedMethod = &BleChessPeripheral::handleCentralUnexpectdCommand;
    }
    else if (cmd.starts_with(BleChessCommand::Move))
    {
        bleChessConnection.getPeripheralForOnline().handleCentralMove(getParams(cmd));
    }
    else if (cmd.starts_with(BleChessCommand::Begin))
    {
        _handleAckMethod = &BleChessPeripheral::handleCentralUnexpectdAck;
        _handlePromotedMethod = &BleChessPeripheral::handleCentralUnexpectdCommand;
        bleChessConnection.getPeripheralForOnline().handleCentralBegin(getParams(cmd));
    }
    else if (cmd.starts_with(BleChessCommand::SetVariant))
    {
        bleChessConnection.getPeripheralForOnline().handleCentralSetVariant(getParams(cmd));
    }
    else if (cmd.starts_with(BleChessCommand::Check))
    {
        bleChessConnection.getPeripheralForOnline().handleCentralCheck(getParams(cmd));
    }
    else if (cmd.starts_with(BleChessCommand::End))
    {
        bleChessConnection.getPeripheralForOnline().handleCentralEnd(getParams(cmd));
    }
    else if (cmd.starts_with(BleChessCommand::Promote))
    {
        (bleChessConnection.getPeripheralForOnline().*_handlePromotedMethod)(getParams(cmd));
        _handleAckMethod = &BleChessPeripheral::handleCentralUnexpectdAck;
        _handlePromotedMethod = &BleChessPeripheral::handleCentralUnexpectdCommand;
    }
    else if (cmd.starts_with(BleChessCommand::Feature))
    {
        bleChessConnection.getPeripheralForOnline().handleCentralFeature(getParams(cmd));
    }
    else if (cmd.starts_with(BleChessCommand::Variant))
    {
        bleChessConnection.getPeripheralForOnline().handleCentralVariant(getParams(cmd));
    }
    else if (cmd.starts_with(BleChessCommand::GetState))
    {
        bleChessConnection.getPeripheralForOnline().handleCentralGetState();
    }
    else if (cmd.starts_with(BleChessCommand::SetState))
    {
        bleChessConnection.getPeripheralForOnline().handleCentralSetState();
    }
    else if (cmd.starts_with(BleChessCommand::State))
    {
        bleChessConnection.getPeripheralForOnline().handleCentralState(getParams(cmd));
    }
    else if (cmd.starts_with(BleChessCommand::LastMove))
    {
        bleChessConnection.getPeripheralForOnline().handleCentralLastMove(getParams(cmd));
    }
    else if (cmd.starts_with(BleChessCommand::Msg))
    {
        bleChessConnection.getPeripheralForOnline().handleCentralMsg(getParams(cmd));
    }
    else if (cmd.starts_with(BleChessCommand::UndoOffer))
    {
        bleChessConnection.getPeripheralForOnline().handleCentralUndoOffer();
    }
    else if (cmd.starts_with(BleChessCommand::Undo))
    {
        bleChessConnection.getPeripheralForOnline().handleCentralUndo(getParams(cmd));
    }
    else if (cmd.starts_with(BleChessCommand::Redo))
    {
        bleChessConnection.getPeripheralForOnline().handleCentralRedo(getParams(cmd));
    }
    else if (cmd.starts_with(BleChessCommand::DrawOffer))
    {
        bleChessConnection.getPeripheralForOnline().handleCentralDrawOffer();
    }
    else if (cmd.starts_with(BleChessCommand::Side))
    {
        bleChessConnection.getPeripheralForOnline().handleCentralSide(getParams(cmd));
    }
    else if (cmd.starts_with(BleChessCommand::Time))
    {
        bleChessConnection.getPeripheralForOnline().handleCentralTime(getParams(cmd));
    }
    else if (cmd.starts_with(BleChessCommand::Score))
    {
        bleChessConnection.getPeripheralForOnline().handleCentralScore(getParams(cmd));
    }
    else if (cmd.starts_with(BleChessCommand::OptionsBegin))
    {
        bleChessConnection.getPeripheralForOnline().handleCentralOptionsBegin();
    }
    else if (cmd.starts_with(BleChessCommand::OptionsReset))
    {
        bleChessConnection.getPeripheralForOnline().handleCentralOptionsReset();
    }
    else if (cmd.starts_with(BleChessCommand::SetOption))
    {
        bleChessConnection.getPeripheralForOnline().handleCentralSetOption(getParams(cmd));
    }
    else
    {
        bleChessConnection.getPeripheralForOnline().handleCentralUnexpectdCommand(cmd);
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
    _handleAckMethod = &BleChessPeripheral::handlePeripheralMoveAck;
    _handlePromotedMethod = &BleChessPeripheral::handlePeripheralMovePromoted;
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
    _handleAckMethod = &BleChessPeripheral::handlePeripheralUndoOfferAck;
    send(BleChessCommand::UndoOffer);
}

void BleChessProtocol::sendPeripheralDrawOffer()
{
    _handleAckMethod = &BleChessPeripheral::handlePeripheralDrawOfferAck;
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
    BLE_CHESS_LOG(TAG, "Send: %s", str.c_str());

    ArduinoBleChess.send(str);
}

BleChessProtocol chessProtocol{};