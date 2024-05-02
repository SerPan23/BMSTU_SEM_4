#include "algorithm.h"


void simple_cut(Drawer &drawer, rect_t &clipper, line_t line)
{
    // int xl = std::min(cut_rect.left_top.x(), cut_rect.right_down.x());
    // int xr = std::max(cut_rect.left_top.x(), cut_rect.right_down.x());
    // int yb = std::min(cut_rect.left_top.y(), cut_rect.right_down.y());
    // int yt = std::max(cut_rect.left_top.y(), cut_rect.right_down.y());
    int xl = clipper.left_top.x();
    int xr = clipper.right_down.x();
    int yb = clipper.left_top.x();
    int yt = clipper.right_down.x();


}
