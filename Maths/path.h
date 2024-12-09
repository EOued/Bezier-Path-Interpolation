#ifndef PATH_H
#define PATH_H

#include <SFML/System/Vector2.hpp>
#include <vector>
class Path
{
private:
  std::vector<sf::Vector2f> points;

public:
  void addPoint(sf::Vector2f point);
  std::vector<sf::Vector2f> getPoints();
  std::vector<sf::Vector2f> LERP(int space);
  std::vector<sf::Vector2f> LERPSmoothed(int space, int dToP);
};

#endif
