/*
Copyright (c) 2016, OpenEmu Team

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
* Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
* Neither the name of the OpenEmu Team nor the
names of its contributors may be used to endorse or promote products
derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY OpenEmu Team ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL OpenEmu Team BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#import <Cocoa/Cocoa.h>
#import "OEGCSystemResponderClient.h"
#import "OEWiiSystemResponderClient.h"

#include "Core/GeckoCode.h"
#include "InputCommon/ControllerInterface/Device.h"

class DolHost {
public:
    static DolHost* GetInstance();
    void Init(std::string supportDirectoryPath, std::string cpath);

    bool LoadFileAtPath();
    void RequestStop();
    void Reset();
    void UpdateFrame();
    void Pause(bool);

    void RunCore();
    void SetPresentationFBO(int RenderFBO);
    
    void SetButtonState(int button,int state, int player);
    void SetAxis(int button, float value, int player);

    void setNunchukAccel(double X,double Y,double Z,int player);
    void setWiimoteAccel(double X,double Y,double Z,int player);

    void setIRdata(OEwiimoteIRinfo IRinfo, int player);

    void changeWiimoteExtension(int extension, int player);

    void toggleAudioMute();
    void volumeDown();
    void volumeUp();
    void SetVolume(float value);
    void DisplayMessage(std::string message);

    bool SaveState(std::string saveStateFile);
    bool LoadState(std::string saveStateFile);
    bool setAutoloadFile(std::string saveStateFile);

    void SetCheat(std::string code, std::string value, bool enabled);
    std::vector<Gecko::GeckoCode> gcodes;
    Gecko::GeckoCode gcode;

    private:
    
    static DolHost* m_instance;
    DolHost();

    void GetGameInfo();
    std::string GetRegionOfCountry(int country);
    std::string _gamePath;
    std::string _gameID;
    std::string _gameName;
    std::string _gameRegion;
    bool        _onBoot = true;
    bool        _wiiGame, _wiiWAD;
    bool        _wiiChangeExtension[4] = { false, false, false, false };
    int         _wiiMoteType;

    void SetUpPlayerInputs();
    ciface::Core::Device::Input* m_playerInputs[4][OEWiiButtonCount];
};