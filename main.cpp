#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

void draw_menu(int* current_scr, RenderWindow &window) {
	// Create font
	Font font;
	if (!font.loadFromFile("fonts/pc98.ttf")) {
		cout << "Error loading fonts" << endl;
		exit(1);
	}
	Text logo;
	logo.setFont(font);
	logo.setString("Afraid Of The Shadows");
	logo.setCharacterSize(24);
	logo.setPosition(1024 / 2 - (24 * 21) / 2 / 2, 576 / 2 / 2 - 24 / 2);

	window.clear();
	window.draw(logo);
}

void draw_game(int* current_scr, RenderWindow& window) {

}

void draw_scr(int* current_scr, RenderWindow &window) {
	/*
	 *  0 - Menu
	 *  1 - Game
	 */

	switch (*current_scr) {
	case 0:
		draw_menu(current_scr, window);
		break;
	case 1:
		draw_game(current_scr, window);
		break;
	default:
		break;
	}
}

int main(void) {
	int current_scr[1] = { 0 };

	// Initialize window
	RenderWindow window(VideoMode(1024, 576), "Afraid Of The Shadows", Style::Resize | Style::Close);
	window.setFramerateLimit(60);

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		draw_scr(current_scr, window);
		window.display();
	}

	return 0;
}