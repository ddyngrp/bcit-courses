#include "stdafx.h"
#include "CircularQue.h"

/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
*/


///////////////////////////////////////////////////////////////////
// CircularQue


CircularQue::CircularQue () :

	m_que(0),
	m_queSz(0),
	m_read(0),
	m_write(0),
	m_wrapType(idNoWrap),
	m_lock(),
	m_rxEvent(),
	m_wrapEvent()

{}


CircularQue::~CircularQue ()
{
	release();
}

bool CircularQue::create ( long queSz )
{
	// if invalid que size
	if ( queSz <= 0 )
		return false;

	// create que
	m_queSz = queSz;
	m_que = new BYTE[m_queSz];

	// if failed stop
	if ( m_que )
	{
		m_rxEvent.create();
		m_wrapEvent.create();
		return true;
	}
	else
	{
		m_queSz = 0;
		return false;
	}
}	


void CircularQue::release ()
{
	if ( !m_que )
		return;

	// release que
	delete[] m_que;
	m_que   = 0;
	m_queSz = 0;
	m_read   = 0;
	m_write	= 0;
	m_wrapType = idNoWrap;

	// release events
	m_rxEvent.release();
	m_wrapEvent.release();
}



// inc read/write pos based
// on operation
bool CircularQue::incPos ( long inc, long op )
{
	// if inc > que size stop
	if ( inc < 0 || inc > m_queSz )
		return false;

	// get pos to modify
	long * pos = &m_write;
	if ( op == idRead )
		pos = &m_read;

	// get len to que end
	long lenToEnd = lengthToEnd(op);

	// if inc not beyond que end
	if ( inc <= lenToEnd )
		*pos += lenToEnd;
	else
	{
		// set pos to length from start
		// because of wrap
		*pos = inc - lenToEnd;

		// could set wrap event here
	}

	// if either pos has wrapped to other
	if ( m_read == m_write )
	{
		m_wrapType = idWriteWrap;
		if ( op == idRead )
			m_wrapType = idReadWrap;
	}
	else
		m_wrapType = idNoWrap;

	return true;
}


// set read/write pos based
// on operation
bool CircularQue::setPos ( long set, long op )
{
	// if inc > que size stop
	if ( set < 0 || set > m_queSz )
		return false;

	// get pos to modify
	long * pos = &m_write;
	if ( op == idRead )
		pos = &m_read;

	// set new position
	*pos = set;

	// if either pos has wrapped to other
	if ( m_read == m_write )
	{
		m_wrapType = idWriteWrap;
		if ( op == idRead )
			m_wrapType = idReadWrap;
	}
	else
		m_wrapType = idNoWrap;

	return true;
}

bool CircularQue::getCount ( long & count, long op )
{
	// get write and read positions
	// we are not locked so take a snap shot
	long write = m_write;
	long read  = m_read;

	// get the write count
	count = 0;
	if ( write == read )
	{
		count = m_queSz;
		if ( m_wrapType == idWriteWrap )
			count = 0;
	}
	else if ( write > read )
	{
		// sub que size from next read pos then add
		// to end pos 
		count = (m_queSz - write) + read;
	}
	else
	{
		// sub cur end from next pos to write
		count = read - write;
	}

	// if need read count then sub read
	// count from que size
	if ( op == idRead )
	{
		if ( m_wrapType == idReadWrap )
			count = 0;
		else
			count = m_queSz - count;
	}

	// if nothing to write show none
	if ( count == 0 )
		return false;
	else
		return true;
}


bool CircularQue::readWithCnt ( BYTE * data, long & length )
{
	// show nothing copied
	length = 0;

	// read the length of the frame 
	long count = 0;
	if ( !readCount(count) )
		return false;

	// read the data
	bool success = read(data,count);

	// update length
	if ( success )
		length = count;

	return true;
}

bool CircularQue::read ( BYTE * data, long length )
{
	// show data block to long
	if ( length < 0 || length > m_queSz )
		return false;

	// set read lock
	if ( !m_lock.lock() )
		return false;

	// read length to que end
	long lenToEnd = lengthToEnd(idRead);

	// copy from read to end of buffer
	if ( lenToEnd > 0 )
		memcpy( data, &m_que[m_read], lenToEnd );

	// copy remainder to start of buffer
	long lenRemaining = length - lenToEnd;
	if ( lenRemaining > 0 )
		memcpy( &data[lenToEnd], &m_que[0], lenRemaining );

	// inc read pos
	incPos( length, idRead );

	// clear read lock
	m_lock.unlock();


	return true;
}


bool CircularQue::write ( BYTE * data, long length )
{
	// show data block to long
	if ( length < 0 || length > m_queSz )
		return false;

	// wait for write lock
	if ( !m_lock.lock() )
		return false;

	// read length to que end
	long lenToEnd = lengthToEnd(idWrite);

	// copy to end of buffer
	if ( lenToEnd > 0 )
		memcpy( &m_que[m_write], data, lenToEnd );

	// copy remainder to start of buffer
	long lenRemaining = length - lenToEnd;
	if ( lenRemaining > 0 )
		memcpy( &m_que[0], &data[lenToEnd], lenRemaining );

	// inc write pos
	incPos( length, idWrite );

	m_lock.unlock();

	// set recieve event
	m_rxEvent.set();

	return true;
}


bool CircularQue::read ( string & data )
{
	// read if any data availible
	long count;
	if ( !readCount(count) )
		return false;

	// clear string
	data = "";

	// setup buffer
	TCHAR * buf = new TCHAR[count];
	if ( !buf )
		return false;

	memset(buf,0,count);

	// read data
	bool success = read( (BYTE *) buf, count );
	if ( success )
		data = buf;
	
	// release buffer
	delete[] buf;

	return success;
}

bool CircularQue::write ( string & data )
{
	return write( (BYTE *) data.c_str(), data.size() );
}


