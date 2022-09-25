#ifndef CRAZYCLOCK_PASSED_MILLIS_H
#define CRAZYCLOCK_PASSED_MILLIS_H

#define ARDUINO_MAX_MILLIS 1234L

class PassedTime {

private:
    long _seconds;
    long _millis;

    PassedTime(long seconds, long millis);

public:
    static PassedTime fromDistance(long startMillis, long endMillis);

    long getSeconds();
    long getMillis();
};

#endif
