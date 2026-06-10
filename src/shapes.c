#include "shapes.h"
#include <stdio.h>
#include <stdlib.h>

char canvas[CANVAS_HEIGHT][CANVAS_WIDTH];

// Safely plots a point on the canvas if within boundaries
static void plot_point(int x, int y) {
    if (x >= 0 && x < CANVAS_WIDTH && y >= 0 && y < CANVAS_HEIGHT) {
        canvas[y][x] = '*';
    }
}

// Clears the canvas, resetting it to '_'
void clear_canvas(void) {
    for (int y = 0; y < CANVAS_HEIGHT; y++) {
        for (int x = 0; x < CANVAS_WIDTH; x++) {
            canvas[y][x] = '_';
        }
    }
}

// Displays the canvas on the stdout with border and coordinates rule
void display_canvas(void) {
    // Print tens digit of column index
    printf("   ");
    for (int x = 0; x < CANVAS_WIDTH; x++) {
        if (x % 10 == 0) {
            printf("%d", (x / 10) % 10);
        } else {
            printf(" ");
        }
    }
    printf("\n");

    // Print ones digit of column index
    printf("   ");
    for (int x = 0; x < CANVAS_WIDTH; x++) {
        printf("%d", x % 10);
    }
    printf("\n");

    // Top border
    printf("  +");
    for (int x = 0; x < CANVAS_WIDTH; x++) {
        printf("-");
    }
    printf("+\n");

    // Canvas rows
    for (int y = 0; y < CANVAS_HEIGHT; y++) {
        printf("%2d|", y);
        for (int x = 0; x < CANVAS_WIDTH; x++) {
            putchar(canvas[y][x]);
        }
        printf("|\n");
    }

    // Bottom border
    printf("  +");
    for (int x = 0; x < CANVAS_WIDTH; x++) {
        printf("-");
    }
    printf("+\n");
}

// Renders all current shapes onto the canvas
void render_objects(GraphicalObject objects[], int object_count) {
    clear_canvas();
    for (int i = 0; i < object_count; i++) {
        GraphicalObject obj = objects[i];
        switch (obj.type) {
            case SHAPE_LINE:
                draw_line(obj.data.line.x1, obj.data.line.y1, obj.data.line.x2, obj.data.line.y2);
                break;
            case SHAPE_RECTANGLE:
                draw_rectangle(obj.data.rect.x, obj.data.rect.y, obj.data.rect.width, obj.data.rect.height);
                break;
            case SHAPE_CIRCLE:
                draw_circle(obj.data.circle.xc, obj.data.circle.yc, obj.data.circle.radius);
                break;
            case SHAPE_TRIANGLE:
                draw_triangle(obj.data.triangle.x1, obj.data.triangle.y1, obj.data.triangle.x2, obj.data.triangle.y2, obj.data.triangle.x3, obj.data.triangle.y3);
                break;
        }
    }
}

// Bresenham's Line Algorithm
void draw_line(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int sx = x1 < x2 ? 1 : -1;
    int dy = -abs(y2 - y1);
    int sy = y1 < y2 ? 1 : -1;
    int err = dx + dy;
    int e2;

    while (1) {
        plot_point(x1, y1);
        if (x1 == x2 && y1 == y2) {
            break;
        }
        e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            x1 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y1 += sy;
        }
    }
}

// Border-only Rectangle drawing
void draw_rectangle(int x, int y, int width, int height) {
    if (width <= 0 || height <= 0) return;
    
    // Draw top and bottom sides
    for (int i = 0; i < width; i++) {
        plot_point(x + i, y);
        plot_point(x + i, y + height - 1);
    }
    // Draw left and right sides
    for (int i = 0; i < height; i++) {
        plot_point(x, y + i);
        plot_point(x + width - 1, y + i);
    }
}

// Midpoint Circle Algorithm (Bresenham's Circle)
void draw_circle(int xc, int yc, int radius) {
    if (radius < 0) return;
    if (radius == 0) {
        plot_point(xc, yc);
        return;
    }

    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    while (y >= x) {
        plot_point(xc + x, yc + y);
        plot_point(xc - x, yc + y);
        plot_point(xc + x, yc - y);
        plot_point(xc - x, yc - y);
        plot_point(xc + y, yc + x);
        plot_point(xc - y, yc + x);
        plot_point(xc + y, yc - x);
        plot_point(xc - y, yc - x);

        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

// Triangle outline drawing by connecting three vertices
void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    draw_line(x1, y1, x2, y2);
    draw_line(x2, y2, x3, y3);
    draw_line(x3, y3, x1, y1);
}
