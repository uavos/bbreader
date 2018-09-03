#include "escparser.h"

EscParser::EscParser()
{

}

EscParser::ExtractResult EscParser::extractData(EscParser::DataBuffer &buffer, EscParser::DataBuffer &data)
{
    //find 0x55,0x01 start flag
    auto startPos = std::adjacent_find(buffer.begin(), buffer.end(), [](auto v1, auto v2){
        return v1 == 0x55 && v2 == 0x01;
    });
    if(startPos != buffer.end())
    {
        //startPos always placed at buffer begin, otherwise remove trash bytes
        if(startPos != buffer.begin())
        {
            buffer.erase(buffer.begin(), startPos);
            startPos = buffer.begin();
        }

        //find 0x55,0x02 or 0x55,0x03 end flags
        auto endPos = std::adjacent_find(buffer.begin(), buffer.end(), [](auto v1, auto v2){
            return v1 == 0x55 && v2 == 0x03;
        });

        if(endPos != buffer.end())
        {
            //get real end pos
            std::advance(endPos, 2);

            DataBuffer message(startPos, endPos);
            //unescape
            makeUnescaped(message);

            //get data start and data end iterators
            auto dataStartPos = message.begin() + 2;
            auto dataEndPos = message.end() - 2;
            //if message size > 0
            if(std::distance(dataStartPos, dataEndPos) > 0)
            {
                //calc and check crc
                uint8_t crc = std::accumulate(dataStartPos, std::prev(dataEndPos), uint8_t(0));
                uint8_t messageCrc = *std::prev(dataEndPos);
                bool crcOk = (crc == messageCrc);
                if(crcOk)
                    data.assign(dataStartPos, dataEndPos);

                //remove message from input buffer
                buffer.erase(startPos, endPos);

                if(crcOk)
                    return erOk;
                else
                    return erCrcError;
            }

            //remove message from input buffer
            buffer.erase(startPos, endPos);

            return erUnknownError;
        }
        else
            return erDataEnd;
    }
    else
        return erDataEnd;
}

void EscParser::makeUnescaped(EscParser::DataBuffer &buffer)
{
    for(size_t i = 0; i < buffer.size() - 1; i++)
        if(buffer[i] == 0x55 && buffer[i + 1] == 0x02)
            buffer.erase(buffer.begin() + i + 1);
}
