#include "BleChessData.h"

constexpr const char* BleChessFeature::GetState;
constexpr const char* BleChessFeature::SetState;
constexpr const char* BleChessFeature::StateStream;
constexpr const char* BleChessFeature::LastMove;
constexpr const char* BleChessFeature::Check;
constexpr const char* BleChessFeature::Undo;
constexpr const char* BleChessFeature::Moved;
constexpr const char* BleChessFeature::Msg;
constexpr const char* BleChessFeature::Resign;
constexpr const char* BleChessFeature::UndoOffer;
constexpr const char* BleChessFeature::DrawOffer;
constexpr const char* BleChessFeature::Side;
constexpr const char* BleChessFeature::Time;
constexpr const char* BleChessFeature::Score;
constexpr const char* BleChessFeature::Option;
constexpr const char* BleChessFeature::DrawReason;
constexpr const char* BleChessFeature::VariantReason;

constexpr const char* BleChessVariant::Standard;
constexpr const char* BleChessVariant::Chess960;
constexpr const char* BleChessVariant::ThreeCheck;
constexpr const char* BleChessVariant::Atomic;
constexpr const char* BleChessVariant::KingOfTheHill;
constexpr const char* BleChessVariant::AntiChess;
constexpr const char* BleChessVariant::Horde;
constexpr const char* BleChessVariant::RacingKings;
constexpr const char* BleChessVariant::CrazyHouse;
constexpr const char* BleChessVariant::Unsupported;

constexpr const char* BleChessEndReason::Undefined;
constexpr const char* BleChessEndReason::Checkmate;
constexpr const char* BleChessEndReason::Draw;
constexpr const char* BleChessEndReason::Timeout;
constexpr const char* BleChessEndReason::Resign;
constexpr const char* BleChessEndReason::Abort;

constexpr const char* BleChessDrawReason::DrawOffer;
constexpr const char* BleChessDrawReason::Stalemate;
constexpr const char* BleChessDrawReason::ThreefoldRepetition;
constexpr const char* BleChessDrawReason::FiftyMove;
constexpr const char* BleChessDrawReason::InsufficientMaterial;
constexpr const char* BleChessDrawReason::DeadPosition;

constexpr const char* BleChessVariantReason::ThreeCheck;
constexpr const char* BleChessVariantReason::KingOfTheHill;

constexpr const char* BleChessCommand::Ok;
constexpr const char* BleChessCommand::Nok;
constexpr const char* BleChessCommand::Feature;
constexpr const char* BleChessCommand::Variant;
constexpr const char* BleChessCommand::SetVariant;
constexpr const char* BleChessCommand::Begin;
constexpr const char* BleChessCommand::State;
constexpr const char* BleChessCommand::Sync;
constexpr const char* BleChessCommand::Unsync;
constexpr const char* BleChessCommand::Move;
constexpr const char* BleChessCommand::End;
constexpr const char* BleChessCommand::Promote;
constexpr const char* BleChessCommand::Err;
constexpr const char* BleChessCommand::Drop;
constexpr const char* BleChessCommand::GetState;
constexpr const char* BleChessCommand::SetState;
constexpr const char* BleChessCommand::UnsyncSettable;
constexpr const char* BleChessCommand::LastMove;
constexpr const char* BleChessCommand::Check;
constexpr const char* BleChessCommand::Undo;
constexpr const char* BleChessCommand::Moved;
constexpr const char* BleChessCommand::Msg;
constexpr const char* BleChessCommand::Resign;
constexpr const char* BleChessCommand::UndoOffer;
constexpr const char* BleChessCommand::DrawOffer;
constexpr const char* BleChessCommand::Side;
constexpr const char* BleChessCommand::Time;
constexpr const char* BleChessCommand::Score;
constexpr const char* BleChessCommand::OptionsBegin;
constexpr const char* BleChessCommand::Option;
constexpr const char* BleChessCommand::OptionsEnd;
constexpr const char* BleChessCommand::OptionsReset;
constexpr const char* BleChessCommand::SetOption;

constexpr const char* BleChessSide::White;
constexpr const char* BleChessSide::Black;
constexpr const char* BleChessSide::Both;

constexpr const char* BleChessOptionType::Bool;
constexpr const char* BleChessOptionType::Enum;
constexpr const char* BleChessOptionType::Str;
constexpr const char* BleChessOptionType::Int;
constexpr const char* BleChessOptionType::Float;

constexpr const char* BleChessBoolOptionValue::False;
constexpr const char* BleChessBoolOptionValue::True;