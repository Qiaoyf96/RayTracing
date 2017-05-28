//
// Created by 乔逸凡 on 2017/5/19.
//

#ifndef RAY_TRACING_COLOR_H
#define RAY_TRACING_COLOR_H

class color {
public:
    double r, g, b;

    inline color(): r(0), g(0), b(0) {}
    inline color(double r, double g, double b): r(r), g(g), b(b) {}
    inline double maxColor() {
        if (r > g) {
            if (r > b) return r;
            return b;
        }
        if (g > b) return g;
        return b;
    }
    inline color operator * (double x) const {
        return color(r * x, g * x, b * x);
    }
    inline color merge(const color &a) const {
        return color(r * a.r / 255, g * a.g / 255, b * a.b / 255);
    }
    inline color operator + (const color &x) const {
        return color(r + x.r, g + x.g, b + x.b);
    }
    inline color norm() const {
        return color(r > 255 ? 255 : r, g > 255 ? 255 : g, b > 255 ? 255 : b);
    }
};

#endif //RAY_TRACING_COLOR_H
