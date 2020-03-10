#include <SimpleTimerA.h>
#include <PubSubClient.h>
#include <Ethernet.h>
#include <SPI.h>

//USER CONFIGURED SECTION START//
const char* mqtt_server = "your_mqtt_IP";
const int mqtt_port = 1883;
const char *mqtt_user = "mqttlogin";
const char *mqtt_pass = "password";
const char *mqtt_client_name = "MegaAlarmBoard"; // Client connections can't have the same connection name
const char *mqtt_topic = "MEGA_State";
const char *mqtt_command = "MEGA_Cmnd";
uint8_t mac[6] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x06}; //MAC address
//USER CONFIGURED SECTION END//


//Pin Configuration
//Relays
const int Heat_Master = 42;
const int Heat_Kitchen = 43;
const int Heat_Piano = 44;
const int Heat_Office = 45;
const int Heat_Toyroom = 46;
const int Heat_Basement = 47;
const int Heat_Theater = 48;
const int Main_AC = 49;
//Sensors
const int FrontDoor = 22;
const int GarageEntry = 23;
const int KitchenEntry = 24;
const int BasementDoorSouth = 25;
const int BasementDoorNorth = 26;
const int PianoRoomWindows = 27;
const int KitchenWindows = 28;
const int MudroomWindows = 29;
const int MasterWindows = 30;
const int MasterBathWindow = 31;
const int TheaterWindowEast = 32;
const int TheaterWindowWest = 33;
const int GuestBedWindowEast = 34;
const int GuestBedWindowWest = 35;
const int GymWindow = 36;
const int OfficeWindow = 37;
const int BoysWindow = 38;
const int ToyroomWindows = 39;
const int GirlsWindow = 40;
const int GirlsBathWindow = 41;

//Variables
bool boot = true;
//bool oldButton1 = HIGH;
//bool oldButton2 = HIGH;
//bool oldButton3 = HIGH;
//bool oldButton4 = HIGH;
//bool oldButton5 = HIGH;



EthernetClient ethClient;
PubSubClient client(ethClient);
SimpleTimer timer;

void reconnect() 
{
  while (!client.connected()) 
  {
    if (client.connect(mqtt_client_name, mqtt_user, mqtt_pass, mqtt_topic, 1, 0, "Offline"))  
    {
      // Once connected, publish an announcement...
      if(boot == false)
      {
        client.publish(mqtt_topic, "Reconnected"); 
      }
      if(boot == true)
      {
        client.publish(mqtt_topic, "Rebooted");
        boot = false;
      }
      // ... and resubscribe
      client.subscribe(mqtt_command);
    } 
    else 
    {
      Ethernet.maintain();
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) 
{
  payload[length] = '\0';
  String newPayload = String((char *)payload);
  if (topic == mqtt_command) 
  {
    if (newPayload == "Turn On Master Heat")
    {
      digitalWrite(Heat_Master, HIGH);
      client.publish(mqtt_topic, "Master Heat On"); 
    }
    if (newPayload == "Turn Off Master Heat")
    {
      digitalWrite(Heat_Master, LOW);
      client.publish(mqtt_topic, "Master Heat Off"); 
    }
    if (newPayload == "Turn On Kitchen Heat")
    {
      digitalWrite(Heat_Kitchen, HIGH);
      client.publish(mqtt_topic, "Kitchen Heat On"); 
    }
    if (newPayload == "Turn Off Kitchen Heat")
    {
      digitalWrite(Heat_Kitchen, LOW);
      client.publish(mqtt_topic, "Kitchen Heat Off"); 
    }
    if (newPayload == "Turn On Piano Room Heat")
    {
      digitalWrite(Heat_Piano, HIGH);
      client.publish(mqtt_topic, "Piano Room Heat On"); 
    }
    if (newPayload == "Turn Off Piano Room Heat")
    {
      digitalWrite(Heat_Piano, LOW);
      client.publish(mqtt_topic, "Piano Room Heat Off"); 
    }
    if (newPayload == "Turn On Office Heat")
    {
      digitalWrite(Heat_Office, HIGH);
      client.publish(mqtt_topic, "Office Heat On"); 
    }
    if (newPayload == "Turn Off Office Heat")
    {
      digitalWrite(Heat_Office, LOW);
      client.publish(mqtt_topic, "Office Heat Off"); 
    }
    if (newPayload == "Turn On Basement Heat")
    {
      digitalWrite(Heat_Basement, HIGH);
      client.publish(mqtt_topic, "Basement Heat On"); 
    }
    if (newPayload == "Turn Off Basement Heat")
    {
      digitalWrite(Heat_Basement, LOW);
      client.publish(mqtt_topic, "Basement Heat Off"); 
    }
    if (newPayload == "Turn On Theater Heat")
    {
      digitalWrite(Heat_Theater, HIGH);
      client.publish(mqtt_topic, "Theater Heat On"); 
    }
    if (newPayload == "Turn Off Theater Heat")
    {
      digitalWrite(Heat_Theater, LOW);
      client.publish(mqtt_topic, "Theater Heat Off"); 
    }
    if (newPayload == "Turn On Main AC")
    {
      digitalWrite(Main_AC, HIGH);
      client.publish(mqtt_topic, "Main AC On"); 
    }
    if (newPayload == "Turn Off Main AC")
    {
      digitalWrite(Main_AC, LOW);
      client.publish(mqtt_topic, "Main AC Off"); 
    }
    if (newPayload == "Turn On Toyroom Heat")
    {
      digitalWrite(Heat_Toyroom, HIGH);
      client.publish(mqtt_topic, "Toyroom Heat On"); 
    }
    if (newPayload == "Turn Off Toyroom Heat")
    {
      digitalWrite(Heat_Toyroom, LOW);
      client.publish(mqtt_topic, "Toyroom Heat Off"); 
    }
  }
}

void checkButtons()
{
  if(digitalRead(FrontDoor) == LOW)
  {
    client.publish(mqtt_topic, "Front Door Open"); 
    while(digitalRead(FrontDoor) == LOW){};
  }
  if(digitalRead(GarageEntry) == LOW)
  {
    client.publish(mqtt_topic, "Garage Door Open"); 
    while(digitalRead(GarageEntry) == LOW){};
  }
  if(digitalRead(KitchenEntry) == LOW)
  {
    client.publish(mqtt_topic, "Kitchen Door Open"); 
    while(digitalRead(KitchenEntry) == LOW){};
  }
  if(digitalRead(BasementDoorSouth) == LOW)
  {
    client.publish(mqtt_topic, "Basement South Door Open"); 
    while(digitalRead(BasementDoorSouth) == LOW){};
  }
  if(digitalRead(BasementDoorNorth) == LOW)
  {
    client.publish(mqtt_topic, "Basement North Door Open"); 
    while(digitalRead(BasementDoorNorth) == LOW){};
  }
  if(digitalRead(PianoRoomWindows) == LOW)
  {
    client.publish(mqtt_topic, "Piano Room Window Open"); 
    while(digitalRead(PianoRoomWindows) == LOW){};
  }
  if(digitalRead(KitchenWindows) == LOW)
  {
    client.publish(mqtt_topic, "Kitchen Windows Open"); 
    while(digitalRead(KitchenWindows) == LOW){};
  }
  if(digitalRead(MudroomWindows) == LOW)
  {
    client.publish(mqtt_topic, "Mudroom Window Open"); 
    while(digitalRead(MudroomWindows) == LOW){};
  }
  if(digitalRead(MasterWindows) == LOW)
  {
    client.publish(mqtt_topic, "Master Bedroom Windows Open"); 
    while(digitalRead(MasterWindows) == LOW){};
  }
  if(digitalRead(MasterBathWindow) == LOW)
  {
    client.publish(mqtt_topic, "Master Bathroom Window Open"); 
    while(digitalRead(MasterBathWindow) == LOW){};
  }
  if(digitalRead(TheaterWindowEast) == LOW)
  {
    client.publish(mqtt_topic, "Theater East Window Open"); 
    while(digitalRead(TheaterWindowEast) == LOW){};
  }
  if(digitalRead(TheaterWindowWest) == LOW)
  {
    client.publish(mqtt_topic, "Theater West Window Open"); 
    while(digitalRead(TheaterWindowWest) == LOW){};
  }
  if(digitalRead(GuestBedWindowEast) == LOW)
  {
    client.publish(mqtt_topic, "East Guest Bedroom Window Open"); 
    while(digitalRead(GuestBedWindowEast) == LOW){};
  }
  if(digitalRead(GuestBedWindowWest) == LOW)
  {
    client.publish(mqtt_topic, "West Guest Bedroom Window Open"); 
    while(digitalRead(GuestBedWindowWest) == LOW){};
  }
  if(digitalRead(GymWindow) == LOW)
  {
    client.publish(mqtt_topic, "Gym Window Open"); 
    while(digitalRead(GymWindow) == LOW){};
  }
  if(digitalRead(OfficeWindow) == LOW)
  {
    client.publish(mqtt_topic, "Office Window Open"); 
    while(digitalRead(OfficeWindow) == LOW){};
  }
  if(digitalRead(BoysWindow) == LOW)
  {
    client.publish(mqtt_topic, "Boys Window Open"); 
    while(digitalRead(BoysWindow) == LOW){};
  }
  if(digitalRead(ToyroomWindows) == LOW)
  {
    client.publish(mqtt_topic, "Toyroom Window Open"); 
    while(digitalRead(ToyroomWindows) == LOW){};
  }
  if(digitalRead(GirlsWindow) == LOW)
  {
    client.publish(mqtt_topic, "Girls Window Open"); 
    while(digitalRead(GirlsWindow) == LOW){};
  }
  if(digitalRead(GirlsBathWindow) == LOW)
  {
    client.publish(mqtt_topic, "Girls Bathroom Window Open"); 
    while(digitalRead(GirlsBathWindow) == LOW){};
  }
}


void setup() {
  Serial.begin(9600);
    if (Ethernet.begin(mac) == 0) {
    //Serial.println(F("Unable to configure Ethernet using DHCP"));
    for (;;);
  }
  Serial.println(F("Ethernet configured via DHCP"));
  Serial.print("IP address: ");
  Serial.println(Ethernet.localIP());

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  pinMode(FrontDoor, INPUT_PULLUP);
  pinMode(GarageEntry, INPUT_PULLUP);
  pinMode(KitchenEntry, INPUT_PULLUP);
  pinMode(BasementDoorSouth, INPUT_PULLUP);
  pinMode(BasementDoorNorth, INPUT_PULLUP);
  pinMode(PianoRoomWindows, INPUT_PULLUP);
  pinMode(KitchenWindows, INPUT_PULLUP);
  pinMode(MudroomWindows, INPUT_PULLUP);
  pinMode(MasterWindows, INPUT_PULLUP);
  pinMode(MasterBathWindow, INPUT_PULLUP);
  pinMode(TheaterWindowEast, INPUT_PULLUP);
  pinMode(TheaterWindowWest, INPUT_PULLUP);
  pinMode(GuestBedWindowEast, INPUT_PULLUP);
  pinMode(GuestBedWindowWest, INPUT_PULLUP);
  pinMode(GymWindow, INPUT_PULLUP);
  pinMode(OfficeWindow, INPUT_PULLUP);
  pinMode(BoysWindow, INPUT_PULLUP);
  pinMode(ToyroomWindows, INPUT_PULLUP);
  pinMode(GirlsWindow, INPUT_PULLUP);
  pinMode(GirlsBathWindow, INPUT_PULLUP);

  pinMode(Heat_Master, OUTPUT);
  pinMode(Heat_Kitchen, OUTPUT);
  pinMode(Heat_Piano, OUTPUT);
  pinMode(Heat_Office, OUTPUT);
  pinMode(Heat_Toyroom, OUTPUT);
  pinMode(Heat_Basement, OUTPUT);
  pinMode(Heat_Theater, OUTPUT);
  pinMode(Main_AC, OUTPUT);
  
  timer.setInterval(200, checkButtons);
}

void loop() 
{
  if (!client.connected()) 
  {
    reconnect();
  }
  client.loop();
  timer.run();
}
