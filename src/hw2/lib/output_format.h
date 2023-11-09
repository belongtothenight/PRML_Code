/**
 * @file output_format.h
 * @brief Output format struct for color printing (charactors)
 */

#ifndef OUTPUT_FORMAT_H
#define OUTPUT_FORMAT_H

/// https://stackoverflow.com/questions/2048509/how-to-echo-with-different-colors-in-the-windows-command-line

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
} output_format;

/**
 * @brief Get output format
 * @details Get output format
 * @param pFormat Pointer to output format
 */
void get_format(output_format* pFormat);
//! @endcond
#endif
