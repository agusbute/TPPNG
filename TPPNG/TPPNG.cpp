#include "stdafx.h"
#include "Image.h"
#include "menu.h"

int main()
{
	int num_of_images;
	Image * images = new Image[num_of_images];
	Menu menu(images, num_of_images);
	menu.openImages();
	while (!(menu.getExitStatus))
	{
		event_t event = menu.getKeyboardEvent();
		if (event.eventType == KEY_DOWN)
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
				menu.execute();
			}
			case KEY_UP:
			{
				menu.execute();
			}
			default:
			{
				menu.selectImage(event.eventData);
			}
			break;
			}
			menu.updateMenu();
		}
	}

	delete[] images;
}
