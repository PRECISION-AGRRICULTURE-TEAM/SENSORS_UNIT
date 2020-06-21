#ifndef TIMER_CFG_H_
#define TIMER_CFG_H_




#define Tc         1000UL
#define ARR_value  (FREQUENCY/(Tc))
#define PRESCALER   0
#define TIM4_IRQn   30
#define TIM3_IRQn   29
#define MAIN_PRESCALER  1000UL
#define MAIN_ARR_value  (FREQUENCY/(Tc))

#endif /* TIMER_CFG_H_ */

