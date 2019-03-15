/**
 * This file is part of PHPinnacle/Buffer.
 *
 * (c) PHPinnacle Team <dev@phpinnacle.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#pragma once
#include <vector>
#include <sstream>
#include <exception>

struct BufferOverflow : public std::exception {};

class Buffer {
public:
    Buffer() noexcept;
    Buffer(const std::vector<unsigned char>&) noexcept;

    void clear() noexcept;
    void discard(unsigned long long n);

    unsigned long long size() const noexcept;
    bool empty() const noexcept;

    void merge(const Buffer&) noexcept;

    std::string flush() noexcept;
    std::string bytes() const noexcept;

    /************************** Writing ***************************/

    template <class T> inline void append(const T &val) noexcept;

    void appendString(const std::string&) noexcept;

    void appendBoolean(bool) noexcept;

    void appendInt8(char) noexcept;
    void appendUInt8(unsigned char) noexcept;

    void appendInt16(short) noexcept;
    void appendUInt16(unsigned short) noexcept;

    void appendInt32(int) noexcept;
    void appendUInt32(unsigned int) noexcept;

    void appendInt64(long long) noexcept;
    void appendUInt64(unsigned long long) noexcept;

    void appendFloat(float) noexcept;
    void appendDouble(double) noexcept;

    /************************** Reading ***************************/

    template <class T> inline T read(unsigned long long offset) const;

    std::string        readString(unsigned long long size, unsigned long long offset) const;

    bool               readBoolean(unsigned long long offset) const;

    char               readInt8(unsigned long long offset) const;
    unsigned char      readUInt8(unsigned long long offset) const;

    short              readInt16(unsigned long long offset) const;
    unsigned short     readUInt16(unsigned long long offset) const;

    int                readInt32(unsigned long long offset) const;
    unsigned int       readUInt32(unsigned long long offset) const;

    long long          readInt64(unsigned long long offset) const;
    unsigned long long readUInt64(unsigned long long offset) const;

    float              readFloat(unsigned long long offset) const;
    double             readDouble(unsigned long long offset) const;

    /************************** Consuming ***************************/

    template <class T> inline T consume();

    std::string        consumeString(unsigned long long size);

    bool               consumeBool();

    char               consumeInt8();
    unsigned char      consumeUInt8();

    short              consumeInt16();
    unsigned short     consumeUInt16();

    int                consumeInt32();
    unsigned int       consumeUInt32();

    long long          consumeInt64();
    unsigned long long consumeUInt64();

    float              consumeFloat();
    double             consumeDouble();

    ~Buffer();
private:
    std::vector<unsigned char> buffer;
};
