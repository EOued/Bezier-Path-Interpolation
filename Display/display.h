#ifndef DISPLAY_H
#define DISPLAY_H

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
class Display
{
private:
  std::vector<sf::Shape*>
      renderer; // List of all things that the program will render (as pointer)
public:
  sf::RenderWindow window;
  Display();
  // Add something to the renderer
  void AddToRenderer(sf::Shape* shape);
  // Render everything that is added to the renderer.
  void Render();
  // Delete all elements of the renderer
  void DeleteRenderer();
  // Render something without adding it to the renderer.
  void LazyRender(sf::Shape* shape);
  sf::CircleShape Cursor(int x, int y, int radius, sf::Color color);
  // Return the distance between two points
};
#endif
