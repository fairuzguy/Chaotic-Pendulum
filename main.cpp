#include "Pendulum.h"

const double SCREEN_WIDTH = 1440;
const double SCREEN_HEIGHT = 810;

const double EXPERIMENTAL_TAU = 0.0328847;
const double EXPERIMENTAL_INERTIA = 0.00057507;
const double EXPERIMENTAL_MASS = 0.00452;
const double THETA_0 = 2.5;
const double PHI_0 = 0;
const double ANGULAR_FREQUENCY = 1;
const double EXPERIMENTAL_DAMPING = 0.0021968;
const double EXPERIMENTAL_RADIUS = 0.04516;

int main()
{
    sf::RenderWindow App(sf::VideoMode(SCREEN_WIDTH*1.2, SCREEN_HEIGHT*1.2), "Chaotic Pendulum", sf::Style::Default);

    sf::Font FONT;
    if (!FONT.loadFromFile("Code New Roman.otf")) {
        return EXIT_FAILURE;
    }

    Pendulum Pendulum1(EXPERIMENTAL_MASS, EXPERIMENTAL_INERTIA, EXPERIMENTAL_TAU, ANGULAR_FREQUENCY, THETA_0+0.5, PHI_0,
                       EXPERIMENTAL_DAMPING, EXPERIMENTAL_RADIUS, "sine", sf::Vector2f(400, 600), sf::Vector2f(30, 10), FONT);
    Pendulum Pendulum2(EXPERIMENTAL_MASS, EXPERIMENTAL_INERTIA, EXPERIMENTAL_TAU, ANGULAR_FREQUENCY, THETA_0, PHI_0,
                       EXPERIMENTAL_DAMPING, EXPERIMENTAL_RADIUS, "sine", sf::Vector2f(400, 600), sf::Vector2f(800, 10), FONT);

    sf::Clock FrameClock;
    sf::Time OldTime;

    while (App.isOpen())
    {
        double timeStep = (FrameClock.getElapsedTime().asSeconds() - OldTime.asSeconds());
        OldTime = FrameClock.getElapsedTime();
        Pendulum1.TimeStep(timeStep, FrameClock.getElapsedTime().asSeconds());
        Pendulum2.TimeStep(timeStep, FrameClock.getElapsedTime().asSeconds());

        // Process events
        sf::Event event;
        while (App.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed) {
                App.close();
            }
            if (event.type == sf::Event::MouseButtonPressed ||
                event.type == sf::Event::MouseButtonReleased ||
                event.type == sf::Event::MouseMoved) {
                Pendulum1.MouseInput(event, App);
                Pendulum2.MouseInput(event, App);
            }
        }

        App.clear();

        Pendulum1.DrawPendulum(App);
        Pendulum2.DrawPendulum(App);

        App.display();
    }

    return EXIT_SUCCESS;
}
