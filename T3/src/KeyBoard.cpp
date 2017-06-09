#include <GL/glut.h>
#include <stdio.h>

class KeyBoard {
public:
	bool q;
	bool w;
	bool e;
	bool r;
	bool y;
	bool u;
	bool i;
	bool o;
	bool p;
	bool a;
	bool s;
	bool d;
	bool f;
	bool g;
	bool h;
	bool j;
	bool k;
	bool l;
	bool z;
	bool x;
	bool c;
	bool v;
	bool b;
	bool n;
	bool m;

	void KeyDown(unsigned char key, int x, int y){
		if(this->w)printf("%c", key);
		switch (key) {
			case 27:		//ESC
				exit(0);
				break;
			case 'q':
				this->q = true;
				break;
			case 'w':
				this->w = true;
				break;
			case 'e':
				this->e = true;
				break;
			case 'r':
				this->r = true;
				break;
			case 'y':
				this->y = true;
				break;
			case 'u':
				this->u = true;
				break;
			case 'i':
				this->i = true;
				break;
			case 'o':
				this->o = true;
				break;
			case 'p':
				this->p = true;
				break;
			case 'a':
				this->a = true;
				break;
			case 's':
				this->s = true;
				break;
			case 'd':
				this->d = true;
				break;
			case 'f':
				this->f = true;
				break;
			case 'g':
				this->g = true;
				break;
			case 'h':
				this->h = true;
				break;
			case 'j':
				this->j = true;
				break;
			case 'k':
				this->k = true;
				break;
			case 'l':
				this->l = true;
				break;
			case 'z':
				this->z = true;
				break;
			case 'x':
				this->x = true;
				break;
			case 'c':
				this->c = true;
				break;
			case 'v':
				this->v = true;
				break;
			case 'b':
				this->b = true;
				break;
			case 'n':
				this->n = true;
				break;
			case 'm':
				this->m = true;
				break;
		}
	}

	void KeyUp(unsigned char key, int x, int y){
		switch (key) {
			case 27:		//ESC
				exit(0);
				break;
			case 'q':
				this->q = false;
				break;
			case 'w':
				this->w = false;
				break;
			case 'e':
				this->e = false;
				break;
			case 'r':
				this->r = false;
				break;
			case 'y':
				this->y = false;
				break;
			case 'u':
				this->u = false;
				break;
			case 'i':
				this->i = false;
				break;
			case 'o':
				this->o = false;
				break;
			case 'p':
				this->p = false;
				break;
			case 'a':
				this->a = false;
				break;
			case 's':
				this->s = false;
				break;
			case 'd':
				this->d = false;
				break;
			case 'f':
				this->f = false;
				break;
			case 'g':
				this->g = false;
				break;
			case 'h':
				this->h = false;
				break;
			case 'j':
				this->j = false;
				break;
			case 'k':
				this->k = false;
				break;
			case 'l':
				this->l = false;
				break;
			case 'z':
				this->z = false;
				break;
			case 'x':
				this->x = false;
				break;
			case 'c':
				this->c = false;
				break;
			case 'v':
				this->v = false;
				break;
			case 'b':
				this->b = false;
				break;
			case 'n':
				this->n = false;
				break;
			case 'm':
				this->m = false;
				break;
		}
	}
};