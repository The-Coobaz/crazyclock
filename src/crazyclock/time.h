
class LocalTime {
public:
  int hour;
  int minute;
  int second;
  int millisecond;

  LocalTime(int h, int m, int s);
};

LocalTime fromEpochMillis(long epochMillis);
