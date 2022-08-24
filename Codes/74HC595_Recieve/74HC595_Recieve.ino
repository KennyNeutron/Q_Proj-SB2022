//74HC595 Rcv
//by: KennyNeutron
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

#define buzzPin 4

#define ser   5   //d_in
#define rclk  7   //lat
#define srclk 6   //clk


byte TimeMin = 0;
byte TimeSec = 0;
byte TimeMil = 0;
byte SCSec = 0;
byte SCMil = 0;

byte GTime_Min_Tens = 0;
byte GTime_Min_Ones = 0;
byte GTime_Sec_Tens = 0;
byte GTime_Sec_Ones = 0;
byte GTime_Millis = 0;
byte SC_Tens = 0;
byte SC_Ones = 0;
byte SC_millis;


byte HomeScore = 0;
byte GuestScore = 0;
byte HScore_Hund = 0;
byte HScore_Tens = 0;
byte HScore_Ones = 6;
byte GScore_Hund = 0;
byte GScore_Tens = 0;
byte GScore_Ones = 0;

byte HFoul = 0;
byte GFoul = 0;
byte HTOut = 0;
byte GTOut = 0;

byte Period = 1;
byte BallPos = 0;

bool SET = false;
bool SET_toggle = false;
byte toSET = 0;

bool winner_avail = false;
bool WINNER = false; //WINNER true=HOME  |   false=GUEST
byte win_toggle = 0;

bool buzzer=false;

void setup() {
  pinMode(buzzPin, OUTPUT);
  pinMode(ser, OUTPUT);
  pinMode(rclk, OUTPUT);
  pinMode(srclk, OUTPUT);


  digitalWrite(ser, 0);
  digitalWrite(rclk, 0);
  digitalWrite(srclk, 0);

  //printSEG(8);
  digitalWrite(buzzPin,0);

  Serial.begin(115200);
  Serial.println("START");
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  delay(1000);

  printSEG0(SC_Tens);
  printSEG0(SC_Ones);

  printSEG0(GTime_Min_Tens);
  printSEG0(GTime_Min_Ones);
  printSEG0(GTime_Sec_Tens);
  printSEG0(GTime_Sec_Ones);

  printSEG0(HScore_Tens);
  printSEG0(HScore_Ones);

  printSEG0(GScore_Tens);
  printSEG0(GScore_Ones);
  printSEG0(Period);
  printSEG0(HFoul);
  printSEG0(GFoul);
  printSEG0(HTOut);
  printSEG0(GTOut);
}

void loop() {
  if (radio.available()) {
    char text[7] = "";
    radio.read(&text, sizeof(text));
    //Serial.print(String(text));

    //    byte data;
    //    for (byte a = 0; a <= 14; a++) {
    //      data = text[a];
    //      Serial.println(a + ":" + String(data));
    //    }
    //    delay(50);
    /*
        Serial.println("text[0]:" + String(text[0]));
        Serial.println("text[1]:" + String(int(text[1])));
        Serial.println("text[2]:" + String(int(text[2])));
        Serial.println("text[3]:" + String(int(text[3])));
        Serial.println("text[4]:" + String(int(text[4])));
        Serial.println("text[5]:" + String(int(text[5])));
        Serial.println("text[6]:" + String(text[6]));*/
    if (text[0] == 'A' && text[6] == 'B') {
      TimeMin = byte(text[1]);
      TimeSec = byte(text[2]);
      TimeMil = byte(text[3]);
      SCSec = byte(text[4]);
      SCMil = byte(text[5]);

      /*
        Serial.println("text[0]:" + String(text[0]));
        Serial.println("text[1]:" + String(int(text[1])));
        Serial.println("text[2]:" + String(int(text[2])));
        Serial.println("text[3]:" + String(int(text[3])));
        Serial.println("text[4]:" + String(int(text[4])));
        Serial.println("text[5]:" + String(int(text[5])));
        Serial.println("text[6]:" + String(text[6]));
      */
      GTime_Min_Tens = TimeMin / 10;
      GTime_Min_Ones = TimeMin % 10;
      GTime_Sec_Tens = TimeSec / 10;
      GTime_Sec_Ones = TimeSec % 10;

      SC_Tens = SCSec / 10;
      SC_Ones = SCSec % 10;
      SC_millis = SCMil;

      //      int val_sc=int(text[4]);
      //      int sc_ones=val_sc%10;
      //
      //      int sc_millis=int(text[5]);

      //Serial.println("MS:"+String(sc_millis));

      //printSEG(sc_millis);

    } else if (text[0] == 'C' && text[6] == 'D') {
      winner_avail == false;
      /*
        Serial.println("text[0]:" + String(text[0]));
        Serial.println("text[1]:" + String(int(text[1])));
        Serial.println("text[2]:" + String(int(text[2])));
        Serial.println("text[3]:" + String(int(text[3])));
        Serial.println("text[4]:" + String(byte(text[4])));
        Serial.println("text[5]:" + String(byte(text[5])));
        Serial.println("text[6]:" + String(text[6]));
      */
      byte BPZ = byte(text[1]);
      byte HGFoul = byte(text[2]);
      byte HGTOut = byte(text[3]);
      HomeScore = byte(text[4]);
      GuestScore = byte(text[5]);


      HScore_Hund = HomeScore / 100;
      HScore_Tens = (HomeScore % 100) / 10;
      HScore_Ones = HomeScore % 10;

      GScore_Hund = GuestScore / 100;
      GScore_Tens = (GuestScore % 100) / 10;
      GScore_Ones = GuestScore % 10;

      if (HGFoul == 110) {
        HFoul = 10;
        GFoul = 10;
      } else if (HGFoul >= 200) {
        HFoul = HGFoul - 200;
        GFoul = 10;
      } else {
        HFoul = HGFoul / 10;
        GFoul = HGFoul % 10;
      }

      HTOut = HGTOut / 10;
      GTOut = HGTOut % 10;

      BallPos = BPZ / 100;
      Period = (BPZ % 100) / 10;

      byte bz= BPZ%10;

      if(bz==1){
        buzzer=true;
      }else{
        buzzer=false;
      }

      Serial.println("BPZ:" + String(BPZ));
      //Serial.println("BP:" + String(BallPos));
    } else if (text[0] == 'W' && text[6] == 'X') {

      Serial.println("SET");

      /*
        Serial.println("text[0]:" + String(text[0]));
        Serial.println("text[1]:" + String(int(text[1])));
        Serial.println("text[2]:" + String(int(text[2])));
        Serial.println("text[3]:" + String(int(text[3])));
        Serial.println("text[4]:" + String(byte(text[4])));
        Serial.println("text[5]:" + String(byte(text[5])));
        Serial.println("text[6]:" + String(text[6]));
      */
      TimeMin = byte(text[1]);
      TimeSec = byte(text[2]);
      TimeMil = byte(text[3]);
      SCSec = byte(text[4]);
      //SCMil = int(text[5]);
      toSET = byte(text[5]);
      SET = true;

      GTime_Min_Tens = TimeMin / 10;
      GTime_Min_Ones = TimeMin % 10;
      GTime_Sec_Tens = TimeSec / 10;
      GTime_Sec_Ones = TimeSec % 10;

      SC_Tens = SCSec / 10;
      SC_Ones = SCSec % 10;
      SC_millis = SCMil;

      GTime_Min_Tens = TimeMin / 10;
      GTime_Min_Ones = TimeMin % 10;
      GTime_Sec_Tens = TimeSec / 10;
      GTime_Sec_Ones = TimeSec % 10;

      SC_Tens = SCSec / 10;
      SC_Ones = SCSec % 10;
      SC_millis = SCMil;

      
    } else if (text[0] == 'Y' && text[6] == 'Z') {
      Serial.println("WINNER");
      winner_avail = true;
      byte BPZ = byte(text[1]);
      byte HGFoul = byte(text[2]);
      byte HGTOut = byte(text[3]);
      HomeScore = byte(text[4]);
      GuestScore = byte(text[5]);


      if (HomeScore > GuestScore) {
        WINNER = true;
      } else if (HomeScore < GuestScore) {
        WINNER = false;
      }

      HScore_Hund = HomeScore / 100;
      HScore_Tens = (HomeScore % 100) / 10;
      HScore_Ones = HomeScore % 10;

      GScore_Hund = GuestScore / 100;
      GScore_Tens = (GuestScore % 100) / 10;
      GScore_Ones = GuestScore % 10;

      if (HGFoul == 110) {
        HFoul = 10;
        GFoul = 10;
      } else if (HGFoul >= 200) {
        HFoul = HGFoul - 200;
        GFoul = 10;
      } else {
        HFoul = HGFoul / 10;
        GFoul = HGFoul % 10;
      }

      HTOut = HGTOut / 10;
      GTOut = HGTOut % 10;

      BallPos = BPZ / 100;
      Period = (BPZ % 100) / 10;
    }

  }

  print_display();

  Serial.println("BUZZER:"+String(buzzer));

  /*
    Serial.println("SET:" + String(SET));
    Serial.println("toSET:" + String(toSET));
    Serial.println("SET_tog:" + String(SET_toggle));
  */
  if (winner_avail == true) {
    delay(300);
    win_toggle++;
  }

  if (SET == true) {
    delay(150);
    SET_toggle = !SET_toggle;
  }
  winner_avail = false;
  SET = false;

  if(buzzer==true){
  digitalWrite(buzzPin,1);
  }else{
  digitalWrite(buzzPin,0);
  }
}
