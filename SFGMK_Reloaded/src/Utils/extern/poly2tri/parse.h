//-------------------------------------------------------------------------/
//Copyright (C) 2003, 2004, 2005, ALL RIGHTS RESERVED.
//Centre for Sys. Eng. & App. Mech.           FEMAGSoft S.A.
//Universite Cathalique de Louvain            4, Avenue Albert Einstein
//Batiment Euler, Avenue Georges Lemaitre, 4  B-1348 Louvain-la-Neuve
//B-1348, Louvain-la-Neuve                    Belgium
//Belgium
//-------------------------------------------------------------------------/
//
//Name:         parse.h ( parse command lines options with help and copyright
//                        information )
//Author:       Liang, Wu (wu@mema.ucl.ac.be, wuliang@femagsoft.com)
//Created:      11/2005
//-------------------------------------------------------------------------/

#ifndef  _PARSE_H
#define  _PARSE_H

#include <string>
#include <iostream>

namespace p2t
{
	class Options
	{
		public:
		Options() :parsebdm(true), showme(false), tecplot(false), metapost(true), debug(false), fileindex(1)
		{
		}

		bool parsebdm, showme, tecplot, metapost, debug;
		int  fileindex;
	};

	void help();

	void parse(int argc, char **argv, Options& options);
}

#endif

