/* free.h
 *
 *    Routine to calculate free RAM for Arduino, from 
 *     Arduino Cookbook by Michael Margolis.
 *
 */

#ifndef FREE_H
#define FREE_H

extern int __bss_end;
extern void *__brkval;

int memoryFree() {
    // From Arduino Cookbook
    int freeValue;
    
    if ((int)__brkval == 0)
        freeValue = ((int)&freeValue) - ((int)&__bss_end);
    else
        freeValue = ((int)&freeValue) - ((int)&__brkval);

    return freeValue;
}
#endif
