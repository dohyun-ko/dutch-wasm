#include <emscripten/val.h>
#include <emscripten/bind.h>

using namespace emscripten;

extern "C" {
    void handleClick(val event) {

        val::global("console").call<void>("log", std::string("Button clicked!"));
        val::global("alert")(std::string("Button clicked!"));
    }
}

EMSCRIPTEN_BINDINGS(my_module) {
    function("handleClick", &handleClick);
}

int main() {
    val clickMeButton = val::global("document").call<val>("getElementById", std::string("clickMe"));

    val handleClickJS = val::global("Module")["handleClick"];

    clickMeButton.call<void>("addEventListener", std::string("click"), val::module_property("handleClick"));
}
