#include <stdio.h>

const int WIDTH = 80;
const int HEIGHT = 25;
const int ROCKET_WIDTH = 3;
const int BALL_SIZE = 1;
const int OFFSET = 1;
void clearScreen() {
    printf("\e[1;1H\e[2J");
    printf("\033[H");
}

void draw(int left_rocket, int right_rocket, int ball_x, int ball_y) {
    clearScreen();
    for (int i = 0; i < WIDTH; i++) printf("=");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == ball_x && y == ball_y) {
                printf("*");
            }

            if (x == OFFSET && (y == left_rocket || y == left_rocket + 1 || y == left_rocket - 1) && left_rocket > 1 && left_rocket < HEIGHT - 1) {
                printf("|");
            }
            else if (x == WIDTH - OFFSET && (y == right_rocket || y == right_rocket + 1 || y == right_rocket - 1) && right_rocket > 1 && right_rocket < HEIGHT - 1) {
                if (ball_y == y) {
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

int move_ball_x(int direction) {
    switch (direction) {
    case 1: return 1;
    case -1: return -1;
    default:
        return 0;
    }
}

int move_ball_y(int direction) {
    switch (direction) {
    case 1: return 1;
    case -1: return -1;
    default:
        return 0;
    }
}

int calculate_direction_x(int ball_x, int ball_y, int left_rocket, int right_rocket) {
    if ((ball_x == WIDTH - OFFSET - 1 || ball_x == OFFSET + 1) && ((ball_y == right_rocket || ball_y == right_rocket - 1 || ball_y == right_rocket + 1) ||
        (ball_y == left_rocket || ball_y == left_rocket - 1 || ball_y == left_rocket + 1))) {
        printf("DS");
        return -1;
    }
    return 1;

}

int calculate_direction_y(int ball_x, int ball_y, int left_rocket, int right_rocket) {
    if (ball_y == 1 || ball_y == HEIGHT - 1) {
        printf("DS");
        return -1;
    }
    return 1;

}

int main() {
    int ball_x = 40;
    int ball_y = 12;
    int left_rocket = 12;
    int right_rocket = 12;
    int direction_x = 1;
    int direction_y = 1;
    draw(left_rocket, right_rocket, ball_x, ball_y);
    while (1) {
        char move = getchar();
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

        ball_x += move_ball_x(direction_x);
        ball_y += move_ball_y(direction_y);

        direction_x *= calculate_direction_x(ball_x, ball_y, left_rocket, right_rocket);
        direction_y *= calculate_direction_y(ball_x, ball_y, left_rocket, right_rocket);

        draw(left_rocket, right_rocket, ball_x, ball_y);
    }

    return 0;
}

