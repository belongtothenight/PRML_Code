#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "signal_handler.h"
#include "output_format.h"

void sig_SIGHUP_handler(int signum){
    output_format format;
    get_format(&format);
    printf("%sSIGHUP received.\n", format.status.warning);
    return;
}

void sig_SIGINT_handler(int signum){
    output_format format;
    get_format(&format);
    printf("%sSIGINT received.\n", format.status.warning);
    exit(1);
    return;
}

void sig_SIGQUIT_handler(int signum){
    output_format format;
    get_format(&format);
    printf("%sSIGQUIT received.\n", format.status.warning);
    return;
}

void sig_SIGILL_handler(int signum){
    output_format format;
    get_format(&format);
    printf("%sSIGILL received.\n", format.status.warning);
    return;
}

void sig_SIGTRAP_handler(int signum){
    output_format format;
    get_format(&format);
    printf("%sSIGTRAP received.\n", format.status.warning);
    return;
}

void sig_SIGABRT_handler(int signum){
    output_format format;
    get_format(&format);
    printf("%sSIGABRT received.\n", format.status.warning);
    return;
}

void sig_SIGFPE_handler(int signum){
    output_format format;
    get_format(&format);
    printf("%sSIGFPE received.\n", format.status.warning);
    return;
}


void sig_SIGSEGV_handler(int signum){
    output_format format;
    get_format(&format);
    printf("%sSIGSEGV received.\n", format.status.warning);
    return;
}

void sig_SIGTERM_handler(int signum){
    output_format format;
    get_format(&format);
    printf("%sSIGTERM received.\n", format.status.warning);
    return;
}

void register_all_signal_handlers(){
    // signal(SIGHUP, sig_SIGHUP_handler);
    signal(SIGINT, sig_SIGINT_handler);
    // signal(SIGQUIT, sig_SIGQUIT_handler);
    signal(SIGILL, sig_SIGILL_handler);
    // signal(SIGTRAP, sig_SIGTRAP_handler);
    signal(SIGABRT, sig_SIGABRT_handler);
    signal(SIGFPE, sig_SIGFPE_handler);
    signal(SIGSEGV, sig_SIGSEGV_handler);
    signal(SIGTERM, sig_SIGTERM_handler);
    return;
}
