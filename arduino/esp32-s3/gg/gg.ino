#if ARDUINO_USB_MODE
#warning This sketch should be used when USB is in OTG mode

void setup(){}
void loop(){}

#else

#include <USB.h>
#include <USBHID.h>
#include <USBHIDMouse.h>
#include <USBHIDGamepad.h>
#include <USBHIDKeyboard.h>

USBHIDMouse Mouse;
USBHIDGamepad Gamepad;
USBHIDKeyboard Keyboard;


#include <WiFi.h>
#include <AsyncUDP.h>
#include <map>

#include <Preferences.h>

Preferences prefs;

AsyncUDP udp;

const uint32_t BTTN = 1;
const uint32_t JSTK = 2;
const uint32_t DBTN = 3;
const uint32_t MOUS = 4;
const uint32_t MBTN = 5;
const uint32_t PREF = 6;
const uint32_t HTKY = 7;
const uint32_t KYBD = 8;

std::map<String,uint32_t> inputTypes{
    {"BTTN",BTTN},
    {"JSTK",JSTK},
    {"DBTN",DBTN},
    {"MOUS",MOUS},
    {"MBTN",MBTN},
    {"PREF",PREF},
    {"HTKY",HTKY},
    {"KYBD",KYBD}
};

const uint32_t BUPD = 1;
const uint32_t XJOY = 2;
const uint32_t YJOY = 3;
const uint32_t DBUD = 4;
const uint32_t XMUS = 5;
const uint32_t YMUS = 6;
const uint32_t MBUD = 7;
const uint32_t LCIP = 8;
const uint32_t GWIP = 9;
const uint32_t SNIP = 10;
const uint32_t SSID = 11;
const uint32_t PASS = 12;
const uint32_t HIDD = 13;
const uint32_t CHNL = 14;
const uint32_t CONN = 15;
const uint32_t PORT = 16;
const uint32_t ATOK = 17;
const uint32_t HNTR = 18;
const uint32_t HTAB = 19;
const uint32_t HSTB = 20;
const uint32_t HCPL = 21;
const uint32_t HCMI = 22;
const uint32_t HCTW = 23;
const uint32_t HCTT = 24;
const uint32_t KBMD = 25;
const uint32_t KBKY = 26;
const uint32_t KBRA = 27;
const uint32_t XYMS = 28;
const uint32_t XYJY = 29;
const uint32_t KBKS = 30;
const uint32_t HBKS = 31;


std::map<String,uint32_t> inputKeys{
    {"BUPD",BUPD},
    {"XJOY",XJOY},
    {"YJOY",YJOY},
    {"DBUD",DBUD},
    {"XMUS",XMUS},
    {"YMUS",YMUS},
    {"MBUD",MBUD},
    {"LCIP",LCIP},
    {"GWIP",GWIP},
    {"SNIP",SNIP},
    {"SSID",SSID},
    {"PASS",PASS},
    {"HIDD",HIDD},
    {"CHNL",CHNL},
    {"CONN",CONN},
    {"PORT",PORT},
    {"ATOK",ATOK},
    {"HNTR",HNTR},
    {"HTAB",HTAB},
    {"HSTB",HSTB},
    {"HCPL",HCPL},
    {"HCMI",HCMI},
    {"HCTW",HCTW},
    {"HCTT",HCTT},
    {"KBMD",KBMD},
    {"KBKY",KBKY},
    {"KBRA",KBRA},
    {"XYMS",XYMS},
    {"XYJY",XYJY},
    {"KBKS",KBKS},
    {"HBKS",HBKS}
};

std::map<uint32_t,uint32_t> inputIDType{
    {BUPD,BTTN},
    {XJOY,JSTK},
    {YJOY,JSTK},
    {DBUD,DBTN},
    {XMUS,MOUS},
    {YMUS,MOUS},
    {MBUD,MBTN},
    {LCIP,PREF},
    {GWIP,PREF},
    {SNIP,PREF},
    {SSID,PREF},
    {PASS,PREF},
    {HIDD,PREF},
    {CHNL,PREF},
    {CONN,PREF},
    {PORT,PREF},
    {ATOK,PREF},
    {HNTR,HTKY},
    {HTAB,HTKY},
    {HSTB,HTKY},
    {HCMI,HTKY},
    {HCPL,HTKY},
    {HCTW,HTKY},
    {HCTT,HTKY},
    {KBMD,KYBD},
    {KBKY,KYBD},
    {KBRA,KYBD},
    {XYMS,MOUS},
    {XYJY,JSTK},
    {KBKS,KYBD},
    {HBKS,HTKY}
};


bool cansubstring(String &s,uint start,uint end) {
    return 0<=start&&start<=end&&end<=s.length();
}


bool handleBUPD(bool &ispressed, uint8_t &playerID, uint32_t &inputID) {
    if(ispressed) {
        Gamepad.pressButton(inputID);
    }
    else {
        Gamepad.releaseButton(inputID);
    }
    return true; //no err
}

bool parseBTTN(String &cmd, uint8_t &playerID) {
    if(cmd.length()<=9) {
        Serial.print("inputID not detected");
        Serial.println();
        return false;
    }
    int inputID_end=cmd.indexOf('|',9);
    if(inputID_end==-1) {
        Serial.print("Error getting inputID");
        Serial.println();
        return false;
    }
    uint32_t inputID=uint32_t(cmd.substring(10,inputID_end).toInt());
    if(!cansubstring(cmd, inputID_end+1, inputID_end+1+4)) {
        Serial.print("key not detected");
        Serial.println();
        return false;
    }
    String key = cmd.substring(inputID_end+1,inputID_end+1+4);
    auto key_it = inputKeys.find(key);
    if(key_it == inputKeys.end()) {
        Serial.print("Invalid key for input type ");
        Serial.print("BTTN");
        Serial.println(": ");
        Serial.println(key);
        Serial.print("Valid keys for input type ");
        Serial.print("BTTN");
        Serial.println(": ");
        for(auto &el:inputKeys) {
            if(inputIDType[el.second]==inputTypes["BTTN"]) {
                Serial.println(el.first);
            }
        }
        Serial.println();
        return false;
    }
    switch(key_it->second) {
        case BUPD:
        {
             if(cmd.length()<=inputID_end+1+4+1) {
                Serial.print("ispressed not detected");
                Serial.println();
                return false;
            }
            bool ispressed = (cmd[inputID_end+1+4+1]-'0'==1);
            return handleBUPD(ispressed, playerID, inputID);
        } break;
        default:
        {
            Serial.print("Invalid key for input type ");
            Serial.print("BTTN");
            Serial.println(": ");
            Serial.println(key);
            Serial.print("Valid keys for input type ");
            Serial.print("BTTN");
            Serial.println(": ");
            for(auto &el:inputKeys) {
                if(inputIDType[el.second]==inputTypes["BTTN"]) {
                    Serial.println(el.first);
                }
            }
            Serial.println();
            return false;
        } break;
    }
    return true; //no err
}

uint8_t oldxvaluel=0, oldyvaluel=0;
uint8_t oldxvaluer=0, oldyvaluer=0;
bool handleXJOY(uint8_t &xvalue, uint8_t &playerID, uint32_t &inputID) {
    switch (inputID) {
        case 1: //left
            Gamepad.leftStick(xvalue, oldyvaluel);
            oldxvaluel=xvalue;
            break;
        case 2: //right
            Gamepad.rightStick(xvalue, oldyvaluer);
            oldxvaluer=xvalue;
            break;
    }
    return true; //no err
}

bool handleYJOY(uint8_t &yvalue, uint8_t &playerID, uint32_t &inputID) {
    switch (inputID) {
        case 1: //left
            Gamepad.leftStick(oldxvaluel, yvalue);
            oldyvaluel=yvalue;
            break;
        case 2: //right
            Gamepad.rightStick(oldxvaluer, yvalue);
            oldyvaluer=yvalue;
            break;
    }
    return true; //no err
}

bool handleXYJY(uint8_t &yvalue, uint8_t &xvalue, uint8_t &playerID, uint32_t &inputID) {
    switch (inputID) {
        case 1: //left
            Gamepad.leftStick(xvalue, yvalue);
            oldxvaluel=xvalue;
            oldyvaluel=yvalue;
            break;
        case 2: //right
            Gamepad.rightStick(xvalue, yvalue);
            oldxvaluer=xvalue;
            oldyvaluer=yvalue;
            break;
    }
    return true; //no err
}

bool parseJSTK(String &cmd, uint8_t &playerID) {
    if(cmd.length()<=9) {
        Serial.print("inputID not detected");
        Serial.println();
        return false;
    }
    int inputID_end=cmd.indexOf('|',9);
    if(inputID_end==-1) {
        Serial.print("Error getting inputID");
        Serial.println();
        return false;
    }
    uint32_t inputID=uint32_t(cmd.substring(10,inputID_end).toInt());
    if(!cansubstring(cmd, inputID_end+1, inputID_end+1+4)) {
        Serial.print("key not detected");
        Serial.println();
        return false;
    }
    String key = cmd.substring(inputID_end+1,inputID_end+1+4);
    auto key_it = inputKeys.find(key);
    if(key_it == inputKeys.end()) {
        Serial.print("Invalid key for input type ");
        Serial.print("JSTK");
        Serial.println(": ");
        Serial.println(key);
        Serial.print("Valid keys for input type ");
        Serial.print("JSTK");
        Serial.println(": ");
        for(auto &el:inputKeys) {
            if(inputIDType[el.second]==inputTypes["JSTK"]) {
                Serial.println(el.first);
            }
        }
        Serial.println();
        return false;
    }
    switch(key_it->second) {
        case XJOY:
        {
            int xvalue_end=cmd.indexOf('|',inputID_end+1+4);
            if(xvalue_end==-1) {
                Serial.print("Error getting xvalue");
                Serial.println();
                return false;
            }
            uint8_t xvalue = uint8_t(cmd.substring(inputID_end+1+4+1,xvalue_end).toInt());
            return handleXJOY(xvalue, playerID, inputID);
        } break;
        case YJOY:
        {
            int yvalue_end=cmd.indexOf('|',inputID_end+1+4);
            if(yvalue_end==-1) {
                Serial.print("Error getting yvalue");
                Serial.println();
                return false;
            }
            uint8_t yvalue = uint8_t(cmd.substring(inputID_end+1+4+1,yvalue_end).toInt());
            return handleYJOY(yvalue, playerID, inputID);
        } break;
        case XYJY:
        {
            int xvalue_end=cmd.indexOf('|',inputID_end+1+4);
            if(xvalue_end==-1) {
                Serial.print("Error getting xvalue");
                Serial.println();
                return false;
            }
            uint8_t xvalue = uint8_t(cmd.substring(inputID_end+1+4+1,xvalue_end).toInt());
            int yvalue_end=cmd.indexOf('|',xvalue_end+1);
            if(yvalue_end==-1) {
                Serial.print("Error getting yvalue");
                Serial.println();
                return false;
            }
            uint8_t yvalue = uint8_t(cmd.substring(xvalue_end+1,yvalue_end).toInt());
            return handleXYJY(xvalue, yvalue, playerID, inputID);
        } break;
        default:
            Serial.print("Invalid key for input type ");
            Serial.print("JSTK");
            Serial.println(": ");
            Serial.println(key);
            Serial.print("Valid keys for input type ");
            Serial.print("JSTK");
            Serial.println(": ");
            for(auto &el:inputKeys) {
                if(inputIDType[el.second]==inputTypes["JSTK"]) {
                    Serial.println(el.first);
                }
            }
            Serial.println();
            return false;
            break;

    }
    return true; //no err
}

int8_t hatv=0;
int8_t hath=0;
bool handleDBUD(bool &ispressed, uint8_t &playerID, uint32_t &inputID) {
    int8_t rhatv=0;
    int8_t rhath=0;
    switch (inputID) {
        case HAT_UP:
            rhatv=1;
            break;
        case HAT_DOWN:
            rhatv=-1;
            break;
        case HAT_LEFT:
            rhath=-1;
            break;
        case HAT_RIGHT:
            rhath=1;
            break;
    }
    if(!ispressed) {
        rhatv*=-1;
        rhath*=-1;
    }
    hath+=rhath;
    hath=constrain(hath, -1, 1);
    hatv+=rhatv;
    hatv=constrain(hatv, -1, 1);
    if(hath!=0||hatv!=0||ispressed) {
        switch (hatv) {
            case -1:
                switch (hath) {
                    case -1:
                        Gamepad.hat(HAT_DOWN_LEFT);
                        break;
                    case 0:
                        Gamepad.hat(HAT_DOWN);
                        break;
                    case 1:
                        Gamepad.hat(HAT_DOWN_RIGHT);
                        break;
                }
                break;
            case 0:
                switch (hath) {
                    case -1:
                        Gamepad.hat(HAT_LEFT);
                        break;
                    case 0:
                        Gamepad.hat(HAT_CENTER);
                        break;
                    case 1:
                        Gamepad.hat(HAT_RIGHT);
                        break;
                }
                break;
            case 1:
                switch (hath) {
                    case -1:
                        Gamepad.hat(HAT_UP_LEFT);
                        break;
                    case 0:
                        Gamepad.hat(HAT_UP);
                        break;
                    case 1:
                        Gamepad.hat(HAT_UP_RIGHT);
                        break;
                }
                break;
        }
    }
    return true; //no err
}

bool parseDBTN(String &cmd, uint8_t &playerID) {
    if(cmd.length()<=9) {
        Serial.print("inputID not detected");
        Serial.println();
        return false;
    }
    int inputID_end=cmd.indexOf('|',9);
    if(inputID_end==-1) {
        Serial.print("Error getting inputID");
        Serial.println();
        return false;
    }
    uint32_t inputID=uint32_t(cmd.substring(10,inputID_end).toInt());
    if(!cansubstring(cmd, inputID_end+1, inputID_end+1+4)) {
        Serial.print("key not detected");
        Serial.println();
        return false;
    }
    String key = cmd.substring(inputID_end+1,inputID_end+1+4);
    auto key_it = inputKeys.find(key);
    if(key_it == inputKeys.end()) {
        Serial.print("Invalid key for input type ");
        Serial.print("DBTN");
        Serial.println(": ");
        Serial.println(key);
        Serial.print("Valid keys for input type ");
        Serial.print("DBTN");
        Serial.println(": ");
        for(auto &el:inputKeys) {
            if(inputIDType[el.second]==inputTypes["DBTN"]) {
                Serial.println(el.first);
            }
        }
        Serial.println();
        return false;
    }
    switch(key_it->second) {
        case DBUD:
        {
            if(cmd.length()<=inputID_end+1+4+1) {
                Serial.print("ispressed not detected");
                Serial.println();
                return false;
            }
            bool ispressed = (cmd[inputID_end+1+4+1]-'0'==1);
            return handleDBUD(ispressed, playerID, inputID);
        } break;
        default:
        {
            Serial.print("Invalid key for input type ");
            Serial.print("DBTN");
            Serial.println(": ");
            Serial.println(key);
            Serial.print("Valid keys for input type ");
            Serial.print("DBTN");
            Serial.println(": ");
            for(auto &el:inputKeys) {
                if(inputIDType[el.second]==inputTypes["DBTN"]) {
                    Serial.println(el.first);
                }
            }
            Serial.println();
            return false;
        } break;
    }
    return true; //no err
}


bool handleXMUS(uint8_t &xvalue, uint8_t &playerID, uint32_t &inputID) {
    Mouse.move(xvalue, 0);
    return true; //no err
}

bool handleYMUS(uint8_t &yvalue, uint8_t &playerID, uint32_t &inputID) {
    Mouse.move(0, yvalue);
    return true; //no err
}

bool handleXYMS(uint8_t &xvalue, uint8_t &yvalue, uint8_t &playerID, uint32_t &inputID) {
    Mouse.move(xvalue, yvalue);
    Serial.println(xvalue);
    Serial.println(yvalue);
    return true; //no err
}

bool parseMOUS(String &cmd, uint8_t &playerID) {
    if(cmd.length()<=9) {
        Serial.print("inputID not detected");
        Serial.println();
        return false;
    }
    int inputID_end=cmd.indexOf('|',9);
    if(inputID_end==-1) {
        Serial.print("Error getting inputID");
        Serial.println();
        return false;
    }
    uint32_t inputID=uint32_t(cmd.substring(10,inputID_end).toInt());
    if(!cansubstring(cmd, inputID_end+1, inputID_end+1+4)) {
        Serial.print("key not detected");
        Serial.println();
        return false;
    }
    String key = cmd.substring(inputID_end+1,inputID_end+1+4);
    auto key_it = inputKeys.find(key);
    if(key_it == inputKeys.end()) {
        Serial.print("Invalid key for input type ");
        Serial.print("MOUS");
        Serial.println(": ");
        Serial.println(key);
        Serial.print("Valid keys for input type ");
        Serial.print("MOUS");
        Serial.println(": ");
        for(auto &el:inputKeys) {
            if(inputIDType[el.second]==inputTypes["MOUS"]) {
                Serial.println(el.first);
            }
        }
        Serial.println();
        return false;
    }
    switch(key_it->second) {
        case XMUS:
        {
            int xvalue_end=cmd.indexOf('|',inputID_end+1+4);
            if(xvalue_end==-1) {
                Serial.print("Error getting xvalue");
                Serial.println();
                return false;
            }
            uint8_t xvalue = uint8_t(cmd.substring(inputID_end+1+4+1,xvalue_end).toInt());
            return handleXMUS(xvalue, playerID, inputID);
        } break;
        case YMUS:
        {
            int yvalue_end=cmd.indexOf('|',inputID_end+1+4);
            if(yvalue_end==-1) {
                Serial.print("Error getting yvalue");
                Serial.println();
                return false;
            }
            uint8_t yvalue = uint8_t(cmd.substring(inputID_end+1+4+1,yvalue_end).toInt());
            return handleYMUS(yvalue, playerID, inputID);
        } break;
        case XYMS:
        {
            int xvalue_end=cmd.indexOf('|',inputID_end+1+4);
            if(xvalue_end==-1) {
                Serial.print("Error getting xvalue");
                Serial.println();
                return false;
            }
            uint8_t xvalue = uint8_t(cmd.substring(inputID_end+1+4+1,xvalue_end).toInt());
            int yvalue_end=cmd.indexOf('|',xvalue_end+1);
            if(yvalue_end==-1) {
                Serial.print("Error getting yvalue");
                Serial.println();
                return false;
            }
            uint8_t yvalue = uint8_t(cmd.substring(xvalue_end+1,yvalue_end).toInt());
            return handleXYMS(xvalue, yvalue, playerID, inputID);
        } break;
        default:
            Serial.print("Invalid key for input type ");
            Serial.print("MOUS");
            Serial.println(": ");
            Serial.println(key);
            Serial.print("Valid keys for input type ");
            Serial.print("MOUS");
            Serial.println(": ");
            for(auto &el:inputKeys) {
                if(inputIDType[el.second]==inputTypes["MOUS"]) {
                    Serial.println(el.first);
                }
            }
            Serial.println();
            return false;
            break;

    }
    return true; //no err
}

bool handleMBUD(bool &ispressed, uint8_t &playerID, uint32_t &inputID) {
    if(ispressed) {
        Mouse.press(inputID);
    }
    else {
        Mouse.release(inputID);
    }
    return true; //no err
}

bool parseMBTN(String &cmd, uint8_t &playerID) {
    if(cmd.length()<=9) {
        Serial.print("inputID not detected");
        Serial.println();
        return false;
    }
    int inputID_end=cmd.indexOf('|',9);
    if(inputID_end==-1) {
        Serial.print("Error getting inputID");
        Serial.println();
        return false;
    }
    uint32_t inputID=uint32_t(cmd.substring(10,inputID_end).toInt());
    if(!cansubstring(cmd, inputID_end+1, inputID_end+1+4)) {
        Serial.print("key not detected");
        Serial.println();
        return false;
    }
    String key = cmd.substring(inputID_end+1,inputID_end+1+4);
    auto key_it = inputKeys.find(key);
    if(key_it == inputKeys.end()) {
        Serial.print("Invalid key for input type ");
        Serial.print("MBTN");
        Serial.println(": ");
        Serial.println(key);
        Serial.print("Valid keys for input type ");
        Serial.print("MBTN");
        Serial.println(": ");
        for(auto &el:inputKeys) {
            if(inputIDType[el.second]==inputTypes["MBTN"]) {
                Serial.println(el.first);
            }
        }
        Serial.println();
        return false;
    }
    switch(key_it->second) {
        case MBUD:
        {
             if(cmd.length()<=inputID_end+1+4+1) {
                Serial.print("ispressed not detected");
                Serial.println();
                return false;
            }
            bool ispressed = (cmd[inputID_end+1+4+1]-'0'==1);
            return handleMBUD(ispressed, playerID, inputID);
        } break;
        default:
        {
            Serial.print("Invalid key for input type ");
            Serial.print("BTTN");
            Serial.println(": ");
            Serial.println(key);
            Serial.print("Valid keys for input type ");
            Serial.print("BTTN");
            Serial.println(": ");
            for(auto &el:inputKeys) {
                if(inputIDType[el.second]==inputTypes["BTTN"]) {
                    Serial.println(el.first);
                }
            }
            Serial.println();
            return false;
        } break;
    }
    return true; //no err
}

bool parseip(String &ip, uint8_t &ip0, uint8_t &ip1, uint8_t &ip2, uint8_t &ip3) {
    int ip0_end=ip.indexOf('.');
    if(ip0_end==-1||ip0_end==0) {
        Serial.print("Error getting ip0");
        Serial.println();
        return false;
    }
    ip0=uint8_t(ip.substring(0,ip0_end).toInt());
    int ip1_end=ip.indexOf('.',ip0_end+1);
    if(ip1_end==-1||ip1_end==ip0_end) {
        Serial.print("Error getting ip1");
        Serial.println();
        return false;
    }
    ip1=uint8_t(ip.substring(ip0_end+1,ip1_end).toInt());
    int ip2_end=ip.indexOf('.',ip1_end+1);
    if(ip2_end==-1) {
        Serial.print("Error getting ip2");
        Serial.println();
        return false;
    }
    ip2=uint8_t(ip.substring(ip1_end+1,ip2_end).toInt());
    ip3=uint8_t(ip.substring(ip2_end+1,ip.length()).toInt());
    return true; //no err
}

bool parsePREF(String &cmd, uint8_t &playerID) {
    if(cmd.length()<=9) {
        Serial.print("inputID not detected");
        Serial.println();
        return false;
    }
    int inputID_end=cmd.indexOf('|',9);
    if(inputID_end==-1) {
        Serial.print("Error getting inputID");
        Serial.println();
        return false;
    }
    uint32_t admintok = prefs.getUInt("ATOK", 1234);
    uint32_t inputID=uint32_t(cmd.substring(10,inputID_end).toInt());
    if(inputID!=admintok) {
        Serial.println("Invalid admintoken");
        return false;
    }
    if(!cansubstring(cmd, inputID_end+1, inputID_end+1+4)) {
        Serial.print("key not detected");
        Serial.println();
        return false;
    }
    String key = cmd.substring(inputID_end+1,inputID_end+1+4);
    auto key_it = inputKeys.find(key);
    if(key_it == inputKeys.end()) {
        Serial.print("Invalid key for input type ");
        Serial.print("PREF");
        Serial.println(": ");
        Serial.println(key);
        Serial.print("Valid keys for input type ");
        Serial.print("PREF");
        Serial.println(": ");
        for(auto &el:inputKeys) {
            if(inputIDType[el.second]==inputTypes["PREF"]) {
                Serial.println(el.first);
            }
        }
        Serial.println();
        return false;
    }
    switch(key_it->second) {
        case LCIP:
        {
            int localIP_end=cmd.indexOf('|',inputID_end+1+4);
            if(localIP_end==-1) {
                Serial.println("Error getting localIP");
                return false;
            }
            String localIP = cmd.substring(inputID_end+1+4+1,localIP_end);
            uint8_t ip0 = prefs.getUChar("lip0", 192);
            uint8_t ip1 = prefs.getUChar("lip1", 168);
            uint8_t ip2 = prefs.getUChar("lip2", 4);
            uint8_t ip3 = prefs.getUChar("lip3", 1);
            if(parseip(localIP, ip0, ip1, ip2, ip3)) {
                prefs.putUChar("lip0", ip0);
                prefs.putUChar("lip1", ip1);
                prefs.putUChar("lip2", ip2);
                prefs.putUChar("lip3", ip3);
                return true;
            }
            else {
                return false;
            }
        } break;
        case GWIP:
        {
            int gwIP_end=cmd.indexOf('|',inputID_end+1+4);
            if(gwIP_end==-1) {
                Serial.println("Error getting gatewayIP");
                return false;
            }
            String gwIP = cmd.substring(inputID_end+1+4+1,gwIP_end);
            uint8_t ip0 = prefs.getUChar("gip0", 192);
            uint8_t ip1 = prefs.getUChar("gip1", 168);
            uint8_t ip2 = prefs.getUChar("gip2", 4);
            uint8_t ip3 = prefs.getUChar("gip3", 1);
            if(parseip(gwIP, ip0, ip1, ip2, ip3)) {
                prefs.putUChar("gip0", ip0);
                prefs.putUChar("gip1", ip1);
                prefs.putUChar("gip2", ip2);
                prefs.putUChar("gip3", ip3);
                return true;
            }
            else {
                return false;
            }
        } break;
        case SNIP:
        {
            int snIP_end=cmd.indexOf('|',inputID_end+1+4);
            if(snIP_end==-1) {
                Serial.println("Error getting subnetIP");
                return false;
            }
            String snIP = cmd.substring(inputID_end+1+4+1,snIP_end);
            uint8_t ip0 = prefs.getUChar("sip0", 192);
            uint8_t ip1 = prefs.getUChar("sip1", 168);
            uint8_t ip2 = prefs.getUChar("sip2", 4);
            uint8_t ip3 = prefs.getUChar("sip3", 1);
            if(parseip(snIP, ip0, ip1, ip2, ip3)) {
                prefs.putUChar("sip0", ip0);
                prefs.putUChar("sip1", ip1);
                prefs.putUChar("sip2", ip2);
                prefs.putUChar("sip3", ip3);
                return true;
            }
            else {
                return false;
            }
        } break;
        case SSID:
        {
            int ssid_end=cmd.indexOf('|',inputID_end+1+4);
            if(ssid_end==-1) {
                Serial.println("Error getting SSID");
                return false;
            }
            String ssid = cmd.substring(inputID_end+1+4+1,ssid_end);
            if(ssid.length()>0&&ssid.length()<32) {
                prefs.putString("ssid", ssid);
                return true;
            }
            else {
                Serial.println("Invalid SSID length");
                Serial.println("Should be between 1 and 31");
                return false;
            }
        } break;
        case PASS:
        {
            int pass_end=cmd.indexOf('|',inputID_end+1+4);
            if(pass_end==-1) {
                Serial.println("Error getting password");
                return false;
            }
            String pass = cmd.substring(inputID_end+1+4+1,pass_end);
            if(pass.length()>=8&&pass.length()<63) {
                prefs.putString("pass", pass);
                return true;
            }
            else {
                Serial.println("Invalid password length");
                Serial.println("Should be between 8 and 62");
                return false;
            }
        } break;
        case CHNL:
        {
            int channel_end=cmd.indexOf('|',inputID_end+1+4);
            if(channel_end==-1) {
                Serial.println("Error getting channel");
                return false;
            }
            uint channel = uint(cmd.substring(inputID_end+1+4+1,channel_end).toInt());
            prefs.putUInt("chnl", channel);
            return true;
        } break;
        case CONN:
        {
            int maxconns_end=cmd.indexOf('|',inputID_end+1+4);
            if(maxconns_end==-1) {
                Serial.println("Error getting maxconnections");
                return false;
            }
            uint maxconns = uint(cmd.substring(inputID_end+1+4+1,maxconns_end).toInt());
            prefs.putUInt("conn", maxconns);
            return true;
        } break;
        case ATOK:
        {
            int atok_end=cmd.indexOf('|',inputID_end+1+4);
            if(atok_end==-1) {
                Serial.println("Error getting admin token");
                return false;
            }
            uint32_t atok = uint(cmd.substring(inputID_end+1+4+1,atok_end).toInt());
            prefs.putUInt("atok", atok);
            return true;
        } break;
        case PORT:
        {
            int port_end=cmd.indexOf('|',inputID_end+1+4);
            if(port_end==-1) {
                Serial.println("Error getting port");
                return false;
            }
            uint port = uint(cmd.substring(inputID_end+1+4+1,port_end).toInt());
            prefs.putUInt("port", port);
            return true;
        } break;
        case HIDD:
        {
            if(cmd.length()<=inputID_end+1+4+1) {
                Serial.print("ishidden not detected");
                Serial.println();
                return false;
            }
            bool ishidden = (cmd[inputID_end+1+4+1]-'0'==1);
            prefs.putBool("hidd", ishidden);
            return true;
        } break;
        default:
        {
            Serial.print("Invalid key for input type ");
            Serial.print("PREF");
            Serial.println(": ");
            Serial.println(key);
            Serial.print("Valid keys for input type ");
            Serial.print("PREF");
            Serial.println(": ");
            for(auto &el:inputKeys) {
                if(inputIDType[el.second]==inputTypes["PREF"]) {
                    Serial.println(el.first);
                }
            }
            Serial.println();
            return false;
        } break;
    }
    return true; //no err
}





bool parseHTKY(String &cmd, uint8_t &playerID) {
    if(cmd.length()<=9) {
        Serial.print("inputID not detected");
        Serial.println();
        return false;
    }
    int inputID_end=cmd.indexOf('|',9);
    if(inputID_end==-1) {
        Serial.print("Error getting inputID");
        Serial.println();
        return false;
    }
    uint32_t inputID=uint32_t(cmd.substring(10,inputID_end).toInt());
    if(!cansubstring(cmd, inputID_end+1, inputID_end+1+4)) {
        Serial.print("key not detected");
        Serial.println();
        return false;
    }
    String key = cmd.substring(inputID_end+1,inputID_end+1+4);
    auto key_it = inputKeys.find(key);
    if(key_it == inputKeys.end()) {
        Serial.print("Invalid key for input type ");
        Serial.print("HTKY");
        Serial.println(": ");
        Serial.println(key);
        Serial.print("Valid keys for input type ");
        Serial.print("HTKY");
        Serial.println(": ");
        for(auto &el:inputKeys) {
            if(inputIDType[el.second]==inputTypes["HTKY"]) {
                Serial.println(el.first);
            }
        }
        Serial.println();
        return false;
    }
    switch(key_it->second) {
        case HNTR:
        {
            Keyboard.write(KEY_RETURN);
            return true;
        } break;
        case HTAB:
        {
            Keyboard.write(KEY_TAB);
            return true;
        } break;
        case HSTB:
        {
            Keyboard.press(KEY_LEFT_SHIFT);
            Keyboard.press(KEY_TAB);
            Keyboard.releaseAll();
            return true;
        } break;
        case HCMI:
        {
            Keyboard.press(KEY_LEFT_CTRL);
            Keyboard.press('-');
            Keyboard.releaseAll();
            return true;
        } break;
        case HCPL:
        {
            Keyboard.press(KEY_LEFT_CTRL);
            Keyboard.press('+');
            Keyboard.releaseAll();
            return true;
        } break;
        case HCTT:
        {
            Keyboard.press(KEY_LEFT_CTRL);
            Keyboard.press('t');
            Keyboard.releaseAll();
            return true;
        } break;
        case HCTW:
        {
            Keyboard.press(KEY_LEFT_CTRL);
            Keyboard.press('w');
            Keyboard.releaseAll();
            return true;
        } break;
        case HBKS:
        {
            Keyboard.write(KEY_BACKSPACE);
            return true;
        } break;
        default:
        {
            Serial.print("Invalid key for input type ");
            Serial.print("HTKY");
            Serial.println(": ");
            Serial.println(key);
            Serial.print("Valid keys for input type ");
            Serial.print("HTKY");
            Serial.println(": ");
            for(auto &el:inputKeys) {
                if(inputIDType[el.second]==inputTypes["HTKY"]) {
                    Serial.println(el.first);
                }
            }
            Serial.println();
            return false;
        } break;
    }
    return true; //no err
}



void uint8_t_to_bools(uint8_t x, bool &_0, bool &_1, bool &_2, bool &_3, bool &_4, bool &_5, bool &_6, bool &_7) {
    _0=x&1; x>>=1;
    _1=x&1; x>>=1;
    _2=x&1; x>>=1;
    _3=x&1; x>>=1;
    _4=x&1; x>>=1;
    _5=x&1; x>>=1;
    _6=x&1; x>>=1;
    _7=x&1; x>>=1;
}

bool handleKBMD(uint8_t &mods, uint8_t &playerID, uint32_t &inputID) {
    bool lctrl=false;
    bool lshift=false;
    bool lalt=false;
    bool lgui=false;
    bool rctrl=false;
    bool rshift=false;
    bool ralt=false;
    bool rgui=false;
    uint8_t_to_bools(mods, lctrl, lshift, lalt, lgui, rctrl, rshift, ralt, rgui);
    if(lctrl)   { Keyboard.press(KEY_LEFT_CTRL);   }
    if(lshift)  { Keyboard.press(KEY_LEFT_SHIFT);  }
    if(lalt)    { Keyboard.press(KEY_LEFT_ALT);    }
    if(lgui)    { Keyboard.press(KEY_LEFT_GUI);    }
    if(rctrl)   { Keyboard.press(KEY_RIGHT_CTRL);  }
    if(rshift)  { Keyboard.press(KEY_RIGHT_SHIFT); }
    if(ralt)    { Keyboard.press(KEY_RIGHT_ALT);   }
    if(rgui)    { Keyboard.press(KEY_RIGHT_GUI);   }
    return true; //no err
}

bool handleKBKY(char &key, uint8_t &playerID, uint32_t &inputID) {
    Keyboard.write(key);
    return true; //no err
}

bool handleKBKS(String &keys, uint8_t &playerID, uint32_t &inputID) {
    if(keys.length()!=inputID) {
        Serial.println("\""+keys+"\".length()!="+inputID);
        return false;
    }
    Keyboard.print(keys);
    return true; //no err
}

bool parseKYBD(String &cmd, uint8_t &playerID) {
    if(cmd.length()<=9) {
        Serial.print("inputID not detected");
        Serial.println();
        return false;
    }
    int inputID_end=cmd.indexOf('|',9);
    if(inputID_end==-1) {
        Serial.print("Error getting inputID");
        Serial.println();
        return false;
    }
    uint32_t inputID=uint32_t(cmd.substring(10,inputID_end).toInt());
    if(!cansubstring(cmd, inputID_end+1, inputID_end+1+4)) {
        Serial.print("key not detected");
        Serial.println();
        return false;
    }
    String key = cmd.substring(inputID_end+1,inputID_end+1+4);
    auto key_it = inputKeys.find(key);
    if(key_it == inputKeys.end()) {
        Serial.print("Invalid key for input type ");
        Serial.print("KYBD");
        Serial.println(": ");
        Serial.println(key);
        Serial.print("Valid keys for input type ");
        Serial.print("KYBD");
        Serial.println(": ");
        for(auto &el:inputKeys) {
            if(inputIDType[el.second]==inputTypes["KYBD"]) {
                Serial.println(el.first);
            }
        }
        Serial.println();
        return false;
    }
    switch(key_it->second) {
        case KBMD:
        {
            int mods_end=cmd.indexOf('|',inputID_end+1+4);
            if(mods_end==-1) {
                Serial.print("Error getting mods");
                Serial.println();
                return false;
            }
            uint8_t mods = uint8_t(cmd.substring(inputID_end+1+4+1,mods_end).toInt());
            return handleKBMD(mods, playerID, inputID);
        } break;
        case KBKY:
        {
            if(cmd.length()<=inputID_end+1+4+1) {
              Serial.print("key not detected");
              Serial.println();
              return false;
            }
            char key=cmd[inputID_end+1+4+1];
            return handleKBKY(key, playerID, inputID);
        } break;
        case KBRA:
        {
            Keyboard.releaseAll();
        } break;
        case KBKS:
        {
            int keys_end=cmd.lastIndexOf('|');
            if(keys_end==-1) {
                Serial.print("Error getting keys");
                Serial.println();
                return false;
            }
            String keys = cmd.substring(inputID_end+1+4+1,keys_end);
            return handleKBKS(keys, playerID, inputID);
        } break;
        default:
        {
            Serial.print("Invalid key for input type ");
            Serial.print("KYBD");
            Serial.println(": ");
            Serial.println(key);
            Serial.print("Valid keys for input type ");
            Serial.print("KYBD");
            Serial.println(": ");
            for(auto &el:inputKeys) {
                if(inputIDType[el.second]==inputTypes["KYBD"]) {
                    Serial.println(el.first);
                }
            }
            Serial.println();
            return false;
        } break;
    }
    return true; //no err
}





void parseinit(String &cmd) {
    if(cmd.length()<20) {
        Serial.print("Invalid command length: ");
        Serial.println(cmd.length());
        Serial.println();
        return;
    }
    if(!cansubstring(cmd, 0, 2)) {
        Serial.print("Protocol not detected");
        Serial.println();
        return;
    }
    if(cmd.substring(0,2)!="GG") {
        Serial.print("Invalid protocol");
        Serial.println();
        return;
    }
    if(cmd.length()<4) {
        Serial.print("playerID not detected");
        Serial.println();
        return;
    }
    uint8_t playerID=cmd[3]-'0';
    if(!cansubstring(cmd, 5, 9)) {
        Serial.print("inputType not detected");
        Serial.println();
        return;
    }
    String inputType = cmd.substring(5,9);
    auto inputType_it = inputTypes.find(inputType);
    if(inputType_it == inputTypes.end()) {
        Serial.print("Invalid input type: ");
        Serial.println(inputType);
        Serial.println("Valid types: ");
        for(auto &el:inputTypes) {
            Serial.println(el.first);
        }
        Serial.println();
        return;
    }
    switch(inputType_it->second) {
        case BTTN:
            parseBTTN(cmd, playerID);
            break;
        case JSTK:
            parseJSTK(cmd, playerID);
            break;
        case DBTN:
            parseDBTN(cmd, playerID);
            break;
        case MOUS:
            parseMOUS(cmd, playerID);
            break;
        case MBTN:
            parseMBTN(cmd, playerID);
            break;
        case PREF:
            if(parsePREF(cmd, playerID)) {
                ESP.restart();
            }
            break;
        case HTKY:
            parseHTKY(cmd, playerID);
            break;
        case KYBD:
            parseKYBD(cmd, playerID);
            break;
    }
    return;
}

void setup()
{
    delay(3000);
    Serial.begin(115200);
    prefs.begin("gg");

    uint32_t admintok = prefs.getUInt("atok", 1234);


    uint8_t lip0 = prefs.getUChar("lip0", 192);
    uint8_t lip1 = prefs.getUChar("lip1", 168);
    uint8_t lip2 = prefs.getUChar("lip2", 4);
    uint8_t lip3 = prefs.getUChar("lip3", 1);

    uint8_t gip0 = prefs.getUChar("gip0", 192);
    uint8_t gip1 = prefs.getUChar("gip1", 168);
    uint8_t gip2 = prefs.getUChar("gip2", 4);
    uint8_t gip3 = prefs.getUChar("gip3", 1);

    uint8_t sip0 = prefs.getUChar("sip0", 255);
    uint8_t sip1 = prefs.getUChar("sip1", 255);
    uint8_t sip2 = prefs.getUChar("sip2", 255);
    uint8_t sip3 = prefs.getUChar("sip3", 0);

    String ssid = prefs.getString("ssid", String("ggwifi"));
    String password = prefs.getString("pass", String("password"));

    uint channel = prefs.getUInt("chnl", 1);
    bool hide_SSID = prefs.getBool("hidd", false);
    uint max_connections = prefs.getUInt("conn", 5);

    uint port = prefs.getUInt("port", 9696);

    IPAddress local_ip(lip0,lip1,lip2,lip3);
    IPAddress gateway(gip0,gip1,gip2,gip3);
    IPAddress subnet(sip0,sip1,sip2,sip3);
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(local_ip, gateway, subnet);
    WiFi.softAP(ssid, password, channel, hide_SSID, max_connections);
    Serial.println(WiFi.softAPIP());

    
    Mouse.begin();
    Gamepad.begin();
    Keyboard.begin();
    USB.begin();
    
    if(udp.listen(port)) {
        Serial.println("UDP Listening");
        udp.onPacket([](AsyncUDPPacket packet) {
            Serial.print("UDP Packet Type: ");
            Serial.print(packet.isBroadcast()?"Broadcast":packet.isMulticast()?"Multicast":"Unicast");
            Serial.print(", From: ");
            Serial.print(packet.remoteIP());
            Serial.print(":");
            Serial.print(packet.remotePort());
            Serial.print(", To: ");
            Serial.print(packet.localIP());
            Serial.print(":");
            Serial.print(packet.localPort());
            Serial.print(", Length: ");
            Serial.print(packet.length());
            Serial.print(", Data: ");
            Serial.write(packet.data(), packet.length());
            Serial.println();
            String cmd(packet.data(),packet.length());
            //cmd.trim()

            parseinit(cmd);

            Serial.println();
            //reply to the client
            //packet.printf("Got %u bytes of data", packet.length());
        });
    }
}

void loop()
{
    delay(3000);
    //Send broadcast
    //udp.broadcast("Anyone here?");
    Serial.println(WiFi.softAPIP());
}


#endif /* ARDUINO_USB_MODE */