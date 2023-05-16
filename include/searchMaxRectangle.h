#ifndef SEARCH_MAX_RECTANGLE_H_
#define SEARCH_MAX_RECTANGLE_H_
#define SMR_SUCCESS (0)
#define SMR_FAILED  (1)

struct SMR_rectangle_t {
    /**
     *
     * min_x           max_x
     *  |               |
     *  V               V
     *  +---------------+ <- max_y
     *  |               |
     *  |               |
     *  |   Rectangle   |
     *  |               |
     *  |               |
     *  +---------------+ <- min_y
     *
    */
    double min_x;
    double max_x;
    double min_y;
    double max_y;
};

struct SMR_ellipse_t {
    double x0;  /* x coordinate of center of ellipse */
    double y0;  /* y coordinate of center of ellipse */
    double A;   /* major axis */
    double B;   /* minor axis */
    double phi; /* rotation angle [degree] */
};

/**
 * @brief find the largest rectangle that encloses multiple ellipses
 * @param[in]  num           number of ellipses
 * @param[in]  ellipses      target ellipses
 * @param[out] max_rectangle output rectangle
 * @return SMR_SUCCESS success this process
 *         SMR_FAILED  failed this process
*/
extern int search_max_rectangle(
    int num,
    const struct SMR_ellipse_t *ellipses,
    struct SMR_rectangle_t *max_rectangle
);

#endif // SEARCH_MAX_RECTANGLE_H_
