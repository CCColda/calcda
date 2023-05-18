#include "Geometry.hpp"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <unordered_set>

namespace Calcda {

/** @protected */ Shape::Shape(Vector2 xymin, Vector2 xymax)
    : m_xymin(xymin), m_xymax(xymax) {}

std::tuple<Vector2, Vector2> Shape::getBoundingRectangle() const {
    return {m_xymin, m_xymax};
}

bool Shape::isPointInsideBoundingRectangle(Vector2 point) const {
    return m_xymin.x <= point.x && point.x <= m_xymax.x &&
           m_xymin.y <= point.y && point.y <= m_xymax.y;
}

bool Shape::doesLineIntersectBoundingRectangle(Vector2 a, Vector2 b,
                                               LineType type) const {
    if (isPointInsideBoundingRectangle(a) || isPointInsideBoundingRectangle(b))
        return true;

    if (Line::intersectRaw(m_xymin, {m_xymax.x, m_xymin.y}, LineType::SEGMENT,
                           a, b, type))
        return true;
    if (Line::intersectRaw(m_xymin, {m_xymin.x, m_xymax.y}, LineType::SEGMENT,
                           a, b, type))
        return true;
    if (Line::intersectRaw({m_xymax.x, m_xymin.y}, m_xymax, LineType::SEGMENT,
                           a, b, type))
        return true;
    if (Line::intersectRaw({m_xymin.x, m_xymax.y}, m_xymax, LineType::SEGMENT,
                           a, b, type))
        return true;

    return false;
};

#pragma region Line

Line::Line(Vector2 begin, Vector2 end, LineType type)
    : Shape(), m_begin(begin), m_end(end), m_type(type) {
    if (begin.lengthSquared() <= end.lengthSquared()) {
        m_xymin = begin;
        m_xymax = end;
    } else {
        m_xymin = end;
        m_xymax = begin;
    }
}

std::tuple<Vector2, Vector2> Line::getPoints() const {
    return {m_begin, m_end};
}

/* virtual */ bool Line::isPointInside(Vector2 point) const /* final */
{
    if (!isPointInsideBoundingRectangle(point))
        return false;

    const auto direction = m_end - m_begin;

    if (direction.x == 0.0f)
        return point.x == m_begin.x;

    const float slope = direction.y / direction.x;

    return (slope * (point.x - m_begin.x) + m_begin.y) == point.y;
}

/* virtual */ std::vector<Vector2>
Line::intersectLine(Vector2 a, Vector2 b, LineType type) const /* final */
{
    const auto intersectResult =
        intersectRaw(m_begin, m_end, m_type, a, b, type);
    return intersectResult.has_value() ? std::vector<Vector2>{*intersectResult}
                                       : std::vector<Vector2>{};
}

std::vector<Vector2> Line::intersectLine(const Line &other) const {
    return intersectLine(other.m_begin, other.m_end, other.m_type);
}

using IntersectionCheckFunction = bool (*)(float, float);
using IntersectionCheckTableEntry =
    std::pair<std::pair<LineType, LineType>, IntersectionCheckFunction>;
constexpr static const IntersectionCheckTableEntry IntersectionCheckTable[] = {
    std::make_pair(std::make_pair(LineType::LINE, LineType::LINE),
                   [](float s, float t) { return true; }),
    std::make_pair(std::make_pair(LineType::SEGMENT, LineType::SEGMENT),
                   [](float s, float t) {
                       return 0.0f <= s && s <= 1.0f && 0.0f <= t && t <= 1.0f;
                   }),
    std::make_pair(std::make_pair(LineType::SEGMENT, LineType::RAY),
                   [](float seg_intersect, float ray_intersect) {
                       return 0.0f <= seg_intersect && seg_intersect <= 1.0f &&
                              ray_intersect >= 0.0f;
                   }),
    std::make_pair(std::make_pair(LineType::SEGMENT, LineType::LINE),
                   [](float s, float t) { return 0.0f <= s && s <= 1.0f; }),
    std::make_pair(std::make_pair(LineType::RAY, LineType::RAY),
                   [](float s, float t) { return s >= 0.0f && t >= 0.0f; }),
    std::make_pair(std::make_pair(LineType::RAY, LineType::LINE),
                   [](float s, float t) { return 0.0f >= s; })};

/* static */ std::optional<Vector2> Line::intersectRaw(Vector2 l1a, Vector2 l1b,
                                                       LineType l1t,
                                                       Vector2 l2a, Vector2 l2b,
                                                       LineType l2t) {
    /*
    l1(t) = l1a + t * (l1b - l1a)
    l2(t) = l2a + t * (l2b - l2a)

    l1(t1) = l2(t2) ==>
    l1a + t1 * (l1a - l1b) = l2a + t2 * (l2a - l2b) // -l1a; -t * (l2a - l2b)
    t * (l1a - l1b) - t2 * (l2a - l2b) = l2a - l1a
    */

    const auto v1 = l1a - l1b, v2 = l2a - l2b, sd = l1a - l2a;

    const auto determinant =
        v2.y * v1.x - v1.y * v2.x; // v1.x * v2.y - v1.y * v2.x;
    if (determinant == 0.0f)       // lines are parallel
        return std::nullopt;       // TODO: parallel rays, lines

    const float inverseDeterminant = 1.0f / determinant;

    const auto l1ratio = inverseDeterminant * (sd.x * v2.y - sd.y * v2.x),
               l2ratio = inverseDeterminant * (sd.x * v1.y - sd.y * v1.x);

    const auto checkEntry = std::find_if(
        std::begin(IntersectionCheckTable), std::end(IntersectionCheckTable),
        [l1t, l2t](const auto &entry) {
            return (entry.first.first == l1t && entry.first.second == l2t) ||
                   (entry.first.second == l1t && entry.first.first == l2t);
        });

    if (checkEntry == std::end(IntersectionCheckTable))
        return std::nullopt;

    const bool switched = checkEntry->first.first == l2t;

    return checkEntry->second(switched ? l2ratio : l1ratio,
                              switched ? l1ratio : l2ratio)
               ? std::optional<Vector2>(l1a -
                                        Vector2::scalar(l1ratio) * (l1a - l1b))
               : std::nullopt;
}

// Line
#pragma endregion

#pragma region Circle

Circle::Circle(Vector2 origin, float radius)
    : Shape(origin - Vector2::scalar(radius), origin + Vector2::scalar(radius)),
      m_origin(origin), m_radius(radius) {}

Vector2 Circle::getOrigin() const { return m_origin; }

float Circle::getRadius() const { return m_radius; }

/* virtual */ bool Circle::isPointInside(Vector2 point) const /* final */
{
    return (m_origin - point).absolute().lengthSquared() <
           (m_radius * m_radius);
}

/**
 * @brief Returns the intersection points of a line and the circle
 * \f[
        m=\frac{B_x-A_x}{B_y-A_y} \\
        g(x)=x-O_x \\
        b(x)=m*x - m*B_x + B_y \\
        q(x)=g(x)^2 + (b(x)-O_y)^2 - r^2 \\
        \Longrightarrow \\
        q(x)=(x-O_x)^2 + ((m*x-m*B_x+B_y)-O_y)^2 - r^2 \\\\
        q(x)=(x^2 - 2*x*O_x + O_x^2) + (m*x - m*B_x + B_y - O_y)^2 - r^2 \\
        q(x)=(1x^2-2O_x*x+O_x^2)+(m*x + (B_y - m*B_x - O_y))^2 - r^2 \\
        q(x)=... + ((m*x)^2 + 2(B_y - m*B_x - O_y)*m*x + (B_y - m*B_x - O_y)^2)
 - r^2 \\
        q(x)=1x^2 -2O_x*x +O_x^2 + m^2*x^2 + 2(B_y - m*B_x - O_y)*m*x + (B_y -
 m*B_x - O_y)^2 - r^2 \\
        q(x)=(1+m^2)x^2+(-2O_x+2(B_y - m*B_x - O_y)*m)x+(O_x^2+(B_y - m*B_x -
 O_y)^2-r^2) \\
        q(x)=(1+m^2)x^2+2(-O_x+(B_y - m*B_x - O_y)*m)x+(O_x^2+(B_y - m*B_x -
 O_y)^2-r^2) \\
        \Longrightarrow \\
        q(x)=a*x^2 + b*x + c
 * \f]
 */
std::vector<Vector2> Circle::intersectLine(Vector2 a, Vector2 b,
                                           LineType type) const {
    const auto aInside = isPointInside(a);
    const auto bInside = isPointInside(b);

    if (a == b && aInside)
        return {a};
    else
        return {};

    if (aInside && bInside)
        return {a, b};
    else if (aInside)
        return {a};
    else if (bInside)
        return {b};

    const auto bavector = b - a;
    const auto to = bavector.y != 0 ? m_origin : m_origin.yx(),
               ta = bavector.y != 0 ? a : a.yx(),
               tb = bavector.y != 0 ? b : b.yx();
    const float m = bavector.y != 0 ? (bavector.x) / (bavector.y) : 0.0f;

    const float qa = 1.0f + std::pow(m, 2),
                qb = 2.0f * (-to.x + m * (tb.y - to.y - tb.x * m)),
                qc = std::pow(to.x, 2.0f) +
                     std::pow(tb.y - to.y - tb.x * m, 2.0f) -
                     std::pow(m_radius, 2.0f);

    const float determinant = std::pow(qb, 2.0f) - 4.0f * qa * qc;

    if (determinant < 0.0f)
        return {};

    if (determinant == 0.0f) {
        const float x = (-std::pow(qb, 2.0f)) / (2.0f * qa);
        const auto y = m * x - tb.x * m + b.y;

        return {bavector.y != 0 ? Vector2{x, y} : Vector2{y, x}};
    }
    const float determinantSqrt = std::sqrt(determinant);

    const float x1 = (-std::pow(qb, 2.0f) + determinantSqrt) / (2.0f * qa),
                x2 = (-std::pow(qb, 2.0f) - determinantSqrt) / (2.0f * qa);
    const auto y1 = m * x1 - tb.x * m + b.y, y2 = m * x2 - tb.x * m + b.y;

    return {(bavector.y != 0 ? Vector2{x1, y1} : Vector2{y1, x1}),
            (bavector.y != 0 ? Vector2{x2, y2} : Vector2{y2, x2})};
}

// Circle
#pragma endregion

#pragma region Polygon

/* private */ void Polygon::calculateMinmax() {
    if (m_points.empty()) {
        m_xymin = m_xymax = Calcda::Vector2::Zero;
        return;
    }

    auto [xmin, xmax] = std::minmax_element(
        m_points.begin(), m_points.end(),
        [](const Vector2 &a, const Vector2 &b) -> bool { return a.x < b.x; });

    auto [ymin, ymax] = std::minmax_element(
        m_points.begin(), m_points.end(),
        [](const Vector2 &a, const Vector2 &b) -> bool { return a.y < b.y; });

    m_xymin = {xmin->x, ymin->y};
    m_xymax = {xmax->x, ymax->y};
}

Polygon::Polygon(const std::vector<Vector2> &points)
    : Shape(), m_points(points) {
    calculateMinmax();
}

Polygon::Polygon(const Polygon &other) : Shape(), m_points(other.getPoints()) {
    calculateMinmax();
}

Polygon::Polygon(std::initializer_list<Vector2> list)
    : Shape(), m_points(list.begin(), list.end()) {
    calculateMinmax();
}

/* virtual */ bool Polygon::isPointInside(Vector2 point) const /* override */
{
    return (intersectLine(point, {point.x + 1.0f, point.y}, LineType::RAY)
                .size() %
            2) == 1;
}

std::vector<Vector2> Polygon::getPoints() const { return m_points; }

std::vector<Polygon::EdgeIntersection>
Polygon::intersectLineEx(Vector2 a, Vector2 b, LineType type) const {
    if (m_points.size() <= 1)
        return {};

    const auto inputLine = Line(a, b, type);

    std::unordered_set<EdgeIntersection> result = {};

    Vector2 x = m_points.at(m_points.size() - 1), y;
    for (std::size_t i = 0; i < m_points.size(); ++i) {
        y = m_points.at(i);

        const auto segment = Line(x, y, LineType::SEGMENT);
        const auto intersection = inputLine.intersectLine(segment);

        if (intersection.size() > 0)
            result.insert({intersection.at(0), segment});

        x = y;
    }

    return std::vector<EdgeIntersection>(result.begin(), result.end());
}

/* virtual */ std::vector<Vector2>
Polygon::intersectLine(Vector2 a, Vector2 b, LineType type) const /* override */
{
    if (m_points.size() <= 1)
        return {};

    const auto inputLine = Line(a, b, type);

    std::unordered_set<Vector2> result = {};

    Vector2 x = m_points.at(m_points.size() - 1), y;
    for (std::size_t i = 0; i < m_points.size(); ++i) {
        y = m_points.at(i);

        const auto intersection =
            inputLine.intersectLine(x, y, LineType::SEGMENT);

        if (intersection.size() > 0)
            result.insert(intersection.at(0));

        x = y;
    }

    return std::vector<Vector2>(result.begin(), result.end());
}

// Polygon
#pragma endregion

} // namespace Calcda