/* symTbl.c - standalone symbol tables wrapper */

/* CREATED BY /media/ipaun1/HDD04/Documents/gitrepos/miscfiles/EmbeddedStuff/util/makeSymTbl.tcl
 *  WITH ARGS {} main.exe symTbl/symTbl.c
 *         ON Tue Sep 05 16:02:17 EEST 2017
 */

#include <stdlib.h>
#include "symbol.h"

IMPORT int __bad_interrupt ();
IMPORT int __bss_end;
IMPORT int __bss_start;
IMPORT int __ctors_end ();
IMPORT int __ctors_start ();
IMPORT int __do_clear_bss ();
IMPORT int __dtors_end ();
IMPORT int __dtors_start ();
IMPORT int _edata;
IMPORT int _etext ();
IMPORT int exit ();
IMPORT int _exit ();
IMPORT int __heap_end ();
IMPORT int __init ();
IMPORT int main ();
IMPORT int __stack ();
IMPORT int __trampolines_end ();
IMPORT int __trampolines_start ();
IMPORT int var1;
IMPORT int __vector_1 ();
IMPORT int __vector_10 ();
IMPORT int __vector_11 ();
IMPORT int __vector_12 ();
IMPORT int __vector_13 ();
IMPORT int __vector_14 ();
IMPORT int __vector_15 ();
IMPORT int __vector_16 ();
IMPORT int __vector_17 ();
IMPORT int __vector_18 ();
IMPORT int __vector_19 ();
IMPORT int __vector_2 ();
IMPORT int __vector_20 ();
IMPORT int __vector_21 ();
IMPORT int __vector_22 ();
IMPORT int __vector_23 ();
IMPORT int __vector_24 ();
IMPORT int __vector_25 ();
IMPORT int __vector_3 ();
IMPORT int __vector_4 ();
IMPORT int __vector_5 ();
IMPORT int __vector_6 ();
IMPORT int __vector_7 ();
IMPORT int __vector_8 ();
IMPORT int __vector_9 ();
IMPORT int __vector_default ();
IMPORT int __vectors ();

SYMBOL standTbl [48] =
    {
        {{NULL}, "__bad_interrupt", (char*) __bad_interrupt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__bss_end", (char*) &__bss_end, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__bss_start", (char*) &__bss_start, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ctors_end", (char*) __ctors_end, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ctors_start", (char*) __ctors_start, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__data_load_end", (char*) 0x000000f0, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "__data_load_start", (char*) 0x000000f0, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "__do_clear_bss", (char*) __do_clear_bss, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__dtors_end", (char*) __dtors_end, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__dtors_start", (char*) __dtors_start, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_edata", (char*) &_edata, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_etext", (char*) _etext, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "exit", (char*) exit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_exit", (char*) _exit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__heap_end", (char*) __heap_end, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__init", (char*) __init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "main", (char*) main, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__stack", (char*) __stack, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__trampolines_end", (char*) __trampolines_end, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__trampolines_start", (char*) __trampolines_start, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "var1", (char*) &var1, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__vector_1", (char*) __vector_1, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__vector_10", (char*) __vector_10, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__vector_11", (char*) __vector_11, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__vector_12", (char*) __vector_12, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__vector_13", (char*) __vector_13, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__vector_14", (char*) __vector_14, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__vector_15", (char*) __vector_15, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__vector_16", (char*) __vector_16, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__vector_17", (char*) __vector_17, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__vector_18", (char*) __vector_18, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__vector_19", (char*) __vector_19, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__vector_2", (char*) __vector_2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__vector_20", (char*) __vector_20, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__vector_21", (char*) __vector_21, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__vector_22", (char*) __vector_22, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__vector_23", (char*) __vector_23, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__vector_24", (char*) __vector_24, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__vector_25", (char*) __vector_25, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__vector_3", (char*) __vector_3, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__vector_4", (char*) __vector_4, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__vector_5", (char*) __vector_5, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__vector_6", (char*) __vector_6, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__vector_7", (char*) __vector_7, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__vector_8", (char*) __vector_8, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__vector_9", (char*) __vector_9, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__vector_default", (char*) __vector_default, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__vectors", (char*) __vectors, 0, 0,  SYM_GLOBAL | SYM_TEXT},
    };


ULONG standTblSize = 48;
