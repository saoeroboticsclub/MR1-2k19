void eight_directions() {
  x = ps2.Analog(PSS_LX);
  y = ps2.Analog(PSS_LY);

  (x == 128) ? (x = 0) : (x > 128) ? (x = map(x, 129, 255, 1, 255)) : (x = map(x, 127, 0, -1, -255));
  (y == 127) ? (y = 0) : (y < 127) ? (y = map(y, 126, 0, 1, 255)) : (y = map(y, 128, 255, -1, -255));

  if (y == -1)  y = 0;
  if (x == 0 && y == 0) return;
  
  if (x == 255 && y == -255 && px == 0 && py == 0) {
    x = px; y = py;
    return;
  }

  if (x > 0 && y > 0) {
    Serial.println("North-East");
    run_motor(m1ac, 0.21 * spd, m2c,  spd, m3ac, 0.707 * spd);
  }

  else if (x < 0 && y > 0) {
    Serial.println("North-West");
    run_motor(m1ac, 0.96 * spd, m2c, 0.26 * spd, m3c, 0.707 * spd);
  }

  else if (x < 0 && y < 0) {
    Serial.println("South-West");
    run_motor(m1c, 0.26 * spd, m2ac, 0.96 * spd, m3c, 0.647 * spd);
  }

  else if (x > 0 && y < 0) {
    Serial.println("South-East");
    run_motor(m1c, 0.96 * spd, m2ac, 0.26 * spd, m3ac, 0.647 * spd);
  }
  if (x == 0 && y > 0) {
    Serial.println("North");
    run_motor(m1ac, spd - (0.0270 * spd), m2c, spd, m3c, 0);
  }

  else if (x == 0 && y < 0) {
    Serial.println("South");
    run_motor(m1c, spd, m2ac, spd + (0.0270 * spd), m3c, 0);
  }

  if (y == 0 && x > 0) {
    Serial.println("East");
    run_motor(m1c, (spd / 2), m2c, (spd / 2), m3ac, spd);
  }

  else if (y == 0 && x < 0) {
    Serial.println("West");
    run_motor(m1ac, (spd / 2), m2ac, (spd / 2), m3c, spd);
  }
  px = x;
  py = y;
}
