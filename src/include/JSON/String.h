#ifndef JSONPARSER_STRING_H
#define JSONPARSER_STRING_H

#include <memory>
#include <string>

namespace JSON{
    using String = std::shared_ptr<std::string>;
}

#endif //JSONPARSER_STRING_H
