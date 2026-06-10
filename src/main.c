#include "shapes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

GraphicalObject objects[MAX_OBJECTS];
int object_count = 0;
int next_id = 1;

// Function declarations
void add_shape(void);
void delete_shape(void);
void modify_shape(void);
void clear_all_shapes(void);
void print_shapes_list(void);
int get_int_input(const char *prompt, int min_val, int max_val);

int main(void) {
    printf("=========================================\n");
    printf("      WELCOME TO 2D GRAPHICS EDITOR      \n");
    printf("=========================================\n");
    printf("Canvas size: %d columns x %d rows\n", CANVAS_WIDTH, CANVAS_HEIGHT);
    printf("Coordinates: X in [0, %d], Y in [0, %d]\n\n", CANVAS_WIDTH - 1, CANVAS_HEIGHT - 1);

    while (1) {
        // Render current objects and display canvas
        render_objects(objects, object_count);
        display_canvas();
        print_shapes_list();

        printf("\n--- MENU ---\n");
        printf("1. Add Shape\n");
        printf("2. Delete Shape\n");
        printf("3. Modify Shape\n");
        printf("4. Clear Canvas (Delete All)\n");
        printf("5. Exit\n");

        int choice = get_int_input("Enter choice (1-5): ", 1, 5);

        switch (choice) {
            case 1:
                add_shape();
                break;
            case 2:
                delete_shape();
                break;
            case 3:
                modify_shape();
                break;
            case 4:
                clear_all_shapes();
                break;
            case 5:
                printf("\nExiting 2D Graphics Editor. Goodbye!\n");
                return 0;
        }
    }
    return 0;
}

// Robust input helper to read integers and clear the buffer to prevent infinite loops
int get_int_input(const char *prompt, int min_val, int max_val) {
    char buffer[128];
    int val;
    char extra;
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("\nEnd of input detected. Exiting.\n");
            exit(0);
        }
        
        int parsed = sscanf(buffer, "%d %c", &val, &extra);
        if (parsed == 1) {
            if (val >= min_val && val <= max_val) {
                return val;
            } else {
                printf("Input out of range (%d to %d). Please try again.\n", min_val, max_val);
            }
        } else {
            printf("Invalid input. Please enter an integer.\n");
        }
    }
}

// Prints a summary of all active shapes
void print_shapes_list(void) {
    printf("\nActive Shapes (%d/%d):\n", object_count, MAX_OBJECTS);
    if (object_count == 0) {
        printf("  No shapes on canvas.\n");
        return;
    }
    printf("  ID  | Shape Type | Parameters\n");
    printf("  ----+------------+-------------------------------------------------\n");
    for (int i = 0; i < object_count; i++) {
        GraphicalObject obj = objects[i];
        switch (obj.type) {
            case SHAPE_LINE:
                printf("  %-3d | Line       | Start: (%d, %d), End: (%d, %d)\n", 
                       obj.id, obj.data.line.x1, obj.data.line.y1, obj.data.line.x2, obj.data.line.y2);
                break;
            case SHAPE_RECTANGLE:
                printf("  %-3d | Rectangle  | Top-Left: (%d, %d), Size: %dx%d\n", 
                       obj.id, obj.data.rect.x, obj.data.rect.y, obj.data.rect.width, obj.data.rect.height);
                break;
            case SHAPE_CIRCLE:
                printf("  %-3d | Circle     | Center: (%d, %d), Radius: %d\n", 
                       obj.id, obj.data.circle.xc, obj.data.circle.yc, obj.data.circle.radius);
                break;
            case SHAPE_TRIANGLE:
                printf("  %-3d | Triangle   | P1: (%d, %d), P2: (%d, %d), P3: (%d, %d)\n", 
                       obj.id, obj.data.triangle.x1, obj.data.triangle.y1, 
                       obj.data.triangle.x2, obj.data.triangle.y2, 
                       obj.data.triangle.x3, obj.data.triangle.y3);
                break;
        }
    }
}

// Prompts user for shape parameters and adds to current list
void add_shape(void) {
    if (object_count >= MAX_OBJECTS) {
        printf("Maximum shapes limit reached (%d). Delete some before adding.\n", MAX_OBJECTS);
        return;
    }

    printf("\nChoose Shape to Add:\n");
    printf("1. Line\n");
    printf("2. Rectangle\n");
    printf("3. Circle\n");
    printf("4. Triangle\n");
    int type_choice = get_int_input("Enter type (1-4): ", 1, 4);

    GraphicalObject new_obj;
    new_obj.id = next_id++;

    switch (type_choice) {
        case 1:
            new_obj.type = SHAPE_LINE;
            new_obj.data.line.x1 = get_int_input("Enter X1 (0-59): ", 0, CANVAS_WIDTH - 1);
            new_obj.data.line.y1 = get_int_input("Enter Y1 (0-19): ", 0, CANVAS_HEIGHT - 1);
            new_obj.data.line.x2 = get_int_input("Enter X2 (0-59): ", 0, CANVAS_WIDTH - 1);
            new_obj.data.line.y2 = get_int_input("Enter Y2 (0-19): ", 0, CANVAS_HEIGHT - 1);
            break;
        case 2:
            new_obj.type = SHAPE_RECTANGLE;
            new_obj.data.rect.x = get_int_input("Enter Top-Left X (0-59): ", 0, CANVAS_WIDTH - 1);
            new_obj.data.rect.y = get_int_input("Enter Top-Left Y (0-19): ", 0, CANVAS_HEIGHT - 1);
            new_obj.data.rect.width = get_int_input("Enter Width (1-60): ", 1, CANVAS_WIDTH);
            new_obj.data.rect.height = get_int_input("Enter Height (1-20): ", 1, CANVAS_HEIGHT);
            break;
        case 3:
            new_obj.type = SHAPE_CIRCLE;
            new_obj.data.circle.xc = get_int_input("Enter Center X (0-59): ", 0, CANVAS_WIDTH - 1);
            new_obj.data.circle.yc = get_int_input("Enter Center Y (0-19): ", 0, CANVAS_HEIGHT - 1);
            new_obj.data.circle.radius = get_int_input("Enter Radius (0-60): ", 0, CANVAS_WIDTH);
            break;
        case 4:
            new_obj.type = SHAPE_TRIANGLE;
            new_obj.data.triangle.x1 = get_int_input("Enter P1 X (0-59): ", 0, CANVAS_WIDTH - 1);
            new_obj.data.triangle.y1 = get_int_input("Enter P1 Y (0-19): ", 0, CANVAS_HEIGHT - 1);
            new_obj.data.triangle.x2 = get_int_input("Enter P2 X (0-59): ", 0, CANVAS_WIDTH - 1);
            new_obj.data.triangle.y2 = get_int_input("Enter P2 Y (0-19): ", 0, CANVAS_HEIGHT - 1);
            new_obj.data.triangle.x3 = get_int_input("Enter P3 X (0-59): ", 0, CANVAS_WIDTH - 1);
            new_obj.data.triangle.y3 = get_int_input("Enter P3 Y (0-19): ", 0, CANVAS_HEIGHT - 1);
            break;
    }

    objects[object_count++] = new_obj;
    printf("Shape ID %d added successfully!\n", new_obj.id);
}

// Searches and deletes a shape by user-selected ID
void delete_shape(void) {
    if (object_count == 0) {
        printf("No shapes to delete.\n");
        return;
    }

    int id_to_delete = get_int_input("Enter the ID of the shape to delete: ", 1, next_id - 1);
    int found_index = -1;

    for (int i = 0; i < object_count; i++) {
        if (objects[i].id == id_to_delete) {
            found_index = i;
            break;
        }
    }

    if (found_index == -1) {
        printf("Shape with ID %d not found in active list.\n", id_to_delete);
        return;
    }

    // Shift remaining elements
    for (int i = found_index; i < object_count - 1; i++) {
        objects[i] = objects[i + 1];
    }
    object_count--;
    printf("Shape with ID %d deleted successfully.\n", id_to_delete);
}

// Modifies properties of a shape based on its ID
void modify_shape(void) {
    if (object_count == 0) {
        printf("No shapes to modify.\n");
        return;
    }

    int id_to_modify = get_int_input("Enter the ID of the shape to modify: ", 1, next_id - 1);
    int found_index = -1;

    for (int i = 0; i < object_count; i++) {
        if (objects[i].id == id_to_modify) {
            found_index = i;
            break;
        }
    }

    if (found_index == -1) {
        printf("Shape with ID %d not found in active list.\n", id_to_modify);
        return;
    }

    GraphicalObject *obj = &objects[found_index];
    printf("\nModifying shape ID %d (%s):\n", obj->id, 
           obj->type == SHAPE_LINE ? "Line" :
           obj->type == SHAPE_RECTANGLE ? "Rectangle" :
           obj->type == SHAPE_CIRCLE ? "Circle" : "Triangle");

    switch (obj->type) {
        case SHAPE_LINE:
            obj->data.line.x1 = get_int_input("Enter new X1 (0-59): ", 0, CANVAS_WIDTH - 1);
            obj->data.line.y1 = get_int_input("Enter new Y1 (0-19): ", 0, CANVAS_HEIGHT - 1);
            obj->data.line.x2 = get_int_input("Enter new X2 (0-59): ", 0, CANVAS_WIDTH - 1);
            obj->data.line.y2 = get_int_input("Enter new Y2 (0-19): ", 0, CANVAS_HEIGHT - 1);
            break;
        case SHAPE_RECTANGLE:
            obj->data.rect.x = get_int_input("Enter new Top-Left X (0-59): ", 0, CANVAS_WIDTH - 1);
            obj->data.rect.y = get_int_input("Enter new Top-Left Y (0-19): ", 0, CANVAS_HEIGHT - 1);
            obj->data.rect.width = get_int_input("Enter new Width (1-60): ", 1, CANVAS_WIDTH);
            obj->data.rect.height = get_int_input("Enter new Height (1-20): ", 1, CANVAS_HEIGHT);
            break;
        case SHAPE_CIRCLE:
            obj->data.circle.xc = get_int_input("Enter new Center X (0-59): ", 0, CANVAS_WIDTH - 1);
            obj->data.circle.yc = get_int_input("Enter new Center Y (0-19): ", 0, CANVAS_HEIGHT - 1);
            obj->data.circle.radius = get_int_input("Enter new Radius (0-60): ", 0, CANVAS_WIDTH);
            break;
        case SHAPE_TRIANGLE:
            obj->data.triangle.x1 = get_int_input("Enter new P1 X (0-59): ", 0, CANVAS_WIDTH - 1);
            obj->data.triangle.y1 = get_int_input("Enter new P1 Y (0-19): ", 0, CANVAS_HEIGHT - 1);
            obj->data.triangle.x2 = get_int_input("Enter new P2 X (0-59): ", 0, CANVAS_WIDTH - 1);
            obj->data.triangle.y2 = get_int_input("Enter new P2 Y (0-19): ", 0, CANVAS_HEIGHT - 1);
            obj->data.triangle.x3 = get_int_input("Enter new P3 X (0-59): ", 0, CANVAS_WIDTH - 1);
            obj->data.triangle.y3 = get_int_input("Enter new P3 Y (0-19): ", 0, CANVAS_HEIGHT - 1);
            break;
    }

    printf("Shape ID %d modified successfully.\n", obj->id);
}

// Clears all shape lists
void clear_all_shapes(void) {
    object_count = 0;
    printf("Canvas cleared. All active shapes deleted.\n");
}
