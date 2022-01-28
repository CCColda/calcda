#ifndef CALCDA_GEOMETRY_H
#define CALCDA_GEOMETRY_H

#include "Vector2.hpp"
#include <initializer_list>
#include <optional>
#include <vector>

namespace Calcda {
enum class LineType { LINE, RAY, SEGMENT };

class Shape {
  protected:
    //! @brief Top left corner of the bounding rectangle
    Vector2 m_xymin;

    //! @brief Bottom right corner of the bounding rectangle
    Vector2 m_xymax;

  protected:
    Shape(Vector2 xymin = Vector2::Zero, Vector2 xymax = Vector2::Zero);

  public:
    std::tuple<Vector2, Vector2> getBoundingRectangle() const;
    bool isPointInsideBoundingRectangle(Vector2 point) const;
    bool
    doesLineIntersectBoundingRectangle(Vector2 a, Vector2 b,
                                       LineType type = LineType::LINE) const;

    virtual bool isPointInside(Vector2 point) const = 0;
    virtual std::vector<Vector2>
    intersectLine(Vector2 a, Vector2 b,
                  LineType type = LineType::LINE) const = 0;
};

class Line : public Shape {
  private:
    Vector2 m_begin;
    Vector2 m_end;
    LineType m_type;

  public:
    Line(Vector2 begin, Vector2 end, LineType type);

    virtual std::vector<Vector2>
    intersectLine(Vector2 a, Vector2 b,
                  LineType type = LineType::LINE) const final;
    virtual bool isPointInside(Vector2 point) const final;

    std::vector<Vector2> intersectLine(const Line &other) const;

    static std::optional<Vector2> intersectRaw(Vector2 l1a, Vector2 l1b,
                                               LineType l1t, Vector2 l2a,
                                               Vector2 l2b, LineType l2t);
};

class Circle : public Shape {
  protected:
    Vector2 m_origin;
    float m_radius;

  public:
    Circle(Vector2 origin, float radius = 1.0f);
    virtual ~Circle() = default;

    virtual bool isPointInside(Vector2 point) const final;
    virtual std::vector<Vector2>
    intersectLine(Vector2 a, Vector2 b,
                  LineType type = LineType::LINE) const final;
};

class Polygon : public Shape {
  protected:
    std::vector<Vector2> m_points;

  private:
    void calculateMinmax();

  public:
    Polygon(const std::vector<Vector2> &points);
    Polygon(std::initializer_list<Vector2> list);
    virtual ~Polygon() = default;

    virtual bool isPointInside(Vector2 point) const override;
    virtual std::vector<Vector2>
    intersectLine(Vector2 a, Vector2 b,
                  LineType type = LineType::LINE) const override;
};
} // namespace Calcda

#endif // !defined(CALCDA_GEOMETRY_H)