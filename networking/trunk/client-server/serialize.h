#ifndef SERIALIZE_H_
#define SERIALIZE_H_
#include "DPlaya.h"

int serialize_player(DPlaya *player, char *buf, size_t buflen);
int unserialize_player(char *buf, DPlaya *player);


#endif


