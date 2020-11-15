#pragma once
#include "stdafx.h"
#include <WINSOCK2.H>   
#include <stdio.h>     
#include<iostream>
#include<string>
using namespace std;
void sendToClient(const string &strMsg, const char *ip);