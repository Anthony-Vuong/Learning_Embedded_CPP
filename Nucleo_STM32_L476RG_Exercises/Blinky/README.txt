Blinky_1 contains the source code to blink an LED(LD2) on the Nucleo STM32lg476rg board.
This source code use defining base and offset as global variable to access registers.

Blinky_2 contains the source code to blink an LED(LD2) on the Nucleo STM32lg476rg board.
The source code here, use typedef structs to get rid of some of the defines, and instead use
typedef structs for GPIOA and RCC(Reset Clock Control).

Blinky_2 contains the source code to blink an LED(LD2) on the Nucleo STM32lg476rg board.
Similar to v1 and v2, but instead we've added include header files from the MCU Package from
st.com and have them as resource in our projects. The source code we have to implement is
further reduced and much more readable.