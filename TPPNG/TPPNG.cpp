#include "stdafx.h"
#include "Image.h"
#include "Menu.h"
#include "Encode.h"
#include "parselib.h"
#include "callback.h"

int main(int argc, char ** argv)
{
	argument_t a = { NULL, 0 };
	argument_t *pUserData = &a;
	if (argc == ARGUMENTOS +1)
	{
		if (parseCmdLine(argc, argv, parseCallback, pUserData) == 1)
		{

			int threshold = atoi(argv[4]);
			int num_of_images = 2;
			Image * images = new Image[num_of_images];
			int u = 0;
			//agragar boost::filesystem, guardar cada imagen ahi
			images[0] = "Files/test.png";
			images[1] = "Files/cuadrados.png";
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
