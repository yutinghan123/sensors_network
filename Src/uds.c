#include "uds.h"
//队列初始化
void Que_Init(CircleQue_TypeDef * pq)
{
  pq->front = pq->rear = 0;
}
//入队
uint8_t Que_In(CircleQue_TypeDef * pq, uint8_t c)
{
  pq->data[pq->rear] = c;
  pq->rear = (pq->rear + 1) % QUESIZE;
  if (pq->front == pq->rear)
    pq->front = (pq->front + 1) % QUESIZE;
  return 1;
}
//出队
uint8_t Que_Out(CircleQue_TypeDef * pq, uint8_t *c)
{
  if (pq->front == pq->rear) {
    return 0;
  }
  *c = pq->data[pq->front];
  pq->front = (pq->front + 1) % QUESIZE;
  return 1;
}
//查询队列：取出对头，但不删除
uint8_t Que_Query(CircleQue_TypeDef * pq, uint8_t *c)
{
  if (pq->front == pq->rear) {
    return 0;
  }
  *c = pq->data[pq->front];
  return 1;
}
