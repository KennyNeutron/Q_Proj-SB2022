void print_display() {

  printSEG0(GTOut);
  printSEG0(HTOut);
  printSEG0(GFoul);
  printSEG0(HFoul);


  if (SET == true && toSET == 6) {
    if (SET_toggle == true) {
      printSEG0(12);
    } else if (SET_toggle == false) {
      Print_Period();
    }
  } else {
    Print_Period();
  }




  if (!winner_avail) {
    Print_GuestScore();
    Print_HomeScore();
  } else if (winner_avail) {
    if (WINNER == true && (win_toggle % 2 == 0)) {
      Print_GuestScore();
      printSEG0(12);
      printSEG0(12);
    } else if (WINNER == true && (win_toggle % 2 != 0)) {
      Print_GuestScore();
      Print_HomeScore();
    }

    if (WINNER == false && (win_toggle % 2 == 0)) {
      printSEG0(12);
      printSEG0(12);
      Print_HomeScore();
    } else if (WINNER == false && (win_toggle % 2 != 0)) {
      Print_GuestScore();
      Print_HomeScore();
    }
  }


  //GTime Sec
  if (SET == true && toSET == 2) {
    if (SET_toggle == true) {
      printSEG0(12);
      printSEG0(12);
    } else if (SET_toggle == false) {
      Print_GTime_Sec();
    }
  } else {
    Print_GTime_Sec();
  }

  //GTime Min
  if (SET == true && toSET == 1) {
    if (SET_toggle == true) {
      printSEG0(12);
      printSEG0(12);
    } else if (SET_toggle == false) {
      Print_GTime_Min();
    }
  } else {
    Print_GTime_Min();
  }

  if (SET == true && toSET == 4) {
    if (SET_toggle == true) {
      printSEG0(12);
      printSEG0(12);
    } else if (SET_toggle == false) {
      Print_SC();
    }
  } else {
    Print_SC();
  }


  rclk_pulse();
}


void Print_GuestScore() {
  if (GScore_Hund == 1) {
    printSEG1(GScore_Ones);
    printSEG1(GScore_Tens);
  } else {
    if (GuestScore < 10) {
      printSEG0(GScore_Ones);
      printSEG0(12);
    } else {
      printSEG0(GScore_Ones);
      printSEG0(GScore_Tens);
    }
  }
}

void Print_HomeScore() {
  if (HScore_Hund == 1) {
    printSEG1(HScore_Ones);
    printSEG1(HScore_Tens);
  } else {
    if (HomeScore < 10) {
      printSEG0(HScore_Ones);
      printSEG0(12);
    } else {
      printSEG0(HScore_Ones);
      printSEG0(HScore_Tens);
    }
  }
}

void Print_Period() {
  if (Period == 5) {
    printSEG0(11);
  } else {
    printSEG0(Period);
  }
}

void Print_GTime_Min() {

  printSEG0(GTime_Min_Ones);
  if (BallPos == 1) {
    if (TimeMin < 10) {
      printSEG1(12);
    } else {
      printSEG1(GTime_Min_Tens);
    }
  } else {
    if (TimeMin < 10) {
      printSEG0(12);
    } else {
      printSEG0(GTime_Min_Tens);
    }
  }
}

void Print_GTime_Sec() {


  if (BallPos == 2) {
  printSEG1(GTime_Sec_Ones);     
  }else{
  printSEG0(GTime_Sec_Ones);
  }
  
  printSEG0(GTime_Sec_Tens);
}

void Print_SC() {
  printSEG0(SC_Ones);
  if (SC_Tens == 0) {
    printSEG0(12);
  } else {
    printSEG0(SC_Tens);
  }
}
