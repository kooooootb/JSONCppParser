#ifndef SBSERVERCLIENT_JSONNODE_H
#define SBSERVERCLIENT_JSONNODE_H

#include <variant>
#include <string>
#include <sstream>

namespace JSON{
    class Node;
}

#include "Object.h"
#include "Array.h"
#include "String.h"

namespace JSON{
    class Node {
    private:
        std::variant<double, bool, String, Array, Object, std::monostate> value;
    public:
        Node();

        template<class T>
        T getValue() const;

        template<class T>
        void setValue(T value_);

        void printNode(std::ostream &ostream, int indentation) const;
        friend std::ostream &operator<<(std::ostream &ostream, const Node &node);
        friend std::stringstream &operator<<(std::stringstream &ostream, const Node &node);

        // remove duplicate keys from object
        void removeDuplicates();
    };

    template<class T>
    T Node::getValue() const { return std::get<T>(value); }

    template<class T>
    void Node::setValue(T value_) { value = value_; }
}

#endif //SBSERVERCLIENT_JSONNODE_H
