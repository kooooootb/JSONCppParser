#ifndef SBSERVERCLIENT_TOKEN_H
#define SBSERVERCLIENT_TOKEN_H

#include <string>

namespace JSON{
    enum class Tokens{
        NULLTYPE = 0, NUMBER, BOOLEAN, STRING, ARRAY_OPEN, ARRAY_CLOSED, CURLY_OPEN, CURLY_CLOSED, COMMA, COLON
    };

    struct Token{
        std::string value;
        Tokens type;

        std::string get();
    };

}

#endif //SBSERVERCLIENT_TOKEN_H
