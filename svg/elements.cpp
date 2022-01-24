#include "elements.hpp"

namespace svg {
    ellipse::ellipse(const svg::color &fill,
                     const point &center,
                     const point &radius) :
            shape(fill), center(center), radius(radius) {

    }
    void ellipse::draw(png_image &img) const {
        img.draw_ellipse(center, radius, get_color());
    }
    void ellipse::translate(const point &t) {
        center = center.translate(t);
    }
    void ellipse::scale(const point &origin, int v) {
        radius.x *= v;
        radius.y *= v;
        center = center.scale(origin,v);
    }

    void ellipse::rotate(const point &origin, int degrees) {
        center = center.rotate(origin, degrees);
    }
    shape *ellipse::duplicate() const {
        return new ellipse(get_color(), center, radius);
    }

    circle::circle(const color &fill,
                   const point &center,
                   const point &radius) :
            ellipse(fill, center, radius) {

    }

    polygon::polygon(const color &fill,
                     const std::vector<point> points) :
                     shape(fill), points(points) {

    }

    void polygon::draw(png_image &img) const {
        img.draw_polygon(points,get_color());
    }

    void polygon::translate(const point &t) {
        for(int i =0; i<points.size();i++)
            points[i] = points[i].translate(t);
    }

    void polygon::scale(const point &origin, int v) {
        for(int i =0; i<points.size();i++)
            points[i] = points[i].scale(origin,v);
    }

    void polygon::rotate(const point &origin, int v) {
        for(int i =0; i<points.size();i++)
            points[i] = points[i].rotate(origin,v);
    }

    shape *polygon::duplicate() const {
        return new polygon(get_color(), points);
    }

    rect::rect(const color &fill,
               std::vector<point> points) :
               polygon(fill, points) {

    }

    polyline::polyline(const color &fill,
                       std::vector<point> points,
                       const color &stroke) :
                       shape(fill),
                       points(points),
                       stroke(stroke) {


    }

    void polyline::draw(png_image &img) const {
        for(auto i = 0; i<points.size()-1;i++)
            img.draw_line(points[i],points[i+1],stroke);
    }

    void polyline::translate(const point &t) {
        for(int i =0; i<points.size();i++)
            points[i] = points[i].translate(t);
    }

    void polyline::scale(const point &origin, int v) {
        for(int i =0; i<points.size();i++)
            points[i] = points[i].scale(origin,v);
    }

    void polyline::rotate(const point &origin, int v) {
        for(int i =0; i<points.size();i++)
            points[i] = points[i].rotate(origin,v);
    }

    shape *polyline::duplicate() const {
        return new polyline(get_color(), points, stroke);
    }

    line::line(std::vector<point> points,
               const color &stroke) :
               polyline(get_color(),
                        points,stroke) {

    }
}
