/* MIT License                                                           */
/*                                                                       */
/* Copyright (c) 2016 David I. S. Mandala                                */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/ 
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*                                                                       */
#include <signal.h>
#include <unistd.h>
#include "mraa.hpp"

/* MRAA does not yet understand GPIO-A to GPIO-L Linaro will add that  */
/* What Mraa does understand is pin out numbers so, pin 23 is GPIO-A */
/* and pin 25 is GPIO-C                                              */
#define GPIO_C 25
#define GPIO_A 23

bool running = true;
bool led_state = false;
int last_touch;
void sig_handler(int signo)
{
        if (signo == SIGINT)
                running = false;
}

int main(int argc, char* argv[])
{
        mraa::Gpio* touch_gpio = new mraa::Gpio(GPIO_A);
        mraa::Gpio* led_gpio = new mraa::Gpio(GPIO_C);
        mraa::Result response;
        int touch;

        signal(SIGINT, sig_handler);

        if ((response = touch_gpio->dir(mraa::DIR_IN))!= mraa::SUCCESS){
                goto fail;
        }
        if ((response = led_gpio->dir(mraa::DIR_OUT))!= mraa::SUCCESS){
                goto fail;
        }

        led_gpio->write(led_state);
        
        while (running) {
                touch = touch_gpio->read();
                if (touch == 1 && last_touch == 0) {
                        led_state = !led_state;
                        response = led_gpio->write(led_state);
                        usleep(100000);
                }
                last_touch = touch;
                usleep(1);
        }
        fail:
        delete led_gpio;
        delete touch_gpio;
        return response;
}

