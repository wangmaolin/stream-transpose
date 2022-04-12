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

void stream_transpose(data_stream &din, inst_stream &instruction, data_stream &dout){
#pragma HLS INTERFACE axis port=din
#pragma HLS INTERFACE axis port=instruction
#pragma HLS INTERFACE axis port=dout

    data_t localA[MAX_SIZE][MAX_SIZE];

    inst_t array_size;
    
    do {
        // the size of array to be transposed
        array_size = instruction.read();

        for(int i=0; i<array_size.data; i++)
        {
            for(int j=0; j<array_size.data; j++)
            {
                localA[i][j] = din.read(); 
            }
        }

        for(int i=0; i<array_size.data; i++)
        {
            for(int j=0; j<array_size.data; j++)
            {
                dout.write(localA[j][i]); 
            }
        }
    } while (!array_size.last);
}