/* Environment.h : classe do Ambiente 
** Essa classe possui a estacao de recarga e as estantes,
** porem, apenas a estacao de recarga foi implementada, para
** simplificar a implementacao do sistema
*/
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "RechargeBase.h"

class Environment
{
public:
	RechargeBase rechargeBase;
	Environment();
	~Environment();
};

#endif // ENVIRONMENT_H