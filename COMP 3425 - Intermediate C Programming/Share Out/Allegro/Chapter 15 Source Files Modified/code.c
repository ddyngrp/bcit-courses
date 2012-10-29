#include <allegro.h>

#define DOWN_RIGHT 0
#define UP_RIGHT 1
#define DOWN_LEFT 2
#define UP_LEFT 3

void moveBall(void);
void respondToKeyboard(void);
void reverseVerticalDirection(void);
void reverseHorizontalDirection(void);

int ball_x;
int ball_y;
int barL_y;
int barR_y;
int scoreL;
int scoreR;
int direction;
BITMAP *ball;
BITMAP *buffer;
BITMAP *bar;
SAMPLE *boing;
FONT *pongFont;

int main() {
    allegro_init();
    install_keyboard();
    set_color_depth(16);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
    ball = load_bitmap("ball.bmp", NULL);
    bar = load_bitmap("bar.bmp", NULL);
    buffer = create_bitmap(640, 480);
    boing = load_sample("boing.wav");
    pongFont = load_font("pongfont.pcx", NULL, NULL);
    ball_x = SCREEN_W / 2;
    ball_y = SCREEN_H / 2;
    barL_y = SCREEN_H / 2;
    barR_y = SCREEN_H / 2;
    scoreL = 0;
    scoreR = 0;
    srand(time(NULL));
    direction = rand() % 4;
    while (!key[KEY_ESC]) {
        moveBall();
        respondToKeyboard();
        rectfill(buffer, 0, 0, 640, 480, makecol(255, 255, 255));
        blit(ball, buffer, 0, 0, ball_x, ball_y, ball->w, ball->h);
        blit(bar, buffer, 0, 0, 0, barL_y, bar->w, bar->h); 
        blit(bar, buffer, 0, 0, 620, barR_y, bar->w, bar->h);
        line(buffer, 0, 30, 640, 30, makecol(0, 0, 0));
        textprintf_ex(buffer, pongFont, 75, 0, makecol(0, 0, 0), -1, "Left Player Score: %d", scoreL);
        textprintf_ex(buffer, pongFont, 400, 0, makecol(0, 0, 0), -1, "Right Player Score: %d", scoreR);
        blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
        clear_bitmap(buffer);
    }
    destroy_bitmap(ball);
    destroy_bitmap(bar);
    destroy_bitmap(buffer);
    destroy_sample(boing);
    destroy_font(pongFont);
    return 0;
}
END_OF_MAIN();

void moveBall() {
    switch (direction) {
        case DOWN_RIGHT:
            ++ball_x;
            ++ball_y;
            break;
        case UP_RIGHT:
            ++ball_x;
            --ball_y;
            break;
        case DOWN_LEFT:
            --ball_x;
            ++ball_y;
            break;
        case UP_LEFT:
            --ball_x;
            --ball_y;
            break;
    }
    if (ball_y <= 30 || ball_y >= 440)
        reverseVerticalDirection();
        
    if (ball_x <= 20 && (direction == DOWN_LEFT || direction == UP_LEFT)) {
        if (ball_y > (barL_y - 35) && ball_y < (barL_y + 95))
            reverseHorizontalDirection();
        else if (ball_x <= -40) {
            ++scoreR;
            ball_x = SCREEN_W / 2;
            ball_y = SCREEN_H / 2;
            direction = rand() % 4;
        }
    }
    
    if (ball_x >= 580 && (direction == DOWN_RIGHT || direction == UP_RIGHT)) {
        if (ball_y > (barR_y - 35) && ball_y < (barR_y + 95))
            reverseHorizontalDirection();
        else if (ball_x >= 640) {
            ++scoreL;
            ball_x = SCREEN_W / 2;
            ball_y = SCREEN_H / 2;
            direction = rand() % 4;
        }
    }
}

void respondToKeyboard() {
     if (key[KEY_A])
        barL_y -= 3;
     if (key[KEY_Z])
        barL_y += 3;
     if (key[KEY_UP])
        barR_y -= 3;
     if (key[KEY_DOWN])
        barR_y += 3;
        
     if (barL_y < 30)
        barL_y = 30;
     if (barL_y > 380)
        barL_y = 380;
     if (barR_y < 30)
        barR_y = 30;
     if (barR_y > 380)
        barR_y = 380;
}

void reverseVerticalDirection() {
     if ((direction % 2) == 0)
        ++direction;
     else
        --direction;
     play_sample(boing, 255, 128, 1000, 0);
}

void reverseHorizontalDirection() {
     direction = (direction + 2) % 4;
     play_sample(boing, 255, 128, 1000, 0);
}
