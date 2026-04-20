#include <algorithm>
#include <functional>
#include <numeric>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std::placeholders;

struct Point
{
    int x;
    int y;
};

struct Polygon
{
    std::vector<Point> points;
};

std::istream& operator>>(std::istream& stream, Point& point)
{
    std::istream::sentry sentry(stream, true);
    if (!sentry)
    {
        return stream;
    }
    char symbol;
    int x = 0;
    int y = 0;

    if (!(stream >> symbol) || symbol != '(')
    {
        stream.setstate(std::ios::failbit);
    }
    if (!(stream >> x) || !(stream >> symbol) || symbol != ';')
    {
        stream.setstate(std::ios::failbit);
    }
    if (!(stream >> y) || !(stream >> symbol) || symbol != ')')
    {
        stream.setstate(std::ios::failbit);
    }
    point.x = x;
    point.y = y;
    return stream;
}

std::istream& operator>>(std::istream& stream, Polygon& poly)
{
    std::istream::sentry sentry(stream);
    if (!sentry)
    {
        return stream;
    }

    Polygon temp;
    std::size_t vertexCount;

    if (!(stream >> vertexCount) || vertexCount < 3)
    {
        stream.setstate(std::ios::failbit);
        return stream;
    }
    temp.points.resize(vertexCount);
    std::copy_n(
        std::istream_iterator<Point>(stream),
        vertexCount,
        temp.points.begin()
    );

    if (!stream)
    {
        return stream;
    }

    poly = std::move(temp);
    return stream;
}

std::vector<Polygon> readPolygons(const std::string& filename)
{
    std::ifstream in(filename);
    std::vector<Polygon> polygons;
    if (!in.is_open())
    {
        throw std::runtime_error("Can't open file - " + filename);
    }
    std::string line;
    while (std::getline(in, line))
    {
        if (line.empty())
        {
            continue;
        }
        std::istringstream stream(line);
        Polygon temp;
        if (stream >> temp)
        {
            char trash;
            if (!(stream >> trash))
            {
                polygons.push_back(temp);
            }
        }
    }
    return polygons;
}

struct AccumulateArea
{
    const std::vector<Point>& points;
    AccumulateArea(const std::vector<Point>& p) : points(p)
    {
    }
    long long operator()(long long sum, size_t i) const
    {
        size_t j = (i + 1) % points.size();
        return sum + static_cast<long long>(points[i].x * points[j].y) -
            static_cast<long long>(points[j].x * points[i].y);
    }
};

double getArea(const Polygon& poly)
{
    const auto& p = poly.points;
    std::vector<size_t> index(p.size());
    std::iota(index.begin(), index.end(), 0);

    long long sum = std::accumulate(index.begin(), index.end(), 0LL,
        AccumulateArea(p));

    return std::abs(sum) / 2.0;
}

struct AreaCalc
{
    double operator()(double sum, const Polygon& poly) const
    {
        return sum + getArea(poly);
    }
};

struct SumAreaIfEven
{
    double operator()(double sum, const Polygon& poly) const
    {
        if (poly.points.size() % 2 == 0)
        {
            return sum + getArea(poly);
        }
        return sum;
    }
};

struct SumAreaIfOdd
{
    double operator()(double sum, const Polygon& poly) const
    {
        if (poly.points.size() % 2 != 0)
        {
            return sum + getArea(poly);
        }
        return sum;
    }
};

struct Mean
{
    double operator()(double sum, size_t size) const
    {
        return sum / size;
    }
};

struct SumAreaIfVertexesCount
{
    double operator()(double sum, int size, const Polygon& poly) const
    {
        if (size == poly.points.size())
        {
            return sum + getArea(poly);
        }
        return sum;
    }
};

struct CompareAreas
{
    bool operator()(const Polygon& p1, const Polygon& p2) const
    {
        return getArea(p1) < getArea(p2);
    }
};

struct CompareVertexes
{
    bool operator()(const Polygon& p1, const Polygon& p2) const
    {
        return p1.points.size() < p2.points.size();
    }
};

struct IsEvenVertexes
{
    bool operator()(const Polygon& poly) const
    {
        return poly.points.size() % 2 == 0;
    }
};

struct IsOddVertexes
{
    bool operator()(const Polygon& poly) const
    {
        return poly.points.size() % 2 != 0;
    }
};

struct IsEqualVertexes
{
    bool operator()(const Polygon& poly, int y) const
    {
        return poly.points.size() == y;
    }
};

struct DistanceSquared
{
    long long operator()(const Point& a, const Point& b) const
    {
        long long dx = static_cast<long long>(a.x) - b.x;
        long long dy = static_cast<long long>(a.y) - b.y;
        return dx * dx + dy * dy;
    }
};

struct IsRectangle
{
    bool operator()(const Polygon& poly) const
    {
        if (poly.points.size() != 4)
        {
            return false;
        }
        const auto& p = poly.points;
        long long d01 = DistanceSquared()(p[0], p[1]);
        long long d02 = DistanceSquared()(p[0], p[2]);
        long long d03 = DistanceSquared()(p[0], p[3]);
        long long d12 = DistanceSquared()(p[1], p[2]);
        long long d13 = DistanceSquared()(p[1], p[3]);
        long long d23 = DistanceSquared()(p[2], p[3]);

        std::vector<long long> dist = { d01, d02, d03, d12, d13, d23 };
        std::sort(dist.begin(), dist.end());
        return dist[0] == dist[1] &&
            dist[2] == dist[3] &&
            dist[4] == dist[5] &&
            dist[0] > 0;
    }
};

struct Orientation
{
    int operator()(const Point& a, const Point& b, const Point& c) const
    {
        long long val = static_cast<long long>((b.y - a.y) * (c.x - b.x)) -
            static_cast<long long>((b.x - a.x) * (c.y - b.y));

        if (val == 0)
        {
            return 0;
        }
        return (val > 0) ? 1 : 2;
    }
};

struct PointOnSegment
{
    bool operator()(const Point& a, const Point& b, const Point& c) const
    {
        return c.x >= std::min(a.x, b.x) && c.x <= std::max(a.x, b.x) &&
            c.y >= std::min(a.y, b.y) && c.y <= std::max(a.y, b.y);
    }
};

struct SegmentsIntersect
{
    bool operator()(const Point& a, const Point& b,
        const Point& c, const Point& d) const
    {
        Orientation orient;
        PointOnSegment onSeg;

        int o1 = orient(a, b, c);
        int o2 = orient(a, b, d);
        int o3 = orient(c, d, a);
        int o4 = orient(c, d, b);
        if (o1 != o2 && o3 != o4)
        {
            return true;
        }
        if (o1 == 0 && onSeg(a, b, c))
        {
            return true;
        }
        if (o2 == 0 && onSeg(a, b, d))
        {
            return true;
        }
        if (o3 == 0 && onSeg(c, d, a))
        {
            return true;
        }
        if (o4 == 0 && onSeg(c, d, b))
        {
            return true;
        }
        return false;
    }
};

struct AccumulateCrosses
{
    const Polygon& poly;
    const Point& p;
    int n;

    AccumulateCrosses(const Polygon& pl, const Point& pt, int N)
        : poly(pl), p(pt), n(N)
    {
    }

    int operator()(int count, int i) const
    {
        int j = (i + 1) % n;
        const Point& a = poly.points[i];
        const Point& b = poly.points[j];

        bool cond1 = (a.y > p.y) != (b.y > p.y);
        if (!cond1)
        {
            return count;
        }

        double xIntersect = (b.x - a.x) * static_cast<double>(p.y - a.y) /
            (b.y - a.y) + a.x;
        if (p.x < xIntersect)
        {
            return count + 1;
        }
        return count;
    }
};

struct PointInPolygon
{
    const Polygon& poly;

    PointInPolygon(const Polygon& p) : poly(p) {}

    bool operator()(const Point& p) const
    {
        int n = poly.points.size();
        std::vector<int> index(n);
        std::iota(index.begin(), index.end(), 0);
        int count = std::accumulate(index.begin(), index.end(), 0,
            AccumulateCrosses(poly, p, n));
        return count % 2 == 1;
    }
};

struct SideIntersectionChecker
{
    const Polygon& poly1;
    const Polygon& poly2;
    int i;
    int j;
    int k;

    SideIntersectionChecker(const Polygon& p1, const Polygon& p2, int idx1, int idx2)
        : poly1(p1), poly2(p2), i(idx1), j((idx1 + 1) % p1.points.size()), k(idx2)
    {
    }

    bool operator()() const
    {
        int l = (k + 1) % poly2.points.size();
        return SegmentsIntersect()(poly1.points[i], poly1.points[j],
            poly2.points[k], poly2.points[l]);
    }
};

struct OneSideVsOneSideWrapper
{
    const Polygon& poly1;
    const Polygon& poly2;
    int i;
    int j;

    OneSideVsOneSideWrapper(const Polygon& p1, const Polygon& p2, int idx)
        : poly1(p1), poly2(p2), i(idx), j((idx + 1) % p1.points.size())
    {
    }

    bool operator()(int k) const
    {
        int l = (k + 1) % poly2.points.size();
        return SegmentsIntersect()(poly1.points[i], poly1.points[j],
            poly2.points[k], poly2.points[l]);
    }
};

struct OneSideVsAllSides
{
    const Polygon& poly1;
    const Polygon& poly2;
    int i;

    OneSideVsAllSides(const Polygon& p1, const Polygon& p2, int idx)
        : poly1(p1), poly2(p2), i(idx) {
    }

    bool operator()() const
    {
        int n2 = poly2.points.size();
        std::vector<int> index2(n2);
        std::iota(index2.begin(), index2.end(), 0);

        std::vector<bool> intersections(n2);
        std::transform(index2.begin(), index2.end(), intersections.begin(),
            OneSideVsOneSideWrapper(poly1, poly2, i));

        auto it = std::find(intersections.begin(), intersections.end(), true);
        return it != intersections.end();
    }
};

struct SideChecker
{
    const Polygon& poly1;
    const Polygon& poly2;

    SideChecker(const Polygon& p1, const Polygon& p2) : poly1(p1), poly2(p2)
    {
    }

    bool operator()(int i) const
    {
        return OneSideVsAllSides(poly1, poly2, i)();
    }
};

struct AnySideIntersects
{
    const Polygon& poly1;
    const Polygon& poly2;

    AnySideIntersects(const Polygon& p1, const Polygon& p2) : poly1(p1), poly2(p2)
    {
    }

    bool operator()() const
    {
        int n1 = poly1.points.size();
        std::vector<int> index1(n1);
        std::iota(index1.begin(), index1.end(), 0);

        std::vector<bool> hasIntersection(n1);
        std::transform(index1.begin(), index1.end(), hasIntersection.begin(),
            SideChecker(poly1, poly2));

        auto it = std::find(hasIntersection.begin(), hasIntersection.end(), true);
        return it != hasIntersection.end();
    }
};

struct PointToBool
{
    const Polygon& poly;
    PointToBool(const Polygon& out) : poly(out)
    {
    }

    bool operator()(const Point& p) const
    {
        PointInPolygon pip(poly);
        return pip(p);
    }
};

struct AnyPointInside
{
    const Polygon& outer;
    const Polygon& inner;

    AnyPointInside(const Polygon& out, const Polygon& in) : outer(out), inner(in)
    {
    }

    bool operator()() const
    {
        std::vector<bool> inside(inner.points.size());
        std::transform(inner.points.begin(), inner.points.end(), inside.begin(),
            PointToBool(outer));
        auto it = std::find(inside.begin(), inside.end(), true);
        return it != inside.end();
    }
};

struct PolygonsIntersect
{
    bool operator()(const Polygon& poly1, const Polygon& poly2) const
    {
        if (AnySideIntersects(poly1, poly2)())
        {
            return true;
        }

        if (AnyPointInside(poly2, poly1)())
        {
            return true;
        }
        if (AnyPointInside(poly1, poly2)())
        {
            return true;
        }
        return false;
    }
};

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    std::string filename = argv[1];
    try
    {
        std::vector<Polygon> polygons = readPolygons(filename);

        std::cout << std::fixed << std::setprecision(1);
        std::string line;
        while (std::getline(std::cin, line))
        {
            if (line.empty())
                continue;

            std::istringstream stream(line);
            std::string command;
            stream >> command;

            if (command == "AREA")
            {
                std::string parameter;
                stream >> parameter;
                if (parameter == "EVEN")
                {
                    double result = std::accumulate(polygons.begin(), polygons.end(),
                        0.0, SumAreaIfEven());
                    std::cout << result << '\n';
                }
                else if (parameter == "ODD")
                {
                    double result = std::accumulate(polygons.begin(), polygons.end(),
                        0.0, SumAreaIfOdd());
                    std::cout << result << '\n';
                }
                else if (parameter == "MEAN")
                {
                    if (polygons.empty())
                    {
                        std::cout << "0.0\n";
                    }
                    else
                    {
                        double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0, AreaCalc());
                        double result = Mean()(sum, polygons.size());
                        std::cout << result << '\n';
                    }
                }
                else
                {
                    try
                    {
                        size_t pos;
                        int vertexCount = std::stoi(parameter, &pos);

                        if (pos != parameter.length() || vertexCount < 3)
                        {
                            std::cout << "<INVALID COMMAND>\n";
                        }
                        else
                        {
                            double result = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                                std::bind(SumAreaIfVertexesCount(), _1, vertexCount, _2));
                            std::cout << result << '\n';
                        }
                    }
                    catch (...)
                    {
                        std::cout << "<INVALID COMMAND>\n";
                        continue;
                    }
                }
            }
            else if (command == "MAX")
            {
                std::string parameter;
                stream >> parameter;
                if (polygons.empty())
                {
                    std::cout << "<INVALID COMMAND>\n";
                    continue;
                }
                if (parameter == "AREA")
                {
                    auto max = std::max_element(polygons.begin(), polygons.end(), CompareAreas());
                    double maxArea = getArea(*max);
                    std::cout << maxArea << '\n';
                }
                else if (parameter == "VERTEXES")
                {
                    auto max = std::max_element(polygons.begin(), polygons.end(), CompareVertexes());
                    size_t maxVertexes = max->points.size();
                    std::cout << maxVertexes << '\n';
                }
                else
                {
                    std::cout << "<INVALID COMMAND>\n";
                }
            }
            else if (command == "MIN")
            {
                std::string parameter;
                stream >> parameter;
                if (polygons.empty())
                {
                    std::cout << "<INVALID COMMAND>\n";
                    continue;
                }

                if (parameter == "AREA")
                {
                    auto min = std::min_element(polygons.begin(), polygons.end(), CompareAreas());
                    double minArea = getArea(*min);
                    std::cout << minArea << '\n';
                }
                else if (parameter == "VERTEXES")
                {
                    auto min = std::min_element(polygons.begin(), polygons.end(), CompareVertexes());
                    size_t minVertexes = min->points.size();
                    std::cout << minVertexes << '\n';
                }
                else
                {
                    std::cout << "<INVALID COMMAND>\n";
                }
            }
            else if (command == "COUNT")
            {
                std::string parameter;
                stream >> parameter;
                if (parameter == "EVEN")
                {
                    auto countEven = std::count_if(polygons.begin(), polygons.end(),
                        IsEvenVertexes());
                    std::cout << countEven << '\n';
                }
                else if (parameter == "ODD")
                {
                    auto countOdd = std::count_if(polygons.begin(), polygons.end(),
                        IsOddVertexes());
                    std::cout << countOdd << '\n';
                }
                else
                {
                    try
                    {
                        size_t pos;
                        int vertexCount = std::stoi(parameter, &pos);
                        if (pos != parameter.length() || vertexCount < 3)
                        {
                            std::cout << "<INVALID COMMAND>\n";
                        }
                        else
                        {
                            auto count = std::count_if(polygons.begin(), polygons.end(),
                                std::bind(IsEqualVertexes(), _1, vertexCount));
                            std::cout << count << '\n';
                        }
                    }
                    catch (...)
                    {
                        std::cout << "<INVALID COMMAND>\n";
                    }
                }
            }
            else if (command == "RECTS")
            {
                auto countRects = std::count_if(polygons.begin(),
                    polygons.end(), IsRectangle());
                std::cout << countRects << '\n';
            }
            else if (command == "INTERSECTIONS")
            {
                Polygon polygon;
                if (!(stream >> polygon))
                {
                    std::cout << "<INVALID COMMAND>\n";
                    continue;
                }
                auto count = std::count_if(polygons.begin(), polygons.end(), std::bind(PolygonsIntersect(), _1, polygon));
                std::cout << count << '\n';
            }
            else
            {
                std::cout << "<INVALID COMMAND>\n";
            }
        }

    }
    catch (const std::runtime_error& err)
    {
        std::cerr << err.what();
        return 1;
    }
    return 0;
}