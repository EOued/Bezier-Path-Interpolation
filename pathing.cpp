#include "Display/display.h"
#include "Maths/bezier.h"
#include "Maths/path.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>
#include <cmath>
#include <unistd.h>
#include <vector>

int main()
{
  // Initialisation of display class, maths class, path class
  CBezier maths;
  Path path;
  Display display;
  display.window.setFramerateLimit(60);

  // Window loop
  while (display.window.isOpen())
  {

    // Clocking for deltaTime
    static sf::Clock clock;
    float deltaTime = clock.restart().asSeconds();

    // To set a delay between clicks, avoiding the add of 10_000 buttons when clicking once
    static sf::Clock keypressHolding;

    // Windows display
    display.window.display();
    display.window.clear();

    // Displaying al points of the path.
    std::vector<sf::Vector2f> pts = path.getPoints();
    for (int i = 0; i < pts.size(); i++)
    {
      sf::CircleShape bezierPoint1;

      bezierPoint1.setFillColor(sf::Color(149, 148, 227));
      bezierPoint1.setRadius(3);
      bezierPoint1.setOrigin(3, 3);
      bezierPoint1.setPosition(pts[i]);
      display.LazyRender(&bezierPoint1);
    }

    // Linear interpolation
    std::vector<sf::Vector2f> points = path.LERP(10);
    sf::CircleShape lPoint(1);
    lPoint.setFillColor(sf::Color(176, 191, 31));
    lPoint.setOrigin(lPoint.getRadius(), lPoint.getRadius());
    for (int _ = 0; _ < points.size(); _++)
    {
      lPoint.setPosition(points[_]);
      display.LazyRender(&lPoint);
    }

    // Smoothed linear
    points = path.LERPSmoothed(10, 100);
    lPoint.setFillColor(sf::Color(220, 12, 31));
    lPoint.setOrigin(lPoint.getRadius(), lPoint.getRadius());
    for (int _ = 0; _ < points.size(); _++)
    {
      lPoint.setPosition(points[_]);
      display.LazyRender(&lPoint);
    }

    // Mouse events
    sf::Vector2f mousePosition =
        display.window.mapPixelToCoords(sf::Mouse::getPosition(display.window));
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
        keypressHolding.getElapsedTime().asSeconds() > 0.1)
    {
      path.addPoint(mousePosition);
      keypressHolding.restart();
    }
    // Close event
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) &&
         sf::Keyboard::isKeyPressed(sf::Keyboard::C)))
      display.window.close();

    // Handling window resizing
    sf::Event event;
    display.window.pollEvent(event);
    if (event.type == sf::Event::Resized)
    {
      sf::View view(sf::FloatRect(0, 0, event.size.width, event.size.height));
      display.window.setView(view);
    }

    // Rendering everything to the window
    display.Render();
  }

  // When game is done clearing the renderer
  display.DeleteRenderer();
  return 0;
}
