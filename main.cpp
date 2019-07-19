#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;
typedef struct {
	float x, y, ang,wx,tx;
	int frames, line, dir, jump,ltrn, door[5];
	Clock cut;
}shadow;

void init_main(shadow* main) {
	main->x = 0;
	main->y = 66 * 5;
	main->line = 1;
	main->dir = 1;
	main->frames = 4;
	main->jump = 0;
	main->ltrn = 0;
	main->ang = 0;
	main->door[0] = 0;
	main->door[1] = 0;
	main->door[2] = 0;
	main->door[3] = 0;
	main->door[4] = 0;

}
int cutscene(Clock clock,IntRect* rectSourceSprite, Sprite* sprite, int size, int frames, int line ,int fps) {
	if (((int)(clock.getElapsedTime().asMilliseconds() / (1000.0 / fps))) % (int)size < frames) {
		(*rectSourceSprite).left = ((int)(clock.getElapsedTime().asMilliseconds() / (1000.0 / fps))) % (int) size;
		(*rectSourceSprite).top = line * size;
		(*sprite).setTextureRect(*rectSourceSprite);
		return 0;
	}
	
	return 1;


}


void animate(Clock clock, IntRect* rectSourceSprite, Sprite* sprite, int size, int frames, int line, int fps) {

	(*rectSourceSprite).left = ((int)(clock.getElapsedTime().asMilliseconds() / (1000.0 / fps))) % (int)frames * size ;
	(*rectSourceSprite).top = line * size;
	(*sprite).setTextureRect(*rectSourceSprite);

}


void write(int n, RenderWindow* window,float size, Color c,float x, float y) {
	Font font;
	if (!font.loadFromFile("fonts/pc98.ttf")) {
		cout << "Error loading fonts" << endl;
		exit(1);
	}
	Text texto;
	texto.setFont(font);
	texto.setFillColor(c);
	texto.setPosition((*window).getSize().x /800*x, (*window).getSize().y /600*y);
	texto.setCharacterSize((*window).getSize().y * size);
	switch (n)
	{
	case 0:
		texto.setString("pao");
		break;
	case 1:
		texto.setString("de");
		break;
	default:
		texto.setString(" ");
	}

	(*window).draw(texto);
}


void draw_menu(int* current_scr, RenderWindow *window) {
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
	logo.setCharacterSize((*window).getSize().y * 0.08);
	opt1.setCharacterSize((*window).getSize().y * 0.05);
	opt2.setCharacterSize((*window).getSize().y * 0.05);
	opt3.setCharacterSize((*window).getSize().y * 0.05);
	logo.setPosition((*window).getSize().x / 2 - ((*window).getSize().y * 0.08 * 21) / 2 / 2, (*window).getSize().y / 2 / 2 - (*window).getSize().y * 0.08 / 2);
	opt1.setPosition((*window).getSize().x * 0.02, (*window).getSize().y * 0.5 + (*window).getSize().y * 0.08 * 3);
	opt2.setPosition((*window).getSize().x * 0.02, (*window).getSize().y * 0.5 + (*window).getSize().y * 0.08 * 4);
	opt3.setPosition((*window).getSize().x * 0.02, (*window).getSize().y * 0.5 + (*window).getSize().y * 0.08 * 5);

	// Menu events
	if (opt1.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)) {
		opt1.setFillColor(Color::Magenta);
		if (Mouse::isButtonPressed(Mouse::Left))
			* current_scr = 1;
	}
	else if (opt2.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)) {
		opt2.setFillColor(Color::Magenta);
		if (Mouse::isButtonPressed(Mouse::Left))
			* current_scr = 2;
	}
	else if (opt3.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)) {
		opt3.setFillColor(Color::Magenta);
		if (Mouse::isButtonPressed(Mouse::Left))
			(*window).close();
	}

	// Draw
	(*window).draw(logo);
	(*window).draw(opt1);
	(*window).draw(opt2);
	(*window).draw(opt3);
}

void draw_game(Texture* textures, double delta, Clock clock, shadow* main, int* room, int* current_scr, RenderWindow* window, Event& event) {
	int h;
	
	IntRect rectMc(0, 0, 160, 160),rectArm(0,0,160,160), rectl(0, 0, 480, 160);
	Sprite mc(textures[0], rectMc),arm(textures[1], rectArm), l(textures[2], rectl);
	sf::Texture rooml;
	Sprite rom;
	arm.setOrigin(18 * 5, 14 * 5);
	l.setOrigin(12*5, 12 * 5);
	switch (*room) 
	{
	case 0:
		
		main->tx = 800;
		if (Keyboard::isKeyPressed(Keyboard::Return) && main->x > 700) {
			main->x = 42 * 5;
			*room = 1;
		}
		break;
	case 1:
		

		if (Keyboard::isKeyPressed(Keyboard::Return) && main->x < 40*5) {
			main->x = 650;
			*room = 0;
		}
		//doors
		if (main->door[4])
			main->tx = 1080 * 5;
		else if (main->door[3])
			main->tx = 1030 * 5;
		else if (main->door[2])
			main->tx = 980 * 5;
		else if (main->door[1])
			main->tx = 750 * 5;
		else
			main->tx = 550 * 5;

		break;

	}
	//switch()
	rom.setTexture(textures[3+*room]);
	rom.setScale((*window).getSize().x / 800.0, (*window).getSize().y / 600.0);
	
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		*current_scr = 0;
	}
	else if (Keyboard::isKeyPressed(Keyboard::A) && main->wx>8*5 ) {

	
		main->line = 1;
		main->dir = -1;
		main->x = main->x -5 / delta;
		main->ang = abs(main->ang);
	}
	else if (Keyboard::isKeyPressed(Keyboard::D) && main->wx < main->tx-15*5 ) {
		main->line = 1;
		main->dir = 1;
		main->x = main->x +5 / delta;
		main->ang = -abs(main->ang);
	}
	else {
		main->line = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		main->line = 2;

	}
	//move arm
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (main->wx * (*window).getSize().x / 800.0 > sf::Mouse::getPosition().x - 30 * 2.5) {
			main->dir = -1;
			if (atan(((main->y + 25 * 5) * (*window).getSize().y / 600.0 - sf::Mouse::getPosition().y) / ((main->wx + 9 * 5) * (*window).getSize().x / 800.0 - sf::Mouse::getPosition().x)) / 3.1415 * 180 > -18)
				main->ang = atan(((main->y + 25 * 5) * (*window).getSize().y / 600.0 - sf::Mouse::getPosition().y) / ((main->wx + 10 * 5) * (*window).getSize().x / 800.0 - sf::Mouse::getPosition().x)) / 3.1415 * 180;

		}
		else  {
			main->dir = 1;
			if (atan(((main->y + 25 * 5) * (*window).getSize().y / 600.0 - sf::Mouse::getPosition().y) / ((main->wx + 9 * 5) * (*window).getSize().x / 800.0 - sf::Mouse::getPosition().x)) / 3.1415 * 180<18)
				main->ang = atan(((main->y + 25 * 5) * (*window).getSize().y / 600.0 - sf::Mouse::getPosition().y) / ((main->wx + 9 * 5) * (*window).getSize().x / 800.0 - sf::Mouse::getPosition().x)) / 3.1415 * 180;


		}
		main->ltrn = 1;
	}
	else
		main->ltrn = 0;

	//flip
	if (main->dir == -1) {
		mc.scale(-1, 1);
		arm.scale(-1, 1);
		l.scale(-1, 1);

	}
	//move all
	if (main->x < 400)
		main->wx = main->x;
	else if (main->x > main->tx - 400)
		main->wx = main->x-main->tx+800;
	else
		main->wx = 400;


	//set parameters
	l.setColor(sf::Color(255, 255, 255, 50));
	rom.setPosition(main->wx-main->x, 0);
	l.setRotation(main->ang);
	l.setPosition((main->wx + ((main->dir + 1) / 2 - 1) * 10 - 32 * 2 + 17 * 5)* ((*window).getSize().x) / 800.0, (main->y + 13 * 5) * ((*window).getSize().y) / 600.0);	arm.setRotation(main->ang);
	arm.setPosition((main->wx + ((main->dir + 1) / 2 -1 ) *10 - 32 * 2+17*5) * ((*window).getSize().x) / 800.0, (main->y +13*5)* ((*window).getSize().y) / 600.0);
	mc.setPosition((main->wx - (((main->dir + 1) / 2 -1)* 32*5) - 32 * 2) * ((*window).getSize().x) / 800.0, main->y * ((*window).getSize().y) / 600.0);
	mc.scale((*window).getSize().x / 800.0, (*window).getSize().y / 600.0);
	arm.scale((*window).getSize().x / 800.0, (*window).getSize().y / 600.0);
	// Draw
	
	animate(clock, &rectMc, &mc, 5 * 32, main->frames, main->line, 10);
	(*window).draw(rom);
	(*window).draw(arm);
	if(main->ltrn)
		(*window).draw(l);
	(*window).draw(mc);

}

void draw_credits_gamso(RenderWindow *window) {
	// Create text
	Font font;
	if (!font.loadFromFile("fonts/pc98.ttf")) {
		cout << "Error loading fonts" << endl;
		exit(1);
	}
	Text credits;
	credits.setFont(font);
	credits.setString("Uma produção Lunare Team e");
	credits.setCharacterSize((*window).getSize().y*0.05);
	credits.setPosition((*window).getSize().x/2-credits.getGlobalBounds().width/2, (*window).getSize().y*0.02);

	// Create texture
	Texture texture;
	if (!texture.loadFromFile("img/gamso.png")){
		cout << "Error loading texture" << endl;
	}
	texture.setSmooth(false);
	Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale((*window).getSize().y / sprite.getLocalBounds().width, (*window).getSize().y / sprite.getLocalBounds().height);
	sprite.setPosition((*window).getSize().x/2-sprite.getGlobalBounds().width/2-22, 0);
	
	(*window).draw(credits);
	(*window).draw(sprite);
}

void draw_credits(int* current_scr, RenderWindow *window) {
	// Create text
	Font font;
	if (!font.loadFromFile("fonts/pc98.ttf")) {
		cout << "Error loading fonts" << endl;
		exit(1);
	}
	Text voltar;
	voltar.setFont(font);
	voltar.setString("Voltar");
	voltar.setCharacterSize((*window).getSize().y * 0.05);
	voltar.setPosition((*window).getSize().x*0.02, (*window).getSize().y*0.5 + (*window).getSize().y * 0.08 * 5);
	Text credits;
	credits.setFont(font);
	credits.setString("Programador de engine: João Bueno (@rito_jobu)\nDireção: João Bueno (@rito_jobu)\nProgramador de gameplay: Matheus Ramos\nArte e Som: Matheus Ramos\n\nCom a colaboração do grupo GAMSo");
	credits.setCharacterSize((*window).getSize().y * 0.05);
	credits.setPosition((*window).getSize().x/2-credits.getGlobalBounds().width/2, (*window).getSize().y/2-credits.getGlobalBounds().height/2);

	// Mouse events
	if (voltar.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)) {
		voltar.setFillColor(Color::Magenta);
		if (Mouse::isButtonPressed(Mouse::Left))
			* current_scr = 0;
	}

	// Draw
	(*window).draw(voltar);
	(*window).draw(credits);
}

void draw_scr(Texture* textures,double delta,Clock clock,shadow* main,int* room,int* current_scr, RenderWindow *window, Event &event) {
	/*
	 *  0 - Menu
	 *  1 - Game
	 */

	switch (*current_scr) {
	case 0:
		draw_menu(current_scr, window);
		init_main(main);
		break;
	case 1:
		draw_game(textures,delta, clock,main,room,current_scr, window, event);
		break;
	case 2:
		draw_credits(current_scr, window);
		break;
	default:
		break;
	}
}

Texture* load_textures() {
	Texture *textures;
	textures=(Texture*)malloc(sizeof(Texture) * 5);
	Texture shadowsheet;
	if (!shadowsheet.loadFromFile("img/shadowsheet.png", IntRect(0, 0, 800, 480))) {
		perror("failed to load shadowsheet image");
		system("pause");

	}
	Texture armt;
	if (!armt.loadFromFile("img/arm.png", IntRect(0, 0, 32 * 5, 32 * 5))) {
		perror("failed to load arm image");
		system("pause");

	}
	Texture ltr;
	if (!ltr.loadFromFile("img/lantern.png", IntRect(0, 0, 480, 160))) {
		perror("failed to load lantern image");
		system("pause");

	}
	Texture rooml;
	if (!rooml.loadFromFile("img/rooms.png", sf::IntRect(0, 0, 800, 600))) {
		perror("failed to load room image");
		system("pause");

	}
	Texture room;
	if (!room.loadFromFile("img/hall.png", sf::IntRect(0, 0, 5400, 600))) {
		perror("failed to load room image");
		system("pause");
	}
	textures[0] = shadowsheet;
	textures[1] = armt;
	textures[2] = ltr;
	textures[3] = rooml;
	textures[4] = room;
	return textures;

}
int main(void) {
	int current_scr[1] = { 0 }, room = 0;

	// Initialize clock
	Clock clock;
	// Initialize window
	RenderWindow window(VideoMode::getDesktopMode(), "Afraid Of The Shadows", Style::Fullscreen);
	window.setFramerateLimit(60);
	shadow main;
	init_main(&main);
	Texture* textures;
	textures = load_textures();


	double nt,ot=0,delta;
	while( window.isOpen()) {		

		Time time;
		time = clock.getElapsedTime();
		nt = time.asMicroseconds();
		delta = (nt - ot)/10000 ;
		Event event;
		while (window.pollEvent(event)){
			if (event.type == Event::Closed)
				window.close();
		}


		window.clear();
		if (time.asSeconds() <= 10)
			draw_credits_gamso(&window);
		else
			draw_scr(textures,delta,clock,&main,&room,current_scr, &window, event);
		window.display();
		ot = nt;
	}

	return 0;

}