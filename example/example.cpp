/*
 * Okra Packed
 * Copyright (C) 2020 Okra Solar Pty Ltd
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

#include "Packer.h"
#include "Unpacker.h"
#include <iostream>

int main()
{
    uint8_t buffer[1000] = {0};
    OkraPacked::Packer packer(buffer, sizeof(buffer));

    int repeatCount = 31;
    int bits = 17;
    int32_t val = -15116;
    size_t packedCount;

    // Pack a bunch of data
    for (int i = 0; i < repeatCount; i++) {
        packedCount = packer.packSigned(val++, bits);
    }

    OkraPacked::Unpacker unpacker(buffer, packedCount);

    // unpack a bunch of data
    for (int i = 0; i < repeatCount; i++) {
        if (--val != unpacker.unpackSigned<int32_t>(bits)) {
            printf("FAILED! Corruptions in a unpacked value\n");
            return 0;
        }
    }

    printf("Successfully packed and unpacked a bunch of data\n");
    return 0;
}
