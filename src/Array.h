#ifndef SBSERVERCLIENT_JSONARRAY_H
#define SBSERVERCLIENT_JSONARRAY_H

#include <list>
#include <memory>

#include "Node.h"

namespace JSON {
    using Array = std::list<std::shared_ptr<Node>>;
}


#endif //SBSERVERCLIENT_JSONARRAY_H
