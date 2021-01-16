// Program based on the MD_MAX72XX library example

#include <MD_MAX72xx.h>

// Turn on debug statements to the serial output
#define  DEBUG  1

#if  DEBUG
#define PRINT(s, x) { Serial.print(F(s)); Serial.print(x); }
#define PRINTS(x) Serial.print(F(x))
#define PRINTD(x) Serial.println(x, DEC)

#else
#define PRINT(s, x)
#define PRINTS(x)
#define PRINTD(x)

#endif

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::ICSTATION_HW
#define MAX_DEVICES	4

#define CS_PIN    D8  // or SS

// SPI hardware interface
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// We always wait a bit between updates of the display
#define  DELAYTIME  100  // in milliseconds

void print_score(int pl1, int pl2)
{
  PRINTS("\nPrinting scode here");
  mx.clear();
  mx.control(MD_MAX72XX::WRAPAROUND, MD_MAX72XX::OFF);

  int pl1digits = pl1 % 10;
  int pl1tens = (pl1 / 10) % 10;
  int pl2digits = pl2 % 10;
  int pl2tens = (pl2 / 10) % 10;

  // draw something that will show changes
  if(pl1tens > 0)
    mx.setChar(mx.getColumnCount()-1, '0'+pl1tens);
  mx.setChar(mx.getColumnCount()-7, '0'+pl1digits);

  mx.setChar(mx.getColumnCount()/2 + 1, '-');

  if(pl2tens > 0)
    mx.setChar(4+6, '0'+pl2tens);
  mx.setChar(4, '0'+pl2digits);
}

void setup()
{
  mx.begin();

#if  DEBUG
  Serial.begin(115200);
#endif
  PRINTS("\n print two numbers");

}

void loop()
{
    for(int i = 0; i < 100; i++)
    {
      print_score(i, 99-i);
      delay(100);
    }
    print_score(1088, 999);
    delay(3000);
}
