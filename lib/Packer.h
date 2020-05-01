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
#include <type_traits>

namespace OkraPacked
{
    class Packer
    {
      public:
        /**
         * @brief Construct a new Unpacker object
         * 
         * @param buffer buffer to write packed data
         * @param len byte length of the buffer
         */
        Packer(uint8_t* buffer, const uint32_t len) :
            _buffer(buffer),
            _len(len) {}

        /**
         * @brief Pack unsigned data into the buffer.
         * @todo boundry checks for packing
         * 
         * @tparam T type of data being packed
         * @param bits number of bits to pack
         */
        template <typename T, class = typename std::enable_if<std::is_unsigned<T>::value>::type>
        size_t packUnsigned(const T val, const uint8_t bits)
        {
            uint8_t bitsCount = 0;
            uint8_t numBytes = bits / 8;
            for (int byte = 0; byte <= numBytes; byte++) {
                do {
                    setBit(_buffer + _bytePos, _bitPos, val & (1 << bitsCount));
                    if (++bitsCount >= bits) {
                        if (++_bitPos >= 8) {
                            _bitPos = 0;
                            _bytePos++;
                        }
                        return packedCount();
                    }
                } while (++_bitPos < 8);
                _bitPos = 0;
                _bytePos++;
            }
            return packedCount();
        }

        /**
         * @brief Pack signed data into the buffer.
         * @todo boundry checks for packing
         * 
         * @tparam T type of data being packed
         * @param bits number of bits to pack
         */
        template <typename T, class = typename std::enable_if<std::is_signed<T>::value>::type>
        size_t packSigned(T val, const uint8_t bits)
        {
            if (val < 0) {
                val *= -1;          // 2's compliment
                val |= 1 << bits;   // flag the first bit
            }
            auto uVal = static_cast<typename std::make_unsigned<T>::type>(val);
            return packUnsigned(uVal, bits + 1);
        }

      private:
        uint8_t* _buffer;
        const uint32_t _len;
        uint8_t _bitPos = 0;
        uint32_t _bytePos = 0;

        size_t packedCount()
        {
            return _bytePos * 8 + _bitPos;
        }

        template <typename T>
        void setBit(T* val, const uint8_t bit, const bool setting)
        {
            if (setting) {
                *val |= (1 << bit);
            } else {
                *val &= ~(1 << bit);
            }
        }
    };
}
