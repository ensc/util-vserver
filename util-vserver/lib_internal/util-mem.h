// $Id$    --*- c -*--

// Copyright (C) 2004 Enrico Scholz <enrico.scholz@informatik.tu-chemnitz.de>
//  
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; version 2 of the License.
//  
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//  
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.


#ifndef H_UTIL_VSERVER_LIB_INTERNAL_UTIL_MEM_H
#define H_UTIL_VSERVER_LIB_INTERNAL_UTIL_MEM_H

#include <string.h>
#include <stdlib.h>

inline static void *
Xmemcpy(void * restrict dst, void const * restrict src, size_t len)
{
  return (char *)(memcpy(dst, src, len))+len;
}

#endif	//  H_UTIL_VSERVER_LIB_INTERNAL_UTIL_MEM_H
