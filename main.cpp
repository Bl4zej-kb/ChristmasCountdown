#include <iostream>
#include <chrono>
#include <csignal>
#include <thread>

#define HEIGHT 10
#define S_HEIGHT 2
#define S_WIDTH 3
#define MINUTE 60
#define HOUR (MINUTE * 60)
#define DAY (HOUR * 24)

void refreshClock();
time_t getClosestChristmas();
bool formatTime(time_t time, std::string &formatted);
void stop(int);

int main() {
    std::signal(SIGINT, stop);

    std::cout << "\033[?25l\033[H\r\033[2J\n";

    for (int i = 0; i <= HEIGHT - 1; i++) {
        std::cout << "\r\033[K";
        for (int j = 0; j <= HEIGHT - i; j++) {
            std::cout << " ";
        }
        for (int j = 0; j <= i * 2; j++) {
            std::cout << "*";
        }
        std::cout << "\n";
    }

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

    std::cout << "\n\n";

    while (true) {
        std::thread clock(refreshClock);

        std::this_thread::sleep_for(std::chrono::seconds(1));

        clock.join();
    }

    return 0;
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