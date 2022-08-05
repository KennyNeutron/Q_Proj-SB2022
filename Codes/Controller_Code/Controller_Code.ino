//SB Cont by: Kenny Neutron
//07-30-2022

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

#include <Wire.h>

#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_NO_ACK | U8G_I2C_OPT_FAST);	// Fast I2C / TWI

//#define u8g_logo_width 38
//#define u8g_logo_height 24
////static unsigned char u8g_logo_bits[] = {
//static unsigned char u8g_logo_bits[] U8G_PROGMEM = {
//   0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xe0, 0xe0,
//   0xff, 0xff, 0x3f, 0xe3, 0xe1, 0xff, 0xff, 0x3f, 0xf3, 0xf1, 0xff, 0xff,
//   0x3f, 0xf3, 0xf1, 0xfe, 0xbf, 0x37, 0xf3, 0x11, 0x1c, 0x1f, 0x30, 0xf3,
//   0x01, 0x08, 0x8c, 0x20, 0xf3, 0x01, 0x00, 0xc0, 0x39, 0xf3, 0x81, 0xc7,
//   0xc1, 0x39, 0xf3, 0xc1, 0xc7, 0xc9, 0x38, 0xf3, 0xc1, 0xc3, 0x19, 0x3c,
//   0xe3, 0x89, 0x01, 0x98, 0x3f, 0xc7, 0x18, 0x00, 0x08, 0x3e, 0x0f, 0x3c,
//   0x70, 0x1c, 0x30, 0x3f, 0xff, 0xfc, 0x87, 0x31, 0xff, 0xff, 0xbf, 0xc7,
//   0x23, 0x01, 0x00, 0x00, 0xc6, 0x23, 0x03, 0x00, 0x00, 0x0e, 0x30, 0xff,
//   0xff, 0x3f, 0x1f, 0x3c, 0xff, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0xff, 0x3f,
//   0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0x3f };

//Buttons
#define pb_shift      4
#define pb_buzzer     5
#define pb_HFoul      6
#define pb_GFoul      7
#define pb_HScore     8
#define pb_GScore     A0
#define pb_ShotClock  A1
#define pb_StartStop  A2
#define pb_BallPos    A3

//Outputs
#define buzzer 3

bool buzzer_IsPressed = false;
bool HFoul_IsPressed = false;
bool GFoul_IsPressed = false;
bool HScore_IsPressed = false;
bool GScore_IsPressed = false;
bool ShotClock_IsPressed = false;
bool StartStop_IsPressed = false;
bool BallPos_IsPressed = false;

bool WINNER = true; //true= HOME WINNER     false= GUEST WINNER     NOTE: only if the game is doene
bool winner_avail = false; //goes true if a winner is declared;

bool toggle1HZ = false;

//Game Variables (RAW)
byte TimeMin = 10; //GameTime Minute
byte TimeSec = 0; //GameTime Second
byte TimeMil = 0; //GameTime Millis

byte SC_sec = 24; //ShotClock Second
byte SC_mil = 0; //ShotClock Millis

byte HomeScore = 0; //HomeScore
byte GuestScore = 0; //GuestScore

byte HomeFoul = 0; //HomeFoul
byte GuestFoul = 0; //GuestFoul

byte period = 1; //Period or Quarter

byte BallPos = 0; //BallPosession 0=NoPossession 1=Home 2=Guest

bool buzz = false;
bool flag_start = false;
bool flag_SSToggle = false;
bool flag_SCToggle = false;
bool flag_SCDisplayed = false;
bool flag_QFinish = false;
bool flag_QFinishToggle = false;
bool flag_HFoulToggle = false;
bool flag_GFoulToggle = false;
bool flag_HScoreToggle = false;
bool flag_GScoreToggle = false;
bool flag_BallPosToggle = false;
bool flag_ChangeMenuToggle = false;
bool flag_WinnerBlink = false;
bool flag_NewGame = false;



uint32_t last_millis = 0;
uint32_t last_millis2 = 0;

uint32_t last_millisWIN = 0; //for blinking (winner);
uint16_t blink_period = 500; //blink period


byte menu_screen = 0;
byte menu_ToSet = 0;
byte ms_counter = 0;  //for SHIFT + START/STOP
byte ms_buzzer = 0; //for SHIFT + BUZZER


char ch_message[7] = "FFFFFF";

uint16_t tcounter = 0;

void setup() {
  // flip screen, if required
  // u8g.setRot180();

  // flip screen, if required
  // u8g.setRot180();

  // set SPI backup if required
  //u8g.setHardwareBackup(u8g_backup_avr_spi);

  // assign default color value
  //Serial.begin(115200);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();

  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255, 255, 255);
  }

  pinMode(pb_shift, INPUT_PULLUP);
  pinMode(pb_buzzer, INPUT_PULLUP);
  pinMode(pb_HFoul, INPUT_PULLUP);
  pinMode(pb_GFoul, INPUT_PULLUP);
  pinMode(pb_HScore, INPUT_PULLUP);
  pinMode(pb_GScore, INPUT_PULLUP);
  pinMode(pb_ShotClock, INPUT_PULLUP);
  pinMode(pb_StartStop, INPUT_PULLUP);
  pinMode(pb_BallPos, INPUT_PULLUP);

  pinMode(buzzer, OUTPUT);
  delay(10);

  tone(buzzer, 1000);
  delay(500);
  noTone(buzzer);


  //Serial.println("START");
  last_millis = millis();
}

void loop() {
  if (SC_sec == 0 && SC_mil == 0 && flag_SCDisplayed == true && !flag_QFinishToggle && !winner_avail) {
    tone(buzzer, 1000);
    buzz = true;
    flag_SCDisplayed = false;
    SC_sec = 24;

    if (flag_QFinish == true && !winner_avail) {
      for (int a = 0; a <= 60; a++) {
        delay(100);
        NRF_Broadcast();
      }
      noTone(buzzer);
      buzz = false;

      if (period == 4 || period == 5) {
        if (HomeScore != GuestScore) {
          //There is a WINNER!
          if (HomeScore > GuestScore) {
            //Serial.println("HOME WINS!");
            WINNER = true;
          } else if (GuestScore > HomeScore) {
            //Serial.println("GUEST WINS!");
            WINNER = false;
          }
          winner_avail = true;
        } else if (HomeScore == GuestScore) {
          //It's a TIE! Go for OT
          period = 5;
        }
      }

      flag_QFinishToggle = true;
      if (period != 5 && !winner_avail) {
        period++;
        TimeMin = 10;
        TimeSec = 0;
        TimeMil = 0;
        SC_sec = 24;
        SC_mil = 0;
        HomeFoul = 0;
        GuestFoul = 0;
        BallPos = 0;
      } else if (period == 5 && !winner_avail) {
        TimeMin = 5;
        TimeSec = 0;
        TimeMil = 0;
        SC_sec = 24;
        SC_mil = 0;
        HomeFoul = 0;
        GuestFoul = 0;
        BallPos = 0;
      }

      flag_QFinish = false;
      flag_QFinishToggle = false;
    } else {
      for (int a = 0; a <= 30; a++) {
        delay(100);
        NRF_Broadcast();
      }
      noTone(buzzer);
      buzz = false;
    }

  }


  last_millis2 = millis();

  u8g.firstPage();
  do {
    draw();
  } while ( u8g.nextPage() );
  //Serial.println("diff: " + String(millis() - last_millis2));

  if (flag_start == true) {
    TimerStarted();
  }

  if (TimeMin == 0 && TimeSec < SC_sec && menu_screen == 0) {
    SC_sec = TimeSec;
    SC_mil = TimeMil;
  }


  NRF_Broadcast();

  if (flag_start == true) {
    TimerStarted();
  }

  buttonUpdate();

  if (flag_start == true) {
    TimerStarted();
  }

  switch (menu_screen) {
    case 0:
      if (!winner_avail) {
        con_StartStop();//Start/Stop Button is Pressed
        con_ShotClock();//ShotClock Button is Pressed
        con_Buzzer();//Buzzer Button is Pressed
        con_HomeFoul();//HomeFoul Button is Pressed
        con_GuestFoul();//GuestFoul Button is Pressed
        con_HScore();//HomeScore Button is Pressed
        con_GScore();//GuestScore Button is Pressed
        con_BallPos();//BallPos Button is Pressed
      } else if (winner_avail == true) {
        con_Buzzer();//Buzzer Button is Pressed
      }
      break;

    case 1:
      con_StartStop();//Start/Stop Button is Pressed
      con_ShotClock();//ShotClock Button is Pressed
      con_BallPos();//BallPos Button is Pressed
      con_HScore();//HomeScore Button is Pressed
      con_GScore();//GuestScore Button is Pressed
      break;

  }

}

void draw() {
  // graphic commands to redraw the complete screen should be placed here
  //u8g.drawXBMP( 0, 0, u8g_logo_width, u8g_logo_height, u8g_logo_bits);

  //display_guidelines();
  display_SB();
}

void NRF_Broadcast() {
  DataEncrypt_Time();
  //Serial.print(ch_message);
  radio.write(&ch_message, sizeof(ch_message));

  DataEncrypt_Other();
  //Serial.print(ch_message);
  radio.write(&ch_message, sizeof(ch_message));
  delay(5);
  radio.write(&ch_message, sizeof(ch_message));
  delay(5);
  radio.write(&ch_message, sizeof(ch_message));
}

void TimerStarted() {
  //Serial.println("act: " + String(millis() - last_millis));
  if ((millis() - last_millis) >= 75) {
    last_millis = millis();
    TimeMil--;
    SC_mil--;
  }

  if (TimeMil == 255) {
    TimeSec--;
    TimeMil = 9;
  }

  if (TimeSec == 255) {
    TimeMin--;
    TimeSec = 59;
  }

  if (TimeMin == 0 && TimeSec == 0 && TimeMil == 0) {
    flag_start = false;
    flag_QFinish = true;
  }

  if (SC_sec == 255) {
    SC_sec = 24;
  }
  if (SC_mil == 255) {
    toggle1HZ = !toggle1HZ;
    SC_sec--;
    SC_mil = 9;
  }

  if (SC_sec == 0 && SC_mil == 0) {
    flag_start = false;
  }
}


void reset_AllVariables() {
  TimeMin = 10; //GameTime Minute
  TimeSec = 0; //GameTime Second
  TimeMil = 0; //GameTime Millis

  SC_sec = 24; //ShotClock Second
  SC_mil = 0; //ShotClock Millis

  HomeScore = 0; //HomeScore
  GuestScore = 0; //GuestScore

  HomeFoul = 0; //HomeFoul
  GuestFoul = 0; //GuestFoul

  period = 1; //Period or Quarter

  BallPos = 0; //BallPosession 0=NoPossession 1=Home 2=Guest

  winner_avail = false;
}
