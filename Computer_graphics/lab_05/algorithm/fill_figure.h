#ifndef FILL_FIGURE_H
#define FILL_FIGURE_H

#include "figure.h"
#include "draw.h"

#include <map>
#include <QTime>
#include <QCoreApplication>

struct node
{
    double x;
    double dx;
    int dy;
};
using node_t = struct node;

node_t create_node(double x, double dx, int dy);

using nodes_t = std::vector<node_t>;


struct edge
{
    Point start;
    Point end;
};
using edge_t = struct edge;

edge_t create_edge(Point start, Point end);

using edges_t = std::vector<edge_t>;

using link_list_t = std::map<int, nodes_t>;


double fill_with_cap(draw_view_t& view, QColor& color, figures_t& closed_figures, bool delay=false, int delay_time=10);

#endif // FILL_FIGURE_H
