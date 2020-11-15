#pragma once
#include "stdafx.h"
#include <WINSOCK2.H>   
#include <stdio.h>     
#include<iostream>
#include<string>

#define PORT           6000         //服务器的端口号      
#define MSGSIZE        1024*10*10        //收发缓冲区的大小 
 
using namespace std;
void snd_to_srv(CString str);