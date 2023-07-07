#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();



		//Personaje
		ofVideoPlayer personaje;
		float posX_p;
		float posY_p;

		bool caminando;
		bool a_derecha;
		bool a_izquierda;

		ofVideoPlayer caminar_izq;
		ofVideoPlayer caminar_der;


		ofSoundPlayer musica;
		float volumen_orig;


		ofImage fondo;

		
		ofVideoPlayer introduccion;
		bool termino_intro;
		
		
		//Proyectil
		ofImage proyectil;
		float posX_pr;
		float posY_pr;

		bool habilitar;

		bool disparar;
		float x_disparo;
		float y_disparo;

		bool izquierda;
		bool derecha;

		ofSoundPlayer disparo;
		ofSoundPlayer impacto;



		//Consolas
		bool abrirConsola;


		ofImage consolas[10];
		float posiciones [10][2];
		ofVideoPlayer videos[10];
		bool reproducir[10];


		
		bool cambiar_propiedades;
		bool cambiar_de[10];
		float velocidades[10];
		int fila_de[10];


		bool fila1;
		bool fila2;
		bool fila3;


		int distancia;




		void keyPressed(int key);
		void keyReleased(int key);
		void mousePressed(int x, int y, int button);
		
};
