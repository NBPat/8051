/**
 * mod PF June 20
 * cmake -DCMAKE_BUILD_TYPE=Debug ..
 * prompt $ openocd -f interface/raspberrypi-swd.cfg -f target/rp2040.cfg
 * go into build/blink
 * prompt $ gdb-multiarch blink.elf
 * blink $ gdb-multiarch blink.elf
 * (gdb) target remote localhost:3333
 * (gdb) target extended-remote localhost:3333
 * (gdb) load blink.elf
 * (gdb) monitor restet init
 * (gdb) continue
 */
#include <stdio.h>
#include "pico/stdlib.h"
const uint LED_PIN = 25;
int i = 0;

void serious(int i) {printf("Hello, world!  %d \n", i);}
void onOff(void) {
        gpio_put(LED_PIN, 1);
        sleep_ms(350);
        gpio_put(LED_PIN, 0);
        sleep_ms(100);
        
        gpio_put(LED_PIN, 1);
        sleep_ms(150);
        gpio_put(LED_PIN, 0);
        sleep_ms(1500);
        
        gpio_put(LED_PIN, 1);
        sleep_ms(200);
        gpio_put(LED_PIN, 0);
        sleep_ms(500);
                }

int main() {
#ifndef PICO_DEFAULT_LED_PIN
#warning blink example requires a board with a regular LED
#else
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true) {
        onOff();
        serious(i++);
    }
#endif
}
