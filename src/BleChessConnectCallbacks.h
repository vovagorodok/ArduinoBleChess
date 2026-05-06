#pragma once

class BleChessConnectCallbacks {
 public:
    virtual void handleConnect() {}
    virtual void handleDisconnect() {}

    virtual ~BleChessConnectCallbacks() = default;
};
