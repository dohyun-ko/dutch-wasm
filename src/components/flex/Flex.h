#pragma once

#include <emscripten/val.h>
#include <string>

#include "../element/Element.h"

using namespace emscripten;
using namespace std;

class Flex: public Element {
public:
    Flex(    
        string direction = "row",
        string justifyContent = "center",
        string alignItems = "center",
        string gap = "0"
    );
    
    virtual ~Flex() override;
};

