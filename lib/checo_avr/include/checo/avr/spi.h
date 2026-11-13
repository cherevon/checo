/*
 * MIT License
 *
 * Copyright (c) 2026 Sergei Cherevichko
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include "avr.h"

namespace checo::avr
{

// Software SPI protocol
template <typename DataPort, uint8_t DataPin, typename ClockPort, uint8_t ClockPin>
class SoftSpi
{
  public:
    SoftSpi() = default;
    ~SoftSpi() = default;

    void shiftOut(uint8_t value, const uint8_t size = 8)
    {
        volatile uint8_t &dataPort = DataPort::port();
        volatile uint8_t &clockPort = ClockPort::port();

        constexpr uint8_t dataMask = (1 << DataPin);
        constexpr uint8_t clockMask = (1 << ClockPin);

        for (uint8_t i = 0; i < size; i++) {
            if (value & 1) {
                dataPort |= dataMask;
            } else {
                dataPort &= ~dataMask;
            }
            value >>= 1;

            clockPort |= clockMask;
            clockPort &= ~clockMask;
        }
    }
};

} // namespace checo::avr
