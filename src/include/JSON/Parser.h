#ifndef SBSERVERCLIENT_PARSER_H
#define SBSERVERCLIENT_PARSER_H

#include <memory>

#include "Node.h"
#include "Tokenizer.h"
#include "Token.h"

namespace JSON {
    template<class TStream>
    class Parser {
    private:
        std::shared_ptr<Node> root = nullptr;
        std::unique_ptr<Node> current = nullptr;

        Tokenizer<TStream> tokenizer;

        void parse();
    public:
        Parser(TStream &istream_);

        std::shared_ptr<Node> parseObject();
        std::shared_ptr<Node> parseArray();
        std::shared_ptr<Node> parseString(Token &token);
        std::shared_ptr<Node> parseNumber(Token &token);
        std::shared_ptr<Node> parseBoolean(Token &token);
        std::shared_ptr<Node> parseNull();

        std::shared_ptr<Node> getRoot() const;
    };

    template<class TStream>
    Parser<TStream>::Parser(TStream &istream_) : tokenizer(istream_) {
        parse();
    }

    template<class TStream>
    void Parser<TStream>::parse() {
        while(tokenizer.hasMoreTokens()){
            Token token = tokenizer.getToken();
            std::shared_ptr<Node> node;

            switch(token.type){
                case Tokens::CURLY_OPEN:
                    node = parseObject();
                    break;
                case Tokens::ARRAY_OPEN:
                    node = parseArray();
                    break;
                case Tokens::STRING:
                    node = parseString(token);
                    break;
                case Tokens::NUMBER:
                    node = parseNumber(token);
                    break;
                case Tokens::BOOLEAN:
                    node = parseBoolean(token);
                    break;
                default:
                    throw std::runtime_error("invalid token");
            }

            if(root == nullptr){
                root = node;
            }
        }
    }

    template<class TStream>
    std::shared_ptr<Node> Parser<TStream>::parseArray() {
        std::shared_ptr<Node> node = std::make_shared<Node>();
        Array array;

        while(true){
            if(!tokenizer.hasMoreTokens()){
                throw std::runtime_error("invalid array syntax, need closing bracket");
            } else{
                Token token = tokenizer.getToken();
                std::shared_ptr<Node> curNode;

                switch(token.type){
                    case Tokens::ARRAY_OPEN:
                        curNode = parseArray();
                        break;
                    case Tokens::CURLY_OPEN:
                        curNode = parseObject();
                        break;
                    case Tokens::STRING:
                        curNode = parseString(token);
                        break;
                    case Tokens::NUMBER:
                        curNode = parseNumber(token);
                        break;
                    case Tokens::BOOLEAN:
                        curNode = parseBoolean(token);
                        break;
                    case Tokens::NULLTYPE:
                        curNode = parseNull();
                        break;
                    default:
                        throw std::runtime_error("invalid syntax while parsing array");
                }

                array->push_back(curNode);
                token = tokenizer.getToken();
                if(token.type == Tokens::ARRAY_CLOSED){
                    break;
                } else if(token.type != Tokens::COMMA){
                    throw std::runtime_error("need comma between values in array");
                }
            }
        }

        node->setValue(array);
        return node;
    }

    template<class TStream>
    std::shared_ptr<Node> Parser<TStream>::parseObject() {
        std::shared_ptr<Node> node = std::make_shared<Node>();
        Object object;
        while(true){
            if(!tokenizer.hasMoreTokens()){
                throw std::runtime_error("invalid syntax while parsing object, need closing bracket");
            } else{
                Token keyToken = tokenizer.getToken();
                std::string &key = keyToken.value;

                Token colon = tokenizer.getToken();
                if(colon.type != Tokens::COLON){
                    throw std::runtime_error("need colon in object");
                }

                Token token = tokenizer.getToken();

                switch(token.type) {
                    case Tokens::STRING:
                        (*object)[key] = parseString(token);
                        break;
                    case Tokens::ARRAY_OPEN:
                        (*object)[key] = parseArray();
                        break;
                    case Tokens::NUMBER:
                        (*object)[key] = parseNumber(token);
                        break;
                    case Tokens::BOOLEAN:
                        (*object)[key] = parseBoolean(token);
                        break;
                    case Tokens::CURLY_OPEN:
                        (*object)[key] = parseObject();
                        break;
                    case Tokens::NULLTYPE:
                        (*object)[key] = parseNull();
                        break;
                    default:
                        throw std::runtime_error("invalid syntax in object parsing");
                }

                Token comma = tokenizer.getToken();
                if(comma.type == Tokens::CURLY_CLOSED){
                    break;
                } else if(comma.type != Tokens::COMMA){
                    throw std::runtime_error("need comma between values in object");
                }
            }
        }

        node->setValue(object);
        return node;
    }

    template<class TStream>
    std::shared_ptr<Node> Parser<TStream>::parseString(Token &token) {
        std::shared_ptr<Node> node = std::make_shared<Node>();
        String string = std::make_shared<String::element_type>(token.value);
        node->setValue(string);
        return node;
    }

    template<class TStream>
    std::shared_ptr<Node> Parser<TStream>::parseNumber(Token &token) {
        std::shared_ptr<Node> node = std::make_shared<Node>();
        std::string string = token.value;
        double number = std::stod(string);
        node->setValue(number);
        return node;
    }

    template<class TStream>
    std::shared_ptr<Node> Parser<TStream>::parseBoolean(Token &token) {
        std::shared_ptr<Node> node = std::make_shared<Node>();
        std::string string = token.value;
        node->setValue(string == "True");
        return node;
    }

    template<class TStream>
    std::shared_ptr<Node> Parser<TStream>::parseNull() {
        std::shared_ptr<Node> node = std::make_shared<Node>();
        node->setValue(std::monostate());
        return node;
    }

    template<class TStream>
    std::shared_ptr<Node> Parser<TStream>::getRoot() const {
        return root;
    }
}


#endif //SBSERVERCLIENT_PARSER_H
