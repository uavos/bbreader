#ifndef ESCPARSER_H
#define ESCPARSER_H

#include <vector>
#include <stdint.h>
#include <algorithm>
#include <numeric>

class EscParser
{
public:
    enum ExtractResult
    {
        erOk,
        erDataEnd,
        erCrcError,
        erUnknownError
    };
    using DataBuffer = std::vector<uint8_t>;
    EscParser();

    ExtractResult extractData(DataBuffer &buffer, DataBuffer &data);
    void makeUnescaped(DataBuffer &buffer);
};

#endif // ESCPARSER_H
