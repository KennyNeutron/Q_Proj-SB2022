void DataEncrypt_Time() {
  ch_message[0] = 'A';        //HEADER
  if (TimeMin == 0) {
    ch_message[1] = 250;  //Will Represent '0'
  } else {
    ch_message[1] = TimeMin;    //GameTime MINUTE
  }

  if (TimeSec == 0) {
    ch_message[2] = 250;  //Will Represent '0'
  } else {
    ch_message[2] = TimeSec;    //GameTime SECOND
  }

  if (TimeMil == 0) {
    ch_message[3] = 250;  //Will Represent '0'
  } else {
    ch_message[3] = TimeMil;    //GameTime MILLIS
  }

  if (SC_sec == 0) {
    ch_message[4] = 250;  //Will Represent '0'
  } else {
    ch_message[4] = SC_sec;    //ShotClock SECOND
  }

  if (SC_mil == 0) {
    ch_message[5] = 250;  //Will Represent '0'
  } else {
    ch_message[5] = SC_mil;    //ShotClock MILLIS
  }

  ch_message[6] = 'B';        //FOOTER
}

void DataEncrypt_Other() {
  byte BPZ = 0; //Ballpos Period Buzzer
  BPZ = (BallPos * 100) + (period * 10) + buzz;

  ch_message[0] = 'C';            //HEADER

  ch_message[1] = BPZ;            //Ball poss. Period Buzzer

  if (HomeFoul == 0) {
    ch_message[2] = 250;          //Will Represent '0'
  } else {
    ch_message[2] = HomeFoul;     //Home Foul
  }

  if (GuestFoul == 0) {
    ch_message[3] = 250;          //Will Represent '0'
  } else {
    ch_message[3] = GuestFoul;     //Guest Foul
  }

  if (HomeScore == 0) {
    ch_message[4] = 250;          //Will Represent '0'
  } else {
    ch_message[4] = HomeScore;     //Home Score
  }

  if (GuestScore == 0) {
    ch_message[5] = 250;          //Will Represent '0'
  } else {
    ch_message[5] = GuestScore;     //Guest Score
  }
  ch_message[6] = 'D';        //FOOTER

}
