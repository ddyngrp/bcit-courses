#ifndef _UTILS_H
#define _UTILS_H

#define ENSURE_BOOL(cond)		if (!(cond)) return false
#define ENSURE_BOOL_THROW(cond, exc) if (!(cond)) throw exc
#define ENSURE_EXCEPTION(i, exc) if(i != exc) throw exc

#endif
