/*
 * MIT License
 *
 * Copyright (c) 2024 Sergei Cherevichko
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

#include "checo_trading_export.h"

#include <chrono>
#include <cmath>

namespace checo::trading
{

struct CHECO_TRADING_EXPORT PriceBar
{
  public:
    inline bool bearish() const
    {
        return m_PriceClose < m_PriceOpen;
    }

    inline bool bullish() const
    {
        return m_PriceClose > m_PriceOpen;
    }

    inline bool doji() const
    {
        return std::fabs(m_PriceClose - m_PriceOpen) < 1e-10;
    }

  public:
    double m_PriceOpen{0.0};
    double m_PriceClose{0.0};
    double m_PriceHigh{0.0};
    double m_PriceLow{0.0};
    std::chrono::system_clock::time_point m_TimeStart{};
    std::chrono::system_clock::time_point m_TimeEnd{};
};

} // namespace checo::trading