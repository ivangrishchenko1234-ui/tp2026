#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cmath>
#include <iomanip>

using namespace std::placeholders;

struct Point {
    int x, y;
};

struct Polygon {
    std::vector<Point> points;
};

size_t getVertexCount(const Polygon& p) {
    return p.points.size();
}

bool isVertexCountEqual(const Polygon& p, size_t n) {
    return p.points.size() == n;
}

bool isVertexCountOdd(const Polygon& p) {
    return p.points.size() % 2 != 0;
}

bool isVertexCountEven(const Polygon& p) {
    return p.points.size() % 2 == 0;
}

double getArea(const Polygon& p) {
    if (p.points.size() < 3) return 0.0;
    double area = 0.0;
    int n = p.points.size();
    for (int i = 0; i < n; ++i) {
        area += p.points[i].x * p.points[(i + 1) % n].y - p.points[(i + 1) % n].x * p.points[i].y;
    }
    return std::abs(area) / 2.0;
}

bool compareArea(const Polygon& a, const Polygon& b) {
    return getArea(a) < getArea(b);
}

bool compareVertexes(const Polygon& a, const Polygon& b) {
    return a.points.size() < b.points.size();
}

struct AreaSummator {
    std::function<bool(const Polygon&)> filter;

    AreaSummator(std::function<bool(const Polygon&)> f) : filter(f) {}

    double operator()(double acc, const Polygon& p) const {
        return filter(p) ? acc + getArea(p) : acc;
    }
};

struct IsRectangle {
    bool operator()(const Polygon& p) const {
        if (p.points.size() != 4) return false;
        auto dot = [](Point a, Point b, Point c) {
            return (b.x - a.x) * (c.x - b.x) + (b.y - a.y) * (c.y - b.y);
        };
        return dot(p.points[3], p.points[0], p.points[1]) == 0 &&
               dot(p.points[0], p.points[1], p.points[2]) == 0 &&
               dot(p.points[1], p.points[2], p.points[3]) == 0 &&
               dot(p.points[2], p.points[3], p.points[0]) == 0;
    }
};

struct SeqState {
    Polygon target;
    int current_max;
    int current_run;

    SeqState(Polygon t) : target(t), current_max(0), current_run(0) {}

    bool isSame(const Polygon& p1, const Polygon& p2) const {
        if (p1.points.size() != p2.points.size()) return false;
        return std::equal(p1.points.begin(), p1.points.end(), p2.points.begin(),
            [](Point a, Point b){ return a.x == b.x && a.y == b.y; });
    }

    SeqState& operator+(const Polygon& p) {
        if (isSame(p, target)) {
            current_run++;
            if (current_run > current_max) current_max = current_run;
        }
        else {
            current_run = 0;
        }
        return *this;
    }
};

Polygon parsePolygon(const std::string& line) {
    std::istringstream iss(line);
    int n;
    if (!(iss >> n)) return {};
    Polygon poly;
    for (int i = 0; i < n; ++i) {
        char op, sem, cl;
        int x, y;
        if (iss >> op >> x >> sem >> y >> cl) {
            poly.points.push_back({x, y});
        }
    }
    return (poly.points.size() == static_cast<size_t>(n)) ? poly : Polygon{};
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: No filename" << '\n';
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) return 1;

    std::vector<Polygon> container;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        Polygon p = parsePolygon(line);
        if (!p.points.empty()) container.push_back(p);
    }

    std::string cmd;
    while (std::cin >> cmd) {
        if (cmd == "AREA") {
            std::string sub; std::cin >> sub;
            double res = 0;
            if (sub == "ODD")
                res = std::accumulate(container.begin(), container.end(), 0.0, AreaSummator(isVertexCountOdd));
            else if (sub == "EVEN")
                res = std::accumulate(container.begin(), container.end(), 0.0, AreaSummator(isVertexCountEven));
            else if (sub == "MEAN") {
                if (container.empty()) { std::cout << "<INVALID COMMAND>" << '\n'; continue; }
                res = std::accumulate(container.begin(), container.end(), 0.0,
                 AreaSummator([](const Polygon&){return true;})) / container.size();
            }
            else {
            else if(std::stoul(sub) > 2) {
                size_t n = std::stoul(sub);
                res = std::accumulate(container.begin(), container.end(), 0.0, AreaSummator(std::bind(isVertexCountEqual, _1, n)));
            }
            std::cout << std::fixed << std::setprecision(1) << res << '\n';
            else {
                std::cout << "<INVALID COMMAND>" << '\n';
                std::getline(std::cin, line);
            }
        }
        else if (cmd == "MAX") {
            std::string sub; std::cin >> sub;
            if (container.empty()) { std::cout << "<INVALID COMMAND>" << '\n'; continue; }
            if (sub == "AREA") {
                auto it = std::max_element(container.begin(), container.end(), compareArea);
                std::cout << std::fixed << std::setprecision(1) << getArea(*it) << '\n';
            }
            else {
                auto it = std::max_element(container.begin(), container.end(), compareVertexes);
                std::cout << it->points.size() << '\n';
            }
        }
        else if (cmd == "COUNT") {
            std::string sub; std::cin >> sub;
            if (sub == "ODD") std::cout << std::count_if(container.begin(), container.end(), isVertexCountOdd) << '\n';
            else if (sub == "EVEN") std::cout << std::count_if(container.begin(), container.end(), isVertexCountEven) << '\n';
            else if (std::stoul(sub) > 2){
                std::cout << std::count_if(container.begin(), container.end(),
                std::bind(isVertexCountEqual, _1, std::stoul(sub))) << '\n';
            }
            else {
                std::cout << "<INVALID COMMAND>" << '\n';
                std::getline(std::cin, line);
            }
        }
        else if (cmd == "RECTS") {
            std::cout << std::count_if(container.begin(), container.end(), IsRectangle()) << '\n';
        }
        else if (cmd == "MAXSEQ") {
            std::string pLine; std::getline(std::cin >> std::ws, pLine);
            Polygon target = parsePolygon(pLine);
            SeqState finalState = std::accumulate(container.begin(), container.end(), SeqState(target),
                std::bind(&SeqState::operator+, _1, _2));
            if(finalState.current_max != 0) std::cout << finalState.current_max << '\n';
            else{
                std::cout << "<INVALID COMMAND>" << '\n';
                std::getline(std::cin, line);
            }
        }
        else {
            std::cout << "<INVALID COMMAND>" << '\n';
            std::getline(std::cin, line);
        }
    }

    return 0;
}
