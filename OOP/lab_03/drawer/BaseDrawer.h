#ifndef BASEDRAWER_H
#define BASEDRAWER_H

class BaseDrawer
{
public:
    BaseDrawer() = default;
    virtual ~BaseDrawer() = default;

    virtual void clear() = 0;
    virtual void drawLine(int x1, int y1, int x2, int y2) = 0;
};

#endif // BASEDRAWER_H
