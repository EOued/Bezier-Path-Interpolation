#ifndef BEZIER_H
#define BEZIER_H

#include <SFML/System/Vector2.hpp>
#include <vector>
class Maths
{
public:
  double Distance(sf::Vector2f p1, sf::Vector2f p2);
  sf::Vector2f Bezier(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2,
                      sf::Vector2f p3, double t);
  std::vector<sf::Vector2f> EvenBezier(sf::Vector2f p0, sf::Vector2f p1,
                                       sf::Vector2f p2, sf::Vector2f p3,
                                       double l);
  sf::Vector2f QuadraticBezier(sf::Vector2f p0, sf::Vector2f p1,
                               sf::Vector2f p2, double t);
  std::vector<sf::Vector2f> QuadraticEvenBezier(sf::Vector2f p0,
                                                sf::Vector2f p1,
                                                sf::Vector2f p2, double l);
};

#endif
