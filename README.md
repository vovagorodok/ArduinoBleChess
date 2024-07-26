# Arduino BLE Chess
Library opens posibility to communicate with mobile chess apps via Bluetooth

## Supported mobile apps
Currently work in progress with: 
- Liches: https://lichess.org/mobile
- WhitePawn: https://khadimfall.com/p/white-pawn
- Chess.com: https://www.chess.com/play/apps

Initially supported:
- Blichess: https://github.com/vovagorodok/blichess?tab=readme-ov-file#download

## Configuration
By default `ArduinoBLE` is used. For `NimBLE-Arduino` some changes are reguired.  
For PlatformIO. Add to `platformio.ini`:
```
build_flags = 
	-D USE_NIM_BLE_ARDUINO_LIB
```

For Arduino IDE. At boards package installation folder create `platform.local.txt`:
```
compiler.cpp.extra_flags=-D USE_NIM_BLE_ARDUINO_LIB
```