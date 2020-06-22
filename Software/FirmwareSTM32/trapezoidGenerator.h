/**
  ******************************************************************************
  * @file    trapezoidGenerator.h
  * @author  Mace Robotics
  * @version V1.0
  * @date    06/02/2016
  * @brief   trapezoidGenerator
  *
 *******************************************************************************/

#ifndef _TRAPEZOIDGENERATOR_H
#define _TRAPEZOIDGENERATOR_H

#include <stdlib.h>

typedef enum{
TRAPEZOID_DISTANCE_FORWARD = 0,
TRAPEZOID_DISTANCE_BACK,
TRAPEZOID_ORIENTATION_LEFT,
TRAPEZOID_ORIENTATION_RIGHT,
}enum_CreateTrapezoid;

typedef enum{
POSITIF_TRAPEZOID = 0,
NEGATIF_TRAPEZOID,
}enum_typeTrapezoid;


typedef enum{
NO_INIT_STATE = 0,
INIT_STATE,
PROCESS_STATE,  // acceleration phase
END_STATE,
ERROR_STATE
}enum_stateTrapezoid;


typedef struct{
unsigned int consigne;
unsigned int maximum;
float acceleration;
float deceleration;
unsigned int periode;
float time1;
float time2;
float time3;
float acceleration_sample;
enum_stateTrapezoid state;
unsigned int time_trapezoid;
int32_t out_trapezoid;
float distance_out;
enum_typeTrapezoid type;
}struct_trapezoid;


bool trapezoidGenerator_create(enum_CreateTrapezoid Trapezoid, uint32_t consigne, uint32_t speed);


bool trapezoidGenerator_init(struct_trapezoid *trapezoid,
		                     unsigned int consigne,
                             unsigned int maximum,
                             float acceleration,
                             float deceleration,
                             unsigned int periode,
                             enum_typeTrapezoid type
                            );

void trapezoidGenerator_management(void);


//void trapezoidGenerator_manage(struct_trapezoid *trapezoid);
enum_stateTrapezoid trapezoidGenerator_state(enum_CreateTrapezoid Trapezoid);
int32_t trapezoidGenerator_out(enum_CreateTrapezoid Trapezoid);

void trapezoidGenerator_reset(void);

//////////


// trapezoid a duree infini
bool trapezoidInfini_create(enum_CreateTrapezoid Trapezoid, uint32_t speed);


 #endif
// End Of File
