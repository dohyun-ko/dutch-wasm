#include "Style.h"
#include "../element/Element.h"
#include <string>

using namespace std;

string Style::primaryBlue = "#30A2FF";
string Style::secondaryBlue = "#00C4FF";
string Style::primaryYellow = "#FFE7A0";
string Style::secondaryYellow = "#FFF5B8";

Style *Style::defaultButtonStyle()
{
    Style *style = new Style();

    style->setWidth("200px")
        .setHeight("44px")
        .setBackground(Style::primaryBlue)
        .setBorder("none")
        .setBorderRadius("6px")
        .setFontSize("1rem")
        .setColor("#FFFFFF")
        .setPadding("0 25px")
        .setBoxShadow("2px 4px 3px rgba(0, 0, 0, 0.15)")
        .setCursor("pointer")
        .setFontWeight("500");

    return style;
}

Style *Style::defaultInputStyle()
{
    Style *style = new Style();
    style->setWidth("148px")
        .setHeight("44px")
        .setBackground(Style::secondaryYellow)
        .setBorder("none")
        .setBorderRadius("6px")
        .setFontSize("1rem")
        .setColor("#000000")
        .setPadding("0 25px")
        .setBoxShadow("inset 2px 2px 3px rgba(0, 0, 0, 0.15)");

    return style;
}

Style::Style() {}

Style::~Style() {}

void Style::notify()
{
    for (Element *observer : observers)
    {
        observer->update();
    }
}

void Style::attach(Element *observer)
{
    observers.push_back(observer);
}

void Style::detach(Element *observer)
{
    observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
}

Style &Style::setWidth(const string &width)
{
    this->width = width;
    return *this;
}

/**
 * Scott, Effective C++: 41. 이동이 저렴하고 항상 복사되는 복사 가능 매개변수에 대해서는 값 전달을 고려하라 - by 송혜근 선배
 *
 * Style& Style::setWidth(string width) {
 *    this->width = std::move(width);
 *    return *this;
 * }
 */

Style &Style::setHeight(const string &height)
{
    this->height = height;
    notify();
    return *this;
}

Style &Style::setBackground(const string &background)
{
    this->background = background;
    notify();
    return *this;
}

Style &Style::setMargin(const string &margin)
{
    this->margin = margin;
    notify();
    return *this;
}

Style &Style::setPadding(const string &padding)
{
    this->padding = padding;
    notify();
    return *this;
}

Style &Style::setBorder(const string &border)
{
    this->border = border;
    notify();
    return *this;
}

Style &Style::setBorderRadius(const string &borderRadius)
{
    this->borderRadius = borderRadius;
    notify();
    return *this;
}

Style &Style::setDisplay(const string &display)
{
    this->display = display;
    notify();
    return *this;
}

Style &Style::setFlexDirection(const string &flexDirection)
{
    this->flexDirection = flexDirection;
    notify();
    return *this;
}

Style &Style::setJustifyContent(const string &justifyContent)
{
    this->justifyContent = justifyContent;
    notify();
    return *this;
}

Style &Style::setAlignItems(const string &alignItems)
{
    this->alignItems = alignItems;
    notify();
    return *this;
}

Style &Style::setGridTemplateColumns(const string &gridTemplateColumns)
{
    this->gridTemplateColumns = gridTemplateColumns;
    notify();
    return *this;
}

Style &Style::setGap(const string &gap)
{
    this->gap = gap;
    notify();
    return *this;
}

Style &Style::setPosition(const string &position)
{
    this->position = position;
    notify();
    return *this;
}

Style &Style::setTop(const string &top)
{
    this->top = top;
    notify();
    return *this;
}

Style &Style::setLeft(const string &left)
{
    this->left = left;
    notify();
    return *this;
}

Style &Style::setRight(const string &right)
{
    this->right = right;
    notify();
    return *this;
}

Style &Style::setBottom(const string &bottom)
{
    this->bottom = bottom;
    notify();
    return *this;
}

Style &Style::setFontSize(const string &fontSize)
{
    this->fontSize = fontSize;
    notify();
    return *this;
}

Style &Style::setColor(const string &color)
{
    this->color = color;
    notify();
    return *this;
}

Style &Style::setFontWeight(const string &fontWeight)
{
    this->fontWeight = fontWeight;
    notify();
    return *this;
}

Style &Style::setCursor(const string &cursor)
{
    this->cursor = cursor;
    notify();
    return *this;
}

Style &Style::setBoxShadow(const string &boxShadow)
{
    this->boxShadow = boxShadow;
    notify();
    return *this;
}

string Style::getCssString() const
{
    string cssString = "";

    if (width != "")
    {
        cssString += "width: " + width + "; ";
    }

    if (height != "")
    {
        cssString += "height: " + height + "; ";
    }

    if (background != "")
    {
        cssString += "background: " + background + "; ";
    }

    if (margin != "")
    {
        cssString += "margin: " + margin + "; ";
    }

    if (padding != "")
    {
        cssString += "padding: " + padding + "; ";
    }

    if (border != "")
    {
        cssString += "border: " + border + "; ";
    }

    if (borderRadius != "")
    {
        cssString += "border-radius: " + borderRadius + "; ";
    }

    if (display != "")
    {
        cssString += "display: " + display + "; ";
    }

    if (flexDirection != "")
    {
        cssString += "flex-direction: " + flexDirection + "; ";
    }

    if (justifyContent != "")
    {
        cssString += "justify-content: " + justifyContent + "; ";
    }

    if (alignItems != "")
    {
        cssString += "align-items: " + alignItems + "; ";
    }

    if (gridTemplateColumns != "")
    {
        cssString += "grid-template-columns: " + gridTemplateColumns + "; ";
    }

    if (gap != "")
    {
        cssString += "gap: " + gap + "; ";
    }

    if (position != "")
    {
        cssString += "position: " + position + "; ";
    }

    if (top != "")
    {
        cssString += "top: " + top + "; ";
    }

    if (left != "")
    {
        cssString += "left: " + left + "; ";
    }

    if (right != "")
    {
        cssString += "right: " + right + "; ";
    }

    if (bottom != "")
    {
        cssString += "bottom: " + bottom + "; ";
    }

    if (fontSize != "")
    {
        cssString += "font-size: " + fontSize + "; ";
    }

    if (color != "")
    {
        cssString += "color: " + color + "; ";
    }

    if (fontWeight != "")
    {
        cssString += "font-weight: " + fontWeight + "; ";
    }

    if (cursor != "")
    {
        cssString += "cursor: " + cursor + "; ";
    }

    if (boxShadow != "")
    {
        cssString += "box-shadow: " + boxShadow + "; ";
    }

    return cssString;
}