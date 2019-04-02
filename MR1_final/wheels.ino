void forward_13() {
  run_motors(m1c, spd, m2c, 0, m3ac, spd);
}

void backward_13() {
  run_motors(m1ac, spd, m2ac, 0, m3c, spd);
}

void left_13() {
  run_motors(m1ac, (spd / 2), m2c, spd , m3ac, (spd / 2));
}

void right_13() {
  run_motors(m1c, (spd / 2), m2ac, spd , m3c, (spd / 2));
}


void forward_23() {
  run_motors(m1ac, 0, m2c, spd, m3ac, spd);
}

void backward_23() {
  run_motors(m1c, 0, m2ac, spd , m3c, spd);
}

void left_23() {
  run_motors(m1c, spd, m2ac, (spd / 2) , m3ac, (spd / 2));
}

void right_23() {
  run_motors(m1ac, spd, m2c, (spd / 2) , m3c, (spd / 2));
}



void forward_12() {
  /*for (; i <= (spd - (0.0270 * spd)) && j <= spd && ps2.Button(PSB_PAD_UP); i += 0.7, j += 0.79) { //180&200 ->0.9,0.78 spd-2.77%spd,spd
                                                                                                    //180     ->0.7,0.87 spd-2.70%spd,spd
                                                                                                     //below 11.9 ->0.7,0.8

    Serial.println("i:" + String(i) + " 70     j:" + String(j));
    ps2.read_gamepad();
    delay(10);
    run_motor(m1ac, i, m2c, j, m3c, 0);
    if (ps2.Button(PSB_R1) || ps2.Button(PSB_L1))
      break;
    }
  */
  run_motors(m1ac, spd, m2c, spd, m3c, 0);
}

void backward_12() {
  run_motors(m1c, spd, m2ac, spd, m3c, 0);
}

void right_12() {
  run_motors(m1c, (spd / 2), m2c, (spd / 2), m3ac, spd);
}

void left_12() {
  run_motors(m1ac, (spd / 2), m2ac, (spd / 2), m3c, spd);
}

void right_1() {
  run_motors(m1c, spd , m2ac, (spd / 2), m3ac, (spd / 2));
}

void left_1() {
  run_motors(m1ac, spd , m2c, (spd / 2), m3c, (spd / 2));
}

void Curve_Clockwise() {
  run_motors(m1c, spd * 0.67, m2c, spd, m3c, 0);
}

void Curve_Anti() {
  run_motors(m1ac, spd, m2ac, spd * 0.67, m3c, 0);
}
