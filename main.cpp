#include <iostream>
#include <math.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;
typedef struct {
	float x, y, ang,wx,tx, battery,san;
	int frames, line, dir, jump,ltrn, door[6],a[1], cs,chat,ignore;
	IntRect rectA;
	Clock cut,ch;
}shadow;

void init_main(shadow* main) {
	main->ignore=0;
	main->chat = 0;
	main->battery = 100;
	main->san = 100;
	main->cs = 0;
	main->x = 235;
	main->y = 66 * 5;
	main->line = 1;
	main->dir = 1;
	main->frames = 4;
	main->jump = 0;
	main->ltrn = 0;
	main->ang = 0;
	main->door[0] = 0;
	main->door[1] = 0;
	IntRect a(0, 0, 800, 600);
	main->rectA = a;
	main->door[2] = 0;
	main->door[3] = 0;
	main->door[4] = 0;
	main->door[5] = 0;
	main->a[0] = 0;

}

int cutscene(Clock clock,IntRect* rectSourceSprite, Sprite* sprite, int sizex, int sizey, int frames, int line ,int fps) {
	if (((int)(clock.getElapsedTime().asMilliseconds() / (1000.0 / fps))) % (int)sizex < frames) {
		(*rectSourceSprite).left = ((int)(clock.getElapsedTime().asMilliseconds() / (1000.0 / fps))) % (int)frames * sizex;
		(*rectSourceSprite).top = line * sizey;
		(*sprite).setTextureRect(*rectSourceSprite);
		return 1;
	}
	
	return 0;
}

void animate(Clock clock, IntRect* rectSourceSprite, Sprite* sprite, int sizex,int sizey, int frames, int line, int fps) {

	(*rectSourceSprite).left = ((int)(clock.getElapsedTime().asMilliseconds() / (1000.0 / fps))) % (int)frames * sizex ;
	(*rectSourceSprite).top = line * sizey;
	(*sprite).setTextureRect(*rectSourceSprite);

}

void write(int n, RenderWindow* window,float size, Color c,float x, float y,int i,string str) {
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
	string s = std::to_string(i);
	switch (n)
	{
	case 0:
		texto.setString(s);
		break;
	case 1:
		texto.setString(str);
		break;
	default:
		texto.setString(" ");
	}

	(*window).draw(texto);
}

void chat(int n, RenderWindow* window) {
	switch (n) {
	case 0:
		write(1, window, 0.03, Color::White, 350, 650, 10, "Está muito escuro aqui...\n");
		write(1, window, 0.02, Color::White, 350, 650, 10, "\n \n ainda bem que há uma lanterna");
		break;
	case 2:

		write(1, window, 0.03, Color::White, 50, 650, 10, "algo ainda me deixa desconfortavel aqui...");
		break;

	case 4:
		write(1, window, 0.03, Color::White, 50, 650, 10, "FUJA!	FUJA!  FUJA RAPIDAMENTE! ,\n ELE NÃO ESTÁ TÃO LONGE...");
		break;
	case 6:
		write(1, window, 0.03, Color::White, 50, 650, 10, "SAIA DO MEU QUARTO,\n crianças não deveriam estar aqui...");
		break;

	default:
		write(1, window, 0.03, Color::White, 50, 650, 10, "");
		break;

	}
}

void draw_menu(int* current_scr,Texture * textures ,RenderWindow *window) {
	// Create text
	IntRect rec(0,0,800,600);
	Sprite menu(textures[7],rec);
	menu.setScale((*window).getSize().x / 800.0, (*window).getSize().y / 600.0);
	menu.setPosition(0, 0);

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
	(*window).draw(menu);
	(*window).draw(logo);
	(*window).draw(opt1);
	(*window).draw(opt2);
	(*window).draw(opt3);
}

Sprite get_prop(Clock clock, Texture* textures, int line, float x, float y) {
	IntRect propRect(0,0,50,50);
	Sprite prop(textures[5], propRect);
	animate(clock, &propRect, &prop, 50, 50, 3, line, 3);
	prop.setPosition(x, y);
	return prop;
}

void draw_game(Sound *sound,Texture* textures, double delta, Clock clock, shadow* main, int* room, int* current_scr, RenderWindow* window, Event& event, int *cursorLine, int *propLine) {
	int h;

	IntRect rectMc(0, 0, 160, 160), rectArm(0, 0, 160, 160), rectl(0, 0, 480, 160) ,rectB(0,500,50,50), rectE(0, 0, 30, 30);
	Sprite mc(textures[0], rectMc),arm(textures[1], rectArm), l(textures[2], rectl),animation(textures[6],main->rectA),battery(textures[5],rectB);
	Texture rooml,green;
	Sprite  energy(green,rectE);
	Sprite prop[6];
	energy.setColor(Color::Green);
	energy.setOrigin(-10, 0);
	energy.setScale((*window).getSize().x / 800.0/2, (*window).getSize().y / 600.0*-1*(main->battery/100));
	energy.setPosition((*window).getSize().x / 800.0 * 100, (*window).getSize().y / 600.0 * (145));
	arm.setOrigin(18 * 5, 14 * 5);
	l.setOrigin(12*5, 12 * 5);
	mc.setScale(1, 1);
	arm.setScale(1, 1);
	l.setScale(1, 1);
	
	int tx;

	if(*room!=1)
		tx=main->tx;
	else
		tx=1080*5;


	battery.setScale((*window).getSize().x / 800.0/2, (*window).getSize().y / 600.0);
	battery.setPosition((*window).getSize().x / 800.0 * 100, (*window).getSize().y / 600.0 * 100);
	
	animation.setColor(Color(255 - (100 - main->san) * 02, 255 - (100 - main->san) * 02, 255 - (100 - main->san) * 02));
	
	

	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		*current_scr = 0;
	}
	if (main->cs == 1) {
		main->cs = cutscene(main->cut, &main->rectA, &animation, 800,600, 15, 0, 5);
		if ((main->cs ) == 0 && main->a[0] == 0)
			main->a[0] = 1;

		main->dir = 1;
		main->line = 0;
		main->chat = 0;
	}
	else if (main->chat % 2==0 && main->ignore==0) {
		main->dir = 1;
		main->line = 0;
		main->san = main->san + 0.05 / delta;
	}
	else if (Keyboard::isKeyPressed(Keyboard::A) && main->wx>8*5 ) {

	
		main->line = 1;
		main->dir = -1;
		main->x = main->x -5 / delta;
		main->ang = abs(main->ang);
	}
	else if (Keyboard::isKeyPressed(Keyboard::D) && main->x < main->tx-15*5 ) {
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
		main->battery = main->battery - 0.2 / delta;
	}
	else
		main->ltrn = 0;

	if (main->battery <= 0) {
		main->battery = 0;
		main->san = main->san - 0.1 / delta;
	}
	if (main->san <= 0) {
		main->san = 0;
	}
	//flip
	if (main->dir == -1) {
		mc.scale(-1, 1);
		arm.scale(-1, 1);
		l.scale(-1, 1);

	}
	//move all
	
	if (main->x < 400)
		main->wx = main->x;
	else if (main->x > (main->tx - 400))
		main->wx =800-(main->tx-main->x);
	else
		main->wx = 400;
	//set parameters

	animate(clock, &rectMc, &mc, 5 * 32, 5 * 32, main->frames, main->line, 10);
	IntRect rerom(0, 0, tx, 600);
	Sprite rom(textures[3 + *room + (*room / 2 >= 1) * 3], rerom);
	rom.setScale((*window).getSize().x / (800.0), (*window).getSize().y / 600.0);
	animate(clock, &rerom, &rom, tx, 600, 2, 0, 4);

	animation.setScale((*window).getSize().x / 800.0, (*window).getSize().y / 600.0);
	rom.setColor(Color(255 - (100 - main->san) * 02, 255 - (100 - main->san) * 02, 255 - (100 - main->san) * 02));

	l.setColor(sf::Color(255, 255, 255, 50));
	rom.setPosition((main->wx-main->x)* (*window).getSize().x / 800.0, 0);
	animation.setPosition(0, 0);
	l.setRotation(main->ang);
	l.setPosition((main->wx + ((main->dir + 1) / 2 - 1) * 10 - 32 * 2 + 17 * 5)* ((*window).getSize().x) / 800.0, (main->y + 13 * 5) * ((*window).getSize().y) / 600.0);	arm.setRotation(main->ang);
	arm.setPosition((main->wx + ((main->dir + 1) / 2 -1 ) *10 - 32 * 2+17*5) * ((*window).getSize().x) / 800.0, (main->y +13*5)* ((*window).getSize().y) / 600.0);
	mc.setPosition((main->wx - (((main->dir + 1) / 2 -1)* 32*5) - 32 * 2) * ((*window).getSize().x) / 800.0, main->y * ((*window).getSize().y) / 600.0);
	mc.scale((*window).getSize().x / 800.0, (*window).getSize().y / 600.0);
	arm.scale((*window).getSize().x / 800.0, (*window).getSize().y / 600.0);
	// Draw
	switch (*room)
	{
	case 0:
		main->tx = 800;
		if (main->x > 700 && propLine[0]!=0) {
			main->x = 23 * 5;
			*room = 1;
			main->door[0] = 1;
		}
		else if (main->x > 700) {
			main->chat = 2;
			main->ignore = 1;
			main->ch.restart();
		}
		else if (main->ch.getElapsedTime().asSeconds() < 4) {
			main->chat = 2;
			main->ignore = 1;
		}
		else if(main->chat % 2 == 1){
			main->chat = 1;
			main->ignore = 0;
		}
		if (main->a[0] == 0) {
			if (main->cs == 0) {
				main->cut.restart();
			}
			main->cs = 1;

		}
		if (!(main->cut.getElapsedTime().asSeconds() < 10 && main->door[0] == 0 && !Keyboard::isKeyPressed(Keyboard::D))) {
			main->chat = 1;

		}

		prop[0] = get_prop(clock, textures, propLine[0], window->getSize().x * 0.665, window->getSize().y * 0.75);

		if (prop[0].getGlobalBounds().intersects(l.getGlobalBounds()) && main->ltrn == 1 && main->battery > 0) {
			propLine[0] = 2;
		}
		if (propLine[0] == 0) {
			main->san = main->san - 0.05 / delta;
		}
		

		//
		break;
	case 1:
		prop[1] = get_prop(clock, textures, propLine[1], (main->wx - main->x+700) * (*window).getSize().x / 800.0, window->getSize().y * 0.75);
		if (prop[1].getGlobalBounds().intersects(l.getGlobalBounds()) && main->ltrn == 1 && main->battery > 0) {
			propLine[1] = 5;
		}
		if (propLine[1] == 0) {
			main->san = main->san - 0.05 / delta;
		}
		
		if (main->x < 20 * 5) {
			main->x = 650;
			*room = 0;
		}
		
		else if (main->x > 200 * 5 && main->x < 228 * 5) {
			*cursorLine = 7;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)&& propLine[1]!=0) {
				main->x = 1400;
				*room = 2;
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				main->chat = 2;
				main->ch.restart();
			}
			else if (main->ch.getElapsedTime().asSeconds() < 4) {
				main->chat = 2;
			}
			else {
				main->chat = 1;
			}
		}
		else if (main->x > 400 * 5 && main->x < 428 * 5) {
			*cursorLine = 7;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				main->x = 1400;
				*room = 3;
			}
		}
		else if (main->x > 600 * 5 && main->x < 628 * 5) {
			*cursorLine = 7;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				main->x = 1400;
				*room = 4;
			}
		}
		else if (main->x > 800 * 5 && main->x < 828 * 5) {
			*cursorLine = 7;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				main->x = 1400;
				*room = 5;
			}
		}
		else if (main->x > 1040 * 5) {
			*cursorLine = 7;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				main->x = 100;
				*room = 6;
			}
		}
		//doors
		if (main->door[4])
			main->tx = 1080 * 5;
		else if (main->door[3])
			main->tx = 1030 * 5;
		else if (main->door[2])
			main->tx = 780 * 5;
		else if (main->door[1])
			main->tx = 550 * 5;
		else
			main->tx = 300 * 5;

		break;

	case 2:
		prop[2] = get_prop(clock, textures, propLine[2], (main->wx - main->x + 900) * (*window).getSize().x / 800.0, window->getSize().y * 0.75);
		if (prop[2].getGlobalBounds().intersects(l.getGlobalBounds()) && main->ltrn == 1 && main->battery > 0) {
			propLine[2] = 8;
		}
		prop[3] = get_prop(clock, textures, propLine[3], (main->wx - main->x + 400) * (*window).getSize().x / 800.0, window->getSize().y * 0.75);
		if (prop[3].getGlobalBounds().intersects(l.getGlobalBounds()) && main->ltrn == 1 && main->battery > 0) {
			propLine[3] = 5;
		}
		if (propLine[2] == 0|| propLine[3] == 0) {
			main->san = main->san - 0.05 / delta;
		}
		main->tx = 1600;
		if (main->wx > 700) {
			*cursorLine = 7;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)&& propLine[2] != 0 && propLine[3] != 0) {
				main->x = 230 * 5;
				*room = 1;
				main->door[1] = 1;
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				main->chat = 2;
				main->ch.restart();
			}
			else if(main->ch.getElapsedTime().asSeconds()<4) {
				main->chat = 2;
			}
			else {
				main->chat=1;
			}
		}
		else if (main->x < 500) {
			if (main->ignore==0) {
				main->ignore = 1;
				main->chat = 4;
				main->ch.restart();
			}
			else if (main->ch.getElapsedTime().asSeconds() < 4) {
				main->chat = 4;
			}
			else {
				main->chat = 1;
				main->ignore = 0;
			}
		}

		//
		break;
	case 3:
		main->tx = 1600;
		if (main->wx > 700) {
			*cursorLine = 7;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)&&propLine[4]!=0) {
				main->x = 430 * 5;
				*room = 1;
				main->door[2] = 1;
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				main->chat = 2;
				main->ch.restart();
			}
			else if (main->ch.getElapsedTime().asSeconds() < 4) {
				main->chat = 2;
			}
			else {
				main->chat = 1;
			}
		}
		else if (main->x < 500) {
			if (main->ignore == 0) {
				main->ignore = 1;
				main->chat = 6;
				main->ch.restart();
			}
			else if (main->ch.getElapsedTime().asSeconds() < 4) {
				main->chat = 6;
			}
			else {
				main->chat = 1;
				main->ignore = 0;
			}
		}
		prop[4] = get_prop(clock, textures, propLine[4], (main->wx - main->x + 400) * (*window).getSize().x / 800.0, window->getSize().y * 0.75);
		if (prop[4].getGlobalBounds().intersects(l.getGlobalBounds()) && main->ltrn == 1 && main->battery > 0) {
			propLine[4] = 4;
		}
		if (propLine[4] == 0 ) {
			main->san = main->san - 0.05 / delta;
		}
		//
		break;
	case 4:
		main->tx = 1600;
		if (main->wx > 700) {
			*cursorLine = 7;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				main->x = 630 * 5;
				*room = 1;
				main->door[3] = 1;
			}
		}

		//
		break;
	case 5:
		main->tx = 1600;
		if (main->wx > 700) {
			*cursorLine = 7;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				main->x = 830 * 5;
				*room = 1;
				main->door[4] = 1;
			}
		}

		//
		break;
	case 6:
		main->tx = 800;
		if (main->wx < 100) {
			*cursorLine = 7;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				main->x = 1030 * 5;
				*room = 1;
				main->door[5] = 1;
			}
		}

		//
		break;
	}

	if (rectMc.left == 0 && main->line == 1 && main->cs == 0) {
		if (sound->getStatus() != sound->Playing)
			sound->play();
	}
	prop[0].setColor(Color(255 - (100 - main->san) * 02, 255 - (100 - main->san) * 02, 255 - (100 - main->san) * 02));
	prop[1].setColor(Color(255 - (100 - main->san) * 02, 255 - (100 - main->san) * 02, 255 - (100 - main->san) * 02));
	prop[2].setColor(Color(255 - (100 - main->san) * 02, 255 - (100 - main->san) * 02, 255 - (100 - main->san) * 02));
	prop[3].setColor(Color(255 - (100 - main->san) * 02, 255 - (100 - main->san) * 02, 255 - (100 - main->san) * 02));
	prop[4].setColor(Color(255 - (100 - main->san) * 02, 255 - (100 - main->san) * 02, 255 - (100 - main->san) * 02));
	prop[5].setColor(Color(255 - (100 - main->san) * 02, 255 - (100 - main->san) * 02, 255 - (100 - main->san) * 02));
	(*window).draw(rom);
	(*window).draw(arm);
	(*window).draw(prop[0]);
	(*window).draw(prop[1]);
	(*window).draw(prop[2]);
	(*window).draw(prop[3]);
	(*window).draw(prop[4]);
	(*window).draw(prop[5]);
	if(main->ltrn && main->battery>0)
		(*window).draw(l);
	(*window).draw(mc);
	(*window).draw(battery);
	(*window).draw(energy);
	write(0, window, 0.05, Color::White, 400, 150, (int)main->san,"");
	write(1, window, 0.05, Color::White, 250, 150, (int)main->san, "sanity:");

	if (main->cs == 1) {
		(*window).draw(animation);
		(*window).draw(prop[0]);
		(*window).draw(prop[1]);
		(*window).draw(prop[2]);
		(*window).draw(prop[3]);
		(*window).draw(prop[4]);
		(*window).draw(prop[5]);
	}
	chat(main->chat, window);


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

void draw_scr(Texture* textures,double delta,Clock clock,shadow* main,int* room,int* current_scr, RenderWindow *window, Event &event,Sound *sound, int *cursorLine, int *propLine) {
	/*
	 *  0 - Menu
	 *  1 - Game
	 *  2 - Credits
	 */

	switch (*current_scr) {
	case 0:
		draw_menu(current_scr,textures, window);
		init_main(main);
		*room = 0;
		break;
	case 1:
		draw_game(sound,textures,delta, clock,main,room,current_scr, window, event, cursorLine, propLine);
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
	textures=(Texture*)malloc(sizeof(Texture) * 13);

	Texture shadowsheet;
	if (!shadowsheet.loadFromFile("img/shadowsheet.png", IntRect(0, 0, 800, 480))) {
		perror("failed to load shadowsheet image");
		exit(1);

	}
	Texture armt;
	if (!armt.loadFromFile("img/arm.png", IntRect(0, 0, 32 * 5, 32 * 5))) {
		perror("failed to load arm image");
		exit(1);

	}
	Texture ltr;
	if (!ltr.loadFromFile("img/lantern.png", IntRect(0, 0, 480, 160))) {
		perror("failed to load lantern image");
		exit(1);

	}
	Texture rooml;
	if (!rooml.loadFromFile("img/rooms.png", sf::IntRect(0, 0, 2*800, 600))) {
		perror("failed to load room image");
		exit(1);

	}
	Texture room;
	if (!room.loadFromFile("img/hall.png", sf::IntRect(0, 0, 2*5400, 600))) {
		perror("failed to load room image");
		exit(1);
	}
	Texture hidden;
	if (!hidden.loadFromFile("img/hiddensheet.png", sf::IntRect(0, 0, 150, 600))) {
		perror("failed to load objects image");
		exit(1);
	}
	Texture animation_1;
	if (!animation_1.loadFromFile("img/room animation.png", sf::IntRect(0, 0, 15*800, 600))) {
		perror("failed to load animation image");
		exit(1);
	}
	Texture menu;
	if (!menu.loadFromFile("img/menu.png", sf::IntRect(0, 0, 800, 600))) {
		perror("failed to load menu image");
		exit(1);
	}
	Texture r;
	if (!r.loadFromFile("img/room.png", sf::IntRect(0, 0, 3200, 600))) {
		perror("failed to load room image");
		exit(1);
	}
	Texture wheel;
	if (!wheel.loadFromFile("img/wheel.png", sf::IntRect(0, 0, 3200, 600))) {
		perror("failed to load room image");
		exit(1);
	}
	Texture mummy;
	if (!mummy.loadFromFile("img/mummy.png", sf::IntRect(0, 0, 3200, 600))) {
		perror("failed to load room image");
		exit(1);
	}
	Texture empty;
	if (!empty.loadFromFile("img/empty.png", sf::IntRect(0, 0, 3200, 600))) {
		perror("failed to load room image");
		exit(1);
	}
	Texture lobby;
	if (!lobby.loadFromFile("img/lobby.png", sf::IntRect(0, 0, 1600, 600))) {
		perror("failed to load lobby image");
		exit(1);
	}
	textures[0] = shadowsheet;
	textures[1] = armt;
	textures[2] = ltr;
	textures[3] = rooml;
	textures[4] = room;
	textures[5] = hidden;
	textures[6] = animation_1;
	textures[7] = menu;
	textures[8] = r;
	textures[9] = wheel;
	textures[10] = mummy;
	textures[11] = empty;
	textures[12] = lobby;
	return textures;

}

int main(void) {
	int current_scr[1] = { 0 }, room = 0, propLine[10] = {0,0,0,0,0,0,0,0,0,0};

	// Initialize clock
	Clock clock;
	// Initialize window
	RenderWindow window(VideoMode::getDesktopMode(), "Afraid Of The Shadows", Style::Fullscreen);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);
	shadow main;
	init_main(&main);
	Texture* textures;
	textures = load_textures();
	Sprite cursor(textures[5]);
	IntRect cursorRect(0,50,50,50);
	SoundBuffer walk,bgm;
	if (!walk.loadFromFile("sound/walk.wav")) {
		cout << "Error loading sound" << endl;
		exit(1);
	}
	if (!bgm.loadFromFile("sound/bgm.wav")) {
		cout << "Error loading sound" << endl;
		exit(1);
	}
	Sound sound,bg;
	sound.setBuffer(walk);
	bg.setBuffer(bgm);

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
		int cursorLine = 1;
		if (time.asSeconds() <= 5)
			draw_credits_gamso(&window);
		else {
			draw_scr(textures, delta, clock, &main, &room, current_scr, &window, event, &sound, &cursorLine, propLine);
			if (bg.getStatus() != bg.Playing && *current_scr == 1)
				bg.play();
			else if (bg.getStatus() == bg.Playing && *current_scr == 0)
				bg.stop();
		}
		cursorRect.top = 50 * cursorLine;
		cursor.setTextureRect(cursorRect);
		cursor.setOrigin(20, 20);
		cursor.setPosition(static_cast<Vector2f>(Mouse::getPosition(window)));
		animate(clock, &cursorRect, &cursor, 50,50, 3, cursorLine, 4);
		window.draw(cursor);
		window.display();
		ot = nt;
	}
	free(textures);
	return 0;

}