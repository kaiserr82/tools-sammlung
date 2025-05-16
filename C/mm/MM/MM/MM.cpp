//sudo apt install libx11-dev

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <random>
#include <iomanip>  // für std::put_time
#include <sstream>  // für std::ostringstream

#ifdef _WIN32
#include <windows.h>
#else
#include <X11/Xlib.h>
#endif

void moveMouse(int x, int y) {
#ifdef _WIN32
    SetCursorPos(x, y);
#else
    Display* display = XOpenDisplay(NULL);
    if (display == NULL) {
        std::cerr << "Kann X Display nicht öffnen.\n";
        return;
    }

    Window root = DefaultRootWindow(display);
    XWarpPointer(display, None, root, 0, 0, 0, 0, x, y);
    XFlush(display);
    XCloseDisplay(display);
#endif
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> pause_dist(10, 240);     // Sekunden
    std::uniform_int_distribution<> pos_dist(100, 500);      // Pixel

    std::cout << "Starte Mausbewegungssimulator...\n";

    while (true) {
        int pause_sec = pause_dist(gen);
        std::cout << "Wartezeit: " << pause_sec << " Sekunden\n";
        std::this_thread::sleep_for(std::chrono::seconds(pause_sec));

        int x = pos_dist(gen);
        int y = pos_dist(gen);

        moveMouse(x, y);

        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);

        std::tm now_tm;
#ifdef _WIN32
        localtime_s(&now_tm, &now_c);
#else
        localtime_r(&now_c, &now_tm);
#endif

        std::ostringstream time_stream;
        time_stream << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
        std::cout << "Maus bewegt nach (" << x << ", " << y << ") um " << time_stream.str() << "\n";
    }

    return 0;
}
