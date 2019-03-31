void Map_ps2() {
  x = ps2.Analog(PSS_RX);
  y = ps2.Analog(PSS_RY);

  //Joystick disconnected
  if (y == 128)  y = 127;

  //Map X-Axis and Y-Axis Into -255 to +255
  (x == 128) ? (x = 0) : (x > 128) ? (x = map(x, 129, 255, -1, -255)) : (x = map(x, 127, 0, 1, 255));
  (y == 127) ? (y = 0) : (y < 127) ? (y = map(y, 126, 0, 1, 255)) : (y = map(y, 128, 255, -1, -255));

  x = constrain(x, -255, 255);
  y = constrain(y, -255, 255);

  angle = atan2(y, x);
  magnitude = sqrt(pow(x, 2) + pow(y, 2));
}
