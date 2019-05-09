//
//  main.cpp
//  NoteReader
//  Created by Sarvesh Bhatnagar
//

#include <iostream>
#include <ApplicationServices/ApplicationServices.h>
#include <fstream>

#define out std::cout
#define endl std::endl

std::ifstream fo;
std::ofstream fw;



void SpeechDoneProc (SpeechChannel chan, long refCon)
{
    DisposeSpeechChannel(chan);
}

void SpeakThisText(const void * text, long size)
{
    SpeechChannel channel;
    NewSpeechChannel (NULL, &channel);
    SpeakText (channel, text, size);
}

int main(int argc, const char * argv[]) {
    fw.open("readme.txt");
    fw<<"hey this is some text \n";
    fw<<"Im glad you are listening";
    fw.close();
    fo.open("readme.txt");
    std::string a;
    while (fo>>a)
    {
        std::string st  = a;
        char * t = &st[0];
        SpeakThisText(t, sizeof(st));
        usleep(570000);
    }
    fo.close();
    
    return 0;
}
