#ifndef _K_H
#define _K_H

void found_version(int type, int major, int minor);

void found_tag_14443a(int id, int pupi);
void found_tag_14443b(int id, int pupi);
void found_tag_15693(int invFlag, int dataFormatID, int uniqueID);
void found_tag_tagit(int id1, int id2);
void found_tag_lfdst(int id, int tag);
void found_tag_14434(char *data, size_t len);	// TODO: find actual paramaters (not final)
void found_tag_apollo(char *data, size_t len);	// TODO: find actual paramaters (not final)
void found_tag_none();

#endif
