#pragma once
#ifndef INFLATOR_H
#define INFLATOR_H

#include "zlib.h"
#include <vector>
typedef std::vector<char> v_char;

class Inflator
{
public:
	Inflator();
	~Inflator();
	void reset();
	int inf(const v_char& in, v_char& out);
	bool is_done();
private:
	z_stream _strm;
	bool _ready;
};

#endif // INFLATOR_H