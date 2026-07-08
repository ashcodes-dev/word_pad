#define _CRT_SECURE_NO_WARNINGS
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui-4.0/src/raygui.h"
#include <stdio.h>
typedef struct {
    char text[100];
int  length;
} data_line;
typedef struct {
    int x;
    int y;
} Point;
int line = 0;


int counter = 0;
int screen_width = 800;
int screen_height = 600;
void input(data_line file[], Point* cursor);
void draw_text(Point* cursor, data_line file[]);

int main() {
    InitWindow(screen_width, screen_height, "Window");
    SetTargetFPS(60); // Set the target frames-per-second
	Point cursor = { 0, 0 }; // Initialize cursor position
    data_line file[100] = { 0 };

    while (!WindowShouldClose()) {    // main loop
        BeginDrawing();
        ClearBackground(RAYWHITE);
        input(file, &cursor);
        DrawRectangle(cursor.x, cursor.y, 10, 20, RED);
        draw_text(&cursor, file);
        
		
		
		
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
void  draw_text(Point* cursor, data_line file[]) {
   
    if (counter > 0 || line >0) {
    for (int i = 0; i <=line; i++) {
        DrawText(file[i].text, 0, i * 20, 20, BLACK);
    }
}
}
void input( data_line file [] , Point  *cursor) {
	int key = GetKeyPressed();

	if (key > 0) {
        
		  file [line].text[counter] = (char)key;
		  file[line].text[counter + 1] = '\0'; // Null-terminate the string
		counter++;
        cursor->x = MeasureText(file[line].text, 20);
        
	}
   
    if  ( (MeasureText(file[line].text, 20) >= screen_width  -20 ) || IsKeyPressed(KEY_ENTER)) {
        cursor->x = 0;
        cursor->y += 20;
        line++;// Move to the next line
        counter = 0;
        file[line].text[counter ] = '\0';
        
    }
}



