#include <Arduino.h>
#include <SPI.h>
#include <EthernetLarge.h>

IPAddress ip(192, 168, 0, 1);
EthernetServer server(80);

const uint8_t w5500_cs = 5; // pin CS module W5500

uint8_t mac[] = {
    0xDE,
    0xAD,
    0xBE,
    0xEF,
    0xFE,
    0xED};

void setup()
{
    Ethernet.init(w5500_cs);
    Serial.begin(115200);

    Ethernet.setHostname("Arduino W5500!");

    Serial.print("DHCP:");
    if (Ethernet.begin(mac) == 0)
    {
        Serial.println(" failed.");
    }
    else
    {
        Serial.println(" OK");
    }

    Serial.print("Module ethernet:");
    if (Ethernet.hardwareStatus() == EthernetNoHardware)
    {
        Serial.println(" Not found. Unable to continue.");
        delay(5000);
        // ESP.restart(); // ESP32 restart
        //  or:
        while (1)
        {
        }
    }
    else
    {
        Serial.println(" OK");
    }

    Serial.print("Cable ethernet:");
    if (Ethernet.linkStatus() == LinkOFF)
    {
        Serial.println(" Not connected.");
    }
    else
    {
        Serial.println(" OK");
    }

    server.begin();

    Serial.print("The server is at http://");
    Serial.println(Ethernet.localIP());
}

void loop()
{
    //...
    //...
    //...
}