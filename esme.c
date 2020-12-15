#include <ncurses.h>

#define H_LOGO 5
#define W_LOGO 23


int logo[H_LOGO][W_LOGO] =
  {
   {1, 1, 1, 1, 1,  0,  1, 1, 1, 1, 1,  0,  1, 1, 1, 1, 1,  0,  1, 1, 1, 1, 1}, 
   {1, 0, 0, 0, 0,  0,  0, 1, 0, 0, 0,  0,  1, 0, 0, 0, 1,  0,  1, 0, 0, 0, 0},
   {1, 1, 1, 1, 0,  0,  0, 0, 1, 0, 0,  0,  1, 0, 0, 0, 1,  0,  1, 1, 1, 1, 0},
   {1, 0, 0, 0, 0,  0,  0, 0, 0, 1, 0,  0,  1, 0, 0, 0, 1,  0,  1, 0, 0, 0, 0},
   {1, 1, 1, 1, 1,  0,  1, 1, 1, 1, 1,  0,  1, 0, 0, 0, 1,  0,  1, 1, 1, 1, 1},
  };

void draw(int x_off, int y_off, char pixel)
{
  int i, j;
  /* Boucle sur les lignes et les colonnes du logo */
  for(i = 0; i < H_LOGO; i++) {
	for(j = 0; j < W_LOGO; j++) {
	  move( (y_off + i) % LINES, (x_off + j) % COLS); /* LINES = nombre de lignes du terminal */
	  if( logo[i][j] ) {
		attron(A_REVERSE);
		addch(pixel);
		attroff(A_REVERSE);
	  }
	}
  }
}

int main(void)
{
  char key = '+';
  int x_off = 0, y_off = 0;

  /* Initialise la structure WINDOW et autres paramètres */
  initscr();

  do {
	clear();
	draw(y_off, x_off, key);

	/* 
	 * Déplace le curseur en bas à gauche pour qu'il ne soit pas à la
	 * fin du deuxième E
	 */
	move(LINES-1,0);

	key = getch();
	switch(key)
	  {
	  case 'o':
		printw("ok");
		break;	
	  case 'm':
		y_off += 1;
		break;
	  case 'l':
		x_off += 1;
		break;
	  case 'k':
		y_off += -1;
		break;
	  }
	x_off = (x_off + LINES) % LINES;
	y_off = (y_off + COLS) % COLS;
  }
  while( !(key == 'a') );

  /*
   * Restaure les paramètres par défaut du terminal. Il peut être instructif
   * d'enlever cette instruction et d'observer les conséquences.
   */
  endwin();

  return 0;
}
