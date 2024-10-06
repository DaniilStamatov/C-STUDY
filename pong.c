#include <stdio.h>
#include <conio.h>
#include <windows.h>
const int WIDTH = 80;
const int HEIGHT = 25;
const int ROCKET_WIDTH = 3;
const int BALL_SIZE = 1;
const int OFFSET = 3;
const int SCORE = 21;
void clear_screen() {

    printf("\033[H");
}

int check_for_rocket(int y, int rocket) {
    return y == rocket || y == rocket - 1 || y == rocket + 1;
}

void draw(int left_rocket, int right_rocket, int ball_x, int ball_y, int score_left, int score_right) {
    clear_screen();
    printf("\t\t%2d\t\t\t\t\t\t%2d\n", score_left, score_right);

    for (int i = 0; i < WIDTH; i++) printf("=");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if ((x == ball_x && y == ball_y)) {
                printf("*");
            }
            if (x == OFFSET && check_for_rocket(y, left_rocket) && left_rocket > 1 && left_rocket < HEIGHT - 1) {
                printf("|");
            }
            else if (x == WIDTH - OFFSET && check_for_rocket(y, right_rocket) && right_rocket > 1 && right_rocket < HEIGHT - 1) {
                if (ball_y == y && ball_x < WIDTH - OFFSET) {
                    printf("\b");
                }
                printf("|");
            }
            else {
                printf(" ");

            }

        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH; i++) printf("=");
}

int move_ball(int direction) {
    switch (direction) {
    case 1: return 1;
    case -1: return -1;
    default:
        return 0;
    }
}

int calculate_direction_x(int ball_x, int ball_y, int left_rocket, int right_rocket) {
    if ((ball_x == WIDTH - OFFSET - 2 || ball_x == OFFSET + 1)
        && (check_for_rocket(ball_y, right_rocket) || check_for_rocket(ball_y, left_rocket))) {
        printf("%d", ball_x);
        return -1;
    }
    return 1;

}

int calculate_direction_y(int ball_x, int ball_y, int left_rocket, int right_rocket) {
    if (ball_y == 1 || ball_y == HEIGHT - 1) {
        return -1;
    }
    return 1;
}

void reset(int score_left, int score_right) {
    draw(12, 12, 40, 12, score_left, score_right);
}

int main() {
    int ball_x = 40;
    int ball_y = 12;
    int left_rocket = 12;
    int right_rocket = 12;
    int direction_x = 1;
    int direction_y = 1;
    int score_left = 0;
    int score_right = 0;
    char move = ' ';
    draw(left_rocket, right_rocket, ball_x, ball_y, score_left, score_right);
    while (score_left < SCORE && score_right < SCORE) {
        if (_kbhit()) {
            move = _getch();
        }
        if ((move == 'A' || move == 'a') && left_rocket > 2) {
            left_rocket--;
        }
        else if ((move == 'K' || move == 'k') && right_rocket > 2) {
            right_rocket--;
        }
        else if ((move == 'Z' || move == 'z') && left_rocket < HEIGHT - 2) {
            left_rocket++;
        }
        else if ((move == 'M' || move == 'm') && right_rocket < HEIGHT - 2) {
            right_rocket++;
        }

        direction_x *= calculate_direction_x(ball_x, ball_y, left_rocket, right_rocket);
        direction_y *= calculate_direction_y(ball_x, ball_y, left_rocket, right_rocket);
        ball_x += move_ball(direction_x);
        ball_y += move_ball(direction_y);
        if (ball_x == WIDTH && !check_for_rocket(ball_y, right_rocket)) {
            score_left++;
            left_rocket = 12;
            right_rocket = 12;
            ball_x = 40;
            ball_y = 12;
        }
        else if (ball_x == 0 && !check_for_rocket(ball_y, left_rocket)) {
            score_right++;

            left_rocket = 12;
            right_rocket = 12;
            ball_x = 40;
            ball_y = 12;
        }

        draw(left_rocket, right_rocket, ball_x, ball_y, score_left, score_right);
        move = ' ';
        Sleep(100);
    }
    clear_screen();
    if (score_left == SCORE) {
        printf("Player 1 WIN");
        for (int i = 0; i < 50; i++) {
            printf("!");
        }
    }
    else if (score_right == SCORE) {
        printf("Player 2 WIN");
        for (int i = 0; i < 50; i++) {
            printf("!");
        }
    }
    return 0;
}

