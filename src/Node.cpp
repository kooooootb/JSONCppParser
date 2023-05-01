#include <iostream>

#include "JSON/Node.h"

namespace JSON {
    Node::Node() = default;

    std::ostream &operator<<(std::ostream &ostream, const Node &node){
        node.printNode(ostream, 0);
        return ostream;
    }

    std::stringstream &operator<<(std::stringstream &stringstream, const Node &node){
        node.printNode(stringstream, 0);
        return stringstream;
    }

    void Node::printNode(std::ostream &ostream, int indentation) const {
        indentation += 1;

        if(std::holds_alternative<double>(value)){
            ostream << std::to_string(std::get<double>(value));
        } else if(std::holds_alternative<bool>(value)){
            bool bol = std::get<bool>(value);
            ostream << (bol ? "true" : "false");
        } else if(std::holds_alternative<std::shared_ptr<std::string>>(value)){
            ostream << "\"" << *std::get<String>(value) << "\"";
        } else if(std::holds_alternative<std::monostate>(value)){
            ostream << "null";
        } else if(std::holds_alternative<Array>(value)){
            auto &array = std::get<Array>(value);
            ostream << "[";
            size_t index = 0, size = array->size();
            for(const auto &node : *array){
                node->printNode(ostream, indentation);
                if(index++ < size - 1){
                    ostream << ", ";
                }
            }
            ostream << ']';
        } else if(std::holds_alternative<Object>(value)) {
            auto &object = std::get<Object>(value);
            ostream << "{\n";
            size_t index = 0, size = object->size();
            for (const auto &nodePair: *object) {
                ostream << std::string(indentation, '\t');
                ostream << "\"" << nodePair.first << "\": ";
                nodePair.second->printNode(ostream, indentation);
                if (index++ < size - 1) {
                    ostream << ',';
                }
                ostream << '\n';
            }
            ostream << std::string(indentation - 1, '\t');
            ostream << '}';
        }
    }

    void Node::removeDuplicates() {
        if(std::holds_alternative<Object>(value)){
            auto &map = std::get<Object>(value);
            // std::map при парсинге сама от дубликатов избавляется, ну то есть при вводе не создается новый элемент,
            // а изменяется старый

        }
    }
}
