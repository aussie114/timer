#include "renderer.h"
#include "time_functions.h"

extern char ascii_numbers[10][56];
extern char ascii_colon[16];

void render(WINDOW * digits[], char * time_label, int seconds, bool flash, bool redraw)
{
	// Check if window is large enough to display output
	if (getmaxx(stdscr) < 86 || getmaxy(stdscr) < 9)
	{
		erase();
		mvprintw(0,0, "window too small for output");
		mvprintw(1,0, "resize or press q to quit...");
		return;
	}

	// Set seconds
	char time[16];
	seconds_to_hms(seconds, time);
	// redraw everything if requested
	if (redraw)
	{
		erase();
		// Redraw header
		mvprintw(0, 1, time_label);
		// Recreate border
		delwin(digits[9]);
		digits[9] = newwin( 7, 86, 1, 0);
		// Recreate digits
		int digits_x[] = {1, 14, 27, 32, 44, 57, 62, 74};
		for (int i = 0; i < 8; i++)
		{
			delwin(digits[i]);
			if (i == 2 || i == 5)  //if colon
			{
				digits[i] = newwin( 5, 3, 2, digits_x[i]);
			}
			else                 // if numeric
			{
				digits[i] = newwin( 5, 11, 2, digits_x[i]);
			}
		}
		box(digits[9], 0, 0);
		// Redraw colons
		mvwprintw(digits[2], 0, 0, ascii_colon);
		mvwprintw(digits[5], 0, 0, ascii_colon);
		// Redraw footer
		mvprintw(8,0, "         p: pause                      r: reset                       q: quit    ");
		// Refresh everything
		refresh();
		wrefresh(digits[9]);
		wrefresh(digits[2]);
		wrefresh(digits[5]);
	}
	// Prints out time
	for (int i = 0; i < 8; i++)
	{
		if (time[i] != ':')
		{
			if (flash)
			{
				werase(digits[i]);
				wrefresh(digits[i]);
			}
			else
			{
				mvwprintw(digits[i], 0, 0, ascii_numbers[time[i] - 48]);
				wrefresh(digits[i]);
			}
		}
	}
}

char ascii_numbers[10][56] =
{
	{
		"  ooooooo  "
		"o888  o888o"
		"888  8  888"
		"888o8  o888"
		"  88ooo88  "
	},
	{
		"     oo    "
		"   o888    "
		"    888    "
		"    888    "
		"   o888o   "
	},
	{
		"  ooooooo  "
		"o88     888"
		"      o888 "
		"   o888   o" 
		"o8888oooo88"
	},                                                                                                            
	{
		"  ooooooo  "
		"o88    888o"
		"    88888o "
		"88o    o888"
		"  88ooo88  "
	},
	{
		"      o88  "
		"    o8888  "
		"  o88 888  "
		"o888oo888oo"
		"     o888o "
	},
	{
		"oooooooooo "
		"888        "
		"888888888o "
		"ooo    o888"
		"  88ooo88  "
	},
	{
		"  ooooooo  "
		"o88        "
		"888888888o "
		"88o    o888"
		"  88ooo88  "
	},
	{
		"ooooooooooo"
		"888    888 "
		"      888  "
		"     888   "
		"    888    "
	},
	{
		"  ooooooo  "
		"o888   888o"
		" 888888888 "
		"888o   o888"
		"  88ooo88  "
	},
	{
		"  ooooooo  "
		" 888    88o"
		"  888oo8888"
		"       888 "
		"    o888   "
	}
};

char ascii_colon[16] = 
{
	"   "
	"888"
	"   "
	"888"
	"   "  
};

