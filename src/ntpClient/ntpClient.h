#ifndef CRAZYCLOCK_NTP_CLIENT_H
#define CRAZYCLOCK_NTP_CLIENT_H

#include <NTPClient.h>

unsigned long retrieveEpochSeconds(NTPClient *ntpClient);

#endif
