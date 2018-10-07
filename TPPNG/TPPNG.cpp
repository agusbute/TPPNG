#include "stdafx.h"
#include "Image.h"
#include "menu.h"

int main()
{
	int num_of_images = 14;
	Image * images = new Image[num_of_images];
	int u = 0;
	while (u < num_of_images)
	{
		images[u] = "Files/default.jpg";
		u++;
	}
	Menu menu(images, num_of_images);
	menu.printError();
	menu.openImages();
	menu.updateMenu();
	while (!(menu.getExitStatus()))
	{
		event_t event = menu.getKeyboardEvent();
		Sleep(50);
		if (event.eventType == KEY_DOWN || event.eventType == EV_KEY_UP)
		{
			switch (event.eventData)
			{
				case KEY_RIGHT:
				case KEY_LEFT:
				{
					menu.changePage(event.eventData);
				}
				break;
				case KEY_ENTER:
				{
					//menu.execute();
				}
				break;
				case KEY_UP: case KEY_ESC:
				{

				}
				break;
				default:
				{
					menu.selectImage(event.eventData);
					menu.updateMenu();
				}
				break;
			}		
		}
		event = { NONE, KEY_NONE };
	}
	return 1;
}
