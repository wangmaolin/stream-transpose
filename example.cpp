/*
 * Copyright 2021 Xilinx, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "example.h"

const int max_trip = MAX_SIZE;

void row_in(data_stream &din,
            inst_stream &instruction,
            data_pack_t column[MAX_SIZE],
            col_stream &ready)
{
row_in_ever_loop:
    do
    {
        inst_t array_size = instruction.read();
        col_idx_t loop_bound = array_size.data;

    row_in_loop_i:
        for (col_idx_t i = 0; i < loop_bound; i++)
        {
 #pragma HLS LOOP_TRIPCOUNT max=max_trip
        row_in_loop_j:
            for (col_idx_t j = 0; j < loop_bound; j++)
            {
 #pragma HLS LOOP_TRIPCOUNT max=max_trip
                data_t v = din.read();
                column[j].data[i] = v;
                if (i == loop_bound-1)
                {
                    ready << loop_bound;
                    ready << j;
                }
            }
        }

        if (array_size.last)
        {
            ready << 0;
            break;
        }

    } while (1);
}

void col_out(data_stream &dout,
             data_pack_t column[MAX_SIZE],
             col_stream &ready)
{
col_out_ever_loop:
    do
    {
        col_idx_t loop_bound = ready.read();

        if (loop_bound == 0)
        {
            break;
        }
 
        col_idx_t col_idx = ready.read();
    col_out_loop_j:
        for (col_idx_t j = 0; j < loop_bound; j++)
        {
 #pragma HLS LOOP_TRIPCOUNT max=max_trip
            data_t v = column[col_idx].data[j];
            dout << v;
        }

    } while (1);
}

void stream_transpose(data_stream &din, inst_stream &instruction, data_stream &dout){
#pragma HLS INTERFACE axis port=din
#pragma HLS INTERFACE axis port=instruction
#pragma HLS INTERFACE axis port=dout

    data_pack_t column[MAX_SIZE];
    col_stream ready; 
    // the size of array to be transposed
#pragma HLS DATAFLOW
    row_in(din, instruction, column, ready);
    col_out(dout, column, ready);
}