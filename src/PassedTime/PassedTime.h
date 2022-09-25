#ifndef CRAZYCLOCK_PASSED_MILLIS_H
#define CRAZYCLOCK_PASSED_MILLIS_H

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
