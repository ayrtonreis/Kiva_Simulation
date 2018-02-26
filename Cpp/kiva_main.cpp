/* kiva_car.cpp : Instancia os objetos das classes
** Kiva, Host e Ambiente, e inicia a rotina de missoes
*/

#include <iostream>
#include "Trajectory.h"
#include "Location.h"
#include "Host.h"
#include "Kiva.h"

using namespace std;	

int main()
{

	Host h;
	Environment env;
	//inicializa o Kiva com um id arbitrario
	Kiva k(125862, &env);
	h.includeKiva(&k);
	//solicita ao host o envio das missoes para o Kiva
	h.startMissionsRoutine();

	//Evita o fechamento automatico do programa no Windows
	char in;
	cin >> in;

    return 0;
}