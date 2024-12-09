#include "display.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/WindowHandle.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <cmath>

Display::Display()
    : window(sf::VideoMode(200, 200),
             "Bezier Curves") // Initialize the RenderWindow
{
}

void Display::AddToRenderer(sf::Shape* shape)
{
  this->renderer.push_back(shape);
  return;
}

void Display::DeleteRenderer()
{
  for (int i = 0; i < this->renderer.size(); i++) delete this->renderer[i];
  return;
}

void Display::Render()
{
  for (int i = 0; i < this->renderer.size(); i++)
    this->window.draw(*(this->renderer[i]));
  return;
}

void Display::LazyRender(sf::Shape* shape) { this->window.draw(*shape); }

sf::CircleShape Display::Cursor(int x, int y, int radius, sf::Color color)
{
  sf::CircleShape cursor;

  cursor.setRadius(radius);
  cursor.setOrigin(radius, radius);
  cursor.setPosition(x, y);
  cursor.setFillColor(color);
  return cursor;
}

// void Display::renderBezier(Hunter hunter)
// {
//   sf::CircleShape start(3);
//   start.setFillColor(sf::Color(0, 0, 255));
//   start.setOrigin(start.getRadius(), start.getRadius());

//   start.setPosition(hunter.getStart().first, hunter.getStart().second);

//   sf::CircleShape goal(3);
//   goal.setFillColor(sf::Color(164, 14, 209));
//   goal.setOrigin(goal.getRadius(), goal.getRadius());

//   goal.setPosition(hunter.getGoal().first, hunter.getGoal().second);

//   sf::CircleShape startDirection(3);
//   startDirection.setFillColor(sf::Color(0, 150, 255));
//   startDirection.setOrigin(startDirection.getRadius(),
//                            startDirection.getRadius());

//   startDirection.setPosition(hunter.getStartDirection().first,
//                              hunter.getStartDirection().second);

//   sf::CircleShape goalDirection(3);
//   goalDirection.setFillColor(sf::Color(164, 140, 209));
//   goalDirection.setOrigin(goalDirection.getRadius(),
//   goalDirection.getRadius());

//   goalDirection.setPosition(hunter.getGoalDirection().first,
//                             hunter.getGoalDirection().second);

//   // Lines for control point showing
//   sf::VertexArray lines(sf::Lines, 2);
//   lines[0] = sf::Vector2f(hunter.getGoal().first,
//   hunter.getGoal().second); lines[1] =
//   sf::Vector2f(hunter.getGoalDirection().first,
//                           hunter.getGoalDirection().second);

//   sf::VertexArray lines2(sf::Lines, 2);
//   lines2[0] = sf::Vector2f(hunter.getStart().first,
//   hunter.getStart().second); lines2[1] =
//   sf::Vector2f(hunter.getStartDirection().first,
//                            hunter.getStartDirection().second);

//   // Show bezier curve

//   sf::CircleShape bezier(2);
//   bezier.setFillColor(sf::Color(255, 0, 188));
//   bezier.setOrigin(bezier.getRadius(), bezier.getRadius());

//   int x;
//   int y;
//   for (double t = 0.0; t <= 1; t += 0.005)
//   {
//     x = hunter.bezier(t, hunter.getStart().first,
//                       hunter.getStartDirection().first,
//                       hunter.getGoalDirection().first,
//                       hunter.getGoal().first);
//     y = hunter.bezier(
//         t, hunter.getStart().second, hunter.getStartDirection().second,
//         hunter.getGoalDirection().second, hunter.getGoal().second);
//     bezier.setPosition(x, y);
//     this->window.draw(bezier);
//   }
//   this->window.draw(start);
//   this->window.draw(goal);
//   this->window.draw(startDirection);
//   this->window.draw(goalDirection);
//   this->window.draw(lines);
//   this->window.draw(lines2);
//   return;
// }

// void Display::renderPlayer(Player& player)
// {

//   sf::CircleShape shape((int)player.getRadius() * 2);
//   shape.setOrigin(shape.getRadius(),
//                   shape.getRadius()); // set the shape color to green
//   if (typeid(player) == typeid(Prey))
//     shape.setFillColor(sf::Color(100, 250, 50));
//   else
//     shape.setFillColor(sf::Color(250, 100, 50));
//   shape.setPosition(player.getX(), player.getY());
//   if (typeid(player) == typeid(Prey)) this->window.clear();
//   this->window.draw(shape);
//   return;
// }
