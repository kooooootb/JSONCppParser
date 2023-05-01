#ifndef SBSERVERCLIENT_JSONOBJECT_H
#define SBSERVERCLIENT_JSONOBJECT_H

#include <map>
#include <memory>

#include "Node.h"

namespace JSON{
    using Object = std::shared_ptr<std::map<std::string, std::shared_ptr<Node>>>;
}


#endif //SBSERVERCLIENT_JSONOBJECT_H
