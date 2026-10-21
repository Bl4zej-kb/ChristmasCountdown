#include <iostream>
#include <chrono>
#include <csignal>
#include <thread>
#include <cstdlib>

#define HEIGHT 10
#define S_HEIGHT 2
#define S_WIDTH 3
#define MINUTE 60
#define HOUR (MINUTE * 60)
#define DAY (HOUR * 24)
#define BAUBLE_CHANCE 3


// function declarations ----------------------------------
void refreshClock();
void refreshTree();
time_t getClosestChristmas();
bool formatTime(time_t time, std::string &formatted);
void stop(int);
void refreshAll();
void drawPixel();
// function declarations ==================================


// function definitions -----------------------------------
int main() {
    srand(time(nullptr));

    std::signal(SIGINT, stop);

    std::cout << "\033[?25l\033[H\r\033[2J\n"; //hide cursor, move it to top left corner, move to start of line, clear whole terminal, move to new line

    while (true) {
        std::thread tick(refreshAll);

        std::this_thread::sleep_for(std::chrono::seconds(1));

        tick.join();
    }

    return 0;
}

void refreshTree() {
    std::cout << "\033[H\r\033[2J\n";

    for (int i = 0; i <= HEIGHT - 1; i++) {
        std::cout << "\r\033[K";
        for (int j = 0; j <= HEIGHT - i; j++) {
            std::cout << " ";
        }
        for (int j = 0; j <= i * 2; j++) {
            drawPixel();
        }
        std::cout << "\n";
    }

    std::cout << "\033[90m";

    for (int i = 0; i <= S_HEIGHT - 1; i++) {
        std::cout << "\r\033[K";
        for (int j = 0; j <= HEIGHT - (S_WIDTH / 2); j++) {
            std::cout << " ";
        }
        for (int j = 0; j <= S_WIDTH - 1; j++) {
            std::cout << "I";
        }
        std::cout << "\n";
    }

    std::cout << "\033[39m\n\n";
}

void refreshClock() {
    time_t now = std::time(nullptr);
    time_t closestChristmas = getClosestChristmas();

    time_t timeUntilChristmas = closestChristmas - now;

    std::string formatted;
    formatTime(timeUntilChristmas, formatted);

    std::cout << "\r\033[K" << "Time left to Christmas Eve: " << formatted << std::flush;
}

time_t getClosestChristmas() {
    return 1798066800;
}

bool formatTime(time_t time, std::string &formatted) {
    std::string days = "999", hours = "99", minutes = "99", seconds = "99";
    uint16_t iDays;
    uint8_t iHours, iMinutes, iSeconds;

    iDays = time / DAY;
    iHours = time / HOUR - iDays * 24;
    iMinutes  = time / MINUTE - iHours * 60 - iDays * 24 * 60;
    iSeconds = time - iMinutes * 60 - iHours * 60 * 60 - iDays * 24 * 60 * 60;

    days = std::to_string(iDays);
    hours = std::to_string(iHours);
    minutes = std::to_string(iMinutes);
    seconds = std::to_string(iSeconds);

    formatted = "\033[42m\033[31m" + days + "D " + hours + "H " + minutes + "M " + seconds + "S\033[49m\033[39m";

    return true;
}

void stop(int) {
    write(STDOUT_FILENO, "\033[?25h\033[0m\033[H\r\033[2J", 18);
    _exit(130);
}

void refreshAll() {
    refreshTree();
    refreshClock();
}

void drawPixel() {
    if (rand()%BAUBLE_CHANCE == 0) {
        switch (rand()%14) {
            case 0:
                std::cout << "\033[31m";
                break;

            case 1:
                std::cout << "\033[32m";
                break;

            case 2:
                std::cout << "\033[33m";
                break;

            case 3:
                std::cout << "\033[34m";
                break;

            case 4:
                std::cout << "\033[35m";
                break;

            case 5:
                std::cout << "\033[36m";
                break;

            case 6:
                std::cout << "\033[37m";
                break;

            case 7:
                std::cout << "\033[91m";
                break;

            case 8:
                std::cout << "\033[92m";
                break;

            case 9:
                std::cout << "\033[93m";
                break;

            case 10:
                std::cout << "\033[94m";
                break;

            case 11:
                std::cout << "\033[95m";
                break;

            case 12:
                std::cout << "\033[96m";
                break;

            case 13:
                std::cout << "\033[97m";
                break;


        }
    }
    else std::cout << "\033[32m";

    std::cout << "*\033[39m";
}
// function definitions ===================================