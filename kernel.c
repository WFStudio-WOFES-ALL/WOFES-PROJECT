// kernel.c
#define VIDEO_MEMORY 0xb8000
#define COLS 80
#define ROWS 25

int cursor_x = 0;
int cursor_y = 0;

void scroll() {
    char* video = (char*) VIDEO_MEMORY;
    for (int y = 1; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            int src = (y * COLS + x) * 2;
            int dst = ((y-1) * COLS + x) * 2;
            video[dst] = video[src];
            video[dst+1] = video[src+1];
        }
    }
    int last = (ROWS-1) * COLS * 2;
    for (int x = 0; x < COLS * 2; x += 2) {
        video[last + x] = ' ';
        video[last + x + 1] = 0x0F;
    }
    cursor_y--;
}

void putchar(char c, char color) {
    char* video = (char*) VIDEO_MEMORY;
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else {
        int pos = (cursor_y * COLS + cursor_x) * 2;
        video[pos] = c;
        video[pos+1] = color;
        cursor_x++;
    }
    
    if (cursor_x >= COLS) {
        cursor_x = 0;
        cursor_y++;
    }
    
    if (cursor_y >= ROWS) {
        scroll();
    }
}

void print(const char* str, char color) {
    for (int i = 0; str[i] != '\0'; i++) {
        putchar(str[i], color);
    }
}

void kernel_main() {
    char* video = (char*) VIDEO_MEMORY;
    for (int i = 0; i < COLS * ROWS * 2; i += 2) {
        video[i] = ' ';
        video[i+1] = 0x0F;
    }
    
    print("=== WOFES OS ===\n", 0x0F);
    print("Hello from the kernel!\n", 0x2F);
    print("Color text works.\n", 0x1F);
    print("Next: keyboard and commands.\n", 0x0F);
    
    while(1);
}