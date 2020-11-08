/*---------------------------------------------------------
 * file: console.h
 *   by: P.Allen
 *  org: COP 2001, Spring 2020
 *  for: source file for the console library of functions
 *       for graphics, keyboard input, and timing
 *---------------------------------------------------------*/
#include "console.h"

COLORREF getColorRef(Color colorIn);

/**********************************************************
 * Initializes the console window for drawing, and returns
 * a handle to a drawing context for the console.
 * Params:
 * width	- width of the console window
 * height	- height of the console window
 * scale	- scale of each pixel
 * @returns HDC	- handle to console's device context
 **********************************************************/
HDC initConsole(int width, int height, int scale)
{
	//Get a handle to console window
	HWND conWindow = GetConsoleWindow();

	//Get handle to console standard output stream
	HANDLE conOut = GetStdHandle(STD_OUTPUT_HANDLE);

	//Get a handle to a device context for drawing on the console
	HDC conDc = GetDC(conWindow);

	// resize the console window
	RECT conDimensions;
	GetWindowRect(conWindow, &conDimensions);
	MoveWindow(conWindow, conDimensions.left, conDimensions.top, width * scale + 34 + (BORDERS.left + BORDERS.right), height * scale + 44 + (BORDERS.top + BORDERS.bottom), true);

	// turn off the blinking cursor
	CONSOLE_CURSOR_INFO cursor;
	cursor.dwSize = 1;
	cursor.bVisible = false;
	SetConsoleCursorInfo(conOut, &cursor);

	return conDc;
}

void drawBorders(HDC hdc, int screenWidth, int screenHeight, int scale, Color borderColor) {
	int top, left, width, height;

	// top border
	top = BORDERS.top - scale;
	left = BORDERS.left - scale;
	width = screenWidth * scale;
	height = 1;
	draw(hdc, left, top, width, height, borderColor);

	// left border
	top = BORDERS.top - scale;
	left = BORDERS.left - scale;
	width = 1;
	height = screenHeight * scale;
	draw(hdc, left, top, width, height, borderColor);

	// right border
	top = BORDERS.top - scale;
	left = screenWidth * scale + BORDERS.left - scale;
	width = 1;
	height = screenHeight * scale;
	draw(hdc, left, top, width, height, borderColor);

	// bottom border
	top = screenHeight * scale + BORDERS.top - scale;
	left = BORDERS.left - scale;
	width = screenWidth * scale;
	height = 1;
	draw(hdc, left, top, width, height, borderColor);

	return;
}


//Get a handle to console window
HWND conWindow = GetConsoleWindow();

/**********************************************************
 * Draw a pixel or block of pixels to the console.
 * @param hdc	- handle to console's device context
 * @param xpos	- x-coordinate of top/left pixel
 * @param ypos	- y-coordinate of top/left pixel
 **********************************************************/
void draw(HDC hdc, int xpos, int ypos, int scale, Color colorCode)
{
	
	COLORREF color = getColorRef(colorCode);

	for (int y = ypos * scale + BORDERS.top; y <= ypos * scale + scale + BORDERS.top; y++) {

		for (int x = xpos * scale + BORDERS.left; x <= xpos * scale + scale + BORDERS.left; x++) {
			SetPixel(hdc, x, y, color);
		}
	}

	return;
} // end draw

void draw(HDC hdc, int xpos, int ypos) {
	draw(hdc, xpos, ypos, 1, White);
}

void draw(HDC hdc, int xpos, int ypos, int scale) {
	draw(hdc, xpos, ypos, scale, White);
}

void draw(HDC hdc, int xpos, int ypos, Color colorCode) {
	draw(hdc, xpos, ypos, 1, colorCode);
}


/**********************************************************
 * Draw a pixel or block of pixels to the console.
 * @param hdc	- handle to console's device context
 * @param xpos	- x-coordinate of top/left pixel
 * @param ypos	- y-coordinate of top/left pixel
 **********************************************************/
void draw(HDC hdc, int xpos, int ypos, int width, int height, Color colorCode) {

	COLORREF color = getColorRef(colorCode);

	for (int y = ypos + BORDERS.top; y <= ypos + height + BORDERS.top; y++) {

		for (int x = xpos + BORDERS.left; x <= xpos + width + BORDERS.left; x++) {
			SetPixel(hdc, x, y, color);
		}
	}

	return;
} // end draw

/**********************************************************
 * Scan the keyboard and return a game related key if entered
 * Parameters:
 * Returns:
 *	int		- a virtual key code
 **********************************************************/
int getGameKeys() {
    int input = VK_NONE;	// return direction to move

	//Get handle to console standard input stream
	HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);

	INPUT_RECORD eventBuff[128];				// event buffer
	unsigned long eventCount, eventsRead;

	// see if there are any events on the standard input stream
	GetNumberOfConsoleInputEvents(hin, &eventCount);

	if (eventCount > 0)
	{
		// read all events availabe into an array buffer
		ReadConsoleInput(
			hin,
			eventBuff,
			128,
			&eventsRead);

		/* see if any of the events read are keyboard events
		   and specifically one of the keys we care about */
		unsigned long i = 0;
		while (input == VK_NONE && i < eventsRead)
		{
			if (eventBuff[i].EventType == KEY_EVENT)
			{
				switch (eventBuff[i].Event.KeyEvent.wVirtualKeyCode)
				{
				// one of the game keys was hit
				case VK_W:		
				case VK_UP:		
				case VK_S:		
				case VK_DOWN:	
				case VK_A:		
				case VK_LEFT:	
				case VK_D:		
				case VK_RIGHT:	
				case VK_X:		
				case VK_ESCAPE:	
					// return the key
					input = eventBuff[i].Event.KeyEvent.wVirtualKeyCode;
					break;

				default:		// some other key was pressed
					input = VK_NONE;
				} //end case statement

			} // end keyboard event type

			i++;
		} // end while events exist

	}

	// get rid of any other input in the stream
	FlushConsoleInputBuffer(hin);

	return input;
}


/**********************************************************
 * Private Functions
 **********************************************************/

/**********************************************************
 * Convert an integer color code to an RGB value
 * Parameters:
 *  colorIn - integer with bytes pattern (00RRGGBB)
 * Returns:
 *  COLORREF - RGB as a Windows color structure
 **********************************************************/
COLORREF getColorRef(Color colorIn) {
	unsigned char red = (colorIn & 0x00FF0000) >> 16;
	unsigned char green = (colorIn & 0x0000FF00) >> 8;
	unsigned char blue = (colorIn & 0x000000FF);
	return RGB(red, green, blue);
}