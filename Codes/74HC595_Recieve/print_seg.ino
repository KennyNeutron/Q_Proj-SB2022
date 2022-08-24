
void printSEG0(int segNum) {
  switch (segNum) {
    case 0:
      shiftOut(ser, srclk, LSBFIRST, 0b00000011);
      break;
    case 1:
      shiftOut(ser, srclk, LSBFIRST, 0b10011111);
      break;
    case 2:
      shiftOut(ser, srclk, LSBFIRST, 0b00100101);
      break;
    case 3:
      shiftOut(ser, srclk, LSBFIRST, 0b00001101);
      break;
    case 4:
      shiftOut(ser, srclk, LSBFIRST, 0b10011001);
      break;
    case 5:
      shiftOut(ser, srclk, LSBFIRST, 0b01001001);
      break;
    case 6:
      shiftOut(ser, srclk, LSBFIRST, 0b01000001);
      break;
    case 7:
      shiftOut(ser, srclk, LSBFIRST, 0b00011111);
      break;
    case 8:
      shiftOut(ser, srclk, LSBFIRST, 0b00000001);
      break;
    case 9:
      shiftOut(ser, srclk, LSBFIRST, 0b00001001);
      break;
    case 10: //P
      shiftOut(ser, srclk, LSBFIRST, 0b00110001);
      break;
    case 11: //O
      shiftOut(ser, srclk, LSBFIRST, 0b11000101);
      break;
    case 12: //OFF
      shiftOut(ser, srclk, LSBFIRST, 0b11111111);
      break;
  }
}

void printSEG1(int segNum) {
  switch (segNum) {
    case 0:
      shiftOut(ser, srclk, LSBFIRST, 0b00000010);
      break;
    case 1:
      shiftOut(ser, srclk, LSBFIRST, 0b10011110);
      break;
    case 2:
      shiftOut(ser, srclk, LSBFIRST, 0b00100100);
      break;
    case 3:
      shiftOut(ser, srclk, LSBFIRST, 0b00001100);
      break;
    case 4:
      shiftOut(ser, srclk, LSBFIRST, 0b10011000);
      break;
    case 5:
      shiftOut(ser, srclk, LSBFIRST, 0b01001000);
      break;
    case 6:
      shiftOut(ser, srclk, LSBFIRST, 0b01000000);
      break;
    case 7:
      shiftOut(ser, srclk, LSBFIRST, 0b00011110);
      break;
    case 8:
      shiftOut(ser, srclk, LSBFIRST, 0b00000000);
      break;
    case 9:
      shiftOut(ser, srclk, LSBFIRST, 0b00001000);
      break;
    case 10: //P
      shiftOut(ser, srclk, LSBFIRST, 0b00110000);
      break;
    case 11: //O
      shiftOut(ser, srclk, LSBFIRST, 0b11000100);
      break;
    case 12: //OFF
      shiftOut(ser, srclk, LSBFIRST, 0b11111110);
      break;
  }
}

void srclk_pulse() {
  digitalWrite(srclk, 1);
  digitalWrite(srclk, 0);
}

void rclk_pulse() {
  digitalWrite(rclk, 1);
  digitalWrite(rclk, 0);
}
