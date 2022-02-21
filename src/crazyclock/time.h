
class LocalTime {
public:
  int hour;
  int minute;
  int second;
};

long epochMillis();

LocalTime toWarsawTime(long epochMillis);
