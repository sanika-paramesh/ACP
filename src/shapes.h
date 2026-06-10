#ifndef SHAPES_H
#define SHAPES_H

#define CANVAS_HEIGHT 20
#define CANVAS_WIDTH 60
#define MAX_OBJECTS 100

typedef enum {
    SHAPE_LINE,
    SHAPE_RECTANGLE,
    SHAPE_CIRCLE,
    SHAPE_TRIANGLE
} ShapeType;

typedef struct {
    int x1, y1;
    int x2, y2;
} LineData;

typedef struct {
    int x, y;
    int width, height;
} RectangleData;

typedef struct {
    int xc, yc;
    int radius;
} CircleData;

typedef struct {
    int x1, y1;
    int x2, y2;
    int x3, y3;
} TriangleData;

typedef struct {
    int id;
    ShapeType type;
    union {
        LineData line;
        RectangleData rect;
        CircleData circle;
        TriangleData triangle;
    } data;
} GraphicalObject;

// Canvas definition
extern char canvas[CANVAS_HEIGHT][CANVAS_WIDTH];

// Canvas management
void clear_canvas(void);
void display_canvas(void);
void render_objects(GraphicalObject objects[], int object_count);

// Shape rendering functions
void draw_line(int x1, int y1, int x2, int y2);
void draw_rectangle(int x, int y, int width, int height);
void draw_circle(int xc, int yc, int radius);
void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3);

#endif /* SHAPES_H */
