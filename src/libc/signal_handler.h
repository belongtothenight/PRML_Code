/**
 * @file signal_handler.h
 * @brief Defines custom signal handler.
 * Ref:
 * 1. https://stackoverflow.com/questions/554138/catching-segfaults-in-c
 * 2. https://linuxhint.com/signal_handlers_c_programming_language/
 * 3. https://phoenixnap.com/kb/sigsegv
 * 4. https://www.ibm.com/docs/en/aix/7.2?topic=management-process-termination
 * 5. https://chromium.googlesource.com/chromiumos/docs/+/master/constants/signals.md
*/

#ifndef SIGNAL_HANDLER_H
#define SIGNAL_HANDLER_H

#include <signal.h>

/**
 * @brief Handler for SIGHUP signal. (0x01)
 * @param signum Signal number.
 * @return void
 * Hang-up the process. The SIGHUP signal is used to report disconnection of the user’s terminal, possibly because a remote connection is lost or hangs up.
*/
void sig_SIGHUP_handler(int signum);

/**
 * @brief Handler for SIGINT signal. (0x02)
 * @param signum Signal number.
 * @return void
 * Interrupt the process. When the user types the INTR character (normally Ctrl + C) the SIGINT signal is sent.
*/
void sig_SIGINT_handler(int signum);

/**
 * @brief Handler for SIGQUIT signal. (0x03)
 * @param signum Signal number.
 * @return void
 * Quit the process. When the user types the QUIT character (normally Ctrl + \) the SIGQUIT signal is sent.
*/
void sig_SIGQUIT_handler(int signum);

/**
 * @brief Handler for SIGILL signal. (0x04)
 * @param signum Signal number.
 * @return void
 * Illegal instruction. When an attempt is made to execute garbage or privileged instruction, the SIGILL signal is generated. Also, SIGILL can be generated when the stack overflows, or when the system has trouble running a signal handler.
*/
void sig_SIGILL_handler(int signum);

/**
 * @brief Handler for SIGTRAP signal. (0x05)
 * @param signum Signal number.
 * @return void
 * Trace trap. A breakpoint instruction and other trap instruction will generate the SIGTRAP signal. The debugger uses this signal.
*/
void sig_SIGTRAP_handler(int signum);

/**
 * @brief Handler for SIGABRT signal. (0x06)
 * @param signum Signal number.
 * @return void
 * Abort. The SIGABRT  signal is generated when abort() function is called. This signal indicates an error that is detected by the program itself and reported by the abort() function call.
*/
void sig_SIGABRT_handler(int signum);

/**
 * @brief Handler for SIGFPE signal. (0x08)
 * @param signum Signal number.
 * @return void
 * Floating-point exception. When a fatal arithmetic error occurred the SIGFPE signal is generated.
*/
void sig_SIGFPE_handler(int signum);

/**
 * @brief Handler for SIGSEGV signal. (0x0B)
 * @param signum Signal number.
 * @return void
 * Signal 11, also known as SIGSEGV (signal segmentation violation) is an error signal in Unix systems (Linux). The error appears when a program or code tries to access an invalid memory location. The operating system sends the signal 11 error to the program as a response.
*/
void sig_SIGSEGV_handler(int signum);

/**
 * @brief Handler for SIGTERM signal. (0x0F)
 * @param signum Signal number.
 * @return void
 * (signal 15) is a request to the program to terminate. If the program has a signal handler for SIGTERM that does not actually terminate the application, this kill may have no effect. This is the default signal sent by kill.
*/
void sig_SIGTERM_handler(int signum);

/**
 * @brief Register all signal handlers.
 * @return void
*/
void register_all_signal_handlers();

#endif // SIGNAL_HANDLER_H
