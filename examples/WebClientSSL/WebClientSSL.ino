/*
                              Web Client SSL

   This sketch connects to a website with a
   secure HTTPS connection (https://sistemas.micsg.com.br/ethernet-large-get-example)
   using a W5500 module.

                      created on December 18, 2009
                          by David A. Mellis

                        modified on May 5, 2024
                  by Michel Galvão - https://micsg.com.br

*/

// Inclusion of libraries
#include <SPI.h>           // native
#include <EthernetLarge.h> // https://github.com/MicSG-dev/EthernetLarge
#include <SSLClient.h>     // https://github.com/OPEnSLab-OSU/SSLClient
#include "trust_anchors.h" // the local file trust_anchors.h | Use the Generator at https://openslab-osu.github.io/bearssl-certificate-utility/ informing the sites you will access

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

char server[] = "sistemas.micsg.com.br";     // name address for site
char query[] = "GET /ethernet-large-get-example"; // https://sistemas.micsg.com.br/ethernet-large-get-example

// Set the static IP, Mask, DNS, gateway address to use if the DHCP fails to assign
#define MYIPADDR 192, 168, 1, 28
#define MYIPMASK 255, 255, 255, 0
#define MYDNS 192, 168, 1, 1
#define MYGW 192, 168, 1, 1

// Choose the analog pin to get semi-random data from for SSL
// Pick a pin that's not connected or attached to a randomish voltage source
const int rand_pin = A0;

// Initialize the SSL client library
// We input an EthernetClient, our trust anchors, and the analog pin
EthernetClient base_client;
SSLClient client(base_client, TAs, (size_t)TAs_NUM, rand_pin);

// Variables to measure the speed
unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;
bool printWebData = true; // set to false for better speed measurement

void setup()
{
  Serial.begin(115200);

  while (!Serial)
  {
    delay(100);
  };

  Serial.println("Begin Ethernet");

  // You can use Ethernet.init(pin) to configure the CS pin
  // Ethernet.init(10);  // Most Arduino shields
  // Ethernet.init(5);   // MKR ETH Shield
  // Ethernet.init(0);   // Teensy 2.0
  // Ethernet.init(20);  // Teensy++ 2.0
  // Ethernet.init(15);  // ESP8266 with Adafruit FeatherWing Ethernet
  // Ethernet.init(33);  // ESP32 with Adafruit FeatherWing Ethernet
  // Ethernet.init(PA4); // STM32 with w5500
  Ethernet.init(17); // Raspberry Pi Pico with w5500

  Serial.print("Initialize Ethernet with DHCP: ");
  if (Ethernet.begin(mac))
  { // Dynamic IP setup
    Serial.println("DHCP OK!");
  }
  else
  {
    Serial.println("Failed to configure Ethernet using DHCP :(");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware)
    {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true)
      {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF)
    {
      Serial.println("Ethernet cable is not connected.");
    }

    IPAddress ip(MYIPADDR);
    IPAddress dns(MYDNS);
    IPAddress gw(MYGW);
    IPAddress sn(MYIPMASK);
    Ethernet.begin(mac, ip, dns, gw, sn);
    Serial.println("STATIC OK!");
  }
  delay(1000);

  Serial.print("Local IP : ");
  Serial.println(Ethernet.localIP());
  Serial.print("Subnet Mask : ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("Gateway IP : ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("DNS Server : ");
  Serial.println(Ethernet.dnsServerIP());

  Serial.println("Ethernet Successfully Initialized");

  Serial.println();
  Serial.println("Connecting to the site...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 443))
  {
    Serial.print("connected to ");
    // Make a HTTP request:
    client.print(query);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println();
  }
  else
  {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  beginMicros = micros();
}

void loop()
{
  // if there are incoming bytes available
  // from the server, read them and print them:
  int len = client.available();
  if (len > 0)
  {
    byte buffer[80];
    if (len > 80)
      len = 80;
    client.read(buffer, len);
    if (printWebData)
    {
      Serial.write(buffer, len); // show in the serial monitor (slows some boards)
    }
    byteCount = byteCount + len;
  }

  // if the server's disconnected, stop the client:
  if (!client.connected())
  {
    endMicros = micros();
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    Serial.print("Received ");
    Serial.print(byteCount);
    Serial.print(" bytes in ");
    float seconds = (float)(endMicros - beginMicros) / 1000000.0;
    Serial.print(seconds, 4);
    float rate = (float)byteCount / seconds / 1000.0;
    Serial.print(", rate = ");
    Serial.print(rate);
    Serial.print(" kbytes/second");
    Serial.println();

    // do nothing forevermore:
    while (true)
    {
      delay(1);
    }
  }
}