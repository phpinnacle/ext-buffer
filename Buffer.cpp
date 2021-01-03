/**
 * This file is part of PHPinnacle/Buffer.
 *
 * (c) PHPinnacle Team <dev@phpinnacle.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#include "Buffer.hpp"

/************************* COMMON *************************/
Buffer::Buffer() noexcept {
}

Buffer::Buffer(const std::vector<unsigned char> &_buffer) noexcept:
    buffer(_buffer) {
}

void Buffer::clear() noexcept {
    buffer.clear();
}

void Buffer::write(char * str, long length) noexcept {
    buffer.insert(buffer.end(), str, str + length);
}

void Buffer::discard(unsigned long long n) {
    if (buffer.size() < n)
        throw BufferOverflow();

    buffer.erase(buffer.begin(), buffer.begin() + n);
}

unsigned long long Buffer::size() const noexcept {
    return buffer.size();
}

bool Buffer::empty() const noexcept {
    return buffer.empty();
}

void Buffer::merge(const Buffer &other) noexcept {
    buffer.insert(buffer.end(), other.buffer.begin(), other.buffer.end());
}

std::string Buffer::bytes() const noexcept {
    std::stringstream stream;

    unsigned long long size = buffer.size();
    for (unsigned long long i = 0; i < size; ++i)
        stream << buffer[i];

    return stream.str();
}

std::string Buffer::flush() noexcept {
    std::string out = bytes();

    clear();

    return out;
}

/************************* WRITING *************************/
template <class T> inline void Buffer::append(const T &val) noexcept {
    unsigned int size = sizeof(T);
    unsigned const char *array = reinterpret_cast<unsigned const char*>(&val);

    for (unsigned int i = 0; i < size; ++i)
        buffer.push_back(array[size - i - 1]);
}

void Buffer::appendBoolean(bool val) noexcept {
    append<bool>(val);
}

void Buffer::appendString(const std::string &str) noexcept {
    for (const unsigned char &s : str) appendInt8(s);
}

void Buffer::appendInt8(char val) noexcept {
    append<char>(val);
}
void Buffer::appendUint8(unsigned char val) noexcept {
    append<unsigned char>(val);
}

void Buffer::appendInt16(short val) noexcept {
    append<short>(val);
}
void Buffer::appendUint16(unsigned short val) noexcept {
    append<unsigned short>(val);
}

void Buffer::appendInt32(int val) noexcept {
    append<int>(val);
}
void Buffer::appendUint32(unsigned int val) noexcept {
    append<unsigned int>(val);
}

void Buffer::appendInt64(long long val) noexcept {
    append<long long>(val);
}
void Buffer::appendUint64(unsigned long long val) noexcept {
    append<unsigned long long>(val);
}

void Buffer::appendFloat(float val) noexcept {
    union { float fnum; unsigned long inum; } u;
    u.fnum = val;
    appendUint32(u.inum);
}
void Buffer::appendDouble(double val) noexcept {
    union { double fnum; unsigned long long inum; } u;
    u.fnum = val;
    appendUint64(u.inum);
}

/************************* READING *************************/
template <class T> inline T Buffer::read(unsigned long long offset) const {
    T result = 0;
    unsigned int size = sizeof(T);

    if (offset + size > buffer.size())
        throw BufferOverflow();

    char *dst = (char*) &result;
    char *src = (char*) &buffer[offset];

    for (unsigned int i = 0; i < size; ++i)
        dst[i] = src[size - i - 1];

    return result;
}

bool Buffer::readBoolean(unsigned long long offset) const {
    return read<bool>(offset);
}

std::string Buffer::readString(unsigned long long size, unsigned long long offset) const {
    if (offset + size > buffer.size())
        throw BufferOverflow();

    std::string result(buffer.begin() + offset, buffer.begin() + offset + size);

    return result;
}

char Buffer::readInt8(unsigned long long offset) const {
    return read<char>(offset);
}
unsigned char Buffer::readUint8(unsigned long long offset) const {
    return read<unsigned char>(offset);
}

short Buffer::readInt16(unsigned long long offset) const {
    return read<short>(offset);
}
unsigned short Buffer::readUint16(unsigned long long offset) const {
    return read<unsigned short>(offset);
}

int Buffer::readInt32(unsigned long long offset) const {
    return read<int>(offset);
}
unsigned int Buffer::readUint32(unsigned long long offset) const {
    return read<unsigned int>(offset);
}

long long Buffer::readInt64(unsigned long long offset) const {
    return read<long long>(offset);
}
unsigned long long Buffer::readUint64(unsigned long long offset) const {
    return read<unsigned long long>(offset);
}

float Buffer::readFloat(unsigned long long offset) const {
    return read<float>(offset);
}
double Buffer::readDouble(unsigned long long offset) const {
    return read<double>(offset);
}

/************************* CONSUMING *************************/
template <class T> inline T Buffer::consume() {
    T result = 0;
    unsigned int size = sizeof(T);

    if (size > buffer.size())
        throw BufferOverflow();

    char *dst = (char*) &result;
    char *src = (char*) &buffer[0];

    for (unsigned int i = 0; i < size; ++i)
        dst[i] = src[size - i - 1];

    buffer.erase(buffer.begin(), buffer.begin() + size);

    return result;
}

bool Buffer::consumeBool() {
    return consume<bool>();
}

std::string Buffer::consumeString(unsigned long long size) {
    if (size > buffer.size())
        throw BufferOverflow();

    std::string result(buffer.begin(), buffer.begin() + size);

    buffer.erase(buffer.begin(), buffer.begin() + size);

    return result;
}

char Buffer::consumeInt8() {
    return consume<char>();
}
unsigned char Buffer::consumeUint8() {
    return consume<unsigned char>();
}

short Buffer::consumeInt16() {
    return consume<short>();
}
unsigned short Buffer::consumeUint16() {
    return consume<unsigned short>();
}

int Buffer::consumeInt32() {
    return consume<int>();
}
unsigned int Buffer::consumeUint32() {
    return consume<unsigned int>();
}

long long Buffer::consumeInt64() {
    return consume<long long>();
}
unsigned long long Buffer::consumeUint64() {
    return consume<unsigned long long>();
}

float Buffer::consumeFloat() {
    return consume<float>();
}
double Buffer::consumeDouble() {
    return consume<double>();
}

Buffer::~Buffer() {
    clear();
}
