/*
 * Okra Packed
 * Copyright (C) 2019 Okra Solar Pty Ltd
 * https://www.okrasolar.com/
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#pragma once

#include <bitset>
#include <cstdint>

namespace OkraPacked
{
    class Unpacker
    {
      public:
        /**
         * @brief Construct a new Unpacker object
         * 
         * @param buffer  
         * @param len Number of used bits in the packed buffer.
         */
        Unpacker(const uint8_t* buffer, const uint32_t len) :
            _buffer(buffer),
            _bytePos((len - 1)/8),
            _bitPos((len-1) % 8) 
        {}

        /**
         * @brief Unpack data from the buffer.
         * 
         * @tparam T type to unpack
         * @param bits number of bits to unpack
         * @return T unpacked value
         */
        template<typename T>
        T unpack(const uint8_t bits)
        {
            T ret = 0;
            int8_t bitsCount = bits - 1;
            uint8_t numBytes = bits / 8;
            for (int byte = numBytes; byte > -1; byte--) {
                do {
                    // printf("byte: %02X\n", _buffer[_bytePos]);
                    bool binVal = (_buffer[_bytePos] & (1 << _bitPos)) > 0;
                    setBit(&ret, bitsCount, binVal);
                    if (--bitsCount < 0) {
                        if (--_bitPos < 0) {
                            _bitPos = 7;
                            _bytePos--;
                        };
                        return ret;
                    }
                } while (_bitPos-- > 0);
                _bitPos = 7;
                _bytePos--;
            }
            return ret;
        }

      private:
        const uint8_t* _buffer;
        int8_t _bytePos;
        int8_t _bitPos;

        template<typename T>
        void setBit(T* var, const uint8_t bit, const bool val)
        {
            if (val) {
                *var |= (1 << bit);
            } else {
                *var &= ~(1 << bit);
            }
        }
    };
}
