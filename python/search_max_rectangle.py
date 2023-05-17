import math
from dataclasses import dataclass

@dataclass
class Rectangle:
    """
     min_x           max_x
      |               |
      V               V
      +---------------+ <- max_y
      |               |
      |               |
      |   Rectangle   |
      |               |
      |               |
      +---------------+ <- min_y
    """
    min_x: float
    min_y: float
    max_x: float
    max_y: float

@dataclass
class Ellipse:
    x0:  float # x coordinate of center of ellipse
    y0:  float # y coordinate of center of ellipse
    A:   float # major axis
    B:   float # minor axis
    phi: float # rotation angle [degree]

class SearchMaxRectangle:
    def calculate_rectangle_size(self, ellipse):
        """
        Parameters
        ----------
        ellipse : Ellipse

        Returns
        -------
        rectangle : Rectangle
        """
        # convert degrees to radians
        phi = math.radians(ellipse.phi)
        x0 = ellipse.x0;
        y0 = ellipse.y0;
        sq_major_axis = ellipse.A ** 2.0
        sq_minor_axis = ellipse.B ** 2.0
        sq_sin = math.sin(phi) ** 2.0
        sq_cos = math.cos(phi) ** 2.0
        # calculate rectangle size
        ell_x = math.sqrt(sq_major_axis * sq_cos + sq_minor_axis * sq_sin);
        ell_y = math.sqrt(sq_major_axis * sq_sin + sq_minor_axis * sq_cos);
        # translate ellipse and create rectangle
        rectangle = Rectangle(
            min_x=-ell_x+x0, max_x=ell_x+x0,
            min_y=-ell_y+y0, max_y=ell_y+y0,
        )

        return rectangle

    def search(self, ellipses):
        """
        Parameters
        ----------
        ellipse : list of Ellipse

        Returns
        -------
        max_rectangle : Rectangle
        """
        rectangles = [
            self.calculate_rectangle_size(ellipse)
            for ellipse in ellipses
        ]
        max_rectangle = Rectangle(
            min_x=min(map(lambda rect: rect.min_x, rectangles)),
            min_y=min(map(lambda rect: rect.min_y, rectangles)),
            max_x=max(map(lambda rect: rect.max_x, rectangles)),
            max_y=max(map(lambda rect: rect.max_y, rectangles)),
        )

        return max_rectangle

if __name__ == '__main__':
    ellipses = [
        Ellipse(x0=-3.0, y0=1.0, A=6.0, B=3.0, phi=118.0),
        Ellipse(x0=10.0, y0=-7.0, A=6.4, B=2.0, phi=32.0),
        Ellipse(x0=10.0, y0=7.0, A=3.5, B=1.5, phi=61.0),
        Ellipse(x0=0.0, y0=13.0, A=3.2, B=1.0, phi=123.0),
        Ellipse(x0=-13.0, y0=-13.0, A=3.0, B=3.0, phi=0.0),
    ]
    smr = SearchMaxRectangle()
    max_rectangle = smr.search(ellipses)
    output = [
        'mininum coordinate x: {:+.5f}'.format(max_rectangle.min_x),
        'mininum coordinate y: {:+.5f}'.format(max_rectangle.min_y),
        'maxinum coordinate x: {:+.5f}'.format(max_rectangle.max_x),
        'maxinum coordinate y: {:+.5f}'.format(max_rectangle.max_y),
    ]
    print('\n'.join(output))
