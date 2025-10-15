#include <ncurses.h>
#include <time.h>
#include "time_functions.h"
#include "renderer.h"

int main(int argc, char ** argv)
{
	if (argc != 2) {return -1;}
	// init ncurses
	initscr();
	curs_set(0);
	noecho();
	keypad(stdscr, true);
	nodelay(stdscr, true);

	// Create border and digits window
	WINDOW * digits[10];
	digits[9] = newwin( 7, 86, 0, 0);
	refresh();

	// Creates digit windows
	int digits_x[] = {1, 14, 27, 32, 44, 57, 62, 74};
	for (int i = 0; i < 8; i++)
	{
		if (i == 2 || i == 5)  //if colon
		{
			digits[i] = newwin( 5, 3, 1, digits_x[i]);
		}
		else                 // if numeric
		{
			digits[i] = newwin( 5, 11, 1, digits_x[i]);
		}
		refresh();
		wrefresh(digits[i]);
	}

	int key = 0;
	int previous_time = 0;
	bool paused = false;
	int end_time = time(NULL) + hms_to_seconds(argv[1]);
	int total_seconds = end_time - time(NULL);

	bool flash = false;

	char time_label[64];
	char hms_total_seconds[16];
	seconds_to_hms(total_seconds, hms_total_seconds);
	snprintf(time_label, 64, "%35cTimer %s", ' ', hms_total_seconds);

	// Initial draw
	render(digits, time_label, end_time - time(NULL), flash, true);

	while(1)
	{
		// Called 20 time per second
		key = getch();
		if      (key == 'q')
		{
			echo();
			endwin();
			return 0;
		}

		if (key == 'r')
		{
			end_time = time(NULL) + total_seconds;
			flash = false;
			render(digits, time_label, end_time - time(NULL), flash, false);
		}

		else if (key == 'p' && end_time - time(NULL) > 0)
		{
			paused = !paused;
			flash = false;
			render(digits, time_label, end_time - time(NULL), flash, false);
		}

		else if (key == KEY_RESIZE)
		{
			render(digits, time_label, end_time - time(NULL), flash, true);
		}

		// Called  1 time per second
		if (time(NULL) != previous_time)
		{
			previous_time = time(NULL);
			if (paused)
			{
				end_time++;
			}
			else if (end_time - time(NULL) < 0)
			{
				end_time++;
				flash = !flash;
			}
			render(digits, time_label, end_time - time(NULL), flash, false);
		}

		napms(50); // target 20fps 

	}
	echo();
	endwin();
}

