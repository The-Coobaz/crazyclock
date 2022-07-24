#ifndef CRAZYCLOCK_LOCAL_DATE_TIME_H
#define CRAZYCLOCK_LOCAL_DATE_TIME_H

#define SUCCESS 0

/**
 * Format the time into the buffer (should be at least 8 characters long).
 *
 * @param hour
 * @param minute
 * @param second
 * @param targetBuffer the formatted time will be put in this
 *
 * @return 0 for success or error code in case of some troubles
 */
int formatTime(int hour, int minute, int second, char* targetBuffer);

#endif
