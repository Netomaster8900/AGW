//fecha oficial de version 1.0: 27/02/2026 | DD/MM/YYYY

//version actual: 1.2.1 (version princial 1, 2 cambios añadidos, 1 en trabajos)

#include<windows.h>
#include<vector>
//#include<Audioclient.h>
//#include<Mmdeviceapi.h>
//#include<Audiopolicy.h>
//#include<Audiosessiontypes.h>

//#pragma comment(lib, "Ole32.lib")
//#pragma comment(lib, "msimg32.lib")

#ifdef SDL_2

#define SDL_MAIN_HANDLED
#include<SDL.h>
#pragma comment(lib, "SDL2.lib")

#endif

char func = 1;
char cont = 0;

INT32 XOR[11 * 11] = {
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF,
	0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000,
	0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000,
	0x00000000, 0xFFFFFFFF, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x00000000,
	0xFFFFFFFF, 0xFF000000, 0xFFFFFFFF, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFFFFFFFF, 0xFF000000, 0xFF000000, 0xFFFFFFFF,
	0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFFFFFFFF, 0xFF000000, 0xFF000000, 0xFFFFFFFF,
	0x00000000, 0xFFFFFFFF, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x00000000,
	0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000,
	0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000
};
INT32 AND[11] = {
  0b01111111110000001111111111110001,
  0b00111111100000000011111110000000,
  0b00011111000000000001111100000000,
  0b00111111100000000001111100000000,
  0b01111111110000000011111110000000,
  0b00011111000000001111111111110001
};//

HCURSOR cursor;
HICON icono;
HBITMAP buffer_p;
HDC dc_buffer;
HDC dc;
HWND ventana_p;
HWND ventana_s;
void* buffer_c;
int m_x;
int m_y;
char mover = 0;
char boton = 1;

unsigned long long th = 0;
unsigned long long t1 = 0;
unsigned long long t2 = 0;

struct vent {
	const wchar_t* titulo;
	int tamaño_x;
	int tamaño_y;
	int pos_x;
	int pos_y;
	int color_borrado;
	HFONT fuente = NULL;
};

vent clase;
vent* setup(vent*);
inline void proc1();
inline void proc2();
inline void render1(void*);
inline void render2(void*);
inline void hilo1();
inline void finalizar();
inline int mensaje(HWND hwnd, unsigned int msg, WPARAM wparam, LPARAM lparam);

#ifdef BOTONES
#define BT_ACTIVE			0b10000000///Si se pasa al registrar un boton, este tendra aspecto de presionado al estar en reposo, y aspecto de reposo al estar presionado
#define BT_SHORTCUT			0b01000000///utiliza el argumento de caracter de regis_boton_ex para accionar el boton, sin animarlo
#define BT_DRAW				0b00100000///dibuja el boton independientemente de si esta activo, inactivo, habilitado o inhabiliado
#define BT_DELAY			0b00010000///permite el tiempo de espera bloqueante al accionar con teclas, y con mouse usando el flag BT_REPEAT_ON_CLICK
#define BT_REPEAT_ON_CLICK	0b00001000///repite la accion de pulzar y despulzar al hacer click con el mouse, sin animar el boton, NO APLICA A MODO SWITCH
#define BT_ANIM				0b00000100///habilita la animacion del boton ante pulzaciones fisicas del boton con el mouse, NO APLICA A MODO SWITCH, NO APLICA CON BT_REPEAT_ON_CLICK
#define BT_PUSH				0b00000010///si se utiliza, el boton se apagara al dejar de hacer click, o al abandonar la casilla del boton, si no, se comportara como un boton biestable
#define BT_HABILIT			0b00000001///habilita el boton para que sea pulsable, animable y utilizable, si no se usa, el boton sera gris, sin animacion, y de aspecto fijo


std::vector<unsigned int> bot;
std::vector<void(*)(void*)> funca;
std::vector<void*> args;
std::vector<char> tipos;
std::vector<char> hhhhq;
std::vector<char> atajos;

int num_botones = 0;

int regis_boton_ex(char atajo, char tipo, unsigned int x, unsigned int y, unsigned int ancho, unsigned int alto, void activo(void*), void desactivo(void*), void* arg_act, void* arg_suelt) {
	bot.push_back(x);
	bot.push_back(y);
	bot.push_back(x + ancho);
	bot.push_back(y + alto);
	funca.push_back(activo);
	funca.push_back(desactivo);
	tipos.push_back(tipo);
	args.push_back(arg_act);
	args.push_back(arg_suelt);
	hhhhq.push_back(0);
	atajos.push_back(atajo);
	int b = num_botones;
	num_botones++;
	return b;
}

void botones(int* buffer) {
	int iter = num_botones * 4;
	int es = 0;
	int fun = 0;
	POINT pos = { 0 };
	GetCursorPos(&pos);
	unsigned int* n_bot = bot.data();
	void(**fn)(void*) = funca.data();
	void** argus = args.data();
	char* est = tipos.data();
	for (int i = 0; i < iter; i += 4) {
		if (est[es] & BT_HABILIT) {
			unsigned char bit = 2 - ((est[es] >> 7) & 1) * 2;
			unsigned char bit1 = est[es] >> 7;
			est[es] = (est[es] & 0x7F);
			if (est[es] & BT_DRAW) {
				for (int y = n_bot[i + 1]; y <= n_bot[i + 3]; y++) {
					for (int x = n_bot[i]; x <= n_bot[i + 2]; x++) {
						if (x == n_bot[i + bit] || y == n_bot[i + 1 + bit]) {
							buffer[y * clase.tamaño_x + x] = 0x007F7F7F;
						}
						else {
							if (x == n_bot[i + 2 - bit] || y == n_bot[i + 3 - bit]) {
								buffer[y * clase.tamaño_x + x] = 0x00FFFFFF;
							}
							else {
								buffer[y * clase.tamaño_x + x] = 0x00E1E1E1;
							}
						}
					}
				}
			}
			int x_ = pos.x - clase.pos_x;
			int y_ = pos.y - clase.pos_y;
			char sobre = x_ > n_bot[i] && x_ < n_bot[i + 2] && y_ > n_bot[i + 1] && y_ < n_bot[i + 3];
			if (est[es] & BT_PUSH) {
				if (sobre) {
					if (est[es] & BT_REPEAT_ON_CLICK) {
						if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
							hhhhq[es] = !hhhhq[es];
							bit1 = !bit1;
							if (fn[fun + 1] && hhhhq[es]) {
								(fn[fun + 1])(argus[fun + 1]);
							}
							else {
								if (fn[fun] && hhhhq[es]) {
									(fn[fun])(argus[fun]);
								}
							}
							hhhhq[es] = !hhhhq[es];
							bit1 = !bit1;
							if (fn[fun + 1] && hhhhq[es]) {
								(fn[fun + 1])(argus[fun + 1]);
							}
							else {
								if (fn[fun] && hhhhq[es]) {
									(fn[fun])(argus[fun]);
								}
							}
						}
						if (est[es] & BT_DELAY) {
							Sleep(124);
						}
					}
					else {
						if (!hhhhq[es] && (GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
							hhhhq[es] = 1;
							if (est[es] & BT_ANIM) {
								bit1 = !bit1;
							}
							if (fn[fun]) {
								(fn[fun])(argus[fun]);
							}
						}
						if (hhhhq[es] && !(GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
							hhhhq[es] = 0;
							if (est[es] & BT_ANIM) {
								bit1 = !bit1;
							}
							if (fn[fun + 1]) {
								(fn[fun + 1])(argus[fun + 1]);
							}
						}
					}
				}
			}
			else {
				if (sobre) {
					if (!bit1 && !hhhhq[es] && (GetAsyncKeyState(VK_LBUTTON))) {
						hhhhq[es] = 1;
						bit1 = !bit1;
						if (fn[fun]) {
							(fn[fun])(argus[fun]);
						}
					}
					if (bit1 && !hhhhq[es] && (GetAsyncKeyState(VK_LBUTTON))) {
						hhhhq[es] = 1;
						bit1 = !bit1;
						if (fn[fun + 1]) {
							(fn[fun + 1])(argus[fun + 1]);
						}
					}
					if (hhhhq[es] && !(GetAsyncKeyState(VK_LBUTTON))) {
						hhhhq[es] = 0;
						//bit1 = !bit1;
					}
				}
			}
			if (est[es] & 0x40) {
				if ((GetAsyncKeyState((atajos.data())[es]) & 0x8000)) {
					if (!hhhhq[es]) {
						hhhhq[es] = 1;
						bit1 = !bit1;
						if (fn[fun]) {
							(fn[fun])(argus[fun]);
						}
					}
					if (hhhhq[es]) {
						hhhhq[es] = 0;
						bit1 = !bit1;
						if (fn[fun + 1]) {
							(fn[fun + 1])(argus[fun + 1]);
						}
					}
					if (est[es] & BT_DELAY) {
						Sleep(124);
					}
				}
			}
			if (!sobre && hhhhq[es] && (est[es] & BT_PUSH) && (est[es] & BT_ANIM)) {
				hhhhq[es] = 0;
				bit1 = !bit1;
			}
			est[es] = est[es] | (bit1 << 7);
		}
		else {
			if (est[es] & BT_DRAW) {
				for (int y = n_bot[i + 1]; y <= n_bot[i + 3]; y++) {
					for (int x = n_bot[i]; x <= n_bot[i + 2]; x++) {
						if (x == n_bot[i] || y == n_bot[i + 1]) {
							buffer[y * clase.tamaño_x + x] = 0x00000000;
						}
						else {
							if (x == n_bot[i + 2] || y == n_bot[i + 3]) {
								buffer[y * clase.tamaño_x + x] = 0x00FFFFFF;
							}
							else {
								buffer[y * clase.tamaño_x + x] = 0x00B4B4B4;
							}
						}
					}
				}
			}
		}
		fun += 2;
		es++;
	}
}

#endif


#ifdef SLDR

#define SLID_VISIBLE  0b10000000///establece el tipo del valor en tiempo real como flotante de 32 bits
#define SLID_INFO  0b01000000///establece el tipo del valor en tiempo real como entero sin signo de 32 bits
#define SLID_HABILIT  0b00100000///establece el tipo del valor en tiempo real como entero sin signo de 64 bits
#define SLID_ROJO  0b00010000///establece el tipo del valor en tiempo real como entero sin signo de 16 bits
#define SLID_AZUL 0b00001000///establece el tipo del valor en tiempo real como entero con signo de 32 bits
#define SLID_VERDE 0b00000100///establece el tipo del valor en tiempo real como entero con signo de 64 bits
#define SLID_HORIZONTAL 0b00000010///establece el tipo del valor en tiempo real como entero con signo de 16 bits

std::vector<unsigned int> slid;
std::vector<float*> vals;
std::vector<char> tipo;
std::vector<float> rango;
std::vector<int> pos;
std::vector<float> inver;
std::vector<float> sumer;
int num_sliders = 0;

int regis_slider(char tipo_, int x, int y, int dx, int dy, float min, float max, float* val) {
	y += 9;
	dy -= 31;
	dx -= 9;
	slid.push_back(x);
	slid.push_back(y);
	slid.push_back(x + dx + 8);
	slid.push_back(y + dy + 12);
	tipo.push_back(tipo_);
	rango.push_back(max);
	rango.push_back(min);
	pos.push_back(y + 4);
	if (tipo_ & SLID_HORIZONTAL) {
		inver.push_back((max - min) / (dx));
	}
	else inver.push_back((max - min) / (dy));
	sumer.push_back(min);
	vals.push_back(val);
	int b = num_sliders;
	num_sliders++;
	return b;
}
void mod_slider(int slider_handle, char tipo_, int x, int y, int dx, int dy, float min, float max, float* val) {
	y += 9;
	dy -= 31;
	dx -= 9;
	slid[slider_handle * 4] = (x);
	slid[slider_handle * 4 + 1] = (y);
	slid[slider_handle * 4 + 2] = (x + dx + 8);
	slid[slider_handle * 4 + 3] = (y + dy + 12);
	tipo[slider_handle] = (tipo_);
	rango[slider_handle * 2] = (max);
	rango[slider_handle * 2 + 1] = (min);
	pos[slider_handle] = y + 4;
	if (tipo_ & SLID_HORIZONTAL) {
		inver[slider_handle] = (max - min) / (dx);
	} else inver[slider_handle] = (max - min) / (dy);
	sumer[slider_handle] = min;
	vals[slider_handle] = val;
}

void sliders(int* buffer) {
	HFONT fuente = 0;
	fuente = CreateFontW(-12, 0, 0, 0, 400, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe MDL2 Assets");
	HFONT fuente2 = (HFONT)SelectObject(dc_buffer, fuente);
	SetBkMode(dc_buffer, TRANSPARENT);
	int n = num_sliders * 4;
	POINT pt;
	GetCursorPos(&pt);
	pt.x -= clase.pos_x;
	pt.y -= clase.pos_y;
	int es = 0;
	int q = 0;
	for (int i = 0; i < n; i += 4) {
		if (!(tipo[es] & SLID_VISIBLE)) {
			es++;
			q += 2;
			continue;
		}
		if (tipo[es] & SLID_HORIZONTAL) {
			if (tipo[es] & SLID_INFO) {
				for (int x = (slid[i] - 5); x <= (slid[i + 2] + 5); x++) {
					for (int y = (slid[i + 3] + 10); y <= (slid[i + 3] + 25); y++) {
						if (y == (slid[i + 3] + 10) || x == (slid[i] - 5)) {
							buffer[y * clase.tamaño_x + x] = 0x00000000;
						}
						else if (y == (slid[i + 3] + 25) || x == (slid[i + 2] + 5)) {
							buffer[y * clase.tamaño_x + x] = 0x00F2F2F2;
						}
						else
							buffer[y * clase.tamaño_x + x] = 0x00FFFFFF;
					}
				}
				RECT rc = { slid[i] - 5, slid[i + 3] + 10, slid[i + 2] + 5, slid[i + 3] + 25 };
				wchar_t buf[90] = {};
				if ((*(vals[es])) < 0.1) {
					swprintf(buf, L"%.1f m", (*(vals[es])) * 1000);
				}
				else
					if ((*(vals[es])) < 1000) {
						swprintf(buf, L"%.1f", (*(vals[es])));
					}
					else
						if ((*(vals[es])) < 1000000) {
							swprintf(buf, L"%.1f K", (*(vals[es])) * 0.001);
						}
						else
							if ((*(vals[es])) < 1000000000) {
								swprintf(buf, L"%.1f M", (*(vals[es])) * 0.000001);
							}
				DrawTextW(dc_buffer, buf, -1, &rc, DT_END_ELLIPSIS | DT_CENTER);
			}
			for (int x = slid[i]; x <= slid[i + 2]; x++) {
				for (int y = slid[i + 1] - 9; y <= slid[i + 3] + 9; y++) {
					if (x == slid[i] || y == slid[i + 1] - 9) {
						buffer[y * clase.tamaño_x + x] = 0x00FFFFFF;
					}
					else if (x == slid[i + 2] || y == slid[i + 3] + 9) {
						buffer[y * clase.tamaño_x + x] = 0x007F7F7F;
					}
					else
						buffer[y * clase.tamaño_x + x] = 0x00E1E1E1;
				}
			}
			for (int x = (slid[i] + 4); x <= (slid[i + 2] - 4); x++) {
				for (int y = (slid[i + 1] - 4); y <= (slid[i + 3] + 5); y++) {
					if (y == (slid[i + 3] + 5) || x == (slid[i + 2] - 4)) {
						buffer[y * clase.tamaño_x + x] = 0x00FFFFFF;
					}
					else if (y == (slid[i + 1] - 4) || x == (slid[i] + 4)) {
						buffer[y * clase.tamaño_x + x] = 0x007F7F7F;
					}
					else
						buffer[y * clase.tamaño_x + x] = 0x00E1E1E1;
				}
			}
			if (tipo[es] & SLID_VERDE) {
				for (int x = pos[es] * 1.006; x <= (slid[i + 2] + 4); x++) {
					for (int y = (slid[i + 1] + 5); y <= (slid[i + 3] - 5); y++) {
						buffer[y * clase.tamaño_x + x] = 0x0000DF00;
					}
				}
			}
			if (tipo[es] & SLID_AZUL) {
				for (int x = pos[es] * 1.006; x <= (slid[i + 2] + 4); x++) {
					for (int y = (slid[i + 1] + 5); y <= (slid[i + 3] - 5); y++) {
						buffer[y * clase.tamaño_x + x] = 0x000291ED;
					}
				}
			}
			if (tipo[es] & SLID_ROJO) {
				for (int x = (slid[i] + 4); x <= pos[es] * 1.006; x++) {
					for (int y = (slid[i + 1]); y <= (slid[i + 3]); y++) {
						buffer[y * clase.tamaño_x + x] = 0x00E81824;
					}
				}
			}
			pos[es] = (slid[i + 2] - slid[i]) - (slid[i + 2] - slid[i]) * ((*(vals[es]) - sumer[es]) / (rango[q] - rango[q + 1])) + slid[i];
			int x_ = pos.data()[es] - 4;
			int x__ = pos.data()[es] + 4;
			for (int x = x_; x <= x__; x++) {
				for (int y = slid[i + 1]; y <= slid[i + 3]; y++) {
					if (y == slid[i + 3] || x == x__) {
						buffer[y * clase.tamaño_x + x] = 0x007F7F7F;
					}
					else if (y == slid[i + 1] || x == x_) {
						buffer[y * clase.tamaño_x + x] = 0x00FFFFFF;
					}
					else
						buffer[y * clase.tamaño_x + x] = 0x00E1E1E1;
				}
			}
			char dentro = pt.x > slid[i] && pt.y > slid[i + 1] && pt.x < slid[i + 2] && pt.y < slid[i + 3];
			if (dentro) {
				if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
					tipo[es] = tipo[es] | 0x01;
				}
			}
			if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
				tipo[es] = tipo[es] & 0xFE;
			}
			if (tipo[es] & 0x01) {
				pos[es] = max(min(pt.x, slid[i + 2] - 8), slid[i + 1] + 5);
				*(vals[es]) = rango[q] - ((pos[es] - (slid[i] + 4)) * inver[es]/* + sumer[es] */);
			}
		}
		else {
			if (tipo[es] & SLID_INFO) {
				for (int x = (slid[i] - 5); x <= (slid[i + 2] + 5); x++) {
					for (int y = (slid[i + 3] + 10); y <= (slid[i + 3] + 25); y++) {
						if (y == (slid[i + 3] + 10) || x == (slid[i] - 5)) {
							buffer[y * clase.tamaño_x + x] = 0x00000000;
						}
						else if (y == (slid[i + 3] + 25) || x == (slid[i + 2] + 5)) {
							buffer[y * clase.tamaño_x + x] = 0x00F2F2F2;
						}
						else
							buffer[y * clase.tamaño_x + x] = 0x00FFFFFF;
					}
				}
				RECT rc = { slid[i] - 5, slid[i + 3] + 10, slid[i + 2] + 5, slid[i + 3] + 25 };
				wchar_t buf[90] = {};
				if ((*(vals[es])) < 0.1) {
					swprintf(buf, L"%.1f m", (*(vals[es])) * 1000);
				}
				else
					if ((*(vals[es])) < 1000) {
						swprintf(buf, L"%.1f", (*(vals[es])));
					}
					else
						if ((*(vals[es])) < 1000000) {
							swprintf(buf, L"%.1f K", (*(vals[es])) * 0.001);
						}
						else
							if ((*(vals[es])) < 1000000000) {
								swprintf(buf, L"%.1f M", (*(vals[es])) * 0.000001);
							}
				DrawTextW(dc_buffer, buf, -1, &rc, DT_END_ELLIPSIS | DT_CENTER);
			}
			for (int x = slid[i]; x <= slid[i + 2]; x++) {
				for (int y = slid[i + 1] - 9; y <= slid[i + 3] + 9; y++) {
					if (x == slid[i] || y == slid[i + 1] - 9) {
						buffer[y * clase.tamaño_x + x] = 0x00FFFFFF;
					}
					else if (x == slid[i + 2] || y == slid[i + 3] + 9) {
						buffer[y * clase.tamaño_x + x] = 0x007F7F7F;
					}
					else
						buffer[y * clase.tamaño_x + x] = 0x00E1E1E1;
				}
			}
			for (int x = (slid[i] + 4); x <= (slid[i + 2] - 4); x++) {
				for (int y = (slid[i + 1] - 4); y <= (slid[i + 3] + 5); y++) {
					if (y == (slid[i + 3] + 5) || x == (slid[i + 2] - 4)) {
						buffer[y * clase.tamaño_x + x] = 0x00FFFFFF;
					}
					else if (y == (slid[i + 1] - 4) || x == (slid[i] + 4)) {
						buffer[y * clase.tamaño_x + x] = 0x007F7F7F;
					}
					else
						buffer[y * clase.tamaño_x + x] = 0x00E1E1E1;
				}
			}
			if (tipo[es] & SLID_VERDE) {
				for (int x = (slid[i] + 5); x <= (slid[i + 2] - 5); x++) {
					for (int y = pos[es] * 1.006; y <= (slid[i + 3] + 4); y++) {
						buffer[y * clase.tamaño_x + x] = 0x0000DF00;
					}
				}
			}
			if (tipo[es] & SLID_AZUL) {
				for (int x = (slid[i] + 5); x <= (slid[i + 2] - 5); x++) {
					for (int y = pos[es] * 1.006; y <= (slid[i + 3] + 4); y++) {
						buffer[y * clase.tamaño_x + x] = 0x000291ED;
					}
				}
			}
			if (tipo[es] & SLID_ROJO) {
				for (int x = (slid[i] + 5); x <= (slid[i + 2] - 5); x++) {
					for (int y = pos[es] * 1.006; y <= (slid[i + 3] + 4); y++) {
						buffer[y * clase.tamaño_x + x] = 0x00E81824;
					}
				}
			}
			pos[es] = (slid[i + 3] - slid[i + 1]) - (slid[i + 3] - slid[i + 1]) * ((*(vals[es]) - sumer[es]) / (rango[q] - rango[q + 1])) + slid[i + 1];
			int y_ = pos.data()[es] - 4;
			int y__ = pos.data()[es] + 4;
			for (int x = slid[i] + 5; x <= slid[i + 2] - 5; x++) {
				for (int y = y_; y <= y__; y++) {
					if (y == y__ || x == slid[i + 2] - 5) {
						buffer[y * clase.tamaño_x + x] = 0x007F7F7F;
					}
					else if (y == y_ || x == slid[i] + 5) {
						buffer[y * clase.tamaño_x + x] = 0x00FFFFFF;
					}
					else
						buffer[y * clase.tamaño_x + x] = 0x00E1E1E1;
				}
			}
			char dentro = pt.x > slid[i] && pt.y > slid[i + 1] && pt.x < slid[i + 2] && pt.y < slid[i + 3];
			if (dentro) {
				if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
					tipo[es] = tipo[es] | 0x01;
				}
			}
			if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
				tipo[es] = tipo[es] & 0xFE;
			}
			if (tipo[es] & 0x01) {
				pos[es] = max(min(pt.y, slid[i + 3] - 8), slid[i + 1] + 5);
				*(vals[es]) = rango[q] - ((pos[es] - (slid[i + 1] + 4)) * inver[es]/* + sumer[es] */);
			}
		}
		es++;
		q += 2;
	}
	SelectObject(dc_buffer, fuente2);
	DeleteObject(fuente);
}
#endif


LRESULT CALLBACK principal(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	if (msg == WM_CLOSE) {
		func = 0;
		return 0;
	}
	if (msg == WM_PAINT) {
		PAINTSTRUCT ps = {};
		HDC hdc = BeginPaint(hwnd, &ps);
		SetBkMode(hdc, TRANSPARENT);
		if (mover & 0x02) {
			HBRUSH br = CreateSolidBrush(0x00060504);
			RECT rc = { 0, 0, clase.tamaño_x, 20 };
			HFONT fuente = 0;
			if (clase.fuente != NULL) {
				fuente = clase.fuente;
			}
			else {
				fuente = CreateFontW(-16, 0, 0, 0, 400, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe MDL2 Assets");
			}
			SelectObject(hdc, fuente);
			FillRect(hdc, &rc, br);
			DeleteObject(br);
			br = CreateSolidBrush(0x002311E8);
			rc = { clase.tamaño_x - 30, 0, clase.tamaño_x, 20 };
			FillRect(hdc, &rc, br);
			rc = { 0, 0, clase.tamaño_x - 93, 20 };
			SetTextColor(hdc, 0x00FFFFFF);
			DrawTextW(hdc, clase.titulo, -1, &rc, DT_LEFT);
			DeleteObject(br);
			br = CreateSolidBrush(0x00FF9837);
			rc = { clase.tamaño_x - 62, 0, clase.tamaño_x - 31, 20 };
			FillRect(hdc, &rc, br);
			DeleteObject(br);
			br = CreateSolidBrush(0x00FF9837);
			rc = { clase.tamaño_x - 93, 0, clase.tamaño_x - 63, 20 };
			FillRect(hdc, &rc, br);
			DeleteObject(br);
			HPEN lapiz = CreatePen(PS_SOLID, 1, 0x00FFFFFF);
			HPEN o_lapiz = (HPEN)SelectObject(hdc, lapiz);
			MoveToEx(hdc, clase.tamaño_x - 19, 6, NULL);
			LineTo(hdc, clase.tamaño_x - 11, 14);
			MoveToEx(hdc, clase.tamaño_x - 19, 13, NULL);
			LineTo(hdc, clase.tamaño_x - 11, 5);
			SelectObject(hdc, o_lapiz);
			DeleteObject(lapiz);
			lapiz = CreatePen(PS_SOLID, 1, 0x00060504);
			o_lapiz = (HPEN)SelectObject(hdc, lapiz);

#ifdef MAX
			rc = { 547, 0, 577, 20 };
			MoveToEx(hdc, clase.tamaño_x - 53, 5, NULL);
			LineTo(hdc, clase.tamaño_x - 39, 5);
			MoveToEx(hdc, clase.tamaño_x - 39, 5, NULL);
			LineTo(hdc, clase.tamaño_x - 39, 14);
			MoveToEx(hdc, clase.tamaño_x - 39, 14, NULL);
			LineTo(hdc, clase.tamaño_x - 41, 14);
			SetPixel(hdc, clase.tamaño_x - 53, 6, 0x00060504);
			MoveToEx(hdc, clase.tamaño_x - 55, 7, NULL);
			LineTo(hdc, clase.tamaño_x - 41, 7);
			MoveToEx(hdc, clase.tamaño_x - 41, 7, NULL);
			LineTo(hdc, clase.tamaño_x - 41, 16);
			MoveToEx(hdc, clase.tamaño_x - 41, 16, NULL);
			LineTo(hdc, clase.tamaño_x - 55, 16);
			MoveToEx(hdc, clase.tamaño_x - 55, 16, NULL);
			LineTo(hdc, clase.tamaño_x - 55, 7);
#endif

			MoveToEx(hdc, clase.tamaño_x - 82, 14, NULL);
			LineTo(hdc, clase.tamaño_x - 72, 14);
			SetPixel(hdc, clase.tamaño_x - 73, 13, 0x00060504);
			SetPixel(hdc, clase.tamaño_x - 82, 13, 0x00060504);

			SelectObject(hdc, o_lapiz);
			DeleteObject(lapiz);
		}
		EndPaint(hwnd, &ps);
		return 0;
	}
	if (msg == WM_LBUTTONDOWN) {
		if (HIWORD(lparam) < 20) {
			if (LOWORD(lparam) > clase.tamaño_x - 31) {
				func = 0;
				return 0;
			}
			else {
#ifdef MAX
				if (LOWORD(lparam) > clase.tamaño_x - 61 && (boton & 0x01)) {
					ShowWindow(hwnd, SW_MAXIMIZE);
					boton = 0;
					return 0;
				}
				else {
					if (LOWORD(lparam) > clase.tamaño_x - 63) {
						ShowWindow(hwnd, SW_NORMAL);
						boton = 1;
						return 0;
					}
					else {
#endif
						if (LOWORD(lparam) > clase.tamaño_x - 94 && LOWORD(lparam) < clase.tamaño_x - 63) {
							ShowWindow(hwnd, SW_MINIMIZE);
							return 0;
						}
#ifdef MAX
					}
				}
#endif
			}
			mover = 1;
			POINT p;
			GetCursorPos(&p);
			RECT ventana;
			GetWindowRect(ventana_p, &ventana);
			m_x = p.x - ventana.left;
			m_y = p.y - ventana.top;
			SetCapture(hwnd);
			return 0;
		}
	}
	if (msg == WM_LBUTTONUP) {
		mover = 0;
		ReleaseCapture();
		return 0;
	}
	if (msg == WM_MOUSEMOVE) {
		ShowCursor(1);
		POINT p;
		GetCursorPos(&p);
		if (mover & 0x01) {
			SetWindowPos(ventana_p, NULL, p.x - m_x, p.y - m_y, 640, 400, SWP_NOSIZE);
			clase.pos_x = p.x - m_x;
			clase.pos_y = p.y - m_y;
		}
		SetCursor(LoadCursorW(NULL, IDC_ARROW));
	}
	if (msg == WM_SIZE) {
	}
	return DefWindowProcW(hwnd, msg, wparam, lparam);
}
LRESULT CALLBACK secundario(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	if (msg == WM_CLOSE) {
		func = 0;
		return 0;
	}
	if (msg == WM_PAINT) {
		PAINTSTRUCT ps = {};
		BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		return 0;
	}
	if (msg == WM_MOUSEMOVE) {
		if (HIWORD(lparam) < 21) {
			mover = 2;
			SetWindowPos(hwnd, NULL, 0, 20, 0, 0, SWP_NOSIZE);
		}
		if (HIWORD(lparam) > 20 && mover & 0x02) {
			mover = 0;
			
			SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOSIZE);
		}
		SetCursor(cursor);
	}
	if (msg == WM_SIZE) {
		DeleteObject(buffer_p);
		BITMAPINFO bmp = {};
		bmp.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmp.bmiHeader.biWidth = clase.tamaño_x;
		bmp.bmiHeader.biHeight = -clase.tamaño_y;
		bmp.bmiHeader.biBitCount = 32;
		bmp.bmiHeader.biPlanes = 1;
		bmp.bmiHeader.biCompression = BI_RGB;

		buffer_p = CreateDIBSection(dc_buffer, &bmp, DIB_RGB_COLORS, &buffer_c, NULL, 0);
		SelectObject(dc_buffer, buffer_p);
	}
#ifdef msg_
	if (mensaje(hwnd, msg, wparam, lparam) == 0) {
		return DefWindowProcW(hwnd, msg, wparam, lparam);
	}
#endif
	return DefWindowProcW(hwnd, msg, wparam, lparam);
}

DWORD WINAPI tercero(void* param) {
#ifdef rnd_set2
	proc2();
#endif
	LARGE_INTEGER ciclos = {};
	LARGE_INTEGER tiempo = {};
	LARGE_INTEGER tiempo1 = {};

	QueryPerformanceFrequency(&ciclos);
	MSG msg = {};
	int* buff = (int*)buffer_c;
	QueryPerformanceCounter(&tiempo);
	while (func) {
#ifdef borrador
		for (int x = 0; x < clase.tamaño_x; x += 1) {
			for (int y = 1; y < clase.tamaño_y; y += 2) {
				buff[y * clase.tamaño_x + x] = clase.color_borrado;
			}
		}
#endif
#ifdef rnd2
		render2(buffer_c);
#endif
		QueryPerformanceCounter(&tiempo1);
		long long retraso = tiempo1.QuadPart - tiempo.QuadPart;
		t2 = retraso;
		if ((retraso / (double)ciclos.QuadPart) < 0.033) {
			QueryPerformanceCounter(&tiempo1);
			Sleep(abs(33 - ((tiempo1.QuadPart - tiempo.QuadPart) / (ciclos.QuadPart / 1000))));
			QueryPerformanceCounter(&tiempo);
		}
		else {
			QueryPerformanceCounter(&tiempo);
		}
	}
	return 0;
}

DWORD WINAPI segundo(void* param) {
#ifdef rnd_set1 
	proc1();
#endif
	Sleep(8);
	WNDCLASSW clas = {};
	clas.lpszClassName = L"dibujo";
	clas.hInstance = GetModuleHandleW(NULL);
	clas.lpfnWndProc = secundario;
	RegisterClass(&clas);
	ventana_s = CreateWindowW(L"dibujo", L"frame", WS_CHILD | WS_VISIBLE, 0, 0, clase.tamaño_x, clase.tamaño_y, (HWND)param, NULL, clas.hInstance, NULL);
	ShowWindow(ventana_s, SW_SHOW);
	HDC hdc = GetDC(ventana_s);
	dc = hdc;
	dc_buffer = CreateCompatibleDC(hdc);

	BITMAPINFO bmp = {};
	bmp.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmp.bmiHeader.biWidth = clase.tamaño_x;
	bmp.bmiHeader.biHeight = -clase.tamaño_y;
	bmp.bmiHeader.biBitCount = 32;
	bmp.bmiHeader.biPlanes = 1;
	bmp.bmiHeader.biCompression = BI_RGB;

	buffer_p = CreateDIBSection(dc_buffer, &bmp, DIB_RGB_COLORS, &buffer_c, NULL, 0);
	SelectObject(dc_buffer, buffer_p);
	HANDLE hilo = CreateThread(NULL, 2000000, &tercero, NULL, 0, NULL);

	LARGE_INTEGER ciclos = {};
	LARGE_INTEGER tiempo = {};
	LARGE_INTEGER tiempo1 = {};
	QueryPerformanceFrequency(&ciclos);
	MSG msg = {};
	int* buff = (int*)buffer_c;
	QueryPerformanceCounter(&tiempo);
	while (func) {
#ifdef borrador
		for (int x = 0; x < clase.tamaño_x; x += 1) {
			for (int y = 0; y < clase.tamaño_y; y += 2) {
				buff[y * clase.tamaño_x + x] = clase.color_borrado;
			}
		}
#endif
#ifdef BOTONES
		botones((int*)buffer_c);
#endif
#ifdef rnd1
		render1(buffer_c);
#endif
		QueryPerformanceCounter(&tiempo1);
		long long retraso = tiempo1.QuadPart - tiempo.QuadPart;
		t1 = retraso;
		if ((retraso / (double)ciclos.QuadPart) < 0.033) {
			if (PeekMessage(&msg, ventana_s, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessageW(&msg);
			}
			BitBlt(hdc, 0, 0, clase.tamaño_x, clase.tamaño_y, dc_buffer, 0, 0, SRCCOPY);
			QueryPerformanceCounter(&tiempo1);
			Sleep(abs(33 - ((tiempo1.QuadPart - tiempo.QuadPart) / (ciclos.QuadPart / 1000))));
			QueryPerformanceCounter(&tiempo);
		}
		else {
			if (PeekMessage(&msg, ventana_s, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessageW(&msg);
			}
			BitBlt(hdc, 0, 0, clase.tamaño_x, clase.tamaño_y, dc_buffer, 0, 0, SRCCOPY);
			QueryPerformanceCounter(&tiempo);
		}
	}
	WaitForSingleObject(hilo, INFINITE);
	ReleaseDC(ventana_s, hdc);
	return 0;
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE NA, LPSTR cmdline, int showcmd) {

	if (setup(&clase)) {
		if (clase.tamaño_x && clase.titulo) {
			icono = CreateIcon(hinstance, 11, 11, 1, 32, (BYTE*)(&AND[0]), (BYTE*)(&XOR[0]));
			cursor = CreateCursor(hinstance, 0, 0, 11, 11, (BYTE*)(&AND[0]), (BYTE*)(&XOR[0]));
			WNDCLASSW clas = {};
			clas.lpszClassName = L"principal";
			clas.hIcon = icono;
			clas.hInstance = hinstance;
			//clas.style = NULL;
			clas.lpfnWndProc = principal;
			RegisterClassW(&clas);
			ventana_p = CreateWindowW(L"principal", clase.titulo, WS_POPUP, 0, 0, clase.tamaño_x, clase.tamaño_y, NULL, NULL, hinstance, NULL);
			ShowWindow(ventana_p, SW_SHOW);
			MSG msg = {};
			int n = 0;
			LARGE_INTEGER ciclos = {};
			LARGE_INTEGER tiempo = {};
			LARGE_INTEGER tiempo1 = {};
			HANDLE hilo2 = CreateThread(NULL, 2000000, segundo, ventana_p, 0, NULL);
			QueryPerformanceFrequency(&ciclos);
			while (func) {
				QueryPerformanceCounter(&tiempo);
#ifdef proces
				hilo1();
#endif
				QueryPerformanceCounter(&tiempo1);
				th = (tiempo1.QuadPart - tiempo.QuadPart);
				if (((tiempo1.QuadPart - tiempo.QuadPart) / ciclos.QuadPart) < 0.008) {//todo esto
					if (PeekMessageW(&msg, ventana_p, 0, 0, PM_REMOVE)) {
						TranslateMessage(&msg);
						DispatchMessageW(&msg);
						//MessageBox(ventana_p, L"mensaje", L"texto", MB_OK);
					}
					QueryPerformanceCounter(&tiempo1);
					Sleep(abs(8 - (tiempo1.QuadPart - tiempo.QuadPart) / (ciclos.QuadPart / 1000)));//hasta aca
				}
				else {
					if (PeekMessageW(&msg, ventana_p, 0, 0, PM_REMOVE)) {
						TranslateMessage(&msg);
						DispatchMessageW(&msg);
						//MessageBox(ventana_p, L"mensaje", L"texto", MB_OK);
					}
				}
			}
			finalizar();
			WaitForSingleObject(hilo2, INFINITE);
			DestroyWindow(ventana_p);
			DestroyIcon(icono);
		}
	}
	return 0;
}