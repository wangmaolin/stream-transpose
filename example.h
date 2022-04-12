#include <complex>
#include "ap_axi_sdata.h"
#include "hls_stream.h"

#define MAX_SIZE 16

// typedef hls::axis<ap_uint<8>, 0, 0, 0> data_t;
typedef short data_t;
typedef hls::stream<data_t> data_stream;

typedef hls::axis<ap_uint<16>, 0, 0, 0> inst_t;
typedef hls::stream<inst_t> inst_stream;

extern void stream_transpose(data_stream &din, inst_stream &instruction, data_stream &dout);