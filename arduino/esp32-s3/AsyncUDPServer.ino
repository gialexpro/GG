#include "WiFi.h"
#include "AsyncUDP.h"

#include "arduino_secrets.h"

const char * ssid = SECRET_SSID;
const char * password = SECRET_PASS;
const int channel = 1;
const bool hide_SSID = false;
const int max_connections = 3;


AsyncUDP udp;

IPAddress local_ip(192,168,4,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);


void setup()
{
    delay(3000);
    Serial.begin(115200);
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(local_ip, gateway, subnet);
    WiFi.softAP(ssid, password, channel, hide_SSID, max_connections);
    Serial.println(WiFi.softAPIP());

    
    if(udp.listen(9696)) {
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
            //reply to the client
            packet.printf("Got %u bytes of data", packet.length());
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
