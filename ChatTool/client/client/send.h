#pragma once
#include "stdafx.h"
#include <WINSOCK2.H>   
#include <stdio.h>     
#include<iostream>
#include<string>

#define PORT           6000         //�������Ķ˿ں�      
#define MSGSIZE        1024*10*10        //�շ��������Ĵ�С 
 
using namespace std;
void snd_to_srv(CString str);