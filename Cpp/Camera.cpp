/* Camera.cpp : Classe da camera do KIVA */

#include "Camera.h"

using namespace std;

Camera::Camera()
{
}


Camera::~Camera()
{
}

bool Camera::isActive()
{
	return active;
}

bool Camera::turnOn()
{
	//Detalhes de implementacao de hardware para ligar a camera

	return true;
}
bool Camera::turnOff()
{
	//Detalhes de implementacao de hardware para desligar a camera

	return false;
}

//Retorna um vetor de int correspondente ao QR Code lido.
//Para emular a leitura da camera, optou-se pela leitura
//de um arquivo em txt
vector<unsigned> Camera::getQR()
{
	ifstream file;
	string line;
	int topOrBottom, orientation, posX, posY;
	file.open("bottomQR.txt");

	if (file.is_open())
	{
		while (file >> topOrBottom)
		{
			file >> orientation;
			file >> posX;
			file >> posY;
		}
		file.close();
	}

	vector<unsigned> v;
	v.push_back(topOrBottom); 
	v.push_back(orientation); 
	v.push_back(posX);
	v.push_back(posY);

	return v;
}