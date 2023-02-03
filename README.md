# Arduino BLE Chess
Library opens posibility to communicate with mobile chess apps via universal CECP protocol

By default `ArduinoBLE` is used. If `NimBLE-Arduino` is used, add to platformio.ini:
```
build_flags = 
	-D USE_NIM_BLE_ARDUINO_LIB
```

## Supported mobile apps
Currently work in progress with: 
- Liches: https://lichess.org/mobile
- WhitePawn: https://khadimfall.com/p/white-pawn
- Chess.com: https://www.chess.com/play/apps

## Candidats
