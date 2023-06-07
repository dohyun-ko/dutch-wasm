#pragma once

#include <string>

using namespace std;

class Element;

class Style
{
    string width;
    string height;
    string background;
    string margin;
    string padding;
    string border;
    string borderRadius;
    string display;
    string flexDirection;
    string justifyContent;
    string alignItems;
    string gridTemplateColumns;
    string gap;
    string position;
    string top;
    string left;
    string right;
    string bottom;
    string fontSize;
    string color;
    string fontWeight;
    string cursor;
    string boxShadow;
    string textAlign;
    string lineHeight;

    vector<Element *> observers;

    void notify();

public:
    Style();

    ~Style();

    void attach(Element *observer);

    void detach(Element *observer);

    Style &setWidth(const string &width);

    Style &setHeight(const string &height);

    Style &setBackground(const string &background);

    Style &setMargin(const string &margin);

    Style &setPadding(const string &padding);

    Style &setBorder(const string &border);

    Style &setBorderRadius(const string &borderRadius);

    Style &setDisplay(const string &display);

    Style &setFlexDirection(const string &flexDirection);

    Style &setJustifyContent(const string &justifyContent);

    Style &setAlignItems(const string &alignItems);

    Style &setGridTemplateColumns(const string &gridTemplateColumns);

    Style &setGap(const string &gap);

    Style &setPosition(const string &position);

    Style &setTop(const string &top);

    Style &setLeft(const string &left);

    Style &setRight(const string &right);

    Style &setBottom(const string &bottom);

    Style &setFontSize(const string &fontSize);

    Style &setColor(const string &color);

    Style &setFontWeight(const string &fontWeight);

    Style &setCursor(const string &cursor);

    Style &setBoxShadow(const string &boxShadow);

    Style &setTextAlign(const string &textAlign);

    Style &setLineHeight(const string &lineHeight);

    string getCssString() const;

    static string primary;
    static string primaryVariant;
    static string secondary;
    static string secondaryVariant;

    static Style *defaultButtonStyle();
    static Style *defaultInputStyle();
};
