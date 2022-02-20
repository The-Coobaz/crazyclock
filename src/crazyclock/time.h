
class LocalTime {
public:
  int hour;
  int minute;
  int second;
  int millisecond;
};

LocalTime fromEpochMillis(long epochMillis);
