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

#include <stdio.h>
#include "example.h"

int main()
{
  data_t i;
  short int test_size = 8;

  data_stream din, dout;
  inst_stream inst;

  printf("=====Stream transpose example START=====\n");

  printf("Input stream: \n");
  // Put data into din Stream
  for(i=0; i < test_size * test_size; i++){
      data_t tmp_in = i;
      din.write(tmp_in);
      printf("%d ", tmp_in);
  }
  printf("\n");

  // Tell hardware the size of the array to be transposed
  inst_t tmp_size;
  tmp_size.data = test_size;
  tmp_size.last = 1;
  inst.write(tmp_size);

  // Call the hardware function
  stream_transpose(din, inst, dout);

  // print the results
  printf("Output stream: \n");
  for(i=0; i < test_size * test_size; i++){
      data_t tmp_out = dout.read();
      printf("%d ", tmp_out);
  }
  printf("\n");
  printf("=====Stream transpose example END=====\n");

  return 0;
}
