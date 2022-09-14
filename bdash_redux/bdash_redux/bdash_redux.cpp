#include <iostream>
#include "Game.h"
#include "Thing.h"
#include "Character.h"

int main()
{
	{
		al_init();
		al_init_image_addon();

		ALLEGRO_DISPLAY* display;
		ALLEGRO_EVENT_QUEUE* queue;
		ALLEGRO_TIMER* eventTimer;
		ALLEGRO_TIMER* growTimer;
		ALLEGRO_KEYBOARD_STATE key;
		std::string level = "level_1.txt";

		Character playerCharacter;
		Game map(playerCharacter, level);

		display = al_create_display(1280, 708);
		queue = al_create_event_queue();
		eventTimer = al_create_timer(10.0 / 60);
		growTimer = al_create_timer(60.0 / 60);

		map.draw();
		playerCharacter.draw();

		bool gameOver = false;
		int blockedAmo = 0;

		al_start_timer(growTimer);
		al_start_timer(eventTimer);
		al_install_keyboard();
		al_register_event_source(queue, al_get_keyboard_event_source());
		al_register_event_source(queue, al_get_display_event_source(display));
		al_register_event_source(queue, al_get_timer_event_source(eventTimer));
		al_register_event_source(queue, al_get_timer_event_source(growTimer));

		while (!gameOver)
		{

			ALLEGRO_EVENT event;
			al_wait_for_event(queue, &event);

			if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
				gameOver = true;
			if (event.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				al_get_keyboard_state(&key);
				map.move(key, &playerCharacter);
			}
			if (event.type == ALLEGRO_EVENT_TIMER)
			{
				if (event.timer.source == eventTimer)
				{
					map.itemFall();
					map.showDoor();
					map.checkGrow(blockedAmo);
				}
				if (event.timer.source == growTimer)
					blockedAmo = map.amoebaGrow();
			}
			if (map.nextLevel(level) == true)
			{
				al_stop_timer(eventTimer);
				al_stop_timer(growTimer);
				if (map.getLevel() > 2)
					gameOver = true;
				else
				{
					Game newLevel(playerCharacter, level);
					map = newLevel;
					map.draw();
					playerCharacter.draw();
				}
				al_start_timer(growTimer);
				al_start_timer(eventTimer);
			}
		}
		al_destroy_display(display);
		al_uninstall_keyboard();
	}

	_CrtDumpMemoryLeaks();
	return 0;
}