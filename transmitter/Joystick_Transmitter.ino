#include <SPI.h>
#include <RF24.h>
#include <printf.h>

const int CE = 9;
const int CSN = 10;

const int buzz = 4;
const int battery_pin = A6;

const int left_led = 5;
const int right_led = 6;

float reference_voltage = 5.02;

const int lsw = 8;
const int rsw = 7;
const int lx = A1;
const int ly  =A0;
const int rx = A2;
const int ry = A3;
const int push_button = 3;

int count = 0;

RF24 radio(CE,CSN);

const byte address[6] = "00001";

struct dataPacket{
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

  pinMode(left_led,OUTPUT);
  pinMode(right_led,OUTPUT);
  pinMode(lsw,INPUT_PULLUP);
  pinMode(rsw,INPUT_PULLUP);
  pinMode(push_button,INPUT_PULLUP);
  pinMode(buzz,OUTPUT);

  if(!radio.begin()){
    Serial.println("Nrf not found. Check SPI wiring or module is dead");
    while(1);
  }else{
    Serial.println("Nrf is alive");
  }
  Serial.println("-------Details of module----------");
  radio.printDetails();

   
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_1MBPS);
  radio.openWritingPipe(address);
  radio.stopListening(); //configure it as transmitter

  blink();
  blink();
  
}
void loop(){
  float total = 0;
  for(int i = 0 ;i < 15 ; i++){
    total += analogRead(battery_pin);
    delay(1);
  }

  float analog_value = total/15.0;
  float single_cell = analog_value * (reference_voltage / 1023.0);
  float double_cell = single_cell * 2;
 
  if(double_cell < 6.6 && double_cell > 0.50){
    digitalWrite(left_led,HIGH);
    digitalWrite(right_led,HIGH);
  }else{
    digitalWrite(left_led,LOW);
    digitalWrite(right_led,LOW);
  }

  if(double_cell < 6.0 && double_cell > 0.50){
    tone(buzz,1000);
  }else{
    noTone(buzz);
  }

  // Serial.print("Analog value : ");
  // Serial.print(analog_value);
  // Serial.print(" | Battery voltage :");
  // Serial.println(double_cell);

  dataPacket sendingdata; //Creates an instance of structure

  sendingdata.vlx = analogRead(lx);
  sendingdata.vly = analogRead(ly);
  sendingdata.vrx = analogRead(rx);
  sendingdata.vry = analogRead(ry);

  sendingdata.left_sw = digitalRead(lsw);
  sendingdata.right_sw = digitalRead(rsw);
  sendingdata.vpush_button = digitalRead(push_button);

  radio.write(&sendingdata,sizeof(sendingdata));
  delay(20);

}

void blink(){
  digitalWrite(left_led,HIGH);
  digitalWrite(right_led,HIGH);
  delay(250);
  digitalWrite(left_led,LOW);
  digitalWrite(right_led,LOW);
  delay(250);
}