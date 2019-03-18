#pragma once
static char* cameraData;
void do_AI_algoritm(){
    if(Camera->dataAnvailable()){
          cameraData = Camera->ReadData(); // will also sand a confirmation
    }

}