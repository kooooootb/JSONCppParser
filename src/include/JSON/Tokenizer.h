#ifndef SBSERVERCLIENT_TOKENIZE_H
#define SBSERVERCLIENT_TOKENIZE_H

#include <string>
#include <istream>
#include <memory>
#include <map>

#include "util.h"
#include "Token.h"

namespace JSON{
    template<class TStream>
    class Tokenizer{
    private:
        TStream &istream;

        std::map<char, Tokens> tokensMap = {
                {'n', Tokens::NULLTYPE},
                {'-', Tokens::NUMBER},
                {'1', Tokens::NUMBER},
                {'2', Tokens::NUMBER},
                {'3', Tokens::NUMBER},
                {'4', Tokens::NUMBER},
                {'5', Tokens::NUMBER},
                {'6', Tokens::NUMBER},
                {'7', Tokens::NUMBER},
                {'8', Tokens::NUMBER},
                {'9', Tokens::NUMBER},
                {'0', Tokens::NUMBER},
                {'f', Tokens::BOOLEAN},
                {'t', Tokens::BOOLEAN},
                {'"', Tokens::STRING},
                {'{', Tokens::CURLY_OPEN},
                {'}', Tokens::CURLY_CLOSED},
                {'[', Tokens::ARRAY_OPEN},
                {']', Tokens::ARRAY_CLOSED},
                {':', Tokens::COLON},
                {',', Tokens::COMMA},
        };

        char peek();
        char get();
        void skip(int skipping);

    public:
        explicit Tokenizer(TStream &istream_);

        char getNextCharacter();
        Token getToken();
        bool hasMoreTokens();

    };

    template<class TStream>
    Tokenizer<TStream>::Tokenizer(TStream &istream_) : istream(istream_) {}

    template<class TStream>
    char Tokenizer<TStream>::getNextCharacter() {
        char result;
        do{
            if(istream.bad()){
                throw std::runtime_error("no more tokens");
            }
            result = get();
        } while(isWhitespace(result));

        return result;
    }

    template<class TStream>
    bool Tokenizer<TStream>::hasMoreTokens() {
        char c;
        while(true){
            c = peek();

            if(!istream.good()){
                return false;
            }

            if(isWhitespace(c)){
                get();
            } else{
                return true;
            }
        }
    }

    template<class TStream>
    Token Tokenizer<TStream>::getToken() {
        if(istream.bad()){
            throw std::runtime_error("can't get more tokens");
        }

        char c = getNextCharacter();

        Token token;
        token.type = tokensMap.find(c)->second;
        switch(token.type){
            case Tokens::STRING:
                token.value = "";
                while(true){
                    c = get();
                    if(c == '"'){
                        break;
                    } else{
                        token.value += c;
                    }
                }
                break;
            case Tokens::NUMBER:
            {
                bool first = true;
                token.value = "";
                while(true){
                    if(istream.bad()){
                        break;
                    } else {
                        if(isDigitLike(c)){
                            token.value += c;
                            if(first){
                                first = false;
                            } else {
                                get();
                            }
                        } else{
                            break;
                        }
                    }

                    c = peek();
                }
                break;
            }
            case Tokens::BOOLEAN:
                if(c == 'f'){
                    token.value = "False"; // why big
                    skip(4);
                } else{
                    token.value = "True";
                    skip(3);
                }
                break;
            case Tokens::NULLTYPE:
                skip(3);
                break;
            default:
                //
                break;
        }

        return token;
    }

    template<class TStream>
    char Tokenizer<TStream>::peek() {
//        char result;
//        do {
//            result = istream->peek();
//        } while(result == '\0');
//        return result;
        return istream.peek();
    }

    template<class TStream>
    char Tokenizer<TStream>::get() {
//        char result;
//        do {
//            result = istream->get();
//        } while(result == '\0');
//        return result;
        return istream.get();
    }

    template<class TStream>
    void Tokenizer<TStream>::skip(int skipping) {
//        istream.seekg(3, std::ios_base::cur); // for some reason it fails and skips more than needed
        for(int i = 0;i < skipping;++i){
            get();
        }
    }
}

#endif //SBSERVERCLIENT_TOKENIZE_H
