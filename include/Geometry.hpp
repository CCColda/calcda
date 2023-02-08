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
    friend struct std::hash<Line>;

  private:
    Vector2 m_begin;
    Vector2 m_end;
    LineType m_type;

  public:
    Line(Vector2 begin, Vector2 end, LineType type);

    std::tuple<Vector2, Vector2> getPoints() const;

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
    friend struct std::hash<Circle>;

  protected:
    Vector2 m_origin;
    float m_radius;

  public:
    Circle(Vector2 origin, float radius = 1.0f);
    virtual ~Circle() = default;

    Vector2 getOrigin() const;
    float getRadius() const;

    virtual bool isPointInside(Vector2 point) const final;
    virtual std::vector<Vector2>
    intersectLine(Vector2 a, Vector2 b,
                  LineType type = LineType::LINE) const final;
};

class Polygon : public Shape {
    friend struct std::hash<Polygon>;

  public:
    struct EdgeIntersection {
        Vector2 intersection;
        Line segment;

        inline bool operator==(const EdgeIntersection &other) const {
            //! @todo
            return intersection == other.intersection &&
                   segment.getPoints() == other.segment.getPoints();
        }
    };

  protected:
    std::vector<Vector2> m_points;

  private:
    void calculateMinmax();

  public:
    Polygon(const std::vector<Vector2> &points);
    Polygon(std::initializer_list<Vector2> list);
    virtual ~Polygon() = default;

    std::vector<Vector2> getPoints() const;

    virtual bool isPointInside(Vector2 point) const override;

    std::vector<EdgeIntersection>
    intersectLineEx(Vector2 a, Vector2 b, LineType type = LineType::LINE) const;

    virtual std::vector<Vector2>
    intersectLine(Vector2 a, Vector2 b,
                  LineType type = LineType::LINE) const override;
};
} // namespace Calcda

namespace std {
template <> struct hash<Calcda::Line> {
    size_t operator()(const Calcda::Line &v) const noexcept {
        return Calcda::Internal::hash_combine(
            hash<Calcda::Vector2>()(v.m_begin),
            hash<Calcda::Vector2>()(v.m_end), static_cast<unsigned>(v.m_type));
    }
};
template <> struct hash<Calcda::Circle> {
    size_t operator()(const Calcda::Circle &v) const noexcept {
        return Calcda::Internal::hash_combine(
            hash<Calcda::Vector2>()(v.m_origin), hash<float>()(v.m_radius));
    }
};
template <> struct hash<Calcda::Polygon::EdgeIntersection> {
    size_t
    operator()(const Calcda::Polygon::EdgeIntersection &v) const noexcept {
        return Calcda::Internal::hash_combine(
            hash<Calcda::Vector2>()(v.intersection),
            hash<Calcda::Line>()(v.segment));
    }
};
template <> struct hash<Calcda::Polygon> {
    size_t operator()(const Calcda::Polygon &v) const noexcept {
        if (v.m_points.empty())
            return 0;

        size_t result = hash<Calcda::Vector2>()(v.m_points.at(0));

        for (std::size_t i = 1; i < v.m_points.size(); ++i) {
            result = Calcda::Internal::hash_combine(
                result, hash<Calcda::Vector2>()(v.m_points.at(i)));
        }

        return result;
    }
};
} // namespace std

#endif // !defined(CALCDA_GEOMETRY_H)