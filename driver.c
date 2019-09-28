/*			DRIVER			clefkari@ucsd.edu

#############################################################################*/

#include "Gamecore.h"

int main(int argc, char * argv[]){

	Gamecore * core = newGamecore(argc,argv);

	if(!core){

		return -1;
	
	}

	executeGamecore(core);
	deleteGamecore(&core);

  return 0;

}
