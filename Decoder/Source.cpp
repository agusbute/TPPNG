#include "stdafx.h"
#include "Image.h"
#include "menu.h"
#include "Decoder.h"
#include "parselib.h"
#include "callback.h"
#include "filesystem_header.h"

int main(int argc, char ** argv)
{
	argument_t a = { NULL };
	argument_t *pUserData = &a;
	if (argc == ARGUMENTOS + 1)
	{
		if (parseCmdLine(argc, argv, parseCallback, pUserData) == 1)
		{

			string filenames[30];
			int num_of_images = see_dirContent(a.path, filenames);
			if (num_of_images > 0)
			{
				Image * images = new Image[num_of_images];
				for (int i = 0; i < num_of_images; i++)
				{
					images[i] = filenames[i].c_str();
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
							menu.decodeImage(image_encoder);
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
}

