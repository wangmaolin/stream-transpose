#include "example.h"

void stream_transpose(data_stream &din,
                      inst_stream &instruction, 
                      data_stream &dout) 
{
#pragma HLS INTERFACE axis port=din
#pragma HLS INTERFACE axis port=instruction
#pragma HLS INTERFACE axis port=dout
    data_t buf[MAX_SIZE][MAX_SIZE];
// #pragma HLS ARRAY_PARTITION variable=buf type=complete dim=0
    inst_t array_size;
    do {
        array_size = instruction.read();
        idx_t size = array_size.data;
        for(idx_t i=0; i<2*size-1; i++)
        {
    transpose_loop:
            for(idx_t j=0; j<size; j++)
            {
#pragma HLS PIPELINE II=1
                if(i<size)
                {
                    buf[i][j]=din.read();
                }

                if(i>size-2)
                {
                    dout<<buf[j][i+1-size];
                }
            }
        }
    } while(!array_size.last);
}