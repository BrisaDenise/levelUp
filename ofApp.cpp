#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetBackgroundColor(ofColor(0));
	ofSetWindowTitle("LEVEL UP: Un viaje en el tiempo");


	fondo.load("fondo.png");

	personaje.load("avatar.mov");
	personaje.setLoopState(OF_LOOP_NORMAL);


	posX_p = ofGetWidth() / 2;
	posY_p = ofGetHeight() * 0.9;





	caminar_izq.load("cam_izq.mov");
	caminar_izq.setLoopState(OF_LOOP_NORMAL);


	caminar_der.load("cam_der.mov");
	caminar_der.setLoopState(OF_LOOP_NORMAL);





	proyectil.load("proyectil.png");

	posX_pr = posX_p;
	posY_pr = posY_p;

	disparar = false;
	x_disparo = 0;
	y_disparo = 0;

	izquierda = false;
	derecha = false;

	habilitar = true;

	disparo.load("disparo.wav");
	impacto.load("impacto.wav");
	musica.load("fondo.mp3");
	musica.play();
	volumen_orig = musica.getVolume();
	musica.setLoop(OF_LOOP_NORMAL);



	abrirConsola = false;

	distancia = -100;


	






	//Cargar imágenes
	for (int i = 0; i < 10; i++)
	{
		consolas[i].load(to_string(i) + ".png");
	}





	posiciones[0][0] = (ofGetWidth() * 0.25) - 800;
	posiciones[1][0] = (ofGetWidth() / 2) - 800;
	posiciones[2][0] = (ofGetWidth() * 0.75) - 800;


	posiciones[3][0] = (ofGetWidth() * 0.2) - 800;
	posiciones[4][0] = (ofGetWidth() * 0.4) - 800;
	posiciones[5][0] = (ofGetWidth() * 0.6) - 800;
	posiciones[6][0] = (ofGetWidth() * 0.8) - 800;

	posiciones[7][0] = (ofGetWidth() * 0.25) - 800;
	posiciones[8][0] = (ofGetWidth() / 2) - 800;
	posiciones[9][0] = (ofGetWidth() * 0.75) - 800;





	
	//Cargar videos
	for (int k = 0; k < 10; k++)
	{
		videos[k].load(to_string(k) + ".mp4");
		videos[k].setLoopState(OF_LOOP_NORMAL);
	}



	cambiar_propiedades = true;

	for (int e = 0; e < 10; e++)
	{
		cambiar_de[e] = true;
	}


	for (int v = 0; v < 10; v++)
	{
		velocidades[v] = 3;
	}



	for (int f = 0; f < 3; f++)
	{
		fila_de[f] = 0;
	}

	for (int g = 3; g < 7; g++)
	{
		fila_de[g] = 1;
	}

	for (int h = 7; h < 10; h++)
	{
		fila_de[h] = 2;
	}






}

//--------------------------------------------------------------
void ofApp::update(){

	for (int i = 0; i < 10; i++)
	{
		videos[i].update();
	}

	//introduccion.update();

	personaje.update();
	caminar_izq.update();
	caminar_der.update();

	ofSoundUpdate();

}

//--------------------------------------------------------------
void ofApp::draw(){

	
	
	if (!abrirConsola)
	
	{

		fondo.draw(0,0);


		if (musica.getVolume() < volumen_orig)
		{

			musica.setVolume(musica.getVolume() + 0.1);
		}




		if (caminando)
		{
			if (a_izquierda)
			{
				caminar_izq.play();
				caminar_izq.draw(posX_p, posY_p);
			}
			
			else if (a_derecha)
			{
				caminar_der.play();
				caminar_der.draw(posX_p, posY_p);
			}
		}

		else {
			personaje.play();
			personaje.draw(posX_p, posY_p);
		}

		
		proyectil.draw(posX_pr, posY_pr);




		if (cambiar_propiedades)
		{
			for (int v = 0; v < 10; v++)
			{
				if (cambiar_de[v])
				{
					velocidades[v] = ofRandom(3, 6);
					
					fila_de[v] = int(ofRandom(0, 3));

					cambiar_de[v] = false;
				}

			}

			cambiar_propiedades = false;
			
		}


		for (int p = 0; p < 10; p++)
		{
			posiciones[p][0] += velocidades[p];


			switch (fila_de[p])
			{
				case 0:
					posiciones[p][1] = ofGetHeight() * 0.3;
					break;

				case 1:
					posiciones[p][1] = ofGetHeight() * 0.45;
					break;

				case 2:
					posiciones[p][1] = ofGetHeight() * 0.6;
					break;
			}



			if (posiciones[p][0] > ofGetWidth())
			{
				posiciones[p][0] = distancia;
				cambiar_propiedades = true;
				cambiar_de[p] = true;
			}

		}

		
		for (int l = 0; l < 10; l++)
		{
			consolas[l].draw(posiciones[l][0],posiciones[l][1]);
		}


		for (int m = 0; m < 10; m++)
		{
			if (posX_pr > posiciones[m][0] && posX_pr < posiciones[m][0] + consolas[m].getWidth() && posY_pr > posiciones[m][1] && posY_pr < posiciones[m][1] + consolas[m].getHeight())
			{

				impacto.play();
				posX_pr = posX_p;
				posY_pr = posY_p;
				disparar = false;
				habilitar = true;
				izquierda = false;
				derecha = false;

				abrirConsola = true;
				reproducir[m] = true;
			}
		}

		



		if (disparar == true)
		{

			habilitar = false;



			posY_pr -= y_disparo * 0.1;

			if (posY_pr < -20)
			{
				posX_pr = posX_p;
				posY_pr = posY_p;
				derecha = false;
				izquierda = false;
				disparar = false;
				habilitar = true;
			}




			if (derecha == true)
			{
				if (posX_pr < ofGetWidth() + 50)
				{
					posX_pr += x_disparo * 0.1;
				}
				else
				{
					posX_pr = posX_p;
					posY_pr = posY_p;
					derecha = false;
					disparar = false;
					habilitar = true;

				}
			}





			else if (izquierda == true)
			{
				if (posX_pr > -50)
				{
					posX_pr -= x_disparo * 0.1;
				}
				else
				{
					posX_pr = posX_p;
					posY_pr = posY_p;
					derecha = false;
					disparar = false;
					habilitar = true;

				}
			}

		}

	
	}
	

		
		if (abrirConsola == true)
		{

			if (musica.getVolume() > 0.1)
			{
				musica.setVolume(musica.getVolume() - 0.1);
			}


			for (int n = 0; n < 10; n++)
			{
				if (reproducir[n])
				{
					videos[n].draw(0,0,1024,768);
					videos[n].play();
				}
			}

		}
	
	
}




//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if (key == OF_KEY_RIGHT) 
	{

		caminando = true;
		a_derecha= true;

		

		posX_p += 6;
		
		if (disparar == false) 
		{
			posX_pr += 6;
		}
		
	}

	else if (key == OF_KEY_LEFT)
	{

		caminando = true;
		a_izquierda = true;

		posX_p -= 6;

		if (disparar == false)
		{
			posX_pr -= 6;
		}

	}

	posX_p = ofClamp(posX_p, 0, ofGetWidth() - personaje.getWidth());
	posX_pr = ofClamp(posX_pr, 0, ofGetWidth() - personaje.getWidth());

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == OF_KEY_RIGHT) { caminando = false; a_derecha = false; }
	if (key == OF_KEY_LEFT) { caminando = false; a_izquierda = false; }
}



//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

	if (habilitar == true)
	{

		if (button == 0)
		{
			disparo.play();
			disparar = true;

			y_disparo = posY_pr - y;


			if (posX_pr < x)
			{
				x_disparo = x - posX_pr;
				derecha = true;
			}
			else
			{
				x_disparo = posX_pr - x;
				izquierda = true;
			}


		}
	}


	

	if (abrirConsola)
	{
		if (button == 2)
		{
			for (int i = 0; i < 10; i++)
			{
				if (reproducir[i]) { reproducir[i] = false; videos[i].stop();}
			}


			abrirConsola = false;
		}
	}

	


}

