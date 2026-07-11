#define _CRT_SECURE_NO_WARNINGS
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui-4.0/src/raygui.h"
#include <stdio.h>
typedef struct {
    char text[100];
    int  length;
} data_line;
int line = 0;



int counter = 0;
int screen_width = 800;
int screen_height = 600;
void input(data_line file[], Vector2* cursor, Font text_font);
void  draw_text(Vector2* cursor, data_line file[], Font text_font);
void load_file(data_line file[], FILE* fp);
void save_file(data_line file[], int line_count);
void gui(data_line file[]);

int menu_margin = 30;

int main() {
    InitWindow(screen_width, screen_height, "Wordpad");
    SetTargetFPS(60); // Set the target frames-per-second
    Vector2 cursor = { 0, menu_margin }; // Initialize cursor position
    data_line file[100] = { 0 };
    Font text_font = LoadFontEx("assets/fonts/OpenSans-Regular.ttf", 24, NULL, 0);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 22);

    while (!WindowShouldClose()) {    // main loop
        BeginDrawing();
        ClearBackground(RAYWHITE);
        input(file, &cursor, text_font);
        DrawRectangle(cursor.x, cursor.y, 1, 20, RED);
        gui(file );

        draw_text(&cursor, file, text_font);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
void  draw_text(Vector2* cursor, data_line file[], Font text_font) {

    if (counter > 0 || line > 0) {
        for (int i = 0; i <= line; i++) {
            DrawTextEx(text_font, file[i].text, (Vector2) { 0, i * 20 + menu_margin }, 24, 0, BLACK);
        }
    }
}
void input(data_line file[], Vector2* cursor, Font text_font) {
    int key;
    bool typing = false;


    if ((typing == true &&
        MeasureTextEx(text_font, file[line].text, 24, 0).x >= screen_width - 24) || IsKeyPressed(KEY_ENTER)) {
        cursor->x = 0;

        file[line].length = counter;
        line++;// Move to the next line0

        counter = 0;
        file[line].text[counter] = '\0';
        printf("Line %d: '%s'\n", line, file[line].text);
        printf("counter: %d\n", counter);
        printf("line no %d\n", line);

    }
    while (( key = GetCharPressed()) != 0)
    {
        file[line].text[counter] = (char)key;
		counter++;
        file[line].text[counter] = '\0';
		typing = true;
        


    }
    if ((typing == true &&
        MeasureTextEx(text_font, file[line].text, 24, 0).x >= screen_width - 24) || IsKeyPressed(KEY_ENTER)) {
        cursor->x = 0;

        file[line].length = counter;
        line++;// Move to the next line0

        counter = 0;
        
    }


    
    cursor->x = MeasureTextEx(text_font, file[line].text, 24, 0).x;
    cursor->y = (line * 20) + menu_margin;

    static float cursor_cooldown = 0;
    if (IsKeyDown(KEY_BACKSPACE) && cursor_cooldown <= 0) {
        if (counter <= 0) {
            if (line > 0) {
                line--;
                counter = file[line].length;
                file[line].text[counter] = '\0';
                cursor_cooldown = 1.0f / 10.0f;

            }
        }
        else {
            file[line].text[counter] = '\0';
            counter--;
            cursor_cooldown = 1.0f / 10.0f;
        }
        
    }
	cursor_cooldown -= GetFrameTime();  



}
void gui( data_line file []) {
    static bool file_button_pressed = false;
    if (GuiButton((Rectangle) { 0, 0, 100, menu_margin }, "FILE"))

    {
        file_button_pressed = !file_button_pressed;


    }
    if (file_button_pressed) {
        if (GuiButton((Rectangle) { 0, menu_margin, 100, menu_margin }, "New")) {
            printf("New file created!\n");
            file_button_pressed = false; // Close the menu after clicking
        }
        if (GuiButton((Rectangle) { 0, menu_margin * 2, 100, menu_margin }, "Open")) {
            printf("Open file dialog!\n");
            load_file(file, fopen("data/untitled.txt", "r"));
            file_button_pressed = false; // Close the menu after clicking
        }
        if (GuiButton((Rectangle) { 0, menu_margin * 3, 100, menu_margin }, "Save")) {
            printf("File saved!\n");
			save_file(file, line);
            file_button_pressed = false; // Close the menu after clicking
        }
        if (GuiButton((Rectangle) { 0, menu_margin * 4, 100, menu_margin }, "Exit")) {
            printf("Exiting application!\n");
            file_button_pressed = false; // Close the menu after clicking
        }
    }
    if (GuiButton((Rectangle) { 100, 0, 100, menu_margin }, "EDIT"))
    {
        printf("Button clicked!\n");
    }
}
void create_new_file(data_line file[]) {
	FILE* new_file = fopen("untitled.txt", "w");

}
void save_file(data_line file[], int line_count) {
	FILE* fp= fopen("data/untitled.txt", "w");
    for (int i = 0; i <= line_count; i++) {
        fprintf(fp, "%s\n", file[i].text);
	}
	GuiLabel((Rectangle) { 0, 100, 200, 30 }, "File saved as untitled.txt");
    
}
void load_file(data_line file[], FILE* fp) {
    int i = 0;
    
    while (fgets(file[line].text, sizeof(file[line].text), fp) != NULL) {
        file[line].length = strlen(file[line].text);
        file[i].length = strlen(file[i].text);
        counter = file[i].length;
        line++;
        i++;
    }
    
}
