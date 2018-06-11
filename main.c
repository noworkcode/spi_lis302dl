#include "main.h"


uint8_t main(void)
{        
        init_GPIOA();
        init_GPIOE();
        init_SPI();
        //search();  
                               
        while(1) { 
                search_x();
        }
}
