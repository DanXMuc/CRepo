/*
 * Author: Yevgeniy Kiveish <yevgeniy.kiveisha@intel.com>
 * Copyright (c) 2014 Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "jhd1313m1.h"
#include "mraa.hpp"
#include "unistd.h"

using namespace mraa;

int main(int argc, char **argv)
{
    // 0x62 RGB_ADDRESS, 0x3E LCD_ADDRESS
    upm::Jhd1313m1 *lcd = new upm::Jhd1313m1(0, 0x3E, 0x62);
    char str[256];

    Aio* a1;
    Gpio* d2;

    a1 = new Aio(1);
    d2 = new Gpio(2);
    d2->dir(DIR_OUT);

    int i = 0;
    bool r=false;

    while (true) {
        uint16_t adc_value;
        adc_value = a1->read();
        lcd->setCursor(0,0);

        if ((i++)%2 == 0) lcd->write(". ");
        else lcd->write("o ");

        sprintf(str, "H:%05d", adc_value);
        lcd->write(str);

        if (i%20 == 0) {
        	r = !r;
            lcd->setCursor(1,0);
        	d2->write(r?1:0);
        	lcd->write(r?"on ":"off");
        }

        usleep(500000);
    }

    //lcd->close();
}
