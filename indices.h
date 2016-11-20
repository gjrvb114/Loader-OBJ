#pragma once

#include "includes.h"

class indices
{
	private:
		GLint v;
		GLint vt;
		GLint vn;
	public:
		indices():v(0), vt(0), vn(0){}
		indices(std::ifstream& fichier){fichier >> v >> vt >> vn;}
		void setv(GLint _v){v=_v;}
		void setvt(GLint _vt){vt=_vt;}
		void setvn(GLint _vn){vn=_vn;}
		GLint getv(){return v;}
		GLint getvt(){return vt;}
		GLint getvn(){return vn;}
};