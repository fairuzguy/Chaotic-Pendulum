#ifndef PENDULUM
#define PENDULUM

#include "Slider.h"

const double g = 9.81; /// gravity constant
const double pi = 3.14159;

const double DEFAULT_DAMPING = 0.05; /// damping constant
const double DEFAULT_RADIUS = 0.2; /// metres

const double MAX_MASS = 1;
const double MIN_MASS = 0.0001;
const double MAX_INERTIA = 1;
const double MIN_INERTIA = 0.0001;
const double MAX_TORQUE = 2;
const double MIN_TORQUE = 0;
const double MAX_DAMPING = 0.3;
const double MIN_DAMPING = 0;
const double MAX_THETA = 2*pi;
const double MIN_THETA = 0;
const double MAX_PHI = 10;
const double MIN_PHI = 0;
const double MAX_FREQUENCY = 20;
const double MIN_FREQUENCY = 0.0001;
const double MAX_RADIUS = 10;
const double MIN_RADIUS = 0.0001;

class Pendulum
{
public :
    Pendulum(double mass, double momentOfInertia, double torqueForcing,
             double torqueFrequency, double theta0, double phi0, double damping, double radius,
             std::string forcingType, sf::Vector2f pendulumSize, sf::Vector2f position, sf::Font font);

    void DrawPendulum(sf::RenderWindow &window);
    void MouseInput(sf::Event mouseEvent, sf::RenderWindow &window);
    void TimeStep(double timeStep, double currentTime);

private :
    double MomentOfInertia;
    double Mass;
    double TorqueForcing;
    double TorqueFrequency;
    double ResonanceFrequency;
    double Damping;
    double Radius;
    double InitialTheta;
    double InitialAngularVelocity;

    std::string ForcingType;
    sf::Vector2f Size;
    sf::Vector2f Position;

    sf::CircleShape Disc;
    sf::CircleShape SmallMass;
    sf::CircleShape CenterRod;
    sf::RectangleShape VerticalStand;
    sf::RectangleShape HorizontalStand;
    sf::RectangleShape BoundingRectangle;

    Slider* MassSlider;
    Slider* TorqueSlider;
    Slider* MomentOfInertiaSlider;
    Slider* FrequencySlider;
    Slider* DampingSlider;
    Slider* RadiusSlider;
    Slider* InitialThetaSlider;
    Slider* InitialAngularVelocitySlider;

    sf::Text ResonanceText;
    sf::Font PendulumFont;

    double AngularVelocity;
    double Theta;
};

#endif // PENDULUM
