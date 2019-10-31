#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "triangle.h"
#include "drawline.h"

#define TRIANGLE_PENCOLOR   0xBBBB0000

/*
 * Print triangle coordinates along with a message
 */
void print_triangle(triangle_t *triangle, char *msg)
{
    printf("%s: %d,%d - %d,%d - %d,%d\n",
        msg,
        triangle->x1, triangle->y1,
        triangle->x2, triangle->y2,
        triangle->x3, triangle->y3);
}

/*
 * Return 0 if triangle coordinates are outside the surface boundary. 1 otherwise.
 */
int sanity_check_triangle(SDL_Surface *surface, triangle_t *triangle)
{
    if (triangle->sx1 < 0 || triangle->sx1 >= surface->w ||
        triangle->sx2 < 0 || triangle->sx2 >= surface->w ||
        triangle->sx3 < 0 || triangle->sx3 >= surface->w ||
        triangle->sy1 < 0 || triangle->sy1 >= surface->h ||
        triangle->sy2 < 0 || triangle->sy2 >= surface->h ||
        triangle->sy3 < 0 || triangle->sy3 >= surface->h) {
        return 0;
    } else {
        return 1;
    }
}

/*
 * Scale triangle, altering the on-screen coordinates(e.g. triangle->sx1)
 */
void scale_triangle(triangle_t *triangle)
{
    triangle->sx1 = triangle->x1 * triangle->scale;
    triangle->sx2 = triangle->x2 * triangle->scale;
    triangle->sy2 = triangle->y2 * triangle->scale;
    triangle->sy1 = triangle->y2 * triangle->scale;
    triangle->sx3 = triangle->x3 * triangle->scale;
    triangle->sy3 = triangle->y3 * triangle->scale;

/*
 * Move the triangle to the center of the surface,
 * altering the on-screen coordinates(e.g. triangle->sx1)
 */
void translate_triangle(triangle_t *triangle)
{
    triangle->tx = 800;
    triangle->ty = 450;

    triangle->sx1 = triangle->sx1 + triangle->tx;
    triangle->sx2 = triangle->sx2 + triangle->tx;
    triangle->sy1 = triangle->sy1 + triangle->ty;
    triangle->sy2 = triangle->sy2 + triangle->ty;
    triangle->sx3 = triangle->sx3 + triangle->tx;
    triangle->sy3 = triangle->sy3 + triangle->ty;

}

/*
 * Calculate the triangle bounding box,
 * altering fields of the triangle's rect(e.g. triangle->rect.x)
 */
void calculate_triangle_bounding_box(triangle_t *triangle)
{
  int x1 = triangle->sx1;
  int y1 = triangle->sy1;
  int x2 = triangle->sx2;
  int y2 = triangle->sy2;
  int x3 = triangle->sx3;
  int y3 = triangle->sy3;

  int xmax,xmin,ymax,ymin;

  xmas = x1 > x2 ? (x1>x3 ? x1 : x3) : (x2 > x3 ? x2 : x3);
  xmin = x1 < x2 ? (x1<x3 ? x1 : x3) : (x2 < x3 ? x2 : x3);
  ymas = y1 > y2 ? (x1>y3 ? y1 : y3) : (y2 > y3 ? y2 : y3);
  ymin = y1 < y2 ? (y1<y3 ? y1 : y3) : (y2 < y3 ? y2 : y3);

  triangle->rect.w = xmax - xmin;
  triangle->rect.x = xmin;

  triangle->rect.h = ymax - ymin;
  triangle->rect.y = ymin;

}

/*
 * Fill the triangle on the surface with the triangle's color
 */
void fill_triangle(SDL_Surface *surface, triangle_t *triangle)
//1. For en loop går ned til y-akse
//2. En vannrett for loop fra venstre side til den treffer pencolor
//3. En vannrett for loop fra høyre side til den treffer pencolor
//4. En drawLine på slutten
{
  int a;
  int b;
  int c;
  for (a = triangle->rect.y; a <=triangle-> rect.y + triangle->rect.h; a++)
  {
    for (b = triangle->rect.x; b <= triangle-> rect.x + triangle->rect.w; b++)
    {
      if (get_pixel(surface, b, a) == TRIANGLE_PENCOLOR)
      {
        break;
      }
    }
    draw_line(surface, b, a, c, a triangle->fillcolor);
  }

}

/*
 * Draw a filled triangle on the given surface
 */
void draw_triangle(SDL_Surface *surface, triangle_t *triangle)
{
    int isOK;

    /* Scale. */
    scale_triangle(triangle);

    /* Translate. */
    translate_triangle(triangle);

    /* Determine bounding box */
    calculate_triangle_bounding_box(triangle);

    /* Sanity check that triangle is within surface boundaries. */
    isOK = sanity_check_triangle(surface, triangle);
    if (!isOK) {
        print_triangle(triangle, "Triangle outside surface boundaries");
        return;
    }

    /*
     * TODO: Insert calls to draw_line to draw the triangle.
     * Remember to use the on-surface coordinates (triangle->sx1, etc.)
     */

    /* Fill triangle */
    fill_triangle(surface, triangle);
}
