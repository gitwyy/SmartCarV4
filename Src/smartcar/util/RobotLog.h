//
// Created by wangyangyang on 2021-04-10.
//

#ifndef SMARTCARV4_ROBOTLOG_H
#define SMARTCARV4_ROBOTLOG_H

/************************ 定义 log *************************/
#include <stdio.h>

#define LOG_ENABLE 0
#define LOG_DEBUG 0
#if LOG_ENABLE
#define loginfo(format, ...) printf(format"\r\n",##__VA_ARGS__)
#else
#define loginfo(format, ...)
#endif

#if LOG_ENABLE & LOG_DEBUG
#define logdebug(format, ...) printf(format"\r\n",##__VA_ARGS__)
#else
#define logdebug(format, ...)
#endif


#endif //SMARTCARV4_ROBOTLOG_H
