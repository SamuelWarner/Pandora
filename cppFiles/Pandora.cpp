﻿// Pandora.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "pch.h"
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include <time.h>
#include <allegro5/allegro_primitives.h>
#include "LevelManager.h"
#include <typeinfo>
#include "global.h"
#include "ControlSystem.h"

int main()
{
	ALLEGRO_DISPLAY *display;               //Main display for the game
	ALLEGRO_EVENT event;                    //generic event object for checking events
	const float MAXFRAMERATE = 60.0f;       //Game will not play faster then this framerate
	
	

	//initialize Allegro, and install general purpose modules
	al_init();
	al_install_keyboard();
	al_install_mouse();
	display = al_create_display(640, 480);

	bool gameRunning = true;

	while (true) {
		//create display, queue, and timer instances for use in game loop
		ALLEGRO_TIMER *frameTimer;            //Timer for frame rate timing
		ALLEGRO_EVENT_QUEUE *eventQue;        //general event que

		/*  Main Game LOOP */
		if (!gameRunning) break;
		
		//Startup
		eventQue = al_create_event_queue();
		frameTimer = al_create_timer(1.0 / MAXFRAMERATE);
		assert(frameTimer != NULL);
		al_register_event_source(eventQue, al_get_timer_event_source(frameTimer));
		al_register_event_source(eventQue, al_get_display_event_source(display));
		al_register_event_source(eventQue, al_get_keyboard_event_source());

		// Load game entities
		al_init_image_addon();

		LevelManager *lvlManager = new LevelManager();
		lvlManager->loadLevel(1);

		//setup the game loop variables and start frame timer
			//time stuff
		al_start_timer(frameTimer);
		std::vector<GameEntity*> &objects = lvlManager->allEntities;
		bool renderFrame = false;
		//start game loop
		while (gameRunning) {
			//1. TIMESTEP

			al_wait_for_event(eventQue, &event);
			if (event.type == ALLEGRO_EVENT_TIMER) {
				renderFrame = true;
			}
			else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				gameRunning = false;
			}

			//2. INPUT
			//update key states with events
			else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
				global::keys[event.keyboard.keycode] = 1;
			}
			else if (event.type == ALLEGRO_EVENT_KEY_UP) {
				global::keys[event.keyboard.keycode] = 0;
			}
			if (renderFrame && al_is_event_queue_empty(eventQue)) {
				//3. NETWORKING
				//Collect network messages and data

				//4. SIMULATION
				//Simulate AI and player actions, determine new velocities and states of game entities
				lvlManager->ctrlSys->update();

				
				for (size_t i = 0, lenght = lvlManager->allEntities.size(); i < lenght; ++i) {
					Component* c = lvlManager->allEntities[i]->getComponent("Position");
					if (c != nullptr) {
						c->update();
					}
				}

				//5. COLLISION
				//Find collisions between game entities and resolve them
				lvlManager->collisionSys->update();

				//6. OBJECT UPDATES
				//Update entities with final positions and animations
				

				//7. RENDERING
				//Render the game world to the frame buffer and display for the user
				al_clear_to_color(COLOR_BLACK);

				lvlManager->renderSys->update();
				al_flip_display();

				//8. OTHER
				lvlManager->lifeSys->update();
				renderFrame = false;
			}
		}

		//Shutdown Gameloop
		al_shutdown_image_addon();
		al_destroy_event_queue(eventQue);
		al_destroy_timer(frameTimer);

		if (gameRunning) continue;
		else break;
	}
	
	//Shutdown Mainloop
	al_uninstall_mouse();
	al_uninstall_keyboard();
}
