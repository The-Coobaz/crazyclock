#ifndef CRAZYCLOCK_TIME_FORMATTER_H
#define CRAZYCLOCK_TIME_FORMATTER_H

#define SUCCESS 0
#define INCORRECT_HOUR 1
#define INCORRECT_MINUTE 2
#define INCORRECT_SECOND 3

/**
 * Format the time into the buffer (should be at least 9 characters long).
 *
 * @param hour
 * @param minute
 * @param second
 * @param targetBuffer the formatted time will be put in this
 *
 * @return 0 for success or error code in case of some troubles
 */
int formatTime(int hour, int minute, int second, char *targetBuffer);

#endif
