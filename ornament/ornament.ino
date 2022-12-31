
int pinMin = 0;
int pinMax = 7;

int pinlist[] = {
  // top to bottom
  // connected to pin 8
  3, 1, 0, 5,
  // pin 9
  6, 7, 10
};

// 3, 1, 0, 5
// PA7, PA5, PA4, PB2
// 6, 7, 10
// PB1, PB0, PA3
// 8, 9
// PA1, PA2

int topCommon = 8;
int bottomCommon = 9;

// forward direction (0) is red (write 1 on pos)
// otherwise green
int topColor = 0;
int bottomColor = 0;

// pin with the button
int buttonIn = 2;
unsigned long lastDebounceTime = 0;

int pattern = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // common
  pinMode(topCommon, OUTPUT);
  pinMode(bottomCommon, OUTPUT);

  for (int i = pinMin; i < pinMax; i++)
  {
    pinMode(pinlist[i], OUTPUT);
  }
  pinMode(buttonIn, INPUT_PULLUP);
}

int lastButtonState = 0;
int buttonState = 0;

void handleDebounce()
{
  bool reading = !digitalRead(buttonIn);
  if (reading != lastButtonState)
  {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > 50)
  {
    if (reading != buttonState)
    {
      buttonState = reading;
      if (reading)
      {
        pattern += 1;
      }
    }
  }
  lastButtonState = reading;
}

void cycle() // too bright
{
  // cycle through the pwm pins randomly
  int pinIdx = random(1, 7);
  int color = random(1024) % 2;
  // int color = 0;
  bottomColor = color;
  topColor = color;

  off();

  for (int i = 0; i < 200; i+= 1)
  {
    analogWrite(pinlist[pinIdx], i);
    delay(1);
  }

  off();

  delay(50);
}

int wipeDownIdx = 0;

void wipeDown()
{
  if (wipeDownIdx == 0)
  {
    bottomColor ^= 1;
  }
  topColor = bottomColor;
  off();
  
  digitalWrite(pinlist[wipeDownIdx], bottomColor ^ 1);
  delayMicroseconds(1500);
  off();
  delay(200);

  wipeDownIdx = (wipeDownIdx + 1) % 7;
}

int getColor(int pin)
{
  if (pin == 6 || pin == 7 || pin == 10)
    {
      return bottomColor;
    }
  return topColor;
}

void blonk()
{
  // cycle through the pwm pins randomly
  int pinIdx = random(0, 7);
  int color = random(1024) % 2;
  // int color = 0;
  bottomColor = color;
  topColor = color;

  off();
  int pin = pinlist[pinIdx];
  digitalWrite(pin, color ^ 1);

  // delay(2);

  // maybe would want to tune this value based on battery? or color?
  delayMicroseconds(1500);

  off();
  delay(random(200, 700));
}

void dimGreen()
{
  topColor = 1;
  bottomColor = 1;
  solid();

  auto buh = 50;
  for (int i = 0; i < 100; i++)
  {
    // PORTA.OUTSET = 0b00000110;
    PORTA.OUTTGL = 0b00000110;
    delayMicroseconds(69);
    // PORTA.OUTCLR = 0b00000110;
    PORTA.OUTTGL = 0b00000110;
    delayMicroseconds(1);
  }
}

void dimRed()
{
  topColor = 0;
  bottomColor = 0;
  solid();

  auto buh = 50;
  for (int i = 0; i < 100; i++)
  {
    // PORTA.OUTSET = 0b00000110;
    PORTA.OUTTGL = 0b00000110;
    delayMicroseconds(69);
    // PORTA.OUTCLR = 0b00000110;
    PORTA.OUTTGL = 0b00000110;
    delayMicroseconds(1);
  }
}

void orange()
{
  topColor = 0;
  bottomColor = 0;
  // solid();

  auto buh = 50;
  for (int i = 0; i < 100; i++)
  {
    topColor = topColor ^ 1;
    bottomColor = bottomColor ^ 1;
    solid();
    delayMicroseconds(1);
    // delay(1);
    // PORTA.OUTSET = 0b00000110;
    PORTA.OUTTGL = 0b00000110;
    delayMicroseconds(20);
    // PORTA.OUTCLR = 0b00000110;
    // PORTA.OUTTGL = 0b00000110;
    // delayMicroseconds(1);
  }
}

void off()
{

// 3, 1, 0, 5
// PA7, PA5, PA4, PB2
// 6, 7, 10
// PB1, PB0, PA3
// 8, 9
// PA1, PA2

  // 7 5 4
  int topa_mask = 0b10110000;
  // pb2
  int topb_mask = 0b00000100;

  int bottoma_mask = 0b00001000;
  int bottomb_mask = 0b00000011;

  uint8_t portaTemp = (topColor & 1) << 1 | (bottomColor & 1) << 2;
  uint8_t portbTemp = 0;

  if (topColor)
  {
    // if top color is on
    portaTemp |= topa_mask;
    portbTemp |= topb_mask;
  }
  if (bottomColor)
  {
    // if top color is on
    portaTemp |= bottoma_mask;
    portbTemp |= bottomb_mask;
  }

  PORTA.OUT = portaTemp;
  PORTB.OUT = portbTemp;

  // PORTA = 0b00000000;
  // PORTB = 0b00000000;
  // iotn404.h
  // PORTA.OUTCLR = 0b11111001 | (topColor ^ 1 << 1) | (bottomColor ^ 1 << 2);
  //PORTA.OUT = 0 | ((topColor & 1) << 1) | ((bottomColor & 1) << 2);
  // PORTA.OUT = 0;
  // PORTB.OUTCLR = 0b11111111;

  // quickly turn off pwm
  TCA0.SPLIT.CTRLB = 0;
  // PORTB.OUT = 0;

  // slow
  // PORTA = 0;




  // digitalWrite(topCommon, topColor ^ 1);
  // for (int i = 0; i < 4; i++)
  // {
  //   digitalWrite(pinlist[i], topColor ^ 1);
  // }
  // digitalWrite(bottomCommon, bottomColor ^ 1);
  // for (int i = 4; i < 7; i++)
  // {
  //   digitalWrite(pinlist[i], bottomColor ^ 1);
  // }
}

void clockButNot()
{
  int seconds = millis() / 1000;

  topColor = (millis() / 30000) % 2;

  // if (seconds % 100 == 0)
  // {
  //   topColor ^= 1;
  //   iters = 1000;
  // }
  bottomColor = topColor;

  off();

  seconds = seconds & 0b1111111;
  for (int i = 0; i < 7; i++)
  {
    digitalWrite(pinlist[i], topColor ^ ((seconds & (1 << i)) >> i));
  }

  uint8_t portaToggle = PORTA.OUT;
  uint8_t portbToggle = PORTB.OUT;
  
  for (int i = 0; i < 100; i++)
  {
    off();
    delayMicroseconds(90);

    PORTA.OUT = portaToggle;
    PORTB.OUT = portbToggle;
    delayMicroseconds(10);
  }

  
}

void loop()
{
  handleDebounce();

  switch (pattern)
  {
    // case 0:
    //   // cycle();
    //   // off();
    //   break;
    // case 1:
    //   // too bright
    //   // topColor = 1;
    //   // bottomColor = 1;
    //   // solid();
    //   break;
    case 0:
      wipeDown();
      // solid is tooo bright
      // topColor = 0;
      // bottomColor = 0;
      // solid();
      break;
    case 1:
      blonk();
      break;
    case 2:
      // may break if I end up using different resistors
      dimGreen();
      break;
    case 3:
      dimRed();
      break;
    case 4:
      orange();
      break;
    case 5:
      clockButNot();
      break;
    default:
      pattern = 0;
      break;
  }
}

void solid()
{
  int topa_mask = 0b10110000;
  // pb2
  int topb_mask = 0b00000100;

  int bottoma_mask = 0b00001000;
  int bottomb_mask = 0b00000011;

  // common mask
  // int commona_mask = 0b110;

  uint8_t portaTemp = (topColor & 1) << 1 | (bottomColor & 1) << 2;
  uint8_t portbTemp = 0;

  if (!topColor)
  {
    // if top color is on
    portaTemp |= topa_mask;
    portbTemp |= topb_mask;
  }
  if (!bottomColor)
  {
    // if top color is on
    portaTemp |= bottoma_mask;
    portbTemp |= bottomb_mask;
  }

  PORTA.OUT = portaTemp;
  PORTB.OUT = portbTemp;


  // digitalWrite(topCommon, topColor ^ 1);
  // digitalWrite(bottomCommon, bottomColor ^ 1);

  // for (int i = 0; i < 4; i++)
  // {
  //   digitalWrite(pinlist[i], topColor);
  // }
  // for (int i = 4; i < 7; i++)
  // {
  //   digitalWrite(pinlist[i], bottomColor);
  // }
}

// int a = 0;

// the loop function runs over and over again forever
// void loop() {

//   if (!digitalRead(buttonIn))
//   {
//    a = a ^ 1;
//    delay(100); 
//   }

//   // toggle color
//   digitalWrite(8, a);
//   digitalWrite(9, a);

//   // zero states
//   for (int i = pinMin; i < pinMax; i++)
//   {
//     digitalWrite(pinlist[i], a );
//   }
  
//     auto pressed = !digitalRead(buttonIn);
//     // digitalWrite(0, pressed);

//     // return;

//   for (int i = pinMin; i < pinMax; i++)
//   {
// //    for (int x = 0; x < 50; x+=5)
// //    {
// //      analogWrite(pinlist[i], x);
// //      delay(10);
// //    }
// digitalWrite(pinlist[i], a ^ 1);
// delay(0);
//    // digitalWrite(pinlist[i], HIGH);   // turn the LED on (HIGH is the voltage level)
//   // delay(100);                       // wait for a second
//   // digitalWrite(pinlist[i], a);    // turn the LED off by making the voltage LOW
//   delay(0);                       // wait for a second 
//   }
// }
