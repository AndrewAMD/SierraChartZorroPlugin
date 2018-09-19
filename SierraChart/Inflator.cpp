#include "Inflator.h"

Inflator::Inflator() :
	_ready(false)
{
	reset();
}
Inflator::~Inflator()
{
	inflateEnd(&_strm);
}
void Inflator::reset()
{
	if (_ready)
	{
		inflateEnd(&_strm);
		_ready = false;
	}
	_strm.zalloc = Z_NULL;
	_strm.zfree = Z_NULL;
	_strm.opaque = Z_NULL;
	//_strm.total_out = 0;
	inflateInit(&_strm);
}
int Inflator::inf(const v_char& in, v_char& out)
{
	//v_char out;
	int before = _strm.total_out, after = 0;

	out.resize(in.size() * 20);
	_strm.avail_in = (uInt)in.size(); // size of input
	_strm.next_in = (Bytef *)in.data(); // input char array
	_strm.avail_out = (uInt)out.size(); // size of output
	_strm.next_out = (Bytef *)out.data(); // output char array

										  // the actual DE-compression work.
	int ret = inflate(&_strm, Z_NO_FLUSH);
	//if(_strm.msg)printf("%s\n",_strm.msg);
	after = _strm.total_out;

	out[after - before + 1] = 0; // for testing purposes only
	out.resize(after - before);
	//printf("Uncompressed size is: %lu\n", out.size());
	//printf("Uncompressed string is: %s\n", out.data());
	//printf("inf return value: %d\n", ret);
	switch (ret)
	{
	case Z_OK: // There is more to decompress.  Nothing to do.
		break;
	case Z_STREAM_END:  // We are done.
		_ready = true;
		break;
	case Z_NEED_DICT:
		std::runtime_error("zlib: need dictionary");
		break;
	case Z_ERRNO:
		std::runtime_error("zlib: an unknown error occured");
		break;
	case Z_STREAM_ERROR:
		std::runtime_error("zlib: stream structure was inconsistent");
		break;
	case Z_DATA_ERROR:
		std::runtime_error("zlib: input data was corrupted");
		break;
	case Z_MEM_ERROR:
		std::runtime_error("zlib: not enough memory");
		break;
	case Z_BUF_ERROR:
		std::runtime_error("zlib: no progress is possible");
		break;
	case Z_VERSION_ERROR:
		std::runtime_error("zlib: version error");
		break;
	default:
		std::runtime_error("zlib: received an unknown return code");
	}
	return ret;
}

bool Inflator::is_done()
{
	return _ready;
}

