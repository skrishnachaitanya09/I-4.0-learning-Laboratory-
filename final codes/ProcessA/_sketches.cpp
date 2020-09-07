#include "arduino.hpp"
#include "board.h"
extern void setup(void);
extern void loop(void);

int main(void)
{
    /* run the Arduino setup */
    setup();
    /* and the event loop */
    while (1) {
        loop();
    }
    /* never reached */
    return 0;
}
