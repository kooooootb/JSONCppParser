#include "util.h"

namespace JSON{
    bool isWhitespace(char c){
        return c == ' ' || c == '\n' || c == '\t' || c == '\0';
    }
    bool isDigitLike(char c){
        return c == '-' || (c >= '0' && c <= '9') || c == '.';
    }
}
