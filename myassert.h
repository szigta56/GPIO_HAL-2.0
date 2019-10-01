/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef MYASSERT_H
#define MYASSERT_H
#include <stdint.h>
    
typedef int8_t status_t;

#include "mygpio.h"

//**********************************ERROR CODES********************************

#define  NO_ERROR                   ( 0)
#define  INCORRECT_PIN              (-1)
#define  INCORRECT_CHANNEL          (-2)
#define  INCORRECT_PORT_ADDRESS     (-3)
#define  INCORRECT_INTERRUPT_TYPE   (-4)
#define  INCORRECT_DIRECTION        (-5)
#define  INCORRECT_VALUE            (-6)
#define  INCORRECT_DRIVEMODE        (-7)

//**********************************ASSERT MACROS FOR ERROR HANDLING********************************

#define ASSERT_PORT(port)    		(!((PORT0==port) | (PORT6==port) | (PORT7==port)))
#define ASSERT_PIN(pinNum)          (!((PIN3==pinNum) | (PIN1==pinNum) | (PIN4==pinNum)))
#define ASSERT_VALUE(value)         (!((value==PIN_HIGH) | (value==PIN_LOW)))
#define ASSERT_INTERRUPT(type)      (!((type==INTR_NONE) | (type==INTR_RISING) | (type==INTR_FALLING) | (type==INTR_BOTH)))
#define ASSERT_DIRECTION(direction) (!((direction==OUTPUT)| (direction==INPUT)))
#define ASSERT_DRIVEMODE(drive)     (!((drive==HIGH_IMPEDANCE) | (drive==RES_PULL_UP) | (drive==RES_PULL_DOWN) | (drive==OPN_DRAIN_LOW)|\
                                    (drive==OPN_DRAIN_HIGH) | (drive==STRONG_DRIVE) | (drive==RES_PULL_UPDOWN)))          

#endif

/* [] END OF FILE */
