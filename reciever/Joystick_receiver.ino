#include <RF24.h>
#include <SPI.h>
#include <printf.h>

const int CE = 9;
const int CSN = 10;

int value = 0;

RF24 radio(CE,CSN);

const byte address[6] = "00001";

struct dataPacket {
  int vlx;
  int vly;
  int vrx;
  int vry;

  bool left_sw;
  bool right_sw;
  bool vpush_button;
};

void setup(){
  Serial.begin(115200);
  printf_begin();
  delay(1000);

  if(!radio.begin()){
    Serial.println("Nrf not found. Check SPI wiring or else your module is dead");
    while(1);
  }
  
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_1MBPS);
  radio.openReadingPipe(1,address);
  radio.startListening();
  
}
void loop(){
  if(radio.available()){

    dataPacket incomingdata;

    radio.read(&incomingdata,sizeof(incomingdata));
    Serial.print(incomingdata.vlx );  Serial.print(" ");
    Serial.print(incomingdata.vly );  Serial.print(" ");
    Serial.print(incomingdata.vrx );  Serial.print(" ");
    Serial.print(incomingdata.vry );  Serial.print(" ");

    Serial.print(incomingdata.left_sw );  Serial.print(" ");
    Serial.print(incomingdata.right_sw ); Serial.print(" ");
    Serial.println(incomingdata.vpush_button);
  }
}