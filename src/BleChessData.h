#pragma once

struct BleChessFeature {
    constexpr static const char* GetState = "get_state";
    constexpr static const char* SetState = "set_state";
    constexpr static const char* SubmoveState = "submove_state";
    constexpr static const char* LastMove = "last_move";
    constexpr static const char* Check = "check";
    constexpr static const char* UndoRedo = "undo_redo";
    constexpr static const char* Moved = "moved";
    constexpr static const char* Msg = "msg";
    constexpr static const char* Resign = "resign";
    constexpr static const char* UndoOffer = "undo_offer";
    constexpr static const char* DrawOffer = "draw_offer";
    constexpr static const char* Side = "side";
    constexpr static const char* Time = "time";
    constexpr static const char* Score = "score";
    constexpr static const char* Option = "option";
    constexpr static const char* DrawReason = "draw_reason";
    constexpr static const char* VariantReason = "variant_reason";
};

struct BleChessVariant {
    constexpr static const char* Standard = "standard";
    constexpr static const char* Chess960 = "chess_960";
    constexpr static const char* ThreeCheck = "3_check";
    constexpr static const char* Atomic = "atomic";
    constexpr static const char* KingOfTheHill = "king_of_the_hill";
    constexpr static const char* AntiChess = "anti_chess";
    constexpr static const char* Horde = "horde";
    constexpr static const char* RacingKings = "racing_kings";
    constexpr static const char* CrazyHouse = "crazy_house";
    constexpr static const char* Unsupported = "unsupported";
};

struct BleChessEndReason {
    constexpr static const char* Undefined = "undefined";
    constexpr static const char* Checkmate = "checkmate";
    constexpr static const char* Draw = "draw";
    constexpr static const char* Timeout = "timeout";
    constexpr static const char* Resign = "resign";
    constexpr static const char* Abort = "abort";
};

struct BleChessDrawReason {
    constexpr static const char* DrawOffer = BleChessFeature::DrawOffer;
    constexpr static const char* Stalemate = "stalemate";
    constexpr static const char* ThreefoldRepetition = "threefold_repetition";
    constexpr static const char* FiftyMove = "fifty_move";
    constexpr static const char* InsufficientMaterial = "insufficient_material";
    constexpr static const char* DeadPosition = "dead_position";
};

struct BleChessVariantReason {
    constexpr static const char* ThreeCheck = BleChessVariant::ThreeCheck;
    constexpr static const char* KingOfTheHill = BleChessVariant::KingOfTheHill;
};

struct BleChessCommand {
    constexpr static const char* Ok = "ok";
    constexpr static const char* Nok = "nok";
    constexpr static const char* Feature = "feature";
    constexpr static const char* Variant = "variant";
    constexpr static const char* SetVariant = "set_variant";
    constexpr static const char* Begin = "begin";
    constexpr static const char* State = "state";
    constexpr static const char* Sync = "sync";
    constexpr static const char* Unsync = "unsync";
    constexpr static const char* Move = "move";
    constexpr static const char* End = "end";
    constexpr static const char* Promote = "promote";
    constexpr static const char* Err = "err";
    constexpr static const char* Drop = "drop";
    constexpr static const char* GetState = BleChessFeature::GetState;
    constexpr static const char* SetState = BleChessFeature::SetState;
    constexpr static const char* UnsyncSettable = "unsync_settable";
    constexpr static const char* LastMove = BleChessFeature::LastMove;
    constexpr static const char* Check = BleChessFeature::Check;
    constexpr static const char* Undo = "undo";
    constexpr static const char* Redo = "redo";
    constexpr static const char* Moved = BleChessFeature::Moved;
    constexpr static const char* Msg = BleChessFeature::Msg;
    constexpr static const char* Resign = BleChessFeature::Resign;
    constexpr static const char* UndoOffer = BleChessFeature::UndoOffer;
    constexpr static const char* DrawOffer = BleChessFeature::DrawOffer;
    constexpr static const char* Side = BleChessFeature::Side;
    constexpr static const char* Time = BleChessFeature::Time;
    constexpr static const char* Score = BleChessFeature::Score;
    constexpr static const char* OptionsBegin = "options_begin";
    constexpr static const char* Option = BleChessFeature::Option;
    constexpr static const char* OptionsEnd = "options_end";
    constexpr static const char* OptionsReset = "options_reset";
    constexpr static const char* SetOption = "set_option";
};

struct BleChessSide {
    constexpr static const char* White = "w";
    constexpr static const char* Black = "b";
    constexpr static const char* Both = "?";
};

struct BleChessOptionType {
    constexpr static const char* Bool = "bool";
    constexpr static const char* Enum = "enum";
    constexpr static const char* Str = "str";
    constexpr static const char* Int = "int";
    constexpr static const char* Float = "float";
};

struct BleChessBoolOptionValue {
    constexpr static const char* False = "false";
    constexpr static const char* True = "true";
};