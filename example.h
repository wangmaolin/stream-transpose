#include "ap_axi_sdata.h"
#include "hls_stream.h"
#include "hls_streamofblocks.h"

#define MAX_SIZE 16

typedef short data_t;
typedef hls::stream<data_t> data_stream;

typedef ap_uint<16> idx_t;
typedef hls::axis<idx_t, 0, 0, 0> inst_t;
typedef hls::stream<inst_t> inst_stream;

typedef struct pack_datatype { data_t data[MAX_SIZE]; } data_pack_t;
typedef hls::stream<data_pack_t> col_stream;

extern void stream_transpose(data_stream &din, inst_stream &instruction, data_stream &dout);