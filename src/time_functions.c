#include <stdio.h>

int hms_to_seconds(char * input)
{
	int digit_0, digit_1, digit_2;

	int result = sscanf(input, "%d:%d:%d", &digit_0, &digit_1, &digit_2);

	switch (result)
	{
		case 1:
			return digit_0;
		case 2:
			return digit_0 * 60 + digit_1;
		case 3:
			return digit_0 * 3600 + digit_1 * 60 + digit_2;
		default:
			return 0;
	}
}

void seconds_to_hms(int seconds, char output[16])
{
	int hour = seconds / 3600;
	int minute = (seconds % 3600) / 60;
	int second = seconds % 60;
	snprintf(output, 16, "%02d:%02d:%02d", hour, minute, second);
}
