#include "menu.h"

Menu::
Menu(Image * images_, int number_of_images)
{
	err = { NO_ERROR, "No error." };
	event = { NONE, KEY_NONE };
	if (!(al_init()))
	{
		err.errorNum = AL_INIT_ERROR;
		err.detail = "Error al iniciar Allegro!";
	}
	if (!al_init_image_addon())
	{
		err.errorNum = AL_ADDON_ERROR;
		err.detail = "Error al iniciar el Image Addon de Allegro!";
	}
	if (!al_init_font_addon())
	{
		err.errorNum = AL_ADDON_ERROR;
		err.detail = "Error al iniciar el Font Addon de Allegro!";
	}
	if (!al_init_primitives_addon())
	{
		err.errorNum = AL_ADDON_ERROR;
		err.detail = "Error al iniciar el Primitives Addon de Allegro!";
	}
	display = al_create_display(WIDTH, HEIGHT);
	if (display == NULL)
	{
		err.errorNum = AL_DISPLAY_ERROR;
		err.detail = "Error al iniciar el Display!";
	}
	if (!al_install_keyboard())
	{
		err.errorNum = AL_KEYBOARD_ERROR;
		err.detail = (stderr, "failed to initialize the keyboard!\n");
	}
	alEventQueue = al_create_event_queue();
	if (!alEventQueue)
	{
		err.errorNum = AL_QUEUE_ERROR;
		err.detail = (stderr, "failed to create event_queue!\n");
	}

	imageCount = number_of_images;
	currImg = 0;
	page = 0;
	maxPage = ceil((imageCount / ((double) MAX_MENU_IMG)));
	for (int i = 0; i < imageCount; i++)
	{
		myImages[i].img = &images_[i];
	}
}

Menu::
~Menu()
{
	for (int i = 0; i < imageCount; i++)
	{
		al_destroy_bitmap(myImages[i].bmp);
	}
	al_uninstall_keyboard();
	al_destroy_display(display);
	al_destroy_event_queue(alEventQueue);
	al_shutdown_image_addon();
	al_shutdown_font_addon();
	al_shutdown_primitives_addon();
}

bool Menu::
openImages()
{
	for (int i = 0; i < imageCount; i++)
	{
		myImages[i].bmp = al_load_bitmap(myImages[i].img->getFilename);
	}
}

void Menu::
selectImage(data_t key)
{
	if (key == KEY_A)
	{
		int end = currImg + MAX_MENU_IMG;
		while (currImg < end)
		{
			if (!(onScreenImages[currImg - page * MAX_MENU_IMG]->img->isSelected()))
			{
				onScreenImages[currImg - page * MAX_MENU_IMG]->img->toggleSelect();
			}
		}
	}
	else if (key == KEY_N)
	{
		int end = currImg + MAX_MENU_IMG;
		while (currImg < end)
		{
			if ((onScreenImages[currImg - page * MAX_MENU_IMG]->img->isSelected()))
			{
				onScreenImages[currImg - page * MAX_MENU_IMG]->img->toggleSelect();
			}
		}
	}
	else
	{
		onScreenImages[key]->img->toggleSelect();
	}
}

void Menu::
changePage(data_t key)
{
	if (key == KEY_LEFT)
	{
		if (page > 0)
		{
			page--;
		}
	}
	else if (key == KEY_RIGHT)
	{
		if (page < maxPage)
		{
			page++;
		}
	}
	updateOnScreenImages();
}

void Menu::
updateOnScreenImages()
{
	for (int i = currImg; i < (currImg + MAX_MENU_IMG); i++)
	{
		onScreenImages[(i - currImg)] = &myImages[i];
	}
}

void Menu::
updateMenu()
{
	double pos[] = { 0.0, 0.0 };
	pos[0] += (COL_SIZE / 2.0) + MARGIN; //me paro en el centro(en cuanto a x) de la primera 'columna'
	pos[1] += (IMG_SIZE / 2.0) + MARGIN;

	al_clear_to_color(al_map_rgb(255, 255, 255));

	while (currImg < MAX_MENU_IMG || currImg < imageCount)
	{
		for (int i = 0; i < (MAX_MENU_IMG / 3); i++)
		{
			for (int j = 0; j < (MAX_MENU_IMG / 3); j++)
			{
				//Marcador de imagenes seleccionadas(se hace un contorno amarillo de la imagen):
				/*
				if(onScreenImages[(currImg - (page*MAX_MENU_IMG))]->isSelected())
				{
					al_draw_filled_rectangle((pos[0] - (IMG_SIZE/2.0) - (MARGIN / 5.0)),
											(pos[1] - (IMG_SIZE/2.0) - (MARGIN / 5.0)),
											(pos[0] + (IMG_SIZE/2.0) + (MARGIN / 5.0)),
											(pos[1] - (IMG_SIZE/2.0) + (MARGIN / 5.0)),
											al_map_rgb(255,255,0));
				}
				*/
				al_draw_filled_rectangle((pos[0] - (IMG_SIZE / 2.0)),
					(pos[1] - (IMG_SIZE / 2.0)),
					(pos[0] + (IMG_SIZE / 2.0)),
					(pos[1] - (IMG_SIZE / 2.0)),
					al_map_rgb(255, 0, 0));
				//cambiar por:
				/* al_draw_scaled_bitmap(myImages[currImg].bmp,
										0, 0,
										get_bitmap_width(bmps[currImg]), get_bitmap_height(bmps[currImg]),
										(pos[0] - (IMG_SIZE/2.0)), (pos[1] - (IMG_SIZE/2.0)),
										IMG_SIZE, IMG_SIZE, 0);
				*/
				currImg++;
				pos[1] += (IMG_SIZE + MARGIN);
			}
			pos[0] += ((((COL_SIZE / 2.0) + MARGIN) * 2.0) + (COL_SIZE / 2.0) + (MARGIN / 2.0));
		}
	}
}

event_t Menu::
getKeyboardEvent()
{
	event_t answerEvent = { NONE, KEY_NONE };

	if (alEvent.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		answerEvent.eventType = KEY_DOWN;

		switch (alEvent.keyboard.keycode)
		{
		case ALLEGRO_KEY_UP:
		{
			answerEvent.eventData = KEY_UP;
			break;
		}

		case ALLEGRO_KEY_RIGHT:
		{
			answerEvent.eventData = KEY_RIGHT;
			break;
		}

		case ALLEGRO_KEY_LEFT:
		{
			answerEvent.eventData = KEY_LEFT;
			break;
		}

		case ALLEGRO_KEY_N:
		{
			answerEvent.eventData = KEY_N;
			break;
		}

		case ALLEGRO_KEY_A:
		{
			answerEvent.eventData = KEY_A;
			break;
		}
		case ALLEGRO_KEY_ENTER:
		{
			answerEvent.eventData = KEY_ENTER;
			break;
		}
		case ALLEGRO_KEY_1: case ALLEGRO_KEY_PAD_1:
		{
			answerEvent.eventData = KEY_1;
			break;
		}
		case ALLEGRO_KEY_2: case ALLEGRO_KEY_PAD_2:
		{
			answerEvent.eventData = KEY_2;
			break;
		}
		case ALLEGRO_KEY_3: case ALLEGRO_KEY_PAD_3:
		{
			answerEvent.eventData = KEY_3;
			break;
		}
		case ALLEGRO_KEY_4: case ALLEGRO_KEY_PAD_4:
		{
			answerEvent.eventData = KEY_2;
			break;
		}
		case ALLEGRO_KEY_5: case ALLEGRO_KEY_PAD_5:
		{
			answerEvent.eventData = KEY_5;
			break;
		}
		case ALLEGRO_KEY_6: case ALLEGRO_KEY_PAD_6:
		{
			answerEvent.eventData = KEY_6;
			break;
		}
		case ALLEGRO_KEY_7: case ALLEGRO_KEY_PAD_7:
		{
			answerEvent.eventData = KEY_7;
			break;
		}
		case ALLEGRO_KEY_8: case ALLEGRO_KEY_PAD_8:
		{
			answerEvent.eventData = KEY_8;
			break;
		}
		case ALLEGRO_KEY_9: case ALLEGRO_KEY_PAD_9:
		{
			answerEvent.eventData = KEY_9;
			break;
		}
		case ALLEGRO_KEY_ESCAPE:
		{
			answerEvent.eventData = KEY_ESC;
			exit = true;
			break;
		}
		default:
		{
			answerEvent.eventData = KEY_NONE;
		}
		}
	}
	/*else if (alEvent.eventType == ALLEGRO_EVENT_KEY_UP)
	{
		answerEvent.eventType = EVENT_KEY_UP;

		switch (alEvent.keyboard.keycode)
		{
			case ALLEGRO_KEY_UP:
			{
				answerEvent.eventData = EVENT_DATA_KEY_UP;
				break;
			}

			case ALLEGRO_KEY_RIGHT:
			{
				answerEvent.eventData = RIGHT;
				break;
			}

			case ALLEGRO_KEY_LEFT:
			{
				answerEvent.eventData = KEY_LEFT;
				break;
			}

			case ALLEGRO_KEY_N:
			{
				answerEvent.eventData = KEY_N;
				break;
			}

			case ALLEGRO_KEY_A:
			{
				answerEvent.eventData = KEY_A;
				break;
			}
			case ALLEGRO_KEY_ESCAPE:
			{
				answerEvent.eventData = KEY_ESC;
				exit = true;
				break;
			}
			default:
			{
				answerEvent.eventData = KEY_NONE;
			}
		}
	}*/
	else if (alEvent.keyboard.keycode == ALLEGRO_EVENT_DISPLAY_CLOSE)
	{
		exit = true;
	}

	return answerEvent;
}

bool Menu::
getExitStatus()
{
	return exit;
}

void Menu::
printError()
{
	if (err.errorNum != NO_ERROR)
	{
		std::cout << err.detail << std::endl;
	}
}