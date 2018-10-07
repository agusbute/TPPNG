#include "stdafx.h"
#include "menu.h"

Menu::
Menu(Image * images_, int number_of_images)
{
	myEvent = { NONE, KEY_NONE };
	err = { NO_ERR, "No error." };
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
	if (!al_init_ttf_addon())
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
	font = al_load_ttf_font("Files/ARCADE_N.ttf", 10, 0);
	if (font == NULL)
	{
		err.errorNum = AL_FONT_ERROR;
		err.detail = "Error al iniciar el Font!";
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
	al_register_event_source(alEventQueue, al_get_keyboard_event_source());
	al_register_event_source(alEventQueue, al_get_display_event_source(display));

	imageCount = number_of_images;
	currImg = 0;
	page = 0;
	maxPage = ceil((imageCount / ((double) MAX_MENU_IMG)))-1;
	myImages = (myImage *) malloc(imageCount * sizeof(myImages));
	for (int i = 0; i < imageCount; i++)
	{
		myImages[i].img = images_ + i;
	}
}

Menu::
~Menu()
{
	for (int i = 0; i < imageCount; i++)
	{
		al_destroy_bitmap(myImages[i].bmp);
	}
	free(myImages);
	al_uninstall_keyboard();
	al_destroy_display(display);
	al_destroy_event_queue(alEventQueue);
	al_shutdown_image_addon();
	al_shutdown_font_addon();
	al_shutdown_ttf_addon();
	al_shutdown_primitives_addon();
}

void Menu::
openImages()
{
	for (int i = 0; i < imageCount; i++)
	{
		myImages[i].bmp = al_load_bitmap(myImages[i].img->getFilename().c_str());
		if (myImages[i].bmp == NULL)
		{
			myImages[i].bmp = al_load_bitmap("Files/default.jpg");
		}
	}
	updateOnScreenImages();
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
			currImg++;
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
			currImg++;
		}
	}
	else if(key != KEY_ESC && key != KEY_ENTER && key != KEY_LEFT && key != KEY_RIGHT && key != KEY_NONE && key != KEY_UP)
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
	al_clear_to_color(al_map_rgb(255, 255, 255));
	if (myEvent.eventType == EV_FUNC_BEGIN)
	{

	}
	else if (myEvent.eventType == EV_FUNC_END)
	{

	}
	else
	{
		double x, y;
		x = (COL_SIZE / 2.0) + MARGIN;
		//Hago que currImg apunte al primer elemento del display
		if (currImg % MAX_MENU_IMG == 0 && currImg != 0)//caso que estaba apuntando al ultimo elemento
		{
			currImg -= MAX_MENU_IMG;
		}
		else
		{
			while (!(currImg % MAX_MENU_IMG == 0))//cualquier otro elemento
			{
				currImg--;
			}
		}
		int buff = currImg;
		while (currImg < buff + MAX_MENU_IMG || currImg < imageCount)
		{
			for (int i = 0; i < (MAX_MENU_IMG / 3) && !(currImg < buff + MAX_MENU_IMG); i++)
			{
				y = (IMG_SIZE / 2.0) + MARGIN/2.0;
				for (int j = 0; j < (MAX_MENU_IMG / 3) && !(currImg < buff + MAX_MENU_IMG); j++)
				{
					//Marcador de imagenes seleccionadas(se hace un contorno amarillo de la imagen):
					
					if(onScreenImages[(currImg - (page*MAX_MENU_IMG))]->img->isSelected())
					{
						al_draw_filled_rectangle((x - (IMG_SIZE/2.0) - (MARGIN / 5.0)),
												(y - (IMG_SIZE/2.0) - (MARGIN / 5.0)),
												(x + (IMG_SIZE/2.0) + (MARGIN / 5.0)),
												(y + (IMG_SIZE/2.0) + (MARGIN / 5.0)),
												al_map_rgb(255,255,0));
					}
					
					 al_draw_scaled_bitmap(myImages[currImg].bmp,
											0, 0,
											al_get_bitmap_width(myImages[currImg].bmp), al_get_bitmap_height(myImages[currImg].bmp),
											(x - (IMG_SIZE/2.0)), (y - (IMG_SIZE/2.0)),
											IMG_SIZE, IMG_SIZE, 0);
					 al_draw_text(font, al_map_rgb(0, 0, 0), x, y + IMG_SIZE / 2.0 + MARGIN / 2.0, ALLEGRO_ALIGN_CENTRE, myImages[currImg].img->getFilename().c_str());
					
					currImg++;
					y += (IMG_SIZE + MARGIN);
					al_flip_display();
				}
				x += (COL_SIZE + MARGIN);
			}
		}
	}
	al_flip_display();
}

event_t Menu::
getKeyboardEvent()
{
	event_t answerEvent = { NONE, KEY_NONE };
	if (al_get_next_event(alEventQueue, &alEvent))
	{

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
		else if (alEvent.type == ALLEGRO_EVENT_KEY_UP)
		{
			answerEvent.eventType = EV_KEY_UP;

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
		else if (alEvent.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			exit = true;
		}
	}
	return answerEvent;
}

bool Menu::
getExitStatus()
{
	return exit;
}

void Menu::
execute()
{
	
}

bool Menu::
codeImage(void* coder(Image * img))
{
	return true;
}

void Menu::
printError()
{
	cout << err.detail.c_str() << endl;
	if (err.errorNum != NO_ERR)
	{
		exit = 1;
	}
}