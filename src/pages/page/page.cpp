#include <emscripten/val.h>

#include "page.h"
#include "../../components/element/Element.h"

using namespace emscripten;;

Page::Page() : Element("div") {
    
}