#include <gtk/gtk.h>
#include "main.h"

gint64 get_unix_time()
{
	return (g_get_real_time() / 1000000);
}

guint64 hms_to_seconds(gchar * input)
{
	gchar ** digits = g_strsplit(input, ":", -1);
	int count = 0;
	guint64 seconds;
	while (digits[count] != NULL) { count++; }

	switch (count)
	{
		case 3:
			seconds  = g_ascii_strtoll(digits[0], NULL, 10)* 3600;
			seconds += g_ascii_strtoll(digits[1], NULL, 10) * 60;
			seconds += g_ascii_strtoll(digits[2], NULL, 10);
			break;
		case 2:
			seconds  = g_ascii_strtoll(digits[0], NULL, 10) * 60;
			seconds += g_ascii_strtoll(digits[1], NULL, 10);
			break;
		case 1:
			seconds  = g_ascii_strtoll(digits[0], NULL, 10);
			break;
		default:
			seconds = 0;
	}

	return seconds;

	g_strfreev(digits);
}

gchar * seconds_to_hms(gint64 seconds)
{
	gint64 hour = seconds / 3600;
	gint64 minute = (seconds % 3600) / 60;
	gint64 second = seconds % 60;

	return g_strdup_printf("%02ld:%02ld:%02ld", hour, minute, second);
}
