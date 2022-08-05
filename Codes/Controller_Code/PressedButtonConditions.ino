//Start/Stop Button is Pressed
void con_StartStop() {
  if (StartStop_IsPressed == true && !flag_SSToggle && status_shift() && !flag_ChangeMenuToggle && menu_screen == 0) {
    //delay(10);
    if (status_StartStop()) {
      goto ss_exit;
    }
    if (SC_sec != 0) {
      flag_start = !flag_start;
    } else if (SC_sec == 0) {
      if (SC_mil != 0) {
        flag_start = !flag_start;
      }
    }
    flag_SSToggle = true;
    ms_counter = 0;
ss_exit:
    delay(5);
  } else if (StartStop_IsPressed == true && flag_SSToggle == true && status_shift() && !flag_ChangeMenuToggle) {
    if (status_StartStop()) {
      StartStop_IsPressed = false;
      flag_SSToggle = false;
      //delay(10);
    }
    ms_counter = 0;
  } else if (StartStop_IsPressed == true && !status_shift() && !flag_start && !flag_ChangeMenuToggle) {
    if(!status_StartStop()){
      ms_counter++;
    }else{
      ms_counter=0;
    }
    //Serial.println("SS:" + String(ms_counter));
    //Serial.println("SS_IsPressed:" + String(StartStop_IsPressed));
    if (ms_counter >= 30) {
      if (menu_screen == 0) {
        menu_screen = 1;
        menu_ToSet++;
      } else if (menu_screen == 1) {
        menu_screen = 0;
        menu_ToSet = 0;
      }
      flag_ChangeMenuToggle = true;
      flag_start = false;
    }
  } else if (StartStop_IsPressed == true && status_StartStop() && status_shift()  && flag_ChangeMenuToggle == true) {
    //Serial.println("SS con ENDED..."+String(flag_start));
    ms_counter = 0;
    flag_ChangeMenuToggle = false;
    StartStop_IsPressed == false;
    flag_start = false;
    //delay(10);
  }

}



//ShotClock Button is Pressed
void con_ShotClock() {
  if (ShotClock_IsPressed == true && !flag_SCToggle) {
    if (menu_screen == 0) {
      if (!status_shift()) {
        SC_sec = 14;
        SC_mil = 0;
      } else {
        SC_sec = 24;
        SC_mil = 0;
      }
    } else if (menu_screen == 1) {
      menu_ToSet++;
      if (menu_ToSet > 6) {
        menu_ToSet = 1;
      }
    }
    flag_SCToggle = true;
  } else if (ShotClock_IsPressed == true && flag_SCToggle == true) {
    if (status_ShotClock()) {
      ShotClock_IsPressed = false;
      flag_SCToggle = false;
      //delay(10);
    }
  }

}



//Buzzer Button is Pressed
void con_Buzzer() {

  if (buzzer_IsPressed == true && !flag_start && !flag_NewGame) {
    if (!status_shift()) {
      ms_buzzer++;
      //Serial.println("bz: " + String(ms_buzzer));
      if (ms_buzzer >= 10) {
        flag_NewGame = true;
        reset_AllVariables();
      }
    } else {
      ms_buzzer = 0;
      tone(buzzer, 1000);
    }

  }

  if (status_buzzer()) {
    ms_buzzer = 0;
    buzzer_IsPressed = false;
    flag_NewGame = false;
    noTone(buzzer);
  }
}


//HomeFoul Button is Pressed
void con_HomeFoul() {
  if (HFoul_IsPressed == true && !flag_HFoulToggle) {
    if (!status_shift()) {
      HomeFoul--;
    } else {
      HomeFoul++;
    }

    flag_HFoulToggle = true;

    if (HomeFoul >= 10 && HomeFoul != 255) {
      HomeFoul = 9;
    } else if (HomeFoul == 255) {
      HomeFoul = 0;
    }
  }
}


//GuestFoul Button is Pressed
void con_GuestFoul() {
  if (GFoul_IsPressed == true && !flag_GFoulToggle) {
    if (!status_shift()) {
      GuestFoul--;
    } else {
      GuestFoul++;
    }

    flag_GFoulToggle = true;

    if (GuestFoul >= 10 && GuestFoul != 255) {
      GuestFoul = 9;
    } else if (GuestFoul == 255) {
      GuestFoul = 0;
    }
  }
}



//HomeScore Button is Pressed
void con_HScore() {
  if (HScore_IsPressed == true && !flag_HScoreToggle) {
    if (menu_screen == 0) {
      if (!status_shift()) {
        HomeScore--;
      } else {
        HomeScore++;
      }
    } else if (menu_screen == 1) {
      switch (menu_ToSet) {
        case 1:
          TimeMin--;
          break;
        case 2:
          TimeSec--;
          break;
        case 3:
          TimeMil--;
          break;
        case 4:
          SC_sec--;
          break;
        case 5:
          SC_mil--;
          break;
        case 6:
          period--;
          break;
      }
      if (TimeMin > 99) {
        TimeMin = 0;
      }
      if (TimeSec > 59) {
        TimeSec = 0;
      }
      if (TimeMil > 9) {
        TimeMil = 0;
      }
      if (SC_sec > 24) {
        SC_sec = 0;
      }
      if (SC_mil > 9) {
        SC_mil = 0;
      }
      if (period > 5) {
        period = 1;
      }
    }

    flag_HScoreToggle = true;
    if (HomeScore >= 200 && HomeScore != 255) {
      HomeScore = 199;
    } else if (HomeScore == 255) {
      HomeScore = 0;
    }
  }
}


//GuestScore Button is Pressed
void con_GScore() {
  if (GScore_IsPressed == true && !flag_GScoreToggle) {
    if (menu_screen == 0) {
      if (!status_shift()) {
        GuestScore--;
      } else {
        GuestScore++;
      }
    } else if (menu_screen == 1) {
      switch (menu_ToSet) {
        case 1:
          TimeMin++;
          break;
        case 2:
          TimeSec++;
          break;
        case 3:
          TimeMil++;
          break;
        case 4:
          SC_sec++;
          break;
        case 5:
          SC_mil++;
          break;
        case 6:
          period++;
          break;
      }
      if (TimeMin > 99) {
        TimeMin = 0;
      }
      if (TimeSec > 59) {
        TimeSec = 0;
      }
      if (TimeMil > 9) {
        TimeMil = 0;
      }
      if (SC_sec > 24) {
        SC_sec = 0;
      }
      if (SC_mil > 9) {
        SC_mil = 0;
      }
      if (period > 5) {
        period = 1;
      }
    }

    flag_GScoreToggle = true;

    if (GuestScore >= 200 && GuestScore != 255) {
      GuestScore = 199;
    } else if (GuestScore == 255) {
      GuestScore = 0;
    }
  }
}



//BallPos Button is Pressed
void con_BallPos() {
  if (BallPos_IsPressed == true && !flag_BallPosToggle) {
    if (!status_shift()) {
      BallPos = 0;
    } else {
      if (BallPos == 1) {
        BallPos = 2;
      } else if (BallPos == 0 || BallPos == 2) {
        BallPos = 1;
      }
    }
    flag_BallPosToggle = true;
  }
}
