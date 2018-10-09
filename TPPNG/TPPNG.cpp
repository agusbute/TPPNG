#include "stdafx.h"
#include "Image.h"
#include "Menu.h"
#include "Encode.h"
#include "parselib.h"
#include "callback.h"
#include "filesystem_header.h"


int main(int argc, char ** argv)
{
	argument_t a = { NULL, 0 };
	argument_t *pUserData = &a;
	if (argc == ARGUMENTOS +1)
	{
		if (parseCmdLine(argc, argv, parseCallback, pUserData) == 1)
		{

			const char * filenames[30];
			for (int i = 0; i < 30; i++)
			{
				filenames[i] = NULL;
			}
			int threshold = a.threshold;
			int num_of_images = see_dirContent(a.path, filenames);
			Image * images = new Image[num_of_images];
			for (int i = 0; i < 30; i++)
			{
				images[i] = filenames[i];
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
						menu.updateMenu();
					}
					break;
					case KEY_ENTER:
					{
						menu.encodeImage(Encode, threshold);
						menu.printError();
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

		else
		{
			printf("Error de parametros\n");
			how_to_use();
			return 0; 
		}
	}
	else
	{
		printf("Error de parametros\n");
		how_to_use();
		return 0;
	}
}
