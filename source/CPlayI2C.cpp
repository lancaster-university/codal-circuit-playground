/*
The MIT License (MIT)

Copyright (c) 2017 Lancaster University.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#include "CPlayI2C.h"
#include "Event.h"
#include "CodalCompat.h"
#include "ErrorNo.h"
#include "codal_target_hal.h"
#include "CodalDmesg.h"

namespace mb=::mbed;

using namespace codal;


CPlayI2C::CPlayI2C(codal::Pin& sda, codal::Pin& scl) : codal::_mbed::I2C(sda, scl)
{
}

int CPlayI2C::write(uint16_t address, uint8_t *data, int len, bool repeated = false)
{
    return mb::I2C::write(address, (const char *)data,len,repeated);
}

int CPlayI2C::read(uint16_t address, uint8_t *data, int len, bool repeated = false)
{
    return mb::I2C::read(address, (char *)data,len,repeated);
}