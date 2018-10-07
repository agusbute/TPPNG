#pragma once
#include "stdafx.h"
#include "Image.h"
#include "Encode.h"

#define HEIGHT 600
#define WIDTH 1000

#define MARGIN 50

#define COL_SIZE ((2.0 / 3.0) * ((WIDTH / 2.0) - (2.0* MARGIN))) 
#define IMG_SIZE (((HEIGHT - MARGIN * 2.0) - MARGIN * 2.0) / 3.0)

#define MAX_MENU_IMG 9

using namespace std;

typedef enum { NO_ERR, NO_MEM, AL_INIT_ERROR, AL_DISPLAY_ERROR, AL_ADDON_ERROR, AL_IMAGE_ERROR, AL_FONT_ERROR, AL_KEYBOARD_ERROR, AL_QUEUE_ERROR } errNo_t;

typedef struct
{
	errNo_t errorNum;
	string detail;
}errorType_t;

typedef enum { NONE, KEY_DOWN, EV_KEY_UP, EV_FUNC_END }evType_t;
typedef enum { KEY_1 = 0, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_NONE, KEY_LEFT, KEY_RIGHT, KEY_A, KEY_N, KEY_ESC, FUNC_END, KEY_ENTER, KEY_UP}data_t;

typedef struct
{
	evType_t eventType;
	data_t eventData;
}event_t;

typedef struct
{
	Image * img;
	ALLEGRO_BITMAP * bmp;
}myImage;

class Menu
{
public:

	Menu(Image * images_, int number_of_images);
	~Menu();
	void execute();
	void openImages();
	void updateMenu();
	void selectImage(data_t key);
	void changePage(data_t key);

	void printError();
	bool getExitStatus();
	event_t getKeyboardEvent();

private:

	void updateOnScreenImages();
	bool codeImage(void* coder(Image * img));
	myImage * myImages;

	myImage * onScreenImages[MAX_MENU_IMG];

	int imageCount;
	int currImg;
	int page;
	int maxPage;
	errorType_t err;
	ALLEGRO_DISPLAY * display;
	ALLEGRO_EVENT alEvent;
	ALLEGRO_EVENT_QUEUE * alEventQueue;
	string * finames;
	bool exit;

};