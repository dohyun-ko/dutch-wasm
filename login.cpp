#include <emscripten/val.h>
#include <string>

using namespace emscripten;
using namespace std;

class Element {
    val element;
    static int idCount;
    
public:
    Element(string tag) {
        element = val::global("document").call<val>("createElement", val(tag));
    }

    virtual ~Element() {
        element.call<void>("remove");
    }

    void appendTo(val parent) {
        parent.call<void>("appendChild", element);
    }

    val getElement() {
        return element;
    }
};


class Button: public Element {
    string text;

public:
    Button(string text) : Element("button"), text(text) {
        getElement().set("innerHTML", text);
        getElement().set("style", "width: 200px; background-color: #405cf5; border-radius: 6px; border-width: 0; box-shadow: rgba(50, 50, 93, .1) 0 0 0 1px inset,rgba(50, 50, 93, .1) 0 2px 5px 0,rgba(0, 0, 0, .07) 0 1px 1px 0; height: 44px; outline: none; padding: 0 25px; position: relative; text-align: center; transform: translateZ(0); transition: all .2s,box-shadow .08s ease-in; cursor: pointer; color: #FFFFFF;");
    }
};

class OutlinedButton : public Button {
public:
    OutlinedButton(string text) : Button(text) {
        getElement().set("style", "border: 1px solid black");
    }
};

class Input {
    val element;

public:
    Input(string placeholder = "") {
        element = val::global("document").call<val>("createElement", val("input"));
        element.set("placeholder", placeholder);
        element.set("style", "width: 148px; border: 1px solid black; border-radius: 6px; height: 44px; outline: none; padding: 0 25px; position: relative; text-align: center; transform: translateZ(0); transition: all .2s,box-shadow .08s ease-in; cursor: pointer; color: #FFFFFF;");
    }

    void appendTo(val parent) {
        parent.call<void>("appendChild", element);
    }

    val getElement() {
        return element;
    }
};

class Flex: public Element {
public:
    Flex(
        string direction = "row",
        string justifyContent = "center",
        string alignItems = "center",
        string gap = "0"
    ) : Element("div") {
        getElement().set("style", "display: flex; flex-direction: " + direction + "; justify-content: " + justifyContent + "; align-items: " + alignItems + "; gap: " + gap + ";");
    }
};

val getElementById(string id) {
    return val::global("document").call<val>("getElementById", val(id));
}

int main() {
    val root = getElementById("root");

    Flex container("column", "center", "center", "10px");
    Button loginButton("Login");
    Input usernameInput("Username");
    Input passwordInput("Password");

    container.appendTo(root);
    usernameInput.appendTo(container.getElement());
    passwordInput.appendTo(container.getElement());
    loginButton.appendTo(container.getElement());

}
