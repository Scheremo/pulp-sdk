/*
 * Copyright (C) 2020 ETH Zurich, University of Bologna and GreenWaves Technologies
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Authors:  Francesco Conti <fconti@iis.ee.ethz.ch>
 *           Gianna Paulin <pauling@iis.ee.ethz.ch>
 *           Renzo Andri <andrire@iis.ee.ethz.ch>
 * Main Test Program for the NEUREKA
 */

#include "pmsis.h"
#include "pmsis/cluster/dma/cl_dma.h"
#include <stdint.h>
#include <stdio.h>

#include "hal_neureka.h"

#include "streamin_fs1_output_64x16x16_input_32x16x16/inc/ne16_cfg.h"
#include "streamin_fs1_output_64x16x16_input_32x16x16/inc/ne16_infeat.h"
#include "streamin_fs1_output_64x16x16_input_32x16x16/inc/ne16_weights.h"
#include "streamin_fs1_output_64x16x16_input_32x16x16/inc/ne16_scale.h"
#include "streamin_fs1_output_64x16x16_input_32x16x16/inc/ne16_scale_bias.h"
#include "streamin_fs1_output_64x16x16_input_32x16x16/inc/ne16_scale_shift.h"
#include "streamin_fs1_output_64x16x16_input_32x16x16/inc/ne16_streamin.h"
#include "streamin_fs1_output_64x16x16_input_32x16x16/inc/ne16_outfeat.h"

#include "no_normquant_stride2_output_64x16x16_input_64x32x32/inc/ne16_cfg.h"
#include "no_normquant_stride2_output_64x16x16_input_64x32x32/inc/ne16_infeat.h"
#include "no_normquant_stride2_output_64x16x16_input_64x32x32/inc/ne16_weights.h"
#include "no_normquant_stride2_output_64x16x16_input_64x32x32/inc/ne16_scale.h"
#include "no_normquant_stride2_output_64x16x16_input_64x32x32/inc/ne16_scale_bias.h"
#include "no_normquant_stride2_output_64x16x16_input_64x32x32/inc/ne16_scale_shift.h"
#include "no_normquant_stride2_output_64x16x16_input_64x32x32/inc/ne16_streamin.h"

#include "avgpool_fs3_dw_output_64x32x32_input_64x32x32/inc/ne16_cfg.h"
#include "avgpool_fs3_dw_output_64x32x32_input_64x32x32/inc/ne16_infeat.h"
#include "avgpool_fs3_dw_output_64x32x32_input_64x32x32/inc/ne16_weights.h"
#include "avgpool_fs3_dw_output_64x32x32_input_64x32x32/inc/ne16_scale.h"
#include "avgpool_fs3_dw_output_64x32x32_input_64x32x32/inc/ne16_scale_bias.h"
#include "avgpool_fs3_dw_output_64x32x32_input_64x32x32/inc/ne16_scale_shift.h"
#include "avgpool_fs3_dw_output_64x32x32_input_64x32x32/inc/ne16_streamin.h"

#include "padding_1111_fs3_output_32x16x16_input_32x16x16/inc/ne16_cfg.h"
#include "padding_1111_fs3_output_32x16x16_input_32x16x16/inc/ne16_infeat.h"
#include "padding_1111_fs3_output_32x16x16_input_32x16x16/inc/ne16_weights.h"
#include "padding_1111_fs3_output_32x16x16_input_32x16x16/inc/ne16_scale.h"
#include "padding_1111_fs3_output_32x16x16_input_32x16x16/inc/ne16_scale_bias.h"
#include "padding_1111_fs3_output_32x16x16_input_32x16x16/inc/ne16_scale_shift.h"
#include "padding_1111_fs3_output_32x16x16_input_32x16x16/inc/ne16_streamin.h"

#include "stride2_fs1_output_32x16x16_input_64x32x32/inc/ne16_cfg.h"
#include "stride2_fs1_output_32x16x16_input_64x32x32/inc/ne16_infeat.h"
#include "stride2_fs1_output_32x16x16_input_64x32x32/inc/ne16_weights.h"
#include "stride2_fs1_output_32x16x16_input_64x32x32/inc/ne16_scale.h"
#include "stride2_fs1_output_32x16x16_input_64x32x32/inc/ne16_scale_bias.h"
#include "stride2_fs1_output_32x16x16_input_64x32x32/inc/ne16_scale_shift.h"
#include "stride2_fs1_output_32x16x16_input_64x32x32/inc/ne16_streamin.h"


#define NB_ITER 10

static int glob_errors;

#define WEIGHT_MEM_BASE 0x10400000
#define SRAM_OFFSET 0x00000000
#define MRAM_OFFSET 0x00400000

int run_test() {

  // uint8_t* W0l        = ne16_weights_stride2;
  uint8_t* nq0l       = ne16_scale_stride2;
  uint8_t* nqs0l      = ne16_scale_shift_stride2;
  uint8_t* nqb0l      = ne16_scale_bias_stride2;
  uint8_t* actual_y0l = ne16_streamin_stride2;

  // uint8_t* x1l        = ne16_cfg_padding;
  // uint8_t* W1l        = ne16_weights_padding;
  uint8_t* nq1l       = ne16_scale_padding;
  uint8_t* nqs1l      = ne16_scale_shift_padding;
  uint8_t* nqb1l      = ne16_scale_bias_padding;
  uint8_t* actual_y1l = ne16_streamin_padding;

  uint8_t* x0        = ne16_infeat_avgpool;
  uint8_t* W0        = ne16_weights_avgpool;
  uint8_t* nq0       = ne16_scale_avgpool;
  uint8_t* nqs0      = ne16_scale_shift_avgpool;
  uint8_t* nqb0      = ne16_scale_bias_avgpool;
  uint8_t* actual_y0 = ne16_streamin_avgpool;

  // uint8_t* x1        = ne16_infeat_no_normquant;
  // uint8_t* W1        = ne16_weights_no_normquant;
  uint8_t* nq1       = ne16_scale_no_normquant;
  uint8_t* nqs1      = ne16_scale_shift_no_normquant;
  uint8_t* nqb1      = ne16_scale_bias_no_normquant;
  uint8_t* actual_y1 = ne16_streamin_no_normquant;

  // uint8_t* x2        = ne16_infeat_streamin;
  // uint8_t* W2        = ne16_weights_streamin;
  uint8_t* nq2       = ne16_scale_streamin;
  uint8_t* nqs2      = ne16_scale_shift_streamin;
  uint8_t* nqb2      = ne16_scale_bias_streamin;


  // enable clock
  NEUREKA_CG_ENABLE();

  // setup HCI
  NEUREKA_SETPRIORITY_NEUREKA();
  NEUREKA_RESET_MAXSTALL();
  NEUREKA_SET_MAXSTALL(8);

  // soft-clear NEUREKA
  NEUREKA_WRITE_CMD(NEUREKA_SOFT_CLEAR, NEUREKA_SOFT_CLEAR_ALL);
  for(volatile int kk=0; kk<10; kk++);
// /*
  // program NEUREKA
  int job_id = -1;
  NEUREKA_BARRIER_ACQUIRE(job_id);
  NEUREKA_WRITE_REG(NEUREKA_REG_WEIGHTS_PTR,     NEUREKA_REG_WEIGHTS_PTR+WEIGHT_MEM_BASE+sizeof(ne16_weights_no_normquant)+sizeof(ne16_weights_avgpool)+sizeof(ne16_weights_streamin));
  NEUREKA_WRITE_REG(NEUREKA_REG_INFEAT_PTR,      x0);
  NEUREKA_WRITE_REG(NEUREKA_REG_OUTFEAT_PTR,     actual_y0l);
  NEUREKA_WRITE_REG(NEUREKA_REG_SCALE_PTR,       nq0l);
  NEUREKA_WRITE_REG(NEUREKA_REG_SCALE_SHIFT_PTR, nqs0l);
  NEUREKA_WRITE_REG(NEUREKA_REG_SCALE_BIAS_PTR,  nqb0l);
  for(int i=6; i<24; i++) {
    NEUREKA_WRITE_REG(i*4, ne16_cfg_stride2[i]);
  }

  // configure & reset perf counters
  pi_perf_conf(1 << PI_PERF_CYCLES);
  pi_perf_reset();

  // fake register access for trace level -- only GVSOC!
  NEUREKA_WRITE_REG(NEUREKA_SPECIAL_TRACE_REG, NEUREKA_L3_ALL);

  // start perf counter
  pi_perf_start();
/*
  NEUREKA_WRITE_CMD(NEUREKA_COMMIT_AND_TRIGGER, NEUREKA_TRIGGER_CMD);
  

  NEUREKA_BARRIER_ACQUIRE(job_id);
  NEUREKA_WRITE_REG(NEUREKA_REG_WEIGHTS_PTR,     NEUREKA_REG_WEIGHTS_PTR+WEIGHT_MEM_BASE+sizeof(ne16_weights_no_normquant)+sizeof(ne16_weights_avgpool)+sizeof(ne16_weights_stride2)+sizeof(ne16_weights_streamin));
  NEUREKA_WRITE_REG(NEUREKA_REG_INFEAT_PTR,      actual_y0l-32*17);//offsetting to help padding 
  NEUREKA_WRITE_REG(NEUREKA_REG_OUTFEAT_PTR,     actual_y1l);
  NEUREKA_WRITE_REG(NEUREKA_REG_SCALE_PTR,       nq1l);
  NEUREKA_WRITE_REG(NEUREKA_REG_SCALE_SHIFT_PTR, nqs1l);
  NEUREKA_WRITE_REG(NEUREKA_REG_SCALE_BIAS_PTR,  nqb1l);
  for(int i=6; i<24; i++) {
    NEUREKA_WRITE_REG(i*4, ne16_cfg_padding[i]);
  }
  NEUREKA_WRITE_CMD(NEUREKA_COMMIT_AND_TRIGGER, NEUREKA_TRIGGER_CMD);

  NEUREKA_BARRIER_ACQUIRE(job_id);
  NEUREKA_WRITE_REG(NEUREKA_REG_WEIGHTS_PTR,     NEUREKA_REG_WEIGHTS_PTR+WEIGHT_MEM_BASE);
  NEUREKA_WRITE_REG(NEUREKA_REG_INFEAT_PTR,      x0);
  NEUREKA_WRITE_REG(NEUREKA_REG_OUTFEAT_PTR,     actual_y0);
  NEUREKA_WRITE_REG(NEUREKA_REG_SCALE_PTR,       nq0);
  NEUREKA_WRITE_REG(NEUREKA_REG_SCALE_SHIFT_PTR, nqs0);
  NEUREKA_WRITE_REG(NEUREKA_REG_SCALE_BIAS_PTR,  nqb0);
  for(int i=6; i<24; i++) {
    NEUREKA_WRITE_REG(i*4, ne16_cfg_avgpool[i]);
  }
  NEUREKA_WRITE_CMD(NEUREKA_COMMIT_AND_TRIGGER, NEUREKA_TRIGGER_CMD);

  NEUREKA_BARRIER_ACQUIRE(job_id);
  NEUREKA_WRITE_REG(NEUREKA_REG_WEIGHTS_PTR,     NEUREKA_REG_WEIGHTS_PTR+WEIGHT_MEM_BASE+sizeof(ne16_weights_avgpool));
  NEUREKA_WRITE_REG(NEUREKA_REG_INFEAT_PTR,      actual_y0);
  NEUREKA_WRITE_REG(NEUREKA_REG_OUTFEAT_PTR,     actual_y1);
  NEUREKA_WRITE_REG(NEUREKA_REG_SCALE_PTR,       nq1);
  NEUREKA_WRITE_REG(NEUREKA_REG_SCALE_SHIFT_PTR, nqs1);
  NEUREKA_WRITE_REG(NEUREKA_REG_SCALE_BIAS_PTR,  nqb1);
  for(int i=6; i<24; i++) {
    NEUREKA_WRITE_REG(i*4, ne16_cfg_no_normquant[i]);
  }
  NEUREKA_WRITE_CMD(NEUREKA_COMMIT_AND_TRIGGER, NEUREKA_TRIGGER_CMD);

  NEUREKA_BARRIER_ACQUIRE(job_id);
  NEUREKA_WRITE_REG(NEUREKA_REG_WEIGHTS_PTR,     NEUREKA_REG_WEIGHTS_PTR+WEIGHT_MEM_BASE+sizeof(ne16_weights_avgpool)+sizeof(ne16_weights_no_normquant));
  NEUREKA_WRITE_REG(NEUREKA_REG_INFEAT_PTR,      actual_y1l);
  NEUREKA_WRITE_REG(NEUREKA_REG_OUTFEAT_PTR,     actual_y1);
  NEUREKA_WRITE_REG(NEUREKA_REG_SCALE_PTR,       nq2);
  NEUREKA_WRITE_REG(NEUREKA_REG_SCALE_SHIFT_PTR, nqs2);
  NEUREKA_WRITE_REG(NEUREKA_REG_SCALE_BIAS_PTR,  nqb2);
  for(int i=6; i<24; i++) {
    NEUREKA_WRITE_REG(i*4, ne16_cfg_streamin[i]);
  }
  NEUREKA_WRITE_CMD(NEUREKA_COMMIT_AND_TRIGGER, NEUREKA_TRIGGER_CMD);
*/
  // wait on barrier
  NEUREKA_BARRIER();

  // stop perf counter
  pi_perf_stop();

  // disable clock
  NEUREKA_CG_DISABLE();

  printf("%d cycles\n", pi_perf_read(PI_PERF_CYCLES));

  // int errors = neureka_compare_int(actual_y, golden_y, STIM_Y_SIZE/4);
  // return errors;
  return 0;
}

static struct pi_cluster_task task[1];
static struct pi_task events[1];

static void pe_entry(void *arg) {
  if(pi_core_id() == 0) {
    glob_errors = run_test();
  }
  pi_cl_team_barrier();
}

static void cluster_entry(void *arg) {
  pi_cl_team_fork(0, pe_entry, 0);
}

static int launch_cluster_task() {
  struct pi_device cluster_dev;
  struct pi_cluster_conf conf;
  struct pi_cluster_task task;

  pi_cluster_conf_init(&conf);
  conf.id = 0;
  glob_errors = 0;

  pi_open_from_conf(&cluster_dev, &conf);
  pi_cluster_open(&cluster_dev);

  pi_cluster_task(&task, cluster_entry, NULL);
  pi_cluster_send_task_to_cl(&cluster_dev, &task);
  pi_cluster_close(&cluster_dev);

  return glob_errors;
}

int test_entry() { 
  uint8_t* W0l       = ne16_weights_stride2;
  uint8_t* W1l       = ne16_weights_padding;
  uint8_t* W0        = ne16_weights_avgpool;
  uint8_t* W1        = ne16_weights_no_normquant;
  uint8_t* W2        = ne16_weights_streamin;

  uint32_t* weight_start_ptr = WEIGHT_MEM_BASE; 
  memcpy(weight_start_ptr,(uint32_t*)ne16_weights_avgpool,sizeof(ne16_weights_avgpool));
  
  weight_start_ptr = WEIGHT_MEM_BASE+SRAM_OFFSET+sizeof(ne16_weights_avgpool); 
  memcpy(weight_start_ptr,(uint32_t*)ne16_weights_no_normquant,sizeof(ne16_weights_no_normquant));
  
  weight_start_ptr = WEIGHT_MEM_BASE+SRAM_OFFSET+sizeof(ne16_weights_no_normquant)+sizeof(ne16_weights_avgpool); 
  memcpy(weight_start_ptr,(uint32_t*)ne16_weights_streamin,sizeof(ne16_weights_streamin));

  weight_start_ptr = WEIGHT_MEM_BASE+SRAM_OFFSET+sizeof(ne16_weights_no_normquant)+sizeof(ne16_weights_avgpool)+sizeof(ne16_weights_streamin); 
  memcpy(weight_start_ptr,(uint32_t*)ne16_weights_stride2,sizeof(ne16_weights_stride2));

  weight_start_ptr = WEIGHT_MEM_BASE+SRAM_OFFSET+sizeof(ne16_weights_no_normquant)+sizeof(ne16_weights_avgpool)+sizeof(ne16_weights_stride2)+sizeof(ne16_weights_streamin); 
  memcpy(weight_start_ptr,(uint32_t*)ne16_weights_padding,sizeof(ne16_weights_padding));


  volatile int errors = launch_cluster_task();
  
  if (errors)
    printf("Test failure\n");
  else
    printf("Test success\n");
  return errors;
}

void test_kickoff(void *arg) {
  int ret = test_entry();
  pmsis_exit(ret);
}

int main() {
  return pmsis_kickoff((void *)test_kickoff);
}
