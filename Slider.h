#ifndef SLIDER
#define SLIDER

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

class Slider
{
public :
    Slider(float length, float minValue, float maxValue, sf::Font sliderFont, std::string baseText,
           sf::Vector2f centerPosition, sf::Vector2f handleSize, sf::Color themeColor);

    bool WithinSliderHandle(sf::Vector2i position);
    void MouseInput(sf::Event mouseEvent, sf::RenderWindow &window);
    void SetText();
    void SetRange(float minValue, float maxValue);
    float GetAlpha();
    void SetAlpha(float newAlpha);
    void DrawSlider(sf::RenderWindow &window);

private :
    sf::RectangleShape Handle;
    sf::RectangleShape LeftEnd;
    sf::RectangleShape RightEnd;
    sf::RectangleShape SliderRod;

    sf::Font SliderFont;
    sf::Text SliderText;

    float MinValue;
    float MaxValue;
    std::string BaseText;
    float Alpha;
    bool Active = false;
};

#endif // SLIDER
