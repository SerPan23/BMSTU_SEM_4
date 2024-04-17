#include "fill_figure.h"

node_t create_node(double x, double dx, int dy)
{
    return node_t{x, dx, dy};
}

edge_t create_edge(Point start, Point end)
{
    return edge_t{start, end};
}

void draw_act(draw_view_t& view, QColor& color, nodes_t& active_edges, int y)
{
    for (int i = 0; i < active_edges.size(); i += 2)
    {
        try
        {
            Point tmp1(round(active_edges[i].x), y);
            Point tmp2(active_edges[i + 1].x, y);
            draw_line(view, color, tmp1, tmp2);
        }
        catch (...)
        {
            Point tmp1(round(active_edges[i].x), y);
            Point tmp2(active_edges[i - 1].x, y);
            draw_line(view, color, tmp1, tmp2);
        }
    }
}

static void draw(draw_view_t& view)
{
    view.view->scene()->clear();
    view.view->scene()->addPixmap(*view.scene);
}

static void wait(int millisecondsToWait)
{
    QTime dieTime = QTime::currentTime().addMSecs(millisecondsToWait);
    while(QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

static void draw_edges(draw_view_t& view, edges_t &edges)
{
    QColor line_color = Qt::black;
    for (int i = 0; i < edges.size(); i++)
        draw_line(view, line_color, edges[i].start, edges[i].end);
}

static long delta_time(struct timespec mt1, struct timespec mt2)
{
    return 1000000000 * (mt2.tv_sec - mt1.tv_sec) + (mt2.tv_nsec - mt1.tv_nsec);
}

// start algo

edges_t make_edges(figures_t& figures)
{
    edges_t edges;
    for (int j = 0; j < figures.size(); j++)
    {
        Figure& figure = figures[j];
        int points_count = figure.size();
        for (int i = 0; i < points_count; i++)
        {
            if (i + 1 > points_count - 1)
                edges.push_back(create_edge(figure.get_point(points_count - 1), figure.get_point(0)));
            else
                edges.push_back(create_edge(figure.get_point(i), figure.get_point(i + 1)));
        }
    }
    return edges;
}

Point fing_extrimum_y_figures(figures_t& figures)
{
    int y_min = figures[0].get_point(0).getY();
    int y_max = y_min;
    for (int j = 0; j < figures.size(); j++)
    {
        Figure& figure = figures[j];
        for (int i = 0; i < figure.size(); i++)
        {
            Point& p = figure.get_point(i);

            if (p.getY() > y_max)
                y_max = p.getY();

            if (p.getY() < y_min)
                y_min = p.getY();
        }
    }

    return Point(y_min, y_max);
}

link_list_t make_link_list(int y_min, int y_max)
{
    link_list_t list;
    for (int i = y_max; i > y_min; i--)
        list[i] = nodes_t();

    return list;
}

void update_y_group(link_list_t& y_groups, int x_start, int y_start, int x_end, int y_end)
{
    if (y_start > y_end)
    {
        std::swap(x_start, x_end);
        std::swap(y_start, y_end);
    }

    int y_proj = abs(y_end - y_start);
    if (y_proj != 0)
    {
        double x_step = -(x_end - x_start) * 1.0 / y_proj;
        if (y_groups.count(y_end) == 0)
            y_groups[y_end] = nodes_t();
        y_groups[y_end].push_back(create_node(x_end, x_step, y_proj));
    }
}

void active_edges_iterator(nodes_t& active_edges)
{
    for (int i = 0; i < active_edges.size();)
    {
        active_edges[i].x += active_edges[i].dx;
        active_edges[i].dy -= 1;
        if (active_edges[i].dy < 1)
            //удаляем как в стеке LIFO - размерность списка n x 4,
            //бывают случаи когда нечетное в этом случае не учитвается
            active_edges.erase(active_edges.begin() + i);
        else
            ++i;
    }
}

bool compare_nodes_x(node_t a, node_t b)
{
    return (a.x < b.x);
}

void add_active_edges(link_list_t& y_groups, nodes_t& active_edges, int y)
{
    if (y_groups.count(y))
    {
        nodes_t& y_group = y_groups[y];
        for (int i = 0; i < y_group.size(); i++)
            active_edges.push_back(y_group[i]);
    }

    sort(active_edges.begin(), active_edges.end(), compare_nodes_x);
}

double fill_with_cap(draw_view_t& view, QColor& color, figures_t& figures, bool delay, int delay_time)
{
    struct timespec tbegin, tend;
    clock_gettime(CLOCK_REALTIME, &tbegin);

    edges_t edges = make_edges(figures);

    Point tmp = fing_extrimum_y_figures(figures);
    int y_min = tmp.getX();
    int y_max = tmp.getY();

    link_list_t y_groups = make_link_list(y_min, y_max);

    for (int i = 0; i < edges.size(); i++)
    {
        edge_t& edge = edges[i];
        update_y_group(y_groups, edge.start.getX(), edge.start.getY(),
                       edge.end.getX(), edge.end.getY());
    }


    int y_start = y_min;
    int y_end = y_max;

    // draw_edges(view, edges);

    nodes_t active_edges;
    while (y_end > y_start)
    {
        active_edges_iterator(active_edges);
        add_active_edges(y_groups, active_edges, y_end);

        draw_act(view, color, active_edges, y_end);
        y_end -= 1;
        if (delay)
        {
            wait(delay_time);
            draw(view);
        }
    }

    clock_gettime(CLOCK_REALTIME, &tend);
    double time = delta_time(tbegin, tend) / 1000000.0;

    draw_edges(view, edges);
    draw(view);

    return time;
}
