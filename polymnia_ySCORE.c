/*============================----beg-of-source---============================*/
#include   "polymnia.h"



/*===[[ GNU GENERAL PUBLIC LICENSE (GPL) ]]===================================*/
/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */

#define  P_COPYRIGHT   \
   "copyright (c) 2019 robert.s.heatherly at balsashrike at gmail dot com"

#define  P_LICENSE     \
   "the only place you could have gotten this code is my github, my website,¦"   \
   "or illegal sharing. given that, you should be aware that this is GPL licensed."

#define  P_COPYLEFT    \
   "the GPL COPYLEFT REQUIREMENT means any modifications or derivative works¦"   \
   "must be released under the same GPL license, i.e, must be free and open."

#define  P_INCLUDE     \
   "the GPL DOCUMENTATION REQUIREMENT means that you must include the original¦" \
   "copyright notice and the full licence text with any resulting anything."

#define  P_AS_IS       \
   "the GPL NO WARRANTY CLAUSE means the software is provided without any¦"      \
   "warranty and the author cannot be held liable for damages."

#define  P_THEFT    \
   "if you knowingly violate the spirit of these ideas, i suspect you might¦"    \
   "find any number of freedom-minded hackers may take it quite personally ;)"

/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */
/*===[[ GNU GENERAL PUBLIC LICENSE (GPL) ]]===================================*/



/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */
#define  P_OBJECTIVE   \
   "polymnia_ySCORE.c is focused solely on enabling the ySCORE shared library to¦"    \
   "gather, track, and report function-level analytical stats for each-and-every¦"    \
   "function within a particular project and its related source files."

/*-----  ----------------  ·········1·········2·········3·········4·········5·········*/
#define  P_IMPORTANCE     "´ (low)      very useful, but not required to run"
#define  P_COMPLEXITY     "´ (low)      just enables library"



/*> struct {                                                                          <* 
 *>    char        match       [LEN_LABEL];                                           <* 
 *>    char        desc        [LEN_TERSE];                                           <* 
 *> } s_matches [LEN_DESC] = {                                                        <* 
 *>    /+---(ends)---------------------------+/                                       <* 
 *>    { "c ·· ·· ··· ·",  "leaf"       },                                            <* 
 *>    { "c ·´ ·· ··· ·",  "leaf+"      },                                            <* 
 *>    { "c ·· ·· ··· ´",  "seed"       },                                            <* 
 *>    { "c ·´ ·· ··· ´",  "seed+"      },                                            <* 
 *>    { "c ·· ·· ´·· ´",  "root"       },                                            <* 
 *>    { "c ·· ·· ·´· ´",  "tendril"    },                                            <* 
 *>    { "c ·· ·· ··´ ´",  "flower"     },                                            <* 
 *>    /+---(connections)--------------------+/                                       <* 
 *>    { "c ·´ ·· ··· ·",  "node"       },                                            <* 
 *>    { "c ·· ·´ ··· ·",  "node"       },                                            <* 
 *>    { "c ·´ ·´ ··· ·",  "node+"      },                                            <* 
 *>    { "s ·´ ·· ··· ·",  "access"     },                                            <* 
 *>    { "s ·· ·´ ··· ·",  "access"     },                                            <* 
 *>    { "s ·´ ·´ ··· ·",  "access+"    },                                            <* 
 *>    /+---(done)---------------------------+/                                       <* 
 *>    { "---"          ,  "END-LIST"   },                                            <* 
 *> };                                                                                <*/

/*> char         /+-> classify function by statistics -------------[ leaf       ]-+/ /+-åfc#´·8á71·á···´4·A´1··´2·A1·á·æ¬å1á1···´8·8á······´···´····æ¬å·····´······´····´····æ-+/                                                             <* 
 *> poly_cats__anatomy      (char a_name [LEN_TITLE], char a_rtype, char a_fvars, char a_gvars, char a_fcalls, char a_gcalls, char a_graph, char a_read, char a_write, char a_memory, char r_anatomy [LEN_TERSE], char r_match [LEN_LABEL])   <* 
 *> {                                                                                                                                                                                                                                         <* 
 *>    int         i           =    0;                                                                                                                                                                                                        <* 
 *>    char        x_match     [LEN_LABEL] = "· ·· ·· ··· ·";                                                                                                                                                                                 <* 
 *>    char        x_anatomy   [LEN_TERSE] = "´";                                                                                                                                                                                             <* 
 *>    /+---(quick-out)----------------------+/                                                                                                                                                                                               <* 
 *>    if (strncmp (a_name, "o___", 4) == 0) {                                                                                                                                                                                                <* 
 *>       if (r_anatomy != NULL)  ystrlcpy (r_anatomy, "·········", LEN_TERSE);                                                                                                                                                               <* 
 *>       if (r_match   != NULL)  ystrlcpy (r_match  , ""         , LEN_LABEL);                                                                                                                                                               <* 
 *>       return 0;                                                                                                                                                                                                                           <* 
 *>    }                                                                                                                                                                                                                                      <* 
 *>    /+---(build match)--------------------+/                                                                                                                                                                                               <* 
 *>    if (a_rtype  == 'c')  x_match [ 0]  = 'c';                                                                                                                                                                                             <* 
 *>    if (a_rtype  == 's')  x_match [ 0]  = 's';                                                                                                                                                                                             <* 
 *>    if (a_gvars  >   0 )  x_match [ 2]  = '´';                                                                                                                                                                                             <* 
 *>    if (a_fvars  >   0 )  x_match [ 3]  = '´';                                                                                                                                                                                             <* 
 *>    if (a_gcalls >   0 )  x_match [ 5]  = '´';                                                                                                                                                                                             <* 
 *>    if (a_fcalls >   0 )  x_match [ 6]  = '´';                                                                                                                                                                                             <* 
 *>    if (a_read   >   0 )  x_match [ 8]  = '´';                                                                                                                                                                                             <* 
 *>    if (a_write  >   0 )  x_match [ 9]  = '´';                                                                                                                                                                                             <* 
 *>    if (a_graph  >   0 )  x_match [10]  = '´';                                                                                                                                                                                             <* 
 *>    if (a_memory >   0 )  x_match [12]  = '´';                                                                                                                                                                                             <* 
 *>    /+---(test match)---------------------+/                                                                                                                                                                                               <* 
 *>    ystrlcpy (x_anatomy, "´"        , LEN_TERSE);                                                                                                                                                                                          <* 
 *>    for (i = 0; i < LEN_DESC; ++i) {                                                                                                                                                                                                       <* 
 *>       if (strcmp ("---"  , s_matches [i].match) == 0)   break;                                                                                                                                                                            <* 
 *>       if (strcmp (x_match, s_matches [i].match) != 0)   continue;                                                                                                                                                                         <* 
 *>       ystrlcpy (x_anatomy, s_matches [i].desc, LEN_TERSE);                                                                                                                                                                                <* 
 *>       break;                                                                                                                                                                                                                              <* 
 *>    }                                                                                                                                                                                                                                      <* 
 *>    if (r_anatomy != NULL)  ystrlcpy (r_anatomy, x_anatomy, LEN_TERSE);                                                                                                                                                                    <* 
 *>    if (r_match   != NULL)  ystrlcpy (r_match  , x_match  , LEN_LABEL);                                                                                                                                                                    <* 
 *>    return 0;                                                                                                                                                                                                                              <* 
 *> }                                                                                                                                                                                                                                         <*/



/*
 * anatomy
 *    return type
 *
 *    global vars used          · f G °
 *    file/static vars used
 *
 *    global calls              · f G °
 *    file/static calls
 *
 *    input   user (scanf, ...)
 *    read    file/stream
 *
 *    output  user (printf, ...)
 *    write   file/stream
 *
 *    input
 *    output
 *
 *    graphics
 *    memory alloc/free
 *
 *    any non-local variables
 *    any non-lib, non-std function calls
 *
 */


/*    -  f  g  °
/* HAIR INDICATOR (2 fields)                                            */
/*   ƒ€€€€€€ uses local (-), file (*) ,or global (°) variables          */
/*    ƒ€€€€ calls to none (-), file (*), or global (°) functions       */
/* [·-·-·]¬[fcC##g·L44·27-·E-2D1-]¬[-----·--·-------·---·----]¬[?#p-#·4-2--2·----·----]  */
/* [·*·*·]¬[fcC##g·L44·27-·E-2D1-]¬[-----·--·-------·---·----]¬[?#p-#·4-2--2·----·----]  */
/* [·°·°·]¬[fcC##g·L44·27-·E-2D1-]¬[-----·--·-------·---·----]¬[?#p-#·4-2--2·----·----]  */

/*   leaf      uses only local data and calls only cstd functions   */
/*   tindril                                                        */
/*   creeper                                                        */
/*   vine                                                           */
/*   pod                                                            */
/*   flower                                                         */
/*   burl                                                           */
/*   branch                                                         */
/*   trunk                                                          */
/*   root                                                           */
/*   bark      uses only local data and calls only cstd functions   */


/*> #define     WORK_BEG       work->beg                                              <* 
 *> #define     WORK_END       work->end                                              <* 
 *> #define     WORK_LOCALS    work->locals                                           <*/

static const tySCORE_TB  s_polymnia_table [LEN_FULL] = {
   /*===[[ HAIR ]]================ print======= description========================= style check valid============== ==legend====== ============ ============ ============ ============ ============ ============ ==*/
   { 'Ï' , "HRá "     , '>' ,  0  , "HAIR"                       , ""               , ' ' , ' ' , ""                , ""                                                                                            },
   /*-vis---label----- def-- samp- print------- description------------------------- style check valid-------------- --legend------ ------------ ------------ ------------ ------------ ------------ ------------ --*/
   { 'Ï' , "HCALL"    , '·' , 'f' , "hcall"    , "widest²scope²call²to²function"    , '·' , ' ' , "-fg°"            , "-) none     f) file      g) global    °) extern"                                             },
   { 'Ï' , "HFUNC"    , '·' , '-' , "hfunc"    , "widest·scope·function²used"       , '·' , ' ' , "-fg°"            , "-) none     f) file      g) global    °) extern"                                             },
   { 'Ï' , "HVAR"     , '·' , 'g' , "hvar"     , "widest·scope·variable²used"       , '·' , ' ' , "-fmg°"           , "-) none     f) file      m) access    g) global    °) extern"                                },
   { 'Ï' , "   "      , ' ' ,  3  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },

   /*===[[ COMPLEXITY ]]========== print======= description========================= style check valid============== ==legend====== ============ ============ ============ ============ ============ ============ ==*/
   { 'Ï' , "COá "     , '>' ,  0  , "COMPLEXITY"                 , ""               , ' ' , ' ' , ""                , ""                                                                                            },
   /*-vis---label----- def-- samp- print------- description------------------------- style check valid-------------- --legend------ ------------ ------------ ------------ ------------ ------------ ------------ --*/
   { 'Ï' , "SINGLE"   , '·' , '-' , "single"   , "single²line²function"             , '>' , ' ' , "²y"              , "y) single    ²) multi"                                                                       },
   { 'Ï' , " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*-vis---label----- def-- samp- print------- description------------------------- style check valid-------------- --legend------ ------------ ------------ ------------ ------------ ------------ ------------ --*/
   { 'Ï' , "SCOPE"    , '·' , 'g' , "scope"    , "function²scope"                   , '>' , ' ' , "xgfsu"           , "x) extern    g) global    f) file      s) static    u) unit"                                 },
   { 'Ï' , "RTYPE"    , '·' , 'c' , "rtype"    , "function·return·type"             , '>' , ' ' , "csnpvo"          , "c) char      s) string    n) number    p) point     v) void      o) other"                   },
   { 'Ï' , "FORMAT"   , '·' , 'M' , "format"   , "function·header·format"           , '>' , ' ' , "²Mc1234t?"       , "²) none      M) modern    c) current   1-4) older   t) terse     ?) unknown"                 },
   { 'Ï' , "PURPOS"   , '·' , 'y' , "purpos"   , "function·purpose·narrative"       , '>' , ' ' , "²<y>#?"          , "²) none      <) short     y) exists    >) long      #) trouble   ?) badchar"                 },
   { 'Ï' , " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*-vis---label----- def-- samp- print------- description------------------------- style check valid-------------- --legend------ ------------ ------------ ------------ ------------ ------------ ------------ --*/
   { 'Ï' , "PROTO"    , '·' , 'g' , "proto"    , "function²prototype²location"      , '>' , ' ' , "PBvf²"           , "P) public    B) pub/priv  v) priv      f) file      ²) none"                                 },
   { 'Ï' , "PPAREN"   , '·' , 'y' , "pparen"   , "parenthesis·balanced"             , '>' , ' ' , "?<>=#yv"         , "?) danger    <) no-beg    >) no-end    =) not-bal   #) crazy     y) balance   v) void"       },
   { 'Ï' , "PARAMS"   , '·' , 'A' , "params"   , "number·of·parameters"             , '+' , ' ' , "²0-9#"           , "²) none      1-3) low     4-6) mid     7-9) high    #) huge"                                 },
   { 'Ï' , " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*-vis---label----- def-- samp- print------- description------------------------- style check valid-------------- --legend------ ------------ ------------ ------------ ------------ ------------ ------------ --*/
   { 'Ï' , "PIN"      , '·' , '4' , "pin"      , "incomming·parameters²²²(a)"       , '+' , ' ' , "?²0-9#"          , "?) WTF       ²) none      1-3) low     4-6) mid     7-9) high    #) huge"                    },
   { 'Ï' , "POUT"     , '·' , '3' , "pout"     , "outgoing·parameters²²²²(r)"       , '+' , ' ' , "?²0-9#"          , "?) WTF       ²) none      1-3) low     4-6) mid     7-9) high    #) huge"                    },
   { 'Ï' , "PBOTH"    , '·' , '2' , "pboth"    , "both·in/out·parameters²(b)"       , '+' , ' ' , "?²0-9#"          , "?) WTF       ²) none      1-3) low     4-6) mid     7-9) high    #) huge"                    },
   { 'Ï' , "PCONF"    , '·' , '1' , "pconf"    , "run-time·conf·params²²²(c)"       , '+' , ' ' , "?²0-9#"          , "?) WTF       ²) none      1-3) ok      4+) high"                                             },
   { 'Ï' , "PDIAG"    , '·' , '1' , "pdiag"    , "debug/diagnosis·output²(d)"       , '+' , ' ' , "?²0-9#"          , "?) WTF       ²) none      1-3) ok      4+) high"                                             },
   { 'Ï' , "POLDER"   , '·' , '2' , "polder"   , "non-standard·params"              , '+' , ' ' , "?²0-9#"          , "?) WTF       ²) none      1-3) low     4-6) mid     7-9) high    #) huge"                    },
   { 'Ï' , " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*-vis---label----- def-- samp- print------- description------------------------- style check valid-------------- --legend------ ------------ ------------ ------------ ------------ ------------ ------------ --*/
   { 'Ï' , "PNUM"     , '·' , '1' , "pnum"     , "params²as²numeric²pointers"       , '+' , ' ' , "?²0-9#"          , "?) WTF       ²) none      1-3) low     4-6) mid     7-9) high    #) huge"                    },
   { 'Ï' , "PMULTI"   , '·' , '2' , "pmulti"   , "params·as·multiple·pointers"      , '+' , ' ' , "?²0-9#"          , "?) WTF       ²) none      1-3) low     4-6) mid     7-9) high    #) huge"                    },
   { 'Ï' , "PFUNC"    , '·' , '3' , "pfunc"    , "function·parameters²²²²(e)"       , '+' , ' ' , "?²0-9#"          , "?) WTF       ²) none      1-3) low     4-6) mid     7-9) high    #) huge"                    },
   { 'Ï' , "PSTRUC"   , '·' , '4' , "pstruc"   , "params·as·struct·pointers"        , '+' , ' ' , "?²0-9#"          , "?) WTF       ²) none      1-3) low     4-6) mid     7-9) high    #) huge"                    },
   { 'Ï' , " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*-vis---label----- def-- samp- print------- description------------------------- style check valid-------------- --legend------ ------------ ------------ ------------ ------------ ------------ ------------ --*/
   { 'Ï' , "TOTAL"    , '·' , 'B' , "total"    , "total²lines²(div²5)"              , ' ' , ' ' , "0-9A-Z#"         , "1-4) small   5-9) mod     A-D) full    E-H) large   I-N) huge    O-Z) SCARY   #)JESUS"       },
   { 'Ï' , "DOCS"     , '·' , '1' , "docs"     , "percent·documentation"            , ' ' , ' ' , "0-9#"            , "0-1) tiny    2-4) avg     5-7) high    #) warning"                                           },
   { 'Ï' , "DEBUG"    , '·' , '3' , "debug"    , "percent·debugging"                , ' ' , ' ' , "0-9#"            , "0-1) tiny    2-4) avg     5-7) high    #) warning"                                           },
   { 'Ï' , "CODE"     , '·' , '6' , "code"     , "percent·code"                     , ' ' , ' ' , "0-9#"            , "0-3) low     4-7) avg     8-9) high    #) warning"                                           },
   { 'Ï' , " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*-vis---label----- def-- samp- print------- description------------------------- style check valid-------------- --legend------ ------------ ------------ ------------ ------------ ------------ ------------ --*/
   { 'Ï' , "LOCALS"   , '·' , '4' , "locals"   , "number²of²local²vars²defined"     , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) few     4-6) avg     7-9) heavy   A-Z) SCARY   #) JESUS"                   },
   { 'Ï' , "LSTAT"    , '·' , '1' , "lstat"    , "number·of·locals·also·static"     , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) few     4-6) avg     7-9) heavy   A-Z) SCARY   #) JESUS"                   },
   { 'Ï' , " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*-vis---label----- def-- samp- print------- description------------------------- style check valid-------------- --legend------ ------------ ------------ ------------ ------------ ------------ ------------ --*/
   { 'Ï' , "LVARS"    , '·' , '4' , "lvars"    , "number²of²local²vars²used"        , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) few     4-6) avg     7-9) heavy   A-Z) SCARY   #) JESUS"                   },
   { 'Ï' , "FVARS"    , '·' , '2' , "fvars"    , "number·of·file/static·vars²used"  , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) few     4-6) avg     7-9) heavy   A-Z) SCARY   #) JESUS"                   },
   { 'Ï' , "GVARS"    , '·' , '3' , "gvars"    , "number·of·global·vars·used"       , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) few     4-6) avg     7-9) heavy   A-Z) SCARY   #) JESUS"                   },
   { 'Ï' , "AVARS"    , '·' , '1' , "avars"    , "number·of·accessor·vars·used"     , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) few     4-6) avg     7-9) heavy   A-Z) SCARY   #) JESUS"                   },
   { 'Ï' , " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*-vis---label----- def-- samp- print------- description------------------------- style check valid-------------- --legend------ ------------ ------------ ------------ ------------ ------------ ------------ --*/
   { 'Ï' , "INDENT"   , '·' , '2' , "indent"   , "depth²of²indentation"             , ' ' , ' ' , "0-9#"            , "0) none      1-3) avg     4-6) lots    7+) SCARY"                                            },
   { 'Ï' , "LOOP"     , '·' , '1' , "loop"     , "number·of·looping·statements"     , ' ' , ' ' , "0-9#"            , "0) none      1-2) avg     3-4) lots    5+) SCARY"                                            },
   { 'Ï' , "CHOICE"   , '·' , '3' , "choice"   , "number·of·choices/decisions"      , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) avg     4-9) lots    A+) SCARY"                                            },
   { 'Ï' , "RETURN"   , '·' , '1' , "return"   , "number·of·normal·returns"         , ' ' , ' ' , "0-9A-Z#"         , "0) WTF       1) perfect   2-5) avg     A-Z) SCARY"                                           },
   { 'Ï' , "RCE"      , '·' , '5' , "rce"      , "number·of·error·returns"          , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) avg     4-6) lots    9+) major"                                            },
   { 'Ï' , " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*-vis---label----- def-- samp- print------- description------------------------- style check valid-------------- --legend------ ------------ ------------ ------------ ------------ ------------ ------------ --*/
   { 'Ï' , "MEMORY"   , '·' , '-' , "memory"   , "memory·management·(malloc/free)"  , ' ' , ' ' , "-y"              , "y) in-use    -) none"                                                                        },
   { 'Ï' , "   "      , ' ' ,  3  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },

   /*===[[ INTEGRATION ]========== print======= description========================= style check valid============== ==legend====== ============ ============ ============ ============ ============ ============ ==*/
   { 'Ï' , "INá "     , '>' ,  0  , "INTEGRATION"                , ""               , ' ' , ' ' , ""                , ""                                                                                            },
   /*-vis---label----- def-- samp- print------- description------------------------- style check valid-------------- --legend------ ------------ ------------ ------------ ------------ ------------ ------------ --*/
   { 'Ï' , "CALLBY"   , '·' , '9' , "callby"   , "called²by²anything²else"          , ' ' , ' ' , "-y"              , "y) yes       -) no"                                                                          },
   { 'Ï' , "FCALL"    , '·' , '1' , "fcall"    , "called²by²local²functions"        , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { 'Ï' , "GCALL"    , '·' , '2' , "gcall"    , "called²by²global²functions"       , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { 'Ï' , "XCALL"    , '·' , '6' , "xcall"    , "called²by²external²functions"     , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { 'Ï' , "RECURS"   , '·' , '-' , "recurs"   , "called²recursively"               , ' ' , ' ' , "-y"              , "y) yes       -) no"                                                                          },
   { 'Ï' , " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*-vis---label----- def-- samp- print------- description------------------------- style check valid-------------- --legend------ ------------ ------------ ------------ ------------ ------------ ------------ --*/
   { 'Ï' , "CALLTO"   , '·' , 'C' , "callto"   , "call²to²anything²else"            , ' ' , ' ' , "-y"              , "y) yes       -) no"                                                                          },
   { 'Ï' , "DFUNC"    , '·' , '2' , "dfunc"    , "call²to²debugging²functions"      , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { 'Ï' , "RFUNC"    , '·' , 'A' , "rfunc"    , "call²to²real²functions"           , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { 'Ï' , " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*-vis---label----- def-- samp- print------- description------------------------- style check valid-------------- --legend------ ------------ ------------ ------------ ------------ ------------ ------------ --*/
   { 'Ï' , "FFUNC"    , '·' , '2' , "ffunc"    , "call²to²local²functions"          , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { 'Ï' , "GFUNC"    , '·' , '1' , "gfunc"    , "call²to²global²functions"         , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { 'Ï' , "CSTD"     , '·' , '5' , "cstd"     , "call²to²c-std²functions"          , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { 'Ï' , "YLIB"     , '·' , '2' , "ylib"     , "call²to²ylib²functions"           , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { 'Ï' , "VIKEYS"   , '·' , '-' , "vikeys"   , "call²to²vi-keys²functions"        , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { 'Ï' , "OFUNC"    , '·' , '-' , "ofunc"    , "call²to²other²functions"          , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { 'Ï' , "MYSTRY"   , '·' , '-' , "mystry"   , "call²to²mystery²functions"        , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { 'Ï' , " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*-vis---label----- def-- samp- print------- description------------------------- style check valid-------------- --legend------ ------------ ------------ ------------ ------------ ------------ ------------ --*/
   { 'Ï' , "INPUT"    , '·' , '4' , "input"    , "use²stdin²and²file²input"         , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { 'Ï' , "INTXT"    , '·' , '3' , "intxt"    , "use²text²input"                   , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { 'Ï' , "INBIN"    , '·' , '1' , "inbin"    , "use²binary²input"                 , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { 'Ï' , "IPARSE"   , '·' , '-' , "iparse"   , "use²yparse²library²input"         , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { 'Ï' , " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*-vis---label----- def-- samp- print------- description------------------------- style check valid-------------- --legend------ ------------ ------------ ------------ ------------ ------------ ------------ --*/
   { 'Ï' , "OUTPUT"   , '·' , '5' , "output"   , "use²stdout²and²file²output"       , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { 'Ï' , "OUTTXT"   , '·' , '2' , "outtxt"   , "use²text²output"                  , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { 'Ï' , "OUTBIN"   , '·' , '3' , "outbin"   , "use²binary²output"                , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { 'Ï' , "OPARSE"   , '·' , '-' , "oparse"   , "use²yparse²library²output"        , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { 'Ï' , " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*-vis---label----- def-- samp- print------- description------------------------- style check valid-------------- --legend------ ------------ ------------ ------------ ------------ ------------ ------------ --*/
   { 'Ï' , "SYSTEM"   , '·' , '4' , "system"   , "unix²process²and²system²calls"    , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { 'Ï' , "PROCS"    , '·' , '1' , "procs"    , "process²control²calls"            , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { 'Ï' , "OPSYS"    , '·' , '2' , "opsys"    , "operating²system²calls"           , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { 'Ï' , "FILSYS"   , '·' , '1' , "filsys"   , "file²system²control²calls"        , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { 'Ï' , "YENV"     , '·' , '-' , "yenv"     , "yenv²library²calls"               , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { 'Ï' , " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*-vis---label----- def-- samp- print------- description------------------------- style check valid-------------- --legend------ ------------ ------------ ------------ ------------ ------------ ------------ --*/
   { 'Ï' , "NCURSE"   , '·' , '-' , "ncurse"   , "ncurses²library²calls"            , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { 'Ï' , "WINDOW"   , '·' , '-' , "window"   , "x11²and²window²library²calls"     , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { 'Ï' , "OPENGL"   , '·' , '-' , "opengl"   , "opengl²library²calls"             , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { 'Ï' , "YGRAPH"   , '·' , '-' , "ygraph"   , "my²x11²and²opengl²library²calls"  , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { 'Ï' , "   "      , ' ' ,  3  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },

   /*===[[ WATCH-POINTS ========== print======= description========================= style check valid============== ==legend====== ============ ============ ============ ============ ============ ============ ==*/
   { 'Ï' , "WPá "     , '>' ,  0  , "WATCH-POINTS"               , ""               , ' ' , ' ' , ""                , ""                                                                                            },
   /*-vis---label----- def-- samp- print------- description------------------------- style check valid-------------- --legend------ ------------ ------------ ------------ ------------ ------------ ------------ --*/
   { 'Ï' , "DACTIV"   , '·' , 'y' , "dactiv"   , "debugging²in·use"                 , ' ' , ' ' , "·y-"             , "y) yes       -) no"                                                                          },
   { '>' , "DCOUNT"   ,  0  , '·' , "dcount"   , "debugging total lines"            , '·' , '·' , ""                , ""                                                                                            },
   { 'Ï' , "DSTYLE"   , '·' , 'l' , "dstyle"   , "debugging²style²(long/short)"     , ' ' , ' ' , "·-ls°"           , "-) none      l) long      s) short    °) mixed"                                              },
   { 'Ï' , "DLONG"    , '·' , '5' , "dlong"    , "count²of²debugging²long²calls"    , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { 'Ï' , "DSHORT"   , '·' , '-' , "dshort"   , "count²of²debugging²short²calls"   , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { 'Ï' , "DMACRO"   , '·' , 'a' , "dmacro"   , "specific²debugging²macro²used"    , ' ' , 'X' , ""                , "identifier assigned by yURG"                                                                 },
   { 'Ï' , " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*-vis---label----- def-- samp- print------- description------------------------- style check valid-------------- --legend------ ------------ ------------ ------------ ------------ ------------ ------------ --*/
   { 'Ï' , "DMATCH"   , '·' , 'm' , "dmatch"   , "debugging²enter/exits²match"      , ' ' , ' ' , "y°"              , "m) matched   °) unmatched"                                                                   },
   { 'Ï' , "DENTER"   , '·' , '1' , "denter"   , "count²of²debugging²enter²calls"   , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { 'Ï' , "DEXIT"    , '·' , '2' , "dexit"    , "count²of²debugging²exit²calls"    , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { 'Ï' , "DEXITR"   , '·' , '5' , "dexitr"   , "count²of²debugging²exitr²calls"   , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { 'Ï' , " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*-vis---label----- def-- samp- print------- description------------------------- style check valid-------------- --legend------ ------------ ------------ ------------ ------------ ------------ ------------ --*/
   { 'Ï' , "DFREE"    , '·' , '-' , "dfree"    , "debugging·unguarded by²macro"     , ' ' , ' ' , "²°"              , "²) good      °) warning"                                                                     },
   { 'Ï' , "DPREFX"   , '·' , '-' , "dprefx"   , "debugging·with·unknown·prefix"    , ' ' , ' ' , "²°"              , "²) good      °) warning"                                                                     },
   { 'Ï' , "DBLOCK"   , '·' , '-' , "dblock"   , "debugging·openning·code·block"    , ' ' , ' ' , "²°"              , "²) good      °) warning"                                                                     },
   { 'Ï' , "DCOMM"    , '·' , '-' , "dcomm"    , "debugging·broken·by·comment"      , ' ' , ' ' , "²°"              , "²) good      °) warning"                                                                     },
   { 'Ï' , " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*-vis---label----- def-- samp- print------- description------------------------- style check valid-------------- --legend------ ------------ ------------ ------------ ------------ ------------ ------------ --*/
   { 'Ï' , "MACROS"   , '·' , 'y' , "macros"   , "total·potential²#define²uses"     , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { 'Ï' , "MFILE"    , '·' , '1' , "mfile"    , "count·of·local/file²macros²used"  , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { 'Ï' , "MGLOBL"   , '·' , '3' , "mglobl"   , "count·of·global²macros²used"      , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { 'Ï' , "MCSTD"    , '·' , '1' , "mcstd"    , "count·of·c-standard²macros²used"  , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { 'Ï' , "MYLIB"    , '·' , '2' , "mylib"    , "count·of·ylib²macros²used"        , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { 'Ï' , "MVIKEY"   , '·' , '-' , "mvikey"   , "count·of·vi-keys²macros²used"     , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { 'Ï' , "MOTHER"   , '·' , '-' , "mother"   , "count·of·other²macros²used"       , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { 'Ï' , "MMYST"    , '·' , '-' , "mmyst"    , "count·of·mystery²macros²used"     , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { 'Ï' , " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*-vis---label----- def-- samp- print------- description------------------------- style check valid-------------- --legend------ ------------ ------------ ------------ ------------ ------------ ------------ --*/
   { 'Ï' , "VMASK"    , '·' , '-' , "vmask"    , "variables²masking²higher²ones"    , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { 'Ï' , "MMASK"    , '·' , '-' , "mmask"    , "macros²masking²earlier²ones"      , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { 'Ï' , "FMASK"    , '·' , '-' , "fmask"    , "functions²masking²other²ones"     , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { 'Ï' , " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*-vis---label----- def-- samp- print------- description------------------------- style check valid-------------- --legend------ ------------ ------------ ------------ ------------ ------------ ------------ --*/
   { 'Ï' , "UNITS"    , '·' , '1' , "units"    , "count²of²unit²tests²calling"      , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { 'Ï' , "SCRPS"    , '·' , '3' , "scrps"    , "count²of²test²scripts²calling"    , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { 'Ï' , "STEPS"    , '·' , 'B' , "steps"    , "count²of²calls·in·unit·tests"     , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { 'Ï' , "STRING"   , '·' , '-' , "string"   , "count²of²calls·in·string·tests"   , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },

   /*===[[ END-OF-LIST ]========== print======= description========================= style check valid============== ==legend====== ============ ============ ============ ============ ============ ============ ==*/
   { 'Ï' , "end-list" , '·' , '·' , ""         , "end-of-entries"                   , ' ' , ' ' , ""                , ""                                                                                            },
};

char         /*-> test function to understand look-and-feel-----------------å···æ¬å····á··á····á····á···á····á·····á·æ¬å·····á···á·······á···á···á····á····æ¬å·····á······á········á····á····æ */
poly_test_function          (void)
{
}

char poly_yscore_init       (void) { return ySCORE_init  (s_polymnia_table, 'y', &(my.s_yscore)); }

char poly_yscore_wrap       (void) { return ySCORE_wrap  (&(my.s_yscore)); }

char*
YSCORE_poly                 (void)
{
   ySCORE_stats_to_table (my.s_yscore);
   return ySCORE_poly (my.s_yscore);
}
