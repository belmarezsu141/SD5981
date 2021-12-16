
#ifndef PCM_COMMON_TYPES_H_
#define PCM_COMMON_TYPES_H_

#include <string>
using namespace std;

typedef struct{
	string	port_name;
	string	sdio_pin;
	string	waitplllock;
	string	checkplllock;
	long    checkplllockcycle;
	string  utiliy_relay;
	string  VCXO_relay;
	string	d2s_template[3];
//	string	write_template_prefix;
//	string	read_template_prefix;
//	string	wait_template_prefix;
}T_PCM_DEFINITION;

typedef struct{
	unsigned int Addr;
	unsigned int Data;
} T_PCM_SPI_DATA;

#endif /* PCM_COMMON_TYPES_H_ */
