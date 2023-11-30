/**
 * @file  output_format.h
 * @brief Output format struct for color printing (charactors)
 * Ref:
 * 1. https://stackoverflow.com/questions/2048509/how-to-echo-with-different-colors-in-the-windows-command-line
 * 2. https://stackoverflow.com/questions/37774983/clearing-the-screen-by-printing-a-character
 * 3. https://invisible-island.net/xterm/ctlseqs/ctlseqs.html
*/

#ifndef OUTPUT_FORMAT_H
#define OUTPUT_FORMAT_H

//! @cond Doxygen_Suppress
/**
 * @brief Output format struct for color printing (charactors)
 * @details This struct contains all the color codes for printing in terminal
 */
typedef struct{
    /// @brief Styles
    struct Styles{
        char *reset;        ///< reset
        char *bold;         ///< bold
        char *underline;    ///< underline
        char *inverse;      ///< inverse
    } style;
    /// @brief Text colors
    struct Foreground{
        char *black;        ///< black
        char *red;          ///< red
        char *green;        ///< green
        char *yellow;       ///< yellow
        char *blue;         ///< blue
        char *magenta;      ///< magenta
        char *cyan;         ///< cyan
        char *white;        ///< white
    } foreground;
    /// @brief Background colors
    struct Background{
        char *black;        ///< black
        char *red;          ///< red
        char *green;        ///< green
        char *yellow;       ///< yellow
        char *blue;         ///< blue
        char *magenta;      ///< magenta
        char *cyan;         ///< cyan
        char *white;        ///< white
    } background;
    /// @brief Strong text colors
    struct Strong_Foreground{
        char *black;        ///< black
        char *red;          ///< red
        char *green;        ///< green
        char *yellow;       ///< yellow
        char *blue;         ///< blue
        char *magenta;      ///< magenta
        char *cyan;         ///< cyan
        char *white;        ///< white
    } strong_foreground;
    /// @brief Strong background colors
    struct Strong_Background{
        char *black;        ///< black
        char *red;          ///< red
        char *green;        ///< green
        char *yellow;       ///< yellow
        char *blue;         ///< blue
        char *magenta;      ///< magenta
        char *cyan;         ///< cyan
        char *white;        ///< white
    } strong_background;
    /// @brief Action
    struct Action{
        char *reset_terminal;           ///< reset terminal
        char *clear_screen_below;       ///< clear screen below
        char *clear_screen_above;       ///< clear screen above
        char *clear_screen_all;         ///< clear screen all
        char *clear_screen_saved_lines; ///< clear screen saved lines
        char *clear_selected_right;         ///< clear selected to right
        char *clear_selected_left;          ///< clear selected to left
        char *clear_selected_all;           ///< clear selected all
        char *move_cursor_home;         ///< move cursor home
        char *set_cursor_style_default; ///< set cursor style to default
        char *set_cursor_style_blk_blk; ///< set cursor style to blinking block
        char *set_cursor_style_std_blk; ///< set cursor style to steady block
        char *set_cursor_style_blk_udl; ///< set cursor style to blinking underline
        char *set_cursor_style_std_udl; ///< set cursor style to steady underline
        char *set_cursor_style_blk_bar; ///< set cursor style to blinking bar
        char *set_cursor_style_std_bar; ///< set cursor style to steady bar
        char *set_warning_bell_volume_N;///< set warning bell volume to off
        char *set_warning_bell_volume_L;///< set warning bell volume to low
        char *set_warning_bell_volume_H;///< set warning bell volume to medium
        char *Ps;                       ///< execution_times (used in the following commands)
        char *insert_blank_char;        ///< insert blank char Ps times
        char *move_cursor_up;           ///< move cursor up Ps lines
        char *move_cursor_down;         ///< move cursor down Ps lines
        char *move_cursor_forward;      ///< move cursor forward Ps chars
        char *move_cursor_backward;     ///< move cursor backward Ps chars
        char *move_cursor_next_line;    ///< move cursor to the beginning of the next line Ps lines down
        char *move_cursor_previous_line;///< move cursor to the beginning of the previous line Ps lines up
        char *insert_line;              ///< insert line Ps lines
        char *delete_line;              ///< delete line Ps lines
        char *delete_char;              ///< delete char Ps chars
        char *scroll_up;                ///< scroll up Ps lines
        char *scroll_down;              ///< scroll down Ps lines

    } action;
    /// @brief Status
    struct Status{
        char *success;      ///< success
        char *warning;      ///< warning
        char *error;        ///< error
        char *pass;         ///< pass
        char *fail;         ///< fail
    } status;
} output_format;
//! @endcond

/**
 * @brief Get the format object, return the format struct with value assigned
 * @param pFormat pointer to the output_format struct
 * @param Ps execution times
 * @return void
*/
void get_format(output_format* pFormat, int Ps);

#endif
