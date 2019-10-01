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
#include "mygpio.h"

status_t GPIO_Init (const GPIO_CFG_t *const Config)
{   
    uint8_t i;
    status_t ret;
    volatile uint32_t data;
    volatile PORT_REG_t* port;
    volatile uint8_t pinNum;
    volatile uint8_t drive;
    volatile uint8_t interrupt;
    volatile uint8_t direction;
    volatile uint8_t state;
    
      for (i=0;i<CONFIG_ELEMENTS;i++)
    {
        port = Config[i].Port;
        pinNum  = Config[i].Pin;
        drive = Config[i].DriveMode;
        interrupt = Config [i].Interrupt;
        direction = Config[i].Direction;
        state = Config[i].State;

        if(ASSERT_PORT(port)) ret = INCORRECT_PORT_ADDRESS;
        else
        {
            if(ASSERT_PIN(pinNum))
            {
                ret = INCORRECT_PIN;
                break;
            }
            else
            {
                if(ASSERT_DRIVEMODE(drive)) 
                {
                    ret = INCORRECT_DRIVEMODE;
                    break;
                }
                else
                {
                    if(ASSERT_INTERRUPT(interrupt)) 
                    {
                         ret = INCORRECT_INTERRUPT_TYPE;
                         break;
                    }
                   
                    else
                    {
                        if(ASSERT_DIRECTION(direction)) 
                        {
                            ret = INCORRECT_DIRECTION;
                            break;
                        }
                        else
                        {
                            if(ASSERT_VALUE(state)) 
                            {
                                ret = INCORRECT_VALUE;
                                break;
                            }
                            
                            else
                            {
                                ret = NO_ERROR;
                                if( direction== OUTPUT)
                                { 
                                    port->CFG_REG &= ~(1 << (pinNum*4+3));
                                    if(state==PIN_LOW) port->OUT_REG |= 1<<pinNum;
                                    else if(state==PIN_HIGH)  port->OUT_REG &= ~(1<<pinNum);
                                }
                                else 
                                {  
                                    port->CFG_REG |= 1 <<(pinNum*4+3);
                                    port->OUT_REG |= 1<<pinNum;
                                }
                                data=0;
                                switch (drive)
                                {   
                                
                                    case HIGH_IMPEDANCE:
                                                        port->CFG_REG &= ~(7 << (pinNum*4));
                                                        break;
                                    case RES_PULL_UP:   
                                                        port->CFG_REG |= drive << (pinNum*4);
                                                        break;
                                    case RES_PULL_DOWN:
                                                        port->CFG_REG |= drive << (pinNum*4);
                                                        break;
                                    case OPN_DRAIN_LOW: 
                                                        port->CFG_REG |= drive << (pinNum*4);
                                                        break;
                                    case OPN_DRAIN_HIGH:
                                                        port->CFG_REG |= drive << (pinNum*4);
                                                        break;
                                    case STRONG_DRIVE:
                                                        port->CFG_REG |= drive << (pinNum*4);
                                                        break;
                                    case RES_PULL_UPDOWN:
                                                        port->CFG_REG |= drive << (pinNum*4);
                                                        break;               
                                }
                                switch (interrupt)
                                {
                                    case INTR_NONE:
                                                    port->INTR_MASK_REG &= ~(1<<pinNum);
                                                    port->INTR_CFG_REG  &= ~(1<<pinNum*2);
                                    break;
                                    
                                    case INTR_RISING:
                                                    port->INTR_MASK_REG |= 1<<pinNum;
                                                    port->INTR_CFG_REG  |= interrupt<(pinNum*2);
                                    break;
                                    
                                    case INTR_FALLING:
                                                    port->INTR_MASK_REG |= 1<<pinNum;
                                                    port->INTR_CFG_REG  |= interrupt<<(pinNum*2);
                                    break;
                                    
                                    case INTR_BOTH:
                                                    port->INTR_MASK_REG |= 1<<pinNum;
                                                    port->INTR_CFG_REG  |= interrupt<<(pinNum*2);
                                    break;
                                }
                            }
                        }     
                    }     
                 }    
            }      
        }        
    }  
    return ret;
}

status_t GPIO_Write(PORT_REG_t *port, uint8_t pinNum, uint8_t value )
{   
    status_t ret;
    if(ASSERT_PORT(port)) ret = INCORRECT_PORT_ADDRESS;
    else
    {
        if(ASSERT_PIN(pinNum)) ret = INCORRECT_PIN;
        else
        {
            if(ASSERT_VALUE(value)) ret = INCORRECT_VALUE;
            else
            {
                    ret = NO_ERROR;
                    uint32_t tempReg = 1<<pinNum;
                    if((1 == value) && !(port->IN_STATE_REG & tempReg)) port->OUT_CLR_REG |= 1 << pinNum;   // Writing 1 to the output (because of the opposite logic of register structure)
                    else    port->OUT_SET_REG |= 1 << pinNum;   // Writing 0 to the output 
            }      
        } 
    }
    return ret;     
}

uint8_t GPIO_Read(PORT_REG_t *port, uint8_t pinNum)
{
    uint32_t tempReg;
    uint32_t pinNumMask;
    status_t ret;

    if(ASSERT_PORT(port)) ret = INCORRECT_PORT_ADDRESS;
    else
    {
        if(ASSERT_PIN(pinNum)) ret = INCORRECT_PIN;
        else
        {
            if(port->IN_STATE_REG & (1<<(pinNum+16))) 
            {
                tempReg = port->IN_STATE_REG;
                pinNumMask= 1<<(pinNum+16);
                ret = ((tempReg & pinNumMask)? PIN_HIGH:PIN_LOW);
            }
            else
            {
                pinNumMask = 1<<pinNum;
                tempReg = port->OUT_REG;
                ret = ((tempReg & pinNumMask)? PIN_LOW:PIN_HIGH);
            }
        } 
    }
    return ret; 
}

status_t GPIO_SetDirection(PORT_REG_t *port,uint8_t pinNum,uint8_t direction)
{
    status_t ret;
    if(ASSERT_PORT(port)) ret = INCORRECT_PORT_ADDRESS;
    else
    {
        if(ASSERT_PIN(pinNum)) ret = INCORRECT_PIN;
        else
        {
           if(ASSERT_DIRECTION(direction)) ret = INCORRECT_DIRECTION;
           else
           {
               ret = NO_ERROR;
               if(direction==INPUT) 
                {
                    port->CFG_REG |= 1 << (pinNum*4+3);
                    port->OUT_REG |= 1<<pinNum;
                }
                else if(direction==OUTPUT)
                {
                    port->CFG_REG &= ~(1 << ((pinNum*4)+3));
                }
           }      
        } 
    }
    return ret;     
}

status_t GPIO_SetDriveMode(PORT_REG_t *port,uint8_t pinNum,Drive_mode_t drive)
{
    status_t ret;
    if(ASSERT_PORT(port)) ret = INCORRECT_PORT_ADDRESS;
    else
    {
        if(ASSERT_PIN(pinNum)) ret = INCORRECT_PIN;
        else
        {
           if(ASSERT_DRIVEMODE(drive)) ret = INCORRECT_DRIVEMODE;
           else
           {
               ret = NO_ERROR;
               switch (drive)
                {   
                    case HIGH_IMPEDANCE:
                                        port->CFG_REG &= ~(7 << (pinNum*4));
                                        break;
                    case RES_PULL_UP:   
                                        port->CFG_REG |= drive << (pinNum*4);
                                        break;
                    case RES_PULL_DOWN:
                                        port->CFG_REG |= drive << (pinNum*4);
                                        break;
                    case OPN_DRAIN_LOW:
                                        port->CFG_REG |= drive << (pinNum*4);
                                        break;
                    case OPN_DRAIN_HIGH:                              
                                        port->CFG_REG |= drive << (pinNum*4);
                                        break;
                    case STRONG_DRIVE:
                                        port->CFG_REG |= drive << (pinNum*4);
                                        break;
                    case RES_PULL_UPDOWN:
                                        port->CFG_REG |= drive << (pinNum*4);
                                        break;               
                }
           }      
        } 
    }
    return ret;     
}

status_t GPIO_EnableInterrupt(PORT_REG_t *port,uint8_t pinNum)
{
    status_t ret;
    if(ASSERT_PORT(port)) ret = INCORRECT_PORT_ADDRESS;
    else
    {
        if(ASSERT_PIN(pinNum)) ret = INCORRECT_PIN;
        else
        {
            ret = NO_ERROR;
            port->INTR_MASK_REG |= 1<<pinNum;
        } 
    }
    return ret; 
}

status_t GPIO_DisableInterrupt(PORT_REG_t *port,uint8_t pinNum)
{
    status_t ret;
    if(ASSERT_PORT(port)) ret = INCORRECT_PORT_ADDRESS;
    else
    {
        if(ASSERT_PIN(pinNum)) ret = INCORRECT_PIN;
        else
        {
            ret = NO_ERROR;
            port->INTR_MASK_REG &= ~(1<<pinNum);
        } 
    }
    return ret; 
}

status_t GPIO_SetInterruptType(PORT_REG_t *port,uint8_t pinNum,Intr_mode_t type)
{
    status_t ret;
    if(ASSERT_PORT(port)) ret = INCORRECT_PORT_ADDRESS;
    else
    {
        if(ASSERT_PIN(pinNum)) ret = INCORRECT_PIN;
        else
        {
            ret = NO_ERROR;
            port->INTR_CFG_REG |= type<<(pinNum*2);
        } 
    }
    return ret;
}

status_t GPIO_CLearInterrupt(PORT_REG_t *port,uint8_t pinNum)
{
    status_t ret;
    if(ASSERT_PORT(port)) ret = INCORRECT_PORT_ADDRESS;
    else
    {
        if(ASSERT_PIN(pinNum)) ret = INCORRECT_PIN;
        else
        {
            ret = NO_ERROR;
            port->INTR_REG  |= 1<<pinNum;
        }
    }
    return ret;
}

/* [] END OF FILE */
