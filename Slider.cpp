#include "Slider.h"

Slider::Slider(float length, float minValue, float maxValue, sf::Font sliderFont, std::string baseText,
               sf::Vector2f centerPosition, sf::Vector2f handleSize, sf::Color themeColor) {
    MinValue = minValue;
    MaxValue = maxValue;
    SliderFont = sliderFont;
    BaseText = baseText;

    sf::Vector2f EndSize(1, handleSize.y);
    sf::Vector2f SliderSize(length, 1);

    Handle.setSize(handleSize);
    LeftEnd.setSize(EndSize);
    RightEnd.setSize(EndSize);
    SliderRod.setSize(SliderSize);

    Handle.setPosition(centerPosition);
    LeftEnd.setPosition(sf::Vector2f(centerPosition.x - length/2, centerPosition.y));
    RightEnd.setPosition(sf::Vector2f(centerPosition.x + length/2, centerPosition.y));
    SliderRod.setPosition(centerPosition);

    Handle.setOrigin(handleSize.x/2, handleSize.y/2);
    LeftEnd.setOrigin(EndSize.x/2, EndSize.y/2);
    RightEnd.setOrigin(EndSize.x/2, EndSize.y/2);
    SliderRod.setOrigin(SliderSize.x/2, SliderSize.y/2);

    Handle.setFillColor(themeColor);
    Handle.setOutlineColor(sf::Color(themeColor.r - 10, themeColor.g - 10, themeColor.b - 10));
    LeftEnd.setFillColor(sf::Color(themeColor.r + 20, themeColor.g + 20, themeColor.b + 20));
    RightEnd.setFillColor(sf::Color(themeColor.r + 20, themeColor.g + 20, themeColor.b + 20));
    SliderRod.setFillColor(sf::Color(themeColor.r + 20, themeColor.g + 20, themeColor.b + 20));

    LeftEnd.setOutlineThickness(3);
    RightEnd.setOutlineThickness(3);
    SliderRod.setOutlineThickness(3);

    SliderText.setFont(SliderFont);
    SliderText.setPosition(RightEnd.getPosition().x + 10, RightEnd.getPosition().y - RightEnd.getSize().y/2);
}

bool Slider::WithinSliderHandle(sf::Vector2i position) {
    if (position.x >= Handle.getPosition().x - Handle.getSize().x/2 &&
        position.x <= Handle.getPosition().x + Handle.getSize().x/2 &&
        position.y >= Handle.getPosition().y - Handle.getSize().y/2 &&
        position.y <= Handle.getPosition().y + Handle.getSize().y/2) {
        return true;
    }
    else {
        return false;
    }
}

void Slider::MouseInput(sf::Event mouseEvent, sf::RenderWindow &window) {
    if (mouseEvent.mouseButton.button == sf::Mouse::Left) {
        if (Active && mouseEvent.type == sf::Event::MouseButtonReleased) {
            Active = false;
        }
        else if (!Active && mouseEvent.type == sf::Event::MouseButtonPressed &&
                 WithinSliderHandle(sf::Mouse::getPosition(window))) {
            Active = true;
            /// visual stuff
        }
    }

    if (Active && mouseEvent.type == sf::Event::MouseMoved) {
        int mousePositionX = mouseEvent.mouseMove.x;
        if (mousePositionX > RightEnd.getPosition().x) {
            mousePositionX = RightEnd.getPosition().x;
        }
        else if (mousePositionX < LeftEnd.getPosition().x) {
            mousePositionX = LeftEnd.getPosition().x;
        }
        sf::Vector2f NewPosition(mousePositionX, Handle.getPosition().y);
        Handle.setPosition(NewPosition);
        Alpha = (mousePositionX - LeftEnd.getPosition().x)/SliderRod.getSize().x;
        if (Alpha <= 0) {
            Alpha = 0.0001;
        }
        if (Alpha > 1) {
            Alpha = 1;
        }
        SetText();
    }
}

void Slider::SetText() {
    SliderText.setString(BaseText + ": " + std::to_string(Alpha*(MaxValue - MinValue) + MinValue));
}

void Slider::SetRange(float minValue, float maxValue) {
    MinValue = minValue;
    MaxValue = maxValue;
    SetText();
}

float Slider::GetAlpha() {
    return Alpha;
}

void Slider::SetAlpha(float newAlpha) {
    Alpha = newAlpha;
    sf::Vector2f NewPosition(Alpha*SliderRod.getSize().x + LeftEnd.getPosition().x, Handle.getPosition().y);
    Handle.setPosition(NewPosition);
    SetText();
}

void Slider::DrawSlider(sf::RenderWindow &window) {
    window.draw(SliderRod);
    window.draw(LeftEnd);
    window.draw(RightEnd);
    window.draw(Handle);
    window.draw(SliderText);
}
