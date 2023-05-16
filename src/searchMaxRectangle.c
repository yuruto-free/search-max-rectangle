#include <stddef.h>
#include <math.h>
#include "searchMaxRectangle.h"
#define SMR_RETURN_OK (0)
#define SMR_RETURN_NG (1)
#define SMR_MAX(a, b) (((a) > (b)) ? (a) : (b));
#define SMR_MIN(a, b) (((a) < (b)) ? (a) : (b));

/**
 * @brief calculate rectangle size
 * @param[in]  ellipse   target ellipse
 * @param[out] rectangle output rectangle
 * @return SMR_RETURN_OK success
 *         SMR_RETURN_NG failed
*/
static int calculate_rectangle_size(
    const struct SMR_ellipse_t *ellipse,
    struct SMR_rectangle_t *rectangle
);

int search_max_rectangle(
    int num,
    const struct SMR_ellipse_t *ellipses,
    struct SMR_rectangle_t *max_rectangle
) {
    int ret = (int)SMR_FAILED;
    int func_val;
    int idx;
    const struct SMR_ellipse_t *current;
    struct SMR_rectangle_t target;

    if ((NULL != ellipses) && (NULL != max_rectangle)) {
        current = &ellipses[0];
        func_val = calculate_rectangle_size(current, max_rectangle);

        if ((int)SMR_RETURN_OK != func_val) {
            goto EXIT_SEARCH_MAX_RECTANGLE;
        }

        for (idx = 1; idx < num; idx++) {
            current = &ellipses[idx];
            func_val = calculate_rectangle_size(current, &target);

            if ((int)SMR_RETURN_OK != func_val) {
                goto EXIT_SEARCH_MAX_RECTANGLE;
            }
            /* swap if the ellipse is father away */
            max_rectangle->min_x = SMR_MIN(target.min_x, max_rectangle->min_x);
            max_rectangle->min_y = SMR_MIN(target.min_y, max_rectangle->min_y);
            max_rectangle->max_x = SMR_MAX(target.max_x, max_rectangle->max_x);
            max_rectangle->max_y = SMR_MAX(target.max_y, max_rectangle->max_y);
        }
        ret = (int)SMR_SUCCESS;
    }

EXIT_SEARCH_MAX_RECTANGLE:

    return ret;
}

static int calculate_rectangle_size(
    const struct SMR_ellipse_t *ellipse,
    struct SMR_rectangle_t *rectangle
) {
    int ret = (int)SMR_RETURN_NG;
    double x0, y0, phi;
    double sq_major_axis, sq_minor_axis;
    double sq_sin, sq_cos;

    if ((NULL != ellipse) && (NULL != rectangle)) {
        /* convert degrees to radians */
        phi = ellipse->phi * M_PI / 180.0;

        x0 = ellipse->x0;
        y0 = ellipse->y0;
        sq_major_axis = pow(ellipse->A, 2.0);
        sq_minor_axis = pow(ellipse->B, 2.0);
        sq_sin = pow(sin(phi), 2.0);
        sq_cos = pow(cos(phi), 2.0);
        /* calculate rectangle size */
        rectangle->max_x = sqrt(sq_major_axis * sq_cos + sq_minor_axis * sq_sin);
        rectangle->max_y = sqrt(sq_major_axis * sq_sin + sq_minor_axis * sq_cos);
        rectangle->min_x = -rectangle->max_x;
        rectangle->min_y = -rectangle->max_y;
        /* translation */
        rectangle->max_x += x0;
        rectangle->max_y += y0;
        rectangle->min_x += x0;
        rectangle->min_y += y0;

        ret = (int)SMR_RETURN_OK;
    }

    return ret;
}
