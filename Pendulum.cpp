#include "Pendulum.h"

double Clamp(double x, double minValue, double maxValue) {
    if (x < minValue) {
        return minValue;
    }
    if (x > maxValue) {
        return maxValue;
    }
    return x;
}

Pendulum::Pendulum(double mass, double momentOfInertia, double torqueForcing,
                   double torqueFrequency, double theta0, double phi0, double damping, double radius,
                   std::string forcingType, sf::Vector2f pendulumSize, sf::Vector2f position, sf::Font font) {
    Mass = mass;
    MomentOfInertia = momentOfInertia;
    TorqueForcing = torqueForcing;
    TorqueFrequency = torqueFrequency;
    ForcingType = forcingType;
    Size = pendulumSize;
    Position = position;
    Theta = theta0;
    AngularVelocity = phi0;
    InitialTheta = theta0;
    InitialAngularVelocity = phi0;
    Damping = damping;
    Radius = radius;

    if (Size.x < 0.5*Size.y) {
        Disc.setRadius(Size.x/2);
    }
    else {
        Disc.setRadius(0.25*Size.y);
    }
    sf::Vector2f VerticalStandSize(0.2*Disc.getRadius(), 0.75*Size.y - Disc.getRadius());
    sf::Vector2f HorizontalStandSize(Size.x/2, 0.2*Disc.getRadius());
    SmallMass.setRadius(0.1*Disc.getRadius());
    CenterRod.setRadius(0.15*Disc.getRadius());
    VerticalStand.setSize(VerticalStandSize);
    HorizontalStand.setSize(HorizontalStandSize);
    BoundingRectangle.setSize(Size);

    Disc.setOrigin(Disc.getRadius(), Disc.getRadius());
    SmallMass.setOrigin(SmallMass.getRadius(), SmallMass.getRadius() - 0.65*Disc.getRadius());
    CenterRod.setOrigin(CenterRod.getRadius(), CenterRod.getRadius());
    VerticalStand.setOrigin(VerticalStand.getSize().x/2, VerticalStand.getSize().y);
    HorizontalStand.setOrigin(HorizontalStand.getSize().x/2, HorizontalStand.getSize().y);

    sf::Vector2f DiscPosition(Position.x + Size.x/2, Position.y + Disc.getRadius());
    sf::Vector2f SmallMassPosition(DiscPosition.x, DiscPosition.y);
    sf::Vector2f CenterRodPosition = DiscPosition;
    sf::Vector2f VerticalStandPosition(Position.x + Size.x/2, Position.y + 0.7*Size.y);
    sf::Vector2f HorizontalStandPosition(Position.x + Size.x/2, Position.y + 0.7*Size.y);
    Disc.setPosition(DiscPosition);
    SmallMass.setPosition(SmallMassPosition);
    CenterRod.setPosition(CenterRodPosition);
    VerticalStand.setPosition(VerticalStandPosition);
    HorizontalStand.setPosition(HorizontalStandPosition);
    BoundingRectangle.setPosition(Position);

    Disc.setFillColor(sf::Color(100, 100, 100, 255));
    SmallMass.setFillColor(sf::Color(255, 215, 0, 255));
    CenterRod.setFillColor(sf::Color(75, 75, 75, 255));
    VerticalStand.setFillColor(sf::Color(75, 75, 75, 255));
    HorizontalStand.setFillColor(sf::Color(75, 75, 75, 255));
    BoundingRectangle.setFillColor(sf::Color(255, 255, 255, 0));

    Disc.setOutlineColor(sf::Color(20, 20, 20, 255));
    Disc.setOutlineThickness(-5);
    CenterRod.setOutlineColor(sf::Color(20, 20, 20, 255));
    CenterRod.setOutlineThickness(-5);

    MassSlider = new Slider(Size.x, MIN_MASS, MAX_MASS, font, "M", sf::Vector2f(Position.x + Size.x/2, Position.y + Size.y*0.77),
                         sf::Vector2f(0.05*Size.x, 0.07*Size.y), sf::Color::Red);
    TorqueSlider = new Slider(Size.x, MIN_TORQUE, MAX_TORQUE, font, "T", sf::Vector2f(Position.x + Size.x/2, Position.y + Size.y*0.86),
                         sf::Vector2f(0.05*Size.x, 0.07*Size.y), sf::Color::Red);
    MomentOfInertiaSlider = new Slider(Size.x, MIN_INERTIA, MAX_INERTIA, font, "I", sf::Vector2f(Position.x + Size.x/2, Position.y + Size.y*0.95),
                         sf::Vector2f(0.05*Size.x, 0.07*Size.y), sf::Color::Red);
    FrequencySlider = new Slider(Size.x, MIN_FREQUENCY, MAX_FREQUENCY, font, "w", sf::Vector2f(Position.x + Size.x/2, Position.y + Size.y*1.04),
                         sf::Vector2f(0.05*Size.x, 0.07*Size.y), sf::Color::Red);
    DampingSlider = new Slider(Size.x, MIN_DAMPING, MAX_DAMPING, font, "D", sf::Vector2f(Position.x + Size.x/2, Position.y + Size.y*1.13),
                         sf::Vector2f(0.05*Size.x, 0.07*Size.y), sf::Color::Red);
    RadiusSlider = new Slider(Size.x, MIN_RADIUS, MAX_RADIUS, font, "R", sf::Vector2f(Position.x + Size.x/2, Position.y + Size.y*1.22),
                         sf::Vector2f(0.05*Size.x, 0.07*Size.y), sf::Color::Red);
    InitialThetaSlider = new Slider(Size.x, MIN_THETA, MAX_THETA, font, "Theta0", sf::Vector2f(Position.x + Size.x/2, Position.y + Size.y*1.31),
                         sf::Vector2f(0.05*Size.x, 0.07*Size.y), sf::Color::Red);
    InitialAngularVelocitySlider = new Slider(Size.x, MIN_PHI, MAX_PHI, font, "Phi0", sf::Vector2f(Position.x + Size.x/2, Position.y + Size.y*1.40),
                         sf::Vector2f(0.05*Size.x, 0.07*Size.y), sf::Color::Red);

    Mass = Clamp(Mass, MIN_MASS, MAX_MASS);
    TorqueForcing = Clamp(TorqueForcing, MIN_TORQUE, MAX_TORQUE);
    MomentOfInertia = Clamp(MomentOfInertia, MIN_INERTIA, MAX_INERTIA);
    TorqueFrequency = Clamp(TorqueFrequency, MIN_FREQUENCY, MAX_FREQUENCY);
    Damping = Clamp(Damping, MIN_DAMPING, MAX_DAMPING);
    Radius = Clamp(Radius, MIN_RADIUS, MAX_RADIUS);
    InitialTheta = Clamp(InitialTheta, MIN_THETA, MAX_THETA);
    InitialAngularVelocity = Clamp(InitialAngularVelocity, MIN_PHI, MAX_PHI);

    MassSlider->SetAlpha((Mass - MIN_MASS)/(MAX_MASS - MIN_MASS));
    TorqueSlider->SetAlpha((TorqueForcing - MIN_TORQUE)/(MAX_TORQUE + MIN_TORQUE));
    MomentOfInertiaSlider->SetAlpha((MomentOfInertia - MIN_INERTIA)/(MAX_INERTIA + MIN_INERTIA));
    FrequencySlider->SetAlpha((TorqueFrequency - MIN_FREQUENCY)/(MAX_FREQUENCY - MIN_FREQUENCY));
    DampingSlider->SetAlpha((Damping - MIN_DAMPING)/(MAX_DAMPING - MIN_DAMPING));
    RadiusSlider->SetAlpha((Radius - MIN_RADIUS)/(MAX_RADIUS - MIN_RADIUS));
    InitialThetaSlider->SetAlpha((InitialTheta - MIN_THETA)/(MAX_THETA - MIN_THETA));
    InitialAngularVelocitySlider->SetAlpha((InitialAngularVelocity - MIN_PHI)/(MAX_PHI - MIN_PHI));

    PendulumFont = font;
    ResonanceText.setFont(PendulumFont);
    ResonanceFrequency = sqrt(Mass*g*Radius/MomentOfInertia);
    ResonanceText.setPosition(sf::Vector2f(position.x + Size.x + 10, position.y + Size.y/3));
    ResonanceText.setString("w0 = " + std::to_string(ResonanceFrequency));
}

void Pendulum::DrawPendulum(sf::RenderWindow &window) {
    window.draw(HorizontalStand);
    window.draw(VerticalStand);
    window.draw(Disc);
    window.draw(SmallMass);
    window.draw(CenterRod);
    MassSlider->DrawSlider(window);
    TorqueSlider->DrawSlider(window);
    MomentOfInertiaSlider->DrawSlider(window);
    FrequencySlider->DrawSlider(window);
    DampingSlider->DrawSlider(window);
    RadiusSlider->DrawSlider(window);
    InitialThetaSlider->DrawSlider(window);
    InitialAngularVelocitySlider->DrawSlider(window);
    window.draw(ResonanceText);
    window.draw(BoundingRectangle);
}

void Pendulum::MouseInput(sf::Event mouseEvent, sf::RenderWindow &window) {
    MassSlider->MouseInput(mouseEvent, window);
    TorqueSlider->MouseInput(mouseEvent, window);
    MomentOfInertiaSlider->MouseInput(mouseEvent, window);
    FrequencySlider->MouseInput(mouseEvent, window);
    DampingSlider->MouseInput(mouseEvent, window);
    RadiusSlider->MouseInput(mouseEvent, window);
    InitialThetaSlider->MouseInput(mouseEvent, window);
    InitialAngularVelocitySlider->MouseInput(mouseEvent, window);
}

void Pendulum::TimeStep(double timeStep, double currentTime) {
    double MassAlpha = MassSlider->GetAlpha();
    double InertiaAlpha = MomentOfInertiaSlider->GetAlpha();
    double TorqueAlpha = TorqueSlider->GetAlpha();
    double FrequencyAlpha = FrequencySlider->GetAlpha();
    double DampingAlpha = DampingSlider->GetAlpha();
    double RadiusAlpha = RadiusSlider->GetAlpha();
    double InitialThetaAlpha = InitialThetaSlider->GetAlpha();
    double InitialAngularVelocityAlpha = InitialAngularVelocitySlider->GetAlpha();

    Mass = MassAlpha*(MAX_MASS - MIN_MASS) + MIN_MASS;
    MomentOfInertia = InertiaAlpha*(MAX_INERTIA - MIN_INERTIA) + MIN_INERTIA;
    TorqueForcing = TorqueAlpha*(MAX_TORQUE - MIN_TORQUE) + MIN_TORQUE;
    TorqueFrequency = FrequencyAlpha*(MAX_FREQUENCY - MIN_FREQUENCY) + MIN_FREQUENCY;
    Damping = DampingAlpha*(MAX_DAMPING - MIN_DAMPING) + MIN_DAMPING;
    Radius = RadiusAlpha*(MAX_RADIUS - MIN_RADIUS) + MIN_RADIUS;

    double dt_I = timeStep/MomentOfInertia;
    double cphi = Damping*AngularVelocity;
    double mgrsintheta = Mass*g*Radius*sin(Theta);
    double tau_t;
    if (ForcingType == "sine") {
        tau_t = TorqueForcing*sin(TorqueFrequency*currentTime);
    }
    else {
        return;
    }
    AngularVelocity += dt_I*(tau_t - cphi - mgrsintheta);
    Theta += AngularVelocity*timeStep;
    std::cout << "THETA: " << Theta << ", PHI: " << AngularVelocity << "\n";
    std::cout << "dt_I: " << dt_I << ", c: " << Damping << ", mgr: " << Mass*Radius*g << "\n";
    std::cout << "tau: " << tau_t << "\n";
    SmallMass.setRotation(-Theta/pi*180);
    ResonanceFrequency = sqrt(Mass*g*Radius/MomentOfInertia);
    ResonanceText.setString("w0 = " + std::to_string(ResonanceFrequency));
}
