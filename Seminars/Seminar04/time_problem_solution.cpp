#include <iostream>
#include <cstdio>

struct Time {
    int hours, minutes, seconds;

    void normalize() {
        minutes += seconds / 60;
        seconds %= 60;
        hours += minutes / 60;
        minutes %= 60;
        hours %= 24;
    }

    Time() : hours(0), minutes(0), seconds(0) {}

    Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {
        normalize();
    }

    Time(int total_seconds) {
        hours = (total_seconds / 3600) % 24;
        minutes = (total_seconds % 3600) / 60;
        seconds = total_seconds % 60;
    }

    void increment() {
        seconds++;
        normalize();
    }

    bool is_earlier_than(const Time &other) const {
        if (hours != other.hours) return hours < other.hours;
        if (minutes != other.minutes) return minutes < other.minutes;
        return seconds < other.seconds;
    }

    Time difference(const Time &other) const {
        int total_seconds_1 = hours * 3600 + minutes * 60 + seconds;
        int total_seconds_2 = other.hours * 3600 + other.minutes * 60 + other.seconds;
        int diff_seconds = std::abs(total_seconds_1 - total_seconds_2);

        return Time(diff_seconds / 3600, (diff_seconds % 3600) / 60, diff_seconds % 60);
    }

    void print() const {
        std::cout << (hours < 10 ? "0" : "") << hours << ":"
                  << (minutes < 10 ? "0" : "") << minutes << ":"
                  << (seconds < 10 ? "0" : "") << seconds << std::endl;
    }

    Time time_until_midnight() const {
        return Time(23 - hours, 59 - minutes, 60 - seconds);
    }

    bool is_dinner_time() const {
        return (hours == 20 && minutes >= 30) || (hours == 21) || (hours == 22 && minutes == 0);
    }

    bool is_party_time() const {
        return (hours >= 23) || (hours < 6);
    }
};

void stable_sort(Time arr[], int n) {
    for (int i = 1; i < n; i++) {
        Time key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].is_earlier_than(key)) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
    Time times[10] = {
        Time(12, 30, 45),
        Time(20, 35, 10),
        Time(5, 15, 25),
        Time(23, 59, 59),
        Time(0, 0, 0),
        Time(19, 45, 30),
        Time(14, 10, 5),
        Time(21, 0, 0),
        Time(3, 50, 40),
        Time(22, 10, 15)
    };

    stable_sort(times, 10);

    for (int i = 0; i < 10; i++) {
        times[i].print();
    }

    return 0;
}
