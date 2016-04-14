/*************************************************************************/
/*                                                                       */
/* Writen with 96boardsGPIO C library                                    */
/*                                                                       */
/* Intentionally a simple library to resemble Arduino programming        */
/*                                                                       */
/* You really can't do interupt programming with this libray but         */
/* you can do things like that with libsoc.  This library calls into     */
/* libsoc for its underlying metal calls. So I guess if you really       */
/* wanted to you could extend this library to do interupt programming.   */
/*                                                                       */
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
/*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
#include <gpio.h>

#define TOUCH "GPIO-A"
#define LED "GPIO-C"


int main()
{
    int x;
    int t = 0;
    int last_t = 0;
    int led_state = HIGH;
    
    if(gpio_open(gpio_id(LED), "out")){
        goto fail;
    }
    if (gpio_open(gpio_id(TOUCH), "in")){
        goto fail;
    }

    while(1){
        t = digitalRead(gpio_id(TOUCH));
        if (t && !last_t){
            digitalWrite(gpio_id(LED), led_state);
            usleep(100000);
            led_state=(led_state==HIGH)?LOW:HIGH;
        }
        last_t = t;
        usleep(1);
    }
    fail:
    digitalWrite(gpio_id(LED), LOW);
    return EXIT_SUCCESS;
}
