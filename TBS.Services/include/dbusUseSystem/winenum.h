/*
 * winenum.h
 *
 *  Created on: 5.6.2014
 *      Author: JV
 */

#ifndef WINENUM_H_
#define WINENUM_H_

#ifdef _WIN32

#define POLLIN		0x001		/* There is data to read.  */
#define POLLPRI		0x002		/* There is urgent data to read.  */
#define POLLOUT		0x004		/* Writing now will not block.  */

#define POLLERR		0x008		/* Error condition.  */
#define POLLHUP		0x010		/* Hung up.  */
#define POLLNVAL	0x020		/* Invalid polling request.  */

#endif

#endif /* WINENUM_H_ */
