#include <stdio.h>
#include "searchMaxRectangle.h"
#define MAX_ELLIPSE_NUM (5)

int main(void) {
    int ret;

    /* ellipse list */
    struct SMR_ellipse_t ellipses[MAX_ELLIPSE_NUM] = {
        { -3.0,   1.0, 6.0, 3.0, 118.0},
        { 10.0,  -7.0, 6.4, 2.0,  32.0},
        { 10.0,   7.0, 3.5, 1.5,  61.0},
        {  0.0,  13.0, 3.2, 1.0, 123.0},
        {-13.0, -13.0, 3.0, 3.0,   0.0},
    };
    /* max rectangle */
    struct SMR_rectangle_t max_rectangle;
    /* search max rectangle */
    ret = search_max_rectangle(
        (int)MAX_ELLIPSE_NUM,
        (const struct SMR_ellipse_t *)ellipses,
        &max_rectangle
    );
    if ((int)SMR_SUCCESS != ret) {
        goto EXIT_MAIN;
    }
    fprintf(stdout, "mininum coordinate x: %+.5lf\n", max_rectangle.min_x);
    fprintf(stdout, "mininum coordinate y: %+.5lf\n", max_rectangle.min_y);
    fprintf(stdout, "maxinum coordinate x: %+.5lf\n", max_rectangle.max_x);
    fprintf(stdout, "maxinum coordinate y: %+.5lf\n", max_rectangle.max_y);

EXIT_MAIN:

    return 0;
}
