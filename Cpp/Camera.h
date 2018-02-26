/* Camera.h : Classe da camera do KIVA */

#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Camera
{
private:
	bool active;
	unsigned int fps;

public:
	Camera();
	~Camera();
	bool isActive();
	bool turnOn();
	bool turnOff();

	//retorna um vetor de int correspondente ao QR Code lido
	vector<unsigned> getQR();
};

#endif // CAMERA_H