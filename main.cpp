#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;

void draw_menu(int* current_scr, RenderWindow &window) {
	// Create text
	Font font;
	if (!font.loadFromFile("fonts/pc98.ttf")) {
		cout << "Error loading fonts" << endl;
		exit(1);
	}
	Text logo;
	Text opt1;
	Text opt2;
	Text opt3;
	logo.setFont(font);
	opt1.setFont(font);
	opt2.setFont(font);
	opt3.setFont(font);
	logo.setString("Afraid Of The Shadows");
	opt1.setString("Iniciar");
	opt2.setString("Creditos");
	opt3.setString("Sair");
	logo.setCharacterSize(window.getSize().y * 0.08);
	opt1.setCharacterSize(window.getSize().y * 0.05);
	opt2.setCharacterSize(window.getSize().y * 0.05);
	opt3.setCharacterSize(window.getSize().y * 0.05);
	logo.setPosition(window.getSize().x / 2 - (window.getSize().y * 0.08 * 21) / 2 / 2, window.getSize().y / 2 / 2 - window.getSize().y * 0.08 / 2);
	cout << window.getSize().x * 0.2 << " " << window.getSize().x * 0.6 + 45 * 3 << endl;
	opt1.setPosition(window.getSize().x * 0.02, window.getSize().y * 0.5 + window.getSize().y * 0.08 * 3);
	opt2.setPosition(window.getSize().x * 0.02, window.getSize().y * 0.5 + window.getSize().y * 0.08 * 4);
	opt3.setPosition(window.getSize().x * 0.02, window.getSize().y * 0.5 + window.getSize().y * 0.08 * 5);

	// Menu events
	if (opt1.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
		opt1.setFillColor(Color::Magenta);
		if (Mouse::isButtonPressed(Mouse::Left))
			* current_scr = 1;
	}
	else if (opt2.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
		opt2.setFillColor(Color::Magenta);
		if (Mouse::isButtonPressed(Mouse::Left))
			* current_scr = 2;
	}
	else if (opt3.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
		opt3.setFillColor(Color::Magenta);
		if (Mouse::isButtonPressed(Mouse::Left))
			window.close();
	}

	// Draw
	window.draw(logo);
	window.draw(opt1);
	window.draw(opt2);
	window.draw(opt3);
}

void draw_game(int* current_scr, RenderWindow& window, Event &event) {
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		*current_scr = 0;
	}

	// Draw
}

void draw_credits_gamso(RenderWindow &window) {
	// Create text
	Font font;
	if (!font.loadFromFile("fonts/pc98.ttf")) {
		cout << "Error loading fonts" << endl;
		exit(1);
	}
	Text credits;
	credits.setFont(font);
	credits.setString("Uma produção Lunare Team e");
	credits.setCharacterSize(window.getSize().y*0.05);
	credits.setPosition(window.getSize().x/2-credits.getGlobalBounds().width/2, window.getSize().y*0.02);

	// Create texture
	Texture texture;
	if (!texture.loadFromFile("img/gamso.png")){
		cout << "Error loading texture" << endl;
	}
	texture.setSmooth(false);
	Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(window.getSize().y / sprite.getLocalBounds().width, window.getSize().y / sprite.getLocalBounds().height);
	sprite.setPosition(window.getSize().x/2-sprite.getGlobalBounds().width/2-22, 0);
	
	window.draw(credits);
	window.draw(sprite);
}

void draw_credits(int* current_scr, RenderWindow &window) {
	// Create text
	Font font;
	if (!font.loadFromFile("fonts/pc98.ttf")) {
		cout << "Error loading fonts" << endl;
		exit(1);
	}
	Text voltar;
	voltar.setFont(font);
	voltar.setString("Voltar");
	voltar.setCharacterSize(window.getSize().y * 0.05);
	voltar.setPosition(window.getSize().x*0.02, window.getSize().y*0.5 + window.getSize().y * 0.08 * 5);
	Text credits;
	credits.setFont(font);
	credits.setString("Programador de engine: João Bueno (@rito_jobu)\nDireção: João Bueno (@rito_jobu)\nProgramador de gameplay: Matheus Ramos\nArte e Som: Matheus Ramos\n\nCom a colaboração do grupo GAMSo");
	credits.setCharacterSize(window.getSize().y * 0.05);
	credits.setPosition(window.getSize().x/2-credits.getGlobalBounds().width/2, window.getSize().y/2-credits.getGlobalBounds().height/2);

	// Mouse events
	if (voltar.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
		voltar.setFillColor(Color::Magenta);
		if (Mouse::isButtonPressed(Mouse::Left))
			* current_scr = 0;
	}

	// Draw
	window.draw(voltar);
	window.draw(credits);
}

void draw_scr(int* current_scr, RenderWindow &window, Event &event) {
	/*
	 *  0 - Menu
	 *  1 - Game
	 */

	switch (*current_scr) {
	case 0:
		draw_menu(current_scr, window);
		break;
	case 1:
		draw_game(current_scr, window, event);
		break;
	case 2:
		draw_credits(current_scr, window);
		break;
	default:
		break;
	}
}

int main(void) {
	int current_scr[1] = { 0 };

	// Initialize clock
	Clock clock;

	// Initialize window
	RenderWindow window(VideoMode::getDesktopMode(), "Afraid Of The Shadows", Style::Fullscreen);
	window.setFramerateLimit(60);

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)){
			if (event.type == Event::Closed)
				window.close();
		}

		Time time;
		time = clock.getElapsedTime();

		window.clear();
		if (time.asSeconds() <= 10)
			draw_credits_gamso(window);
		else
			draw_scr(current_scr, window, event);
		window.display();
	}

	return 0;
}