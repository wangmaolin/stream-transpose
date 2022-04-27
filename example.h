#include "ap_axi_sdata.h"
#include "hls_stream.h"

#define MAX_SIZE 16

// typedef hls::axis<ap_uint<8>, 0, 0, 0> data_t;
typedef short data_t;
typedef hls::stream<data_t> data_stream;

typedef ap_uint<16> col_idx_t;
typedef hls::stream<col_idx_t> col_stream;

typedef hls::axis<col_idx_t, 0, 0, 0> inst_t;
typedef hls::stream<inst_t> inst_stream;

typedef struct pack_datatype { data_t data[MAX_SIZE]; } data_pack_t;

extern void stream_transpose(data_stream &din, inst_stream &instruction, data_stream &dout);