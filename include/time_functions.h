#ifndef TIME_FUNCTIONS_H
#define TIME_FUNCTIONS_H
gint64 get_unix_time();
gint64 hms_to_seconds(gchar * input);
gchar * seconds_to_hms(gint64 seconds);
#endif

