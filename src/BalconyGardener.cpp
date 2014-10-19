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

#include "Regelkreis.hpp"
#include "SensorInput.hpp"
#include "Regler.hpp"

#include "jhd1313m1.h"
#include "unistd.h"

using namespace mraa;

// 0x62 RGB_ADDRESS, 0x3E LCD_ADDRESS
upm::Jhd1313m1 *lcd = new upm::Jhd1313m1(0, 0x3E, 0x62);

void control()
{
	SensorInput* sensorInput = Regelkreis::Instance()->getSensorInput();
	Regler* regler = Regelkreis::Instance()->getRegler();
	static int loop_count = 0;
	static char str[256];

	sensorInput->readSensors();

	lcd->setCursor(0,15);
    if ((loop_count++)%2 == 0) lcd->write(". ");
    else lcd->write("o ");

    lcd->setCursor(0,0);
	// 1. Zeile
	sprintf(str, "H:%04d ", sensorInput->getHumidity());
	lcd->write(str);
	sprintf(str, "W:%04d", sensorInput->getWaterLevel());
    lcd->write(str);

    // 2. Zeile
    lcd->setCursor(1,0);
	sprintf(str,"T:%04d ", sensorInput->getTemperature());
    lcd->write(str);
	sprintf(str, "L:%04d", sensorInput->getLight());
    lcd->write(str);

    if (loop_count%20 == 0)
    {
    	lcd->setCursor(0,15);
        lcd->write("v");
    	regler->openValveForTimeSpan(5000);
    }
}

void communicate()
{
}

int main(int argc, char **argv)
{
	while(true)
	{
		control();
		communicate();
		usleep(500000);
	}
}
