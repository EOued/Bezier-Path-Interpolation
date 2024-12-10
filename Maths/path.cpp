#include "path.h"
#include "bezier.h"
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <unistd.h>
#include <vector>

void Path::addPoint(sf::Vector2f point)
{
  this->points.push_back(point);
  return;
}

std::vector<sf::Vector2f> Path::getPoints() { return this->points; }

double Lerp(double x, sf::Vector2f p0, sf::Vector2f p1)
{
  return p0.y + (x - p0.x) * ((p1.y - p0.y) / (p1.x - p0.x));
}

std::vector<sf::Vector2f> LERPAux(int space, sf::Vector2f p0, sf::Vector2f p1)
{
  CBezier maths;
  std::vector<sf::Vector2f> interpolation;
  double distance = 0;
  sf::Vector2f point;
  sf::Vector2f oldPoint;
  distance = 0;
  interpolation.push_back(p0);
  // Not vertical line
  if (p0.x != p1.x)
  {
    oldPoint = sf::Vector2f(std::min(p0.x, p1.x), std::min(p0.y, p1.y));
    for (double x = std::min(p0.x, p1.x); x <= std::max(p0.x, p1.x); x += 0.01)
    {
      point = sf::Vector2f(x, Lerp(x, p0, p1));
      distance += maths.Distance(oldPoint, point);
      if (distance > space)
      {
        interpolation.push_back(point);
        distance = 0;
      }
      oldPoint = point;
    }
  }
  // Vertical line
  else
  {
    oldPoint = sf::Vector2f(std::min(p0.x, p1.x), std::min(p0.y, p1.y));
    for (double y = p0.y; y <= p1.y; y += space)
    {
      point = sf::Vector2f(p0.x, y);
      distance += maths.Distance(oldPoint, point);
      if (distance > space)
      {
        interpolation.push_back(point);
        distance = 0;
      }
      oldPoint = point;
    }
    interpolation.push_back(p1);
  }
  return interpolation;
}

std::vector<sf::Vector2f> Path::LERP(int space)
{
  CBezier maths;
  int n = this->points.size();
  std::vector<sf::Vector2f> interpolation;
  std::vector<sf::Vector2f> interpolationAux;
  double distance = 0;
  sf::Vector2f point;
  sf::Vector2f oldPoint;

  for (int i = 0; i < n - 1; i++)
  {
    interpolationAux = LERPAux(space, this->points[i], this->points[i + 1]);
    interpolation.insert(interpolation.end(), interpolationAux.begin(), interpolationAux.end());
  }
  return interpolation;
}

std::vector<sf::Vector2f> Path::LERPSmoothed(int space, int dToP)
{
  CBezier maths;
  int n = this->points.size();
  std::vector<sf::Vector2f> interpolation;
  double distance = 0;
  sf::Vector2f controlPoint;
  sf::Vector2f startPoint;
  sf::Vector2f goalPoint;
  sf::Vector2f start;
  sf::Vector2f end;
  double dRatio;
  if (n == 2)
  {
    std::vector<sf::Vector2f> lerp1 = LERPAux(space, this->points[0], this->points[1]);
    interpolation.insert(interpolation.end(), lerp1.begin(), lerp1.end());
    return interpolation;
  }
  for (int i = 0; i < n - 2; i++)
  {
    controlPoint = this->points[i + 1];
    distance     = maths.Distance(this->points[i], controlPoint);
    dRatio       = ((double)dToP) / distance;

    startPoint = sf::Vector2f((1 - dRatio) * controlPoint.x + dRatio * this->points[i].x,
                              (1 - dRatio) * controlPoint.y + dRatio * this->points[i].y);
    if (dRatio < 0 || dRatio > 1) startPoint = this->points[i];
    distance = maths.Distance(controlPoint, this->points[i + 2]);
    dRatio   = ((double)dToP) / distance;

    goalPoint = sf::Vector2f((1 - dRatio) * controlPoint.x + dRatio * this->points[i + 2].x,
                             (1 - dRatio) * controlPoint.y + dRatio * this->points[i + 2].y);
    if (dRatio < 0 || dRatio > 1) goalPoint = this->points[i + 2];

    if (i == 0) start = this->points[i];
    else
    {
      distance = maths.Distance(this->points[i], controlPoint);
      dRatio   = ((double)dToP) / distance;

      start = sf::Vector2f((1 - dRatio) * controlPoint.x + dRatio * this->points[i].x,
                           (1 - dRatio) * controlPoint.y + dRatio * this->points[i].y);
    }

    if (i == n - 3) end = this->points[i + 2];
    else
    {
      distance = maths.Distance(controlPoint, this->points[i + 2]);
      dRatio   = ((double)dToP) / distance;
      end      = sf::Vector2f((1 - dRatio) * this->points[i + 2].x + dRatio * controlPoint.x,
                              (1 - dRatio) * this->points[i + 2].y + dRatio * controlPoint.y);
    }

    std::vector<sf::Vector2f> lerp1 = LERPAux(space, start, startPoint);
    std::vector<sf::Vector2f> smooth =
        maths.QuadraticEvenBezier(startPoint, controlPoint, goalPoint, space);
    std::vector<sf::Vector2f> lerp2 = LERPAux(space, goalPoint, end);

    interpolation.insert(interpolation.end(), lerp1.begin(), lerp1.end());
    interpolation.insert(interpolation.end(), smooth.begin(), smooth.end());
    interpolation.insert(interpolation.end(), lerp2.begin(), lerp2.end());
  }
  return interpolation;
}
