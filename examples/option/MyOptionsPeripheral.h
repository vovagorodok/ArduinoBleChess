#pragma once
#include "../MyPeripheral.h"

template <typename T>
struct Option {
  const BleChessString name;
  const T defaultValue;
  T value;
};

enum Enum : char {
  Value1 = 1,
  Value2 = 2
};
const char* value1 = "value1";
const char* value2 = "value2";

template<typename... Args>
inline BleChessString join(const Args&... args) {
    std::initializer_list<BleChessString> strs{args...};
    BleChessString result;
    bool first = true;
    for (const auto& s: strs) {
        if (!first) result += ' ';
        result += s;
        first = false;
    }
    return result;
}

class MyOptionsPeripheral : public MyPeripheral
{
public:
  void handleCentralFeature(BleChessStringView feature) override {
    sendPeripheralAck(feature == BleChessFeature::Option);
  }
  void handleCentralOptionsBegin() override {
    Serial.println("options begin");

    sendPeripheralOption(
      join(optionBool.name, BleChessOptionType::Bool,
        (optionBool.defaultValue ? BleChessBoolOptionValue::True : BleChessBoolOptionValue::False)));
    sendPeripheralOption(
      join(optionEnum.name, BleChessOptionType::Enum,
        (optionEnum.defaultValue == Value1 ? value1 : value2), value1, value2));
    sendPeripheralOption(
      join(optionStr.name, BleChessOptionType::Str, optionStr.defaultValue));
    sendPeripheralOption(
      join(optionInt.name, BleChessOptionType::Int,
        std::to_string(optionInt.defaultValue).c_str(), std::to_string(0).c_str(), std::to_string(100).c_str()));
    sendPeripheralOption(
      join(optionFloat.name, BleChessOptionType::Float,
        std::to_string(optionFloat.defaultValue).c_str(), std::to_string(0.0).c_str(), std::to_string(20.0).c_str()));

    if (optionBool.value != optionBool.defaultValue)
      sendPeripheralSetOption(join(optionBool.name,
        (optionBool.value ? BleChessBoolOptionValue::True : BleChessBoolOptionValue::False)));
    if (optionEnum.value != optionEnum.defaultValue)
      sendPeripheralSetOption(join(optionEnum.name, (optionEnum.value == Value1 ? value1 : value2)));
    if (optionStr.value != optionStr.defaultValue)
      sendPeripheralSetOption(join(optionStr.name, optionStr.value));
    if (optionInt.value != optionInt.defaultValue)
      sendPeripheralSetOption(join(optionInt.name, std::to_string(optionInt.value).c_str()));
    if (optionFloat.value != optionFloat.defaultValue)
      sendPeripheralSetOption(join(optionFloat.name, std::to_string(optionFloat.value).c_str()));

    sendPeripheralOptionsEnd();
  }
  void handleCentralOptionsReset() override {
    Serial.println("options reset");
    optionBool.value = optionBool.defaultValue;
    optionEnum.value = optionEnum.defaultValue;
    optionStr.value = optionStr.defaultValue;
    optionInt.value = optionInt.defaultValue;
    optionFloat.value = optionFloat.defaultValue;
  }
  void handleCentralSetOption(BleChessStringView option) override {
    Serial.print("option set: ");
    Serial.println(option.data());

    auto spacePos = option.find(' ');
    if (spacePos == BleChessStringView::npos) {
      Serial.println("incorrect option");
      return;
    }
    auto name = option.substr(0, spacePos);
    auto value = option.substr(spacePos + 1);

    if (name == optionBool.name)
      optionBool.value = value == BleChessBoolOptionValue::True;
    else if (name == optionEnum.name)
      optionEnum.value = value == value1 ? Value1 : Value2;
    else if (name == optionStr.name)
      optionStr.value = BleChessString(value);
    else if (name == optionInt.name)
      optionInt.value = std::stoi(value.data());
    else if (name == optionFloat.name)
      optionFloat.value = std::stof(value.data());
  }
  void checkPeripheralInput() {
    if (Serial.available()) {
      BleChessStringView input(Serial.readString().c_str());

      bool isOption = input.find(' ') != BleChessStringView::npos;
      if (isOption) {
        handleCentralSetOption(input);
        sendPeripheralSetOption(BleChessString(input));
      }
      else if (input == "reset") {
        handleCentralOptionsReset();
        sendPeripheralOptionsReset();
      }
      else {
        Serial.print("send move: ");
        Serial.println(input.data());
        sendPeripheralMove(BleChessString(input));
      }
    }
  }

  Option<bool> optionBool = {"bool", false, false};
  Option<Enum> optionEnum = {"enum", Value1, Value1};
  Option<BleChessString> optionStr = {"str", "change me", "change me"};
  Option<int> optionInt = {"int", 1, 1};
  Option<float> optionFloat = {"float", 0.1, 0.1};
};