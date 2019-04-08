#ifndef __UDS_H_
#define __UDS_H_
#include "main.h"
#define  QUESIZE 20
//获取队列数据个数
#define __QUE_COUNT(PQUE) (((PQUE)->rear - (PQUE)->front + QUESIZE) % QUESIZE)
typedef struct {
  uint8_t data[QUESIZE];
  uint8_t front;
  uint8_t rear;
}CircleQue_TypeDef;

void Que_Init(CircleQue_TypeDef * pq);
uint8_t Que_In(CircleQue_TypeDef * pq, uint8_t c);
uint8_t Que_Out(CircleQue_TypeDef * pq, uint8_t *c);
uint8_t Que_Query(CircleQue_TypeDef * pq, uint8_t *c);
#endif
