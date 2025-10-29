/*============================----beg-of-source---============================*/
#include  "polymnia.h"



static tPROJ   s_place;



const struct {
   uchar       h_abbr;
   char        h_name        [LEN_LABEL];
   char        h_label       [LEN_LABEL];
   char        h_desc        [LEN_DESC];
   char        h_type;                     /* ° means critical, ´ means set elsewhere, · means non-critical */
   long        h_offset;
   short       h_min;
   short       h_low;
   short       h_high;                     /* high is also the reporting width */
   short       h_max;
} static s_header [LEN_FULL] = {
   /*-------base------------label------------description--------------------------type---offset-----------------------------------------------min--low--hig-max----------------*/
   { 'N' , "···"           , "proj_name"    , "project name"                    , '´' , (long) &(s_place.j_name [0])       - (long) &s_place,   1,   4,  15, LEN_TITLE         },
   { 'D' , "···"           , "proj_dir"     , "project directory"               , '´' , (long) &(s_place.j_dir [0])        - (long) &s_place,   1,   4,  70, LEN_HUND          },
   {  1  , ""              , ""             , ""                                , '·' , -1                                                  ,   0,   0,   0, 0                 },
   /*-------master----------label------------description--------------------------type---offset-----------------------------------------------min--low--hig-max----------------*/
   { 'f' , "P_FOCUS"       , "focus"        , "functional focus"                , '°' , (long) &(s_place.j_focus [0])      - (long) &s_place,   5,  10,  30, LEN_DESC          },
   { 'n' , "P_NICHE"       , "niche"        , "niche within focus"              , '°' , (long) &(s_place.j_niche [0])      - (long) &s_place,   5,  10,  30, LEN_DESC          },
   { 's' , "P_SUBJECT"     , "subject"      , "short purpose statement"         , '°' , (long) &(s_place.j_subject [0])    - (long) &s_place,  10,  20,  30, LEN_DESC          },
   { 'p' , "P_PURPOSE"     , "purpose"      , "longer purpose statement"        , '°' , (long) &(s_place.j_purpose [0])    - (long) &s_place,  30,  50,  70, LEN_HUND          },
   {  1  , ""              , ""             , ""                                , '·' , -1                                                  ,   0,   0,   0, 0                 },
   /*-------greek-----------label------------description--------------------------type---offset-----------------------------------------------min--low--hig-max----------------*/
   { 'ê' , "P_NAMESAKE"    , "namesake"     , "greek pantheon sponsor"          , '°' , (long) &(s_place.j_namesake [0])   - (long) &s_place,  10,  20,  40, LEN_HUND          },
   { '÷' , "P_PRONOUNCE"   , "pronounce"    , "arapabet namesake guide"         , '°' , (long) &(s_place.j_pronounce [0])  - (long) &s_place,   0,   5,  30, LEN_TITLE         },
   { 'î' , "P_HERITAGE"    , "heritage"     , "longer description of god"       , '°' , (long) &(s_place.j_heritage [0])   - (long) &s_place,  40,  40,  70, LEN_HUND          },
   { 'é' , "P_BRIEFLY"     , "briefly"      , "short description of god"        , '°' , (long) &(s_place.j_briefly [0])    - (long) &s_place,   0,  20,  30, LEN_TITLE         },
   { 'ð' , "P_IMAGERY"     , "imagery"      , "description of the god"          , '°' , (long) &(s_place.j_imagery [0])    - (long) &s_place,  40,  40,  70, LEN_HUND          },
   { 'ø' , "P_REASON"      , "reason"       , "reason patronage makes sense"    , '°' , (long) &(s_place.j_reason [0])     - (long) &s_place,  40,  40,  70, LEN_HUND          },
   {  1  , ""              , ""             , ""                                , '·' , -1                                                  ,   0,   0,   0, 0                 },
   /*-------oneline---------label------------description--------------------------type---offset-----------------------------------------------min--low--hig-max----------------*/
   { 'ö' , "P_ONELINE"     , "oneline"      , "reporting suppmary line"         , '°' , (long) &(s_place.j_oneline [0])    - (long) &s_place,  40,  50,  70, LEN_HUND          },
   {  1  , ""              , ""             , ""                                , '·' , -1                                                  ,   0,   0,   0, 0                 },
   /*-------location--------label------------description--------------------------type---offset-----------------------------------------------min--low--hig-max----------------*/
   { 'd' , "P_HOMEDIR"     , "homedir"      , "project source directory"        , '°' , (long) &(s_place.j_homedir [0])    - (long) &s_place,   1,   4,  70, LEN_HUND          },
   { 'b' , "P_BASENAME"    , "progname"     , "run-time executable name"        , '°' , (long) &(s_place.j_progname [0])   - (long) &s_place,   1,   4,  20, LEN_TITLE         },
   { 'f' , "P_FULLPATH"    , "fullpath"     , "installed location"              , '°' , (long) &(s_place.j_fullpath [0])   - (long) &s_place,  10,  20,  70, LEN_HUND          },
   { 's' , "P_SUFFIX"      , "suffix"       , "data file suffix"                , '°' , (long) &(s_place.j_suffix [0])     - (long) &s_place,   0,   3,   6, LEN_LABEL         },
   { 'c' , "P_CONTENT"     , "content"      , "data file content description"   , '°' , (long) &(s_place.j_content [0])    - (long) &s_place,   0,  15,  30, LEN_TITLE         },
   {  1  , ""              , ""             , ""                                , '·' , -1                                                  ,   0,   0,   0, 0                 },
   /*-------chars-----------label------------description--------------------------type---offset-----------------------------------------------min--low--hig-max----------------*/
   { 's' , "P_SYSTEM"      , "system"       , "operating systems required"      , '°' , (long) &(s_place.j_systems [0])    - (long) &s_place,  40,  50,  70, LEN_HUND          },
   { 'l' , "P_LANGUAGE"    , "language"     , "computer programming language"   , '°' , (long) &(s_place.j_language [0])   - (long) &s_place,  40,  50,  70, LEN_HUND          },
   { 'c' , "P_COMPILER"    , "compiler"     , "specific compiler version"       , '°' , (long) &(s_place.j_compiler [0])   - (long) &s_place,   0,   3,  20, LEN_LABEL         },
   { 'z' , "P_CODESIZE"    , "codesize"     , "general size note"               , '°' , (long) &(s_place.j_codesize [0])   - (long) &s_place,  10,  10,  40, LEN_DESC          },
   {  1  , ""              , ""             , ""                                , '·' , -1                                                  ,   0,   0,   0, 0                 },
   /*-------depends---------label------------description--------------------------type---offset-----------------------------------------------min--low--hig-max----------------*/
   { 'D' , "P_DEPSTDC"     , "dep_stdc"     , "standard-c libraries"            , '°' , (long) &(s_place.j_dep_cstd [0])   - (long) &s_place,   0,   0,  70, LEN_HUND          },
   { 'P' , "P_DEPPOSIX"    , "dep_posix"    , "posix-c libraries"               , '°' , (long) &(s_place.j_dep_posix [0])  - (long) &s_place,   0,   0,  70, LEN_HUND          },
   { 'C' , "P_DEPCORE"     , "dep_core"     , "heatherly core libraries"        , '°' , (long) &(s_place.j_dep_core [0])   - (long) &s_place,   0,   0,  70, LEN_HUND          },
   { 'V' , "P_DEPVIKEY"    , "dep_vikey"    , "heatherly vi-keys libraries"     , '°' , (long) &(s_place.j_dep_vikey [0])  - (long) &s_place,   0,   0,  70, LEN_HUND          },
   { 'O' , "P_DEPOTHER"    , "dep_other"    , "all other libraries"             , '°' , (long) &(s_place.j_dep_other [0])  - (long) &s_place,   0,   0,  70, LEN_HUND          },
   { 'G' , "P_DEPGRAPH"    , "dep_graph"    , "heatherly visual libraries"      , '°' , (long) &(s_place.j_dep_graph [0])  - (long) &s_place,   0,   0,  70, LEN_HUND          },
   { 'S' , "P_DEPSOLO"     , "dep_solo"     , "heatherly solo/uver libraries"   , '°' , (long) &(s_place.j_dep_solo [0])   - (long) &s_place,   0,   0,  70, LEN_HUND          },
   {  1  , ""              , ""             , ""                                , '·' , -1                                                  ,   0,   0,   0, 0                 },
   /*-------when------------label------------description--------------------------type---offset-----------------------------------------------min--low--hig-max----------------*/
   { 'a' , "P_AUTHOR"      , "author"       , "primary programmer name"         , '°' , (long) &(s_place.j_author [0])     - (long) &s_place,   5,  10,  40, LEN_TITLE         },
   { 'c' , "P_CREATED"     , "created"      , "data first created"              , '°' , (long) &(s_place.j_created [0])    - (long) &s_place,   4,   7,  20, LEN_LABEL         },
   {  1  , ""              , ""             , ""                                , '·' , -1                                                  ,   0,   0,   0, 0                 },
   /*-------version---------label------------description--------------------------type---offset-----------------------------------------------min--low--hig-max----------------*/
   { 'x' , "P_VERMAJOR"    , "vermajor"     , "major version explanation"       , '°' , (long) &(s_place.j_vermajor [0])   - (long) &s_place,   4,  15,  70, LEN_HUND          },
   { 'n' , "P_VERMINOR"    , "verminor"     , "minor version explanation"       , '°' , (long) &(s_place.j_verminor [0])   - (long) &s_place,   4,  15,  70, LEN_HUND          },
   { 'v' , "P_VERNUM"      , "vernum"       , "specific vertion number"         , '°' , (long) &(s_place.j_vernum [0])     - (long) &s_place,   4,   4,   4, LEN_LABEL         },
   { 't' , "P_VERTXT"      , "vertxt"       , "specific version description"    , '°' , (long) &(s_place.j_vertxt [0])     - (long) &s_place,  10,  20,  70, LEN_HUND          },
   {  1  , ""              , ""             , ""                                , '·' , -1                                                  ,   0,   0,   0, 0                 },
   /*-------warranty--------label------------description--------------------------type---offset-----------------------------------------------min--low--hig-max----------------*/
   { 'l' , "P_LICENSE"     , "license"      , "code is gpl licensed"            , '!' , (long) &(s_place.j_license [0])    - (long) &s_place,   1,   1, 250, LEN_LABEL         },
   { 'c' , "P_COPYLEFT"    , "copyleft"     , "derivatives free and open"       , '!' , (long) &(s_place.j_copyleft [0])   - (long) &s_place,   1,   1, 250, LEN_LABEL         },
   { 'i' , "P_INCLUDE"     , "include"      , "derivatives must include text"   , '!' , (long) &(s_place.j_include [0])    - (long) &s_place,   1,   1, 250, LEN_LABEL         },
   { 'a' , "P_AS_IS"       , "as_is"        , "no one liable for any damages"   , '!' , (long) &(s_place.j_as_is [0])      - (long) &s_place,   1,   1, 250, LEN_LABEL         },
   { 'w' , "P_WARNING"     , "warning"      , "thoughts on cheating"            , '!' , (long) &(s_place.j_warning [0])    - (long) &s_place,   1,   1, 250, LEN_LABEL         },
   {  1  , ""              , ""             , ""                                , '·' , -1                                                  ,   0,   0,   0, 0                 },
   /*-------extra-----------label------------description--------------------------type---offset-----------------------------------------------min--low--hig-max----------------*/
   { 'p' , "P_PRIORITY"    , "priority"     , "programming priorities"          , '!' , (long) &(s_place.j_priority [0])   - (long) &s_place,   1,   1,  70, LEN_LABEL         },
   { 'p' , "P_PRINCIPLE"   , "principle"    , "call to action"                  , '!' , (long) &(s_place.j_principal [0])  - (long) &s_place,   1,   1,  70, LEN_LABEL         },
   { 'r' , "P_REMINDER"    , "reminder"     , "just so you know"                , '!' , (long) &(s_place.j_reminder [0])   - (long) &s_place,   1,   1,  70, LEN_LABEL         },
   { 'd' , "P_DISCLAIM"    , "disclaim"     , "programming disclaimer"          , '!' , (long) &(s_place.j_disclaim [0])   - (long) &s_place,   1,   1, 250, LEN_LABEL         },
   {  1  , ""              , ""             , ""                                , '·' , -1                                                  ,   0,   0,   0, 0                 },
   /*-------why-------------label------------description--------------------------type---offset-----------------------------------------------min--low--hig-max----------------*/
   { 'B' , "P_BOTHER"      , "bother"       , "why do anything?"                , '-' , (long) &(s_place.j_bother [0])     - (long) &s_place,   1,   1, 500, LEN_LABEL         },
   { 'C' , "P_COVERS"      , "covers"       , "what's the overall niche?"       , '-' , (long) &(s_place.j_covers [0])     - (long) &s_place,   1,   1, 500, LEN_LABEL         },
   { 'S' , "P_SUBDISC"     , "sub-disc"     , "what are the niche sub-parts?"   , '-' , (long) &(s_place.j_subdisc [0])    - (long) &s_place,   1,   1, 500, LEN_LABEL         },
   { 'C' , "P_CURRENT"     , "current"      , "current state-of-play"           , '-' , (long) &(s_place.j_current [0])    - (long) &s_place,   1,   1, 500, LEN_LABEL         },
   { 'V' , "P_VALUE"       , "value"        , "benefit of getting this right"   , '-' , (long) &(s_place.j_value [0])      - (long) &s_place,   1,   1, 500, LEN_LABEL         },
   { 'F' , "P_FEAR"        , "fear"         , "are there overriding needs?"     , '-' , (long) &(s_place.j_fear [0])       - (long) &s_place,   1,   1, 500, LEN_LABEL         },
   { 'M' , "P_MISSING"     , "missing"      , "current state gets what wrong"   , '-' , (long) &(s_place.j_missing [0])    - (long) &s_place,   1,   1, 500, LEN_LABEL         },
   { 'K' , "P_KEEPING"     , "keeping"      , "current state gets what right"   , '-' , (long) &(s_place.j_keeping [0])    - (long) &s_place,   1,   1, 500, LEN_LABEL         },
   { 'P' , "P_PERK"        , "perk"         , "benefit of building custom"      , '-' , (long) &(s_place.j_perk [0])       - (long) &s_place,   1,   1, 500, LEN_LABEL         },
   {  1  , ""              , ""             , ""                                , '·' , -1                                                  ,   0,   0,   0, 0                 },
   /*-------what------------label------------description--------------------------type---offset-----------------------------------------------min--low--hig-max----------------*/
   { 'S' , "P_SCOPE"       , "scope"        , "scope of this solution"          , '-' , (long) &(s_place.j_scope [0])      - (long) &s_place,   1,   1, 500, LEN_LABEL         },
   { 'A' , "P_ACCEPT"      , "accepted"     , "accepted objectives"             , '-' , (long) &(s_place.j_accept [0])     - (long) &s_place,   1,   1, 500, LEN_LABEL         },
   { 'R' , "P_REJECT"      , "rejected"     , "rejected objectives"             , '-' , (long) &(s_place.j_reject [0])     - (long) &s_place,   1,   1, 500, LEN_LABEL         },
   { 'A' , "P_ASSUME"      , "assume"       , "environmental assumptions"       , '-' , (long) &(s_place.j_assume [0])     - (long) &s_place,   1,   1, 500, LEN_LABEL         },
   { 'A' , "P_ALWAYS"      , "always"       , "universal objectives"            , '-' , (long) &(s_place.j_always [0])     - (long) &s_place,   1,   1, 500, LEN_LABEL         },
   { '*' , "P_SUMMARY"     , "summary"      , "project summary"                 , '-' , (long) &(s_place.j_summary [0])    - (long) &s_place,   1,   1, 500, LEN_LABEL         },
   { 'G' , "P_GREEK"       , "greek"        , "longer greek heritage"           , '-' , (long) &(s_place.j_greek [0])      - (long) &s_place,   1,   1, 500, LEN_LABEL         },
   {  1  , ""              , ""             , ""                                , '·' , -1                                                  ,   0,   0,   0, 0                 },
   /*-------grade-----------label------------description--------------------------type---offset-----------------------------------------------min--low--hig-max----------------*/
   { ' ' , ""              , "GRADE"        , "final rating on headers"         , '°' , -1                                                  ,   0,   0,   0, 0                 },
   /*-------end-------------label------------description--------------------------type---offset-----------------------------------------------min--low-high-max----------------*/
   {  0  , "end-of-list"   , ""             , ""                                , '·' , -1                                                  ,   0,   0,   0, 0                 },
};

/*>  GYGES                                                                             <* 
 *
 *> .B definition (D).                                                                 <* 
 *> spreadsheets are a modern adaptation of ancient columnar ledgers used              <* 
 *> by accountants, bookkeepers, engineers, quartermasters, warehousemen, and          <* 
 *> statisticians.  they allow control, order, and analysis in situations beyond       <* 
 *> simple counting.                                                                   <* 
 *>                                                                                    <* 
 *> .B what the hell (?).                                                              <* 
 *> i am tackling this problem set because it is fantasically hard, fully              <* 
 *> interactive, well understood, and has been mastered by commercial companies.       <* 
 *> it will cause me to learn a ton and be weighed and measured clearly ];>            <* 
 *> no hiding, no bitching out.                                                        <* 
 *>                                                                                    <* 
 *> .B situation (S).                                                                  <* 
 *> spreadsheets are a modern wonder of interactive calculation, iterative design,     <* 
 *> and complex analysis which can be quite reasonably and economically placed in      <* 
 *> the hands of non-technical users.  they are fantastic and realistic empowerment.   <* 
 *>                                                                                    <* 
 *> .B complication (C).                                                               <* 
 *> raging acceptance led to uncontrolled creeping featurism and kitchen-sink          <* 
 *> capabilities -- replacing everything from todo lists, graphing, database           <* 
 *> management and some production systems.  these systems are now fat, expensive,     <* 
 *> and hard to use efficiently.                                                       <* 
 *>                                                                                    <* 
 *> .B problem (P).                                                                    <* 
 *> spreadsheets are now simply magic -- too many capabilities and flexility           <* 
 *> combined intersecting complex problems and spaghetti solutions.  none of the       <* 
 *> safety, debugging, and testing seem to apply.  i need more -- a fast, light,       <* 
 *> adaptable, portable solution.                                                      <* 
 *>                                                                                    <* 
 *> .B my solution (M).                                                                <* 
 *> tight, keyboard-centric, power-user focused custom solution.  do one thing         <* 
 *> and do it well.  pare back funtionality to a core feature set which can be         <* 
 *> fully understood and tested, hand off non-core to other tools, and make the        <* 
 *> interface more productive.                                                         <* 
 *>                                                                                    <* 
 *> .B target user (T).                                                                <* 
 *> very technical, well-versed, power user.                                           <* 
 *>                                                                                    <* 
 *> .B accepted functionality (a).                                                     <* 
 *>    -- conceptual framework of cells within sheets, within tabs                     <* 
 *>    -- full vi-keys support and a majority of vi/vim features                       <* 
 *>    -- console/terminal formatting to enforce value and focus                       <* 
 *>    -- full set of mathmatical operators for functions                              <* 
 *>    -- full set of core functions, as in lotus, visicalc, and excel                 <* 
 *>    -- dependency-graph calculation method to avoid issues                          <* 
 *>    -- cell coloring for interpretation and dependency-awareness                    <* 
 *>    -- compile calculations to byte-code for speed                                  <* 
 *>    -- fully scriptable using the same commands                                     <* 
 *>                                                                                    <* 
 *> .B rejected functionality (r).                                                     <* 
 *>    -- mouse and touchscreen (fuck off)                                             <* 
 *>    -- any formatting other than alignment and numerical                            <* 
 *>    -- graphing or visual analyses (integrate with other tools)                     <* 
 *>    -- importing or exporting of special formats (like xls, etc)                    <* 
 *>    -- large data tables (which should be in a controlled database)                 <* 
 *>    -- data sorting and filtering (again, database)                                 <* 
 *>    -- reporting and printing (just not a spreadsheet thing)                        <* 
 *>    -- cell notes to provide details                                                <* 
 *>    -- text wrapping (learn word processors or databases)                           <* 
 *>    -- variable number of arguments for functions (rare, ambiguous)                 <* 
 *>    -- any functions that spit out multiple cells                                   <* 
 *>                                                                                    <* 
 *> .B as always, all my applications must (#).                                        <* 
 *>    -- run on any linux box from raspberry to cray                                  <* 
 *>    -- stay focused, small, tight, reliable, and secure                             <* 
 *>    -- forgo sloppy, kitchen-sink languages, like python, java, or perl             <* 
 *>    -- stay away from dependency on external code libraries, like boost             <* 
 *>    -- only human-readable, 7-bit safe, ascii streams (not database)                <* 
 *>    -- have dedicated, maintained, automated unit testing                           <* 
 *>    -- provide either detailed reporting or logging for debugging                   <* 
 *>    -- use secure communications between systems where required                     <* 
 *>    -- clean, clean code so i can maintain after long absences                      <* 
 *>    -- no international, multi-lang, multi-byte support (freaking ever)             <* 
 *>    -- one-hundred percent keyboard driven and centric                              <* 
 *>    -- operate using modes and windows/panels like vi/vim                           <* 
 *>    -- follow the yVIKEYS standard to the letter                                    <* 
 *>    -- all tables must be self describing with labels and queries                   <* 
 *>    -- all data structures must include dumps, reports, and audits                  <* 
 *>                                                                                    <*/

/*>                                                                                   <* 
 *> yENV
 *> a) situation       .                                                              <* 
 *> b) legacy answer   .                                                              <* 
 *> c) complication    .                                                              <* 
 *> d) reaction        .                                                              <* 
 *> e) answer          .                                                              <* 
 *> f) focus           .                                                              <* 
 *> g) value           .                                                              <* 
 *> h) requirements    .                                                              <* 
 *> i) warnings        .                                                              <* 
 *> j) alternatives    .                                                              <* 
 *> k) decision        .                                                              <* 
 *>                                                                                   <*/


/*> spreadsheets are a modern adaptation of ancient columnar ledgers used by accountants, bookkeepers, engineers, quartermasters, warehousemen, and statisticians.  they allow control, order, and analysis in situations beyond simple counting.   <*/

/*> .SH SERIOUS DISCLAIMER                                                            <* 
 *> i am a crazy, naive, dog-fooding c programmer.  i am not trying to be best.       <* 
 *> i optimize for learning, transparency, and ease of maintenance.  if i wanted      <* 
 *> awesome, fast, and cutting-edge, i'd use yours ;)                                 <*/

/*>                                                                                    <* 
 *
 *> .SH SUMMARY                                                                        <* 
 *> gyges (j-eye-j-ees) is a light, clean, powerful, technical, aesthetic, and         <* 
 *> keyboard-centric console spreadsheet focused on functionality, analytics,          <* 
 *> interfacing, scripting, and tailored usage.                                        <* 
 *>                                                                                    <* 
 *> .SH SCOPE, REASONING and DECISION                                                  <* 
 *>                                                                                    <* 
 *> .B definition (D).                                                                 <* 
 *> spreadsheets are a modern adaptation of ancient columnar ledgers used              <* 
 *> by accountants, bookkeepers, engineers, quartermasters, warehousemen, and          <* 
 *> statisticians.  they allow control, order, and analysis in situations beyond       <* 
 *> simple counting.                                                                   <* 
 *>                                                                                    <* 
 *> .B what the hell (?).                                                              <* 
 *> i am tackling this problem set because it is fantasically hard, fully              <* 
 *> interactive, well understood, and has been mastered by commercial companies.       <* 
 *> it will cause me to learn a ton and be weighed and measured clearly ];>            <* 
 *> no hiding, no bitching out.                                                        <* 
 *>                                                                                    <* 
 *> .B situation (S).                                                                  <* 
 *> spreadsheets are a modern wonder of interactive calculation, iterative design,     <* 
 *> and complex analysis which can be quite reasonably and economically placed in      <* 
 *> the hands of non-technical users.  they are fantastic and realistic empowerment.   <* 
 *>                                                                                    <* 
 *> .B complication (C).                                                               <* 
 *> raging acceptance led to uncontrolled creeping featurism and kitchen-sink          <* 
 *> capabilities -- replacing everything from todo lists, graphing, database           <* 
 *> management and some production systems.  these systems are now fat, expensive,     <* 
 *> and hard to use efficiently.                                                       <* 
 *>                                                                                    <* 
 *> .B problem (P).                                                                    <* 
 *> spreadsheets are now simply magic -- too many capabilities and flexility           <* 
 *> combined intersecting complex problems and spaghetti solutions.  none of the       <* 
 *> safety, debugging, and testing seem to apply.  i need more -- a fast, light,       <* 
 *> adaptable, portable solution.                                                      <* 
 *>                                                                                    <* 
 *> .B my solution (M).                                                                <* 
 *> tight, keyboard-centric, power-user focused custom solution.  do one thing         <* 
 *> and do it well.  pare back funtionality to a core feature set which can be         <* 
 *> fully understood and tested, hand off non-core to other tools, and make the        <* 
 *> interface more productive.                                                         <* 
 *>                                                                                    <*/

/*>                                                                                                                <* 
 *> ##/usr/local/bin/polymnia --htags                                                                              <* 
 *> ##                                                                                                             <* 
 *> ##   polymnia-hymnos (many praises) greek muse and protector of divine hymns, dancing, geometry, and grammar   <* 
 *> ##   version 1.1i, prefixed elements of structures proj (j_), file (i_), and func (c_) for easier finding      <* 
 *> ##   htags reporting file for use with vim-ide                                                                 <* 
 *> ##                                                                                                             <* 
 *> ##   33 headers ·  [-.-.----.------.-.-----.----.-------.--.----]                                              <* 
 *> ##                                                                                                             <* 
 *> ##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]          <* 
 *> ##                                                                                                             <* 
 *> ##   name       N  [polymnia]                                                                                  <* 
 *> ##                                                                                                             <* 
 *> ##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]          <* 
 *> ##                                                                                                             <* 
 *> ##   focus      f  []                                                                                          <* 
 *> ##   niche      n  []                                                                                          <* 
 *> ##   subject    s  []                                                                                          <* 
 *> ##   purpose    p  []                                                                                          <* 
 *> ##                                                                                                             <* 
 *> ##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]          <* 
 *> ##                                                                                                             <* 
 *> ##   namesake   ê  []                                                                                          <* 
 *> ##   pronounce  ÷  []                                                                                          <* 
 *> ##   heritage   î  []                                                                                          <* 
 *> ##   briefly    é  []                                                                                          <* 
 *> ##   imagery    ð  []                                                                                          <* 
 *> ##   reason     ø  []                                                                                          <* 
 *> ##                                                                                                             <* 
 *> ##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]          <* 
 *> ##                                                                                                             <* 
 *> ##   one-line   ö  []                                                                                          <* 
 *> ##                                                                                                             <* 
 *> ##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]          <* 
 *> ##                                                                                                             <* 
 *> ##   homedir    d  [/home/system/polymnia.muse_of_coding_structure]                                            <* 
 *> ##   basename   b  []                                                                                          <* 
 *> ##   fullpath   f  []                                                                                          <* 
 *> ##   suffix     s  []                                                                                          <* 
 *> ##   content    c  []                                                                                          <* 
 *> ##                                                                                                             <* 
 *> ##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]          <* 
 *> ##                                                                                                             <* 
 *> ##   system     s  []                                                                                          <* 
 *> ##   language   l  []                                                                                          <* 
 *> ##   compiler   c  []                                                                                          <* 
 *> ##   code-size  z  []                                                                                          <* 
 *> ##                                                                                                             <* 
 *> ##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]          <* 
 *> ##                                                                                                             <* 
 *> ##   dep_cstd   D  []                                                                                          <* 
 *> ##   dep_posix  P  []                                                                                          <* 
 *> ##   dep_core   C  []                                                                                          <* 
 *> ##   dep_vikey  V  []                                                                                          <* 
 *> ##   dep_other  O  []                                                                                          <* 
 *> ##   dep_graph  G  []                                                                                          <* 
 *> ##   dep_solo   S  []                                                                                          <* 
 *> ##                                                                                                             <* 
 *> ##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]          <* 
 *> ##                                                                                                             <* 
 *> ##   author     a  []                                                                                          <* 
 *> ##   created    c  []                                                                                          <* 
 *> ##                                                                                                             <* 
 *> ##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]          <* 
 *> ##                                                                                                             <* 
 *> ##   vermajor   x  []                                                                                          <* 
 *> ##   verminor   n  []                                                                                          <* 
 *> ##   vernum     v  []                                                                                          <* 
 *> ##   vertxt     t  []                                                                                          <* 
 *> ##                                                                                                             <* 
 *> ##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]          <* 
*> ##                                                                                                             <* 
*>                                                                                                                <*/



/*====================------------------------------------====================*/
/*===----                        support functions                     ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

short
poly_header_count       (void)
{
   int         i           =    0;
   int         c           =    0;
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   for (i = 0; i < LEN_FULL; ++i) {
      if (s_header [i].h_abbr == 0)               break;
      DEBUG_INPT   yLOG_complex ("line"      , "%2d (%4d) %s", i, s_header [i].h_abbr, s_header [i].h_label);
      if (s_header [i].h_abbr == 1)               continue;
      if (strcmp (s_header [i].h_name, "") == 0)  continue;
      ++c;
   }
   DEBUG_INPT   yLOG_value   ("c"         , c);
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return c;
}

char
poly_header_clear       (tPROJ *a_proj)
{
   int         i           =    0;
   for (i = 0; i < LEN_FULL; ++i) {
      if (s_header [i].h_abbr == 0)               break;
      if (s_header [i].h_abbr == 1) {
         a_proj->j_header [i] = 'á';
         continue;
      }
      a_proj->j_header [i] = '·';
      if (strcmp (s_header [i].h_name, "") == 0) {
         if (strcmp (s_header [i].h_label, "GRADE") == 0)  a_proj->j_header [i] = ' ';
         continue;
      }
      if (s_header [i].h_offset < 0)              continue;
      if      (strcmp (s_header [i].h_label, "proj_name")    == 0) ;
      else if (strcmp (s_header [i].h_label, "proj_dir")     == 0) ;
      else     strcpy ((long) a_proj + s_header [i].h_offset, "");
   }
   a_proj->j_header [i] = '\0';
   return 0;
}

char
poly_header_rando       (tPROJ *a_proj)
{
   int         i           =    0;
   for (i = 0; i < LEN_FULL; ++i) {
      if (s_header [i].h_abbr == 0)               break;
      if (s_header [i].h_abbr == 1) {
         a_proj->j_header [i] = 'á';
         continue;
      }
      a_proj->j_header [i] = '·';
      if (strcmp (s_header [i].h_name, "") == 0) {
         if (strcmp (s_header [i].h_label, "GRADE") == 0)  a_proj->j_header [i] = ' ';
         continue;
      }
      a_proj->j_header [i] = s_header [i].h_abbr;
      if (s_header [i].h_offset < 0)              continue;
      ystrlcpy ((long) a_proj + s_header [i].h_offset, s_header [i].h_label, s_header [i].h_max);
   }
   return 0;
}

char*
poly_header_memory      (tPROJ *a_proj)
{
   int         i           =    0;
   static char x_print     [LEN_HUND]  = "";
   strcpy (x_print, "");
   if (a_proj == NULL)  return "((null))";
   for (i = 0; i < LEN_FULL; ++i) {
      if (s_header [i].h_abbr == 0)               break;
      if (s_header [i].h_abbr == 1) {
         poly_shared__spacer     (x_print);
         continue;
      }
      poly_shared__check_str  (x_print, (long) a_proj + s_header [i].h_offset);
   }
   /*---(complete)-----------------------*/
   return x_print;
}




/*====================------------------------------------====================*/
/*===----                       searching options                      ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

short
poly_header__find       (char a_label [LEN_LABEL])
{
   char        rce         =  -10;
   int         i           =    0;
   --rce;  if (a_label     == NULL)   return rce;
   --rce;  if (a_label [0] == '\0')   return rce;
   --rce;  if (a_label [0] == ' ' )   return rce;
   for (i = 0; i < LEN_FULL; ++i) {
      if (s_header [i].h_abbr == 0)               break;
      if (s_header [i].h_abbr == 1)               continue;
      if (strcmp (s_header [i].h_name, "") == 0)  continue;
      if (s_header [i].h_offset < 0)              continue;
      if (strcmp (a_label, s_header [i].h_name) != 0)  continue;
      return i;
   }
   return --rce;
}



/*====================------------------------------------====================*/
/*===----                       reading data                           ----===*/
/*====================------------------------------------====================*/
static void  o___READING_________o () { return; }

char
poly_header__standard   (char a_label [LEN_LABEL], char a_data [LEN_RECD])
{
   char        rc          =  '?';
   char        x_expect    [LEN_RECD]  = "";
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   DEBUG_INPT   yLOG_complex ("a_data"    , "%3då%sæ", strlen (a_data), a_data);
   /*---(principles)---------------------*/
   if      (strcmp (a_label, "P_PRIORITY" ) == 0) {
      DEBUG_INPT   yLOG_note    ("matched priority");
      ystrlcpy (x_expect, P_PRIORITY , LEN_RECD);
   }
   else if (strcmp (a_label, "P_PRINCIPLE") == 0) {
      DEBUG_INPT   yLOG_note    ("matched principle");
      ystrlcpy (x_expect, P_PRINCIPLE, LEN_RECD);
   }
   else if (strcmp (a_label, "P_REMINDER" ) == 0) {
      DEBUG_INPT   yLOG_note    ("matched reminder");
      ystrlcpy (x_expect, P_REMINDER , LEN_RECD);
   }
   else if (strcmp (a_label, "P_DISCLAIM" ) == 0) {
      DEBUG_INPT   yLOG_note    ("matched disclaim");
      ystrlcpy (x_expect, P_DISCLAIM , LEN_RECD);
   }
   /*---(licensing)----------------------*/
   if      (strcmp (a_label, "P_LICENSE"  ) == 0) {
      DEBUG_INPT   yLOG_note    ("matched license");
      ystrlcpy (x_expect, P_LICENSE  , LEN_RECD);
   }
   else if (strcmp (a_label, "P_COPYLEFT" ) == 0) {
      DEBUG_INPT   yLOG_note    ("matched copyleft");
      ystrlcpy (x_expect, P_COPYLEFT , LEN_RECD);
   }
   else if (strcmp (a_label, "P_INCLUDE"  ) == 0) {
      DEBUG_INPT   yLOG_note    ("matched include");
      ystrlcpy (x_expect, P_INCLUDE  , LEN_RECD);
   }
   else if (strcmp (a_label, "P_AS_IS"    ) == 0) {
      DEBUG_INPT   yLOG_note    ("matched as_is");
      ystrlcpy (x_expect, P_AS_IS    , LEN_RECD);
   }
   else if (strcmp (a_label, "P_WARNING"  ) == 0) {
      DEBUG_INPT   yLOG_note    ("matched warning");
      ystrlcpy (x_expect, P_WARNING  , LEN_RECD);
   }
   /*---(compare)------------------------*/
   if (strcmp (x_expect, "") != 0) {
      ystrldchg (x_expect, '¦', ' ', LEN_RECD);
      ystrltrim (x_expect, ySTR_SINGLE, LEN_RECD);
      DEBUG_INPT   yLOG_complex (a_label, "%3då%sæ", strlen (x_expect), x_expect);
      if (strcmp (a_data, x_expect) == 0)  rc = 'y';
      else                                 rc = '-';
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
poly_header__single     (tPROJ *a_proj, cchar a_recd [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char       *q           = NULL;
   char       *r           = NULL;
   char        x_label     [LEN_LABEL] = "";
   char        x_data      [LEN_RECD]  = "";
   char        n           =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_proj"    , a_proj);
   --rce;  if (a_proj == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("a_recd"    , a_recd);
   /*---(filter for macros)--------------*/
   if (strncmp (a_recd, "#define ",  8) != 0) {
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(filter for headers)-------------*/
   q = strstr (a_recd, " P_");
   DEBUG_INPT   yLOG_point   ("q"         , q);
   if (q == NULL) {
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(find label)---------------------*/
   ystrlcpy (x_label, q + 1, 13);
   ystrltrim (x_label, ySTR_BOTH, LEN_LABEL);
   DEBUG_INPT   yLOG_info    ("x_label"   , x_label);
   n = poly_header__find (x_label);
   DEBUG_INPT   yLOG_value   ("n"         , n);
   if (n < 0) {
      yURG_err ('w', "found å%sæ which seems like a oneliner, but does not match table", x_label);
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(clip data payload)--------------*/
   ++q;
   DEBUG_INPT   yLOG_info    ("q"         , q);
   r = strchr (a_recd, '"');
   DEBUG_INPT   yLOG_point   ("r"         , r);
   if (r == NULL) {
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   DEBUG_INPT   yLOG_info    ("r"         , r);
   /*---(dequote)------------------------*/
   ystrlcpy (x_data, r, LEN_RECD);
   rc = ystrldequote (x_data, LEN_RECD);
   DEBUG_INPT   yLOG_value   ("unquote"   , rc);
   DEBUG_INPT   yLOG_info    ("x_data"    , x_data);
   /*---(copy to project)----------------*/
   if (strcmp (x_data, "") == 0)  strcpy (x_data, "-");
   ystrlcpy ((long) a_proj + s_header [n].h_offset, x_data, s_header [n].h_max);
   if (s_header [n].h_type == '!') {
      DEBUG_INPT   yLOG_note    ("processing a standard type");
      rc = poly_header__standard (x_label, x_data);
      DEBUG_INPT   yLOG_char    ("standard"  , rc);
      if (rc == 'y') {
         a_proj->j_header [n] = s_header [n].h_abbr;
         DEBUG_INPT   yLOG_info    ("header"    , a_proj->j_header);
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
poly_header__encode     (char *a_header, char n, char a_abbr, char *a_text, char a_min, char a_low, char a_high, char a_max)
{
   char        rce         =  -10;
   int         x_len       =    0;
   uchar       x_mark      =  '·';
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_header"  , a_header);
   --rce;  if (a_header == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("a_text"    , a_text);
   --rce;  if (a_text   == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("a_text"    , a_text);
   /*---(prepare)------------------------*/
   x_len = strlen (a_text);
   DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
   /*---(decide)-------------------------*/
   if      (x_len == 3 && strcmp (a_text, "n/a" ) == 0)  x_mark = '-';
   else if (x_len == 1 && strcmp (a_text, "-"   ) == 0)  x_mark = '-';
   else if (x_len == 1 && strcmp (a_text, "´"   ) == 0)  x_mark = '-';
   else if (x_len == 3 && strcmp (a_text, "..." ) == 0)  x_mark = '-';
   else if (x_len == 3 && strcmp (a_text, "´´´" ) == 0)  x_mark = '-';
   else if (x_len == 3 && strcmp (a_text, "···" ) == 0)  x_mark = '-';
   else if (x_len == 4 && strcmp (a_text, "none") == 0)  x_mark = '-';
   else if (x_len     == 0)       x_mark = '·';
   else if (x_len     <  a_min)   x_mark = '?';
   else if (x_len     <  a_low)   x_mark = '<';
   else if (x_len - 1 >= a_max)   x_mark = '#';
   else if (x_len     >  a_high)  x_mark = '>';
   else                           x_mark = a_abbr;
   DEBUG_INPT   yLOG_char    ("x_mark"    , x_mark);
   /*---(update)-------------------------*/
   DEBUG_INPT   yLOG_value   ("n"         , n);
   a_header [n] = x_mark;
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 1;
}

char*
poly_header__macro_fix  (char a_recd [LEN_RECD])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         c           =    0;
   int         l           =    0;
   int         i           =    0;
   char        x_label     [LEN_LABEL] = "";
   char       *p           =    0;
   char        x_work      [LEN_RECD]  = "";
   static char x_print     [LEN_RECD]  = "";
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   c = ystrldcnt (a_recd, '"', LEN_RECD);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL || a_recd [0] == '\0') {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return "((null/empty))";
   }
   DEBUG_INPT   yLOG_info    ("a_recd"    , a_recd);
   --rce;  if (strncmp (a_recd, "#define ", 8) != 0)  {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return "((not #define))";
   }
   DEBUG_INPT   yLOG_value   ("c"         , c);
   --rce;  if (c < 2) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return "((too few quotes))";
   }
   l = strlen (a_recd);
   DEBUG_INPT   yLOG_value   ("l"         , l);
   --rce;  if (l < 12) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return "((way too short))";
   }
   /*---(prepare)------------------------*/
   ystrlcpy  (x_work, a_recd, LEN_RECD);
   ystrltrim (x_work, ySTR_SINGLE, LEN_RECD);
   DEBUG_INPT   yLOG_info    ("x_work"    , x_work);
   /*---(verify label)-------------------*/
   for (c = 0, i = 8; i < l; ++i) {
      if (x_work [i] == ' ')  break;
      ++c;
   }
   DEBUG_INPT   yLOG_value   ("c"         , c);
   --rce;  if (c <= 4) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return "((name too short))";
   }
   --rce;  if (c >= 12) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return "((name too long))";
   }
   ystrlcpy (x_label, x_work + 8, c + 1);
   DEBUG_INPT   yLOG_info    ("x_label"   , x_label);
   --rce;  if (strncmp (x_label, "P_", 2) != 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return "((not P_ prefix))";
   }
   /*---(remove continuations)-----------*/
   ystrlddel (x_work, '\\', LEN_RECD);
   /*---(remove quotes)------------------*/
   p = x_work + 8 + c + 1;
   DEBUG_INPT   yLOG_char    ("p [0]"     , p [0]);
   --rce;  if (p [0] != '"') {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return "((lead \" wrong))";
   }
   ystrlddel (p + 1, '"', LEN_RECD);
   ystrldchg (p    , '¦', ' ', LEN_RECD);
   ystrltrim (p + 1, ySTR_SINGLE, LEN_RECD);
   ystrlcat  (x_work, "\"", LEN_RECD);
   DEBUG_INPT   yLOG_info    ("x_work"    , x_work);
   /*---(combine)------------------------*/
   snprintf (x_print, LEN_RECD, "#define %-12.12s %s", x_label, p);
   DEBUG_INPT   yLOG_info    ("x_print"   , x_print);
   /*---(complete)----------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return x_print;
}

char
poly_header_summarize   (tPROJ *a_proj)
{
   /*---(locals)-----------+-----------+-*/
   int         i           =    0;
   char        x_namesake  [LEN_HUND]  = "";
   char        x_subject   [LEN_HUND]  = "";
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   for (i = 0; i < LEN_FULL; ++i) {
      /*---(filter)----------------------*/
      if (s_header [i].h_abbr == 0)               break;
      DEBUG_INPT   yLOG_complex ("line"      , "%2d (%4d) %s", i, s_header [i].h_abbr, s_header [i].h_label);
      if (s_header [i].h_abbr == 1)               continue;
      if (strcmp (s_header [i].h_name, "") == 0)  continue;
      if (s_header [i].h_offset < 0)              continue;
      /*---(oneline actions)-------------*/
      if (strcmp (s_header [i].h_label, "subject" ) == 0)   ystrlcpy (x_subject , (long) a_proj + s_header [i].h_offset, LEN_HUND);
      if (strcmp (s_header [i].h_label, "namesake") == 0)   ystrlcpy (x_namesake, (long) a_proj + s_header [i].h_offset, LEN_HUND);
      if (strcmp (s_header [i].h_label, "oneline" ) == 0) {
         if      (strcmp (x_namesake, "") == 0)  ;
         else if (strcmp (x_subject , "") == 0)  ;
         else    snprintf ((long) a_proj + s_header [i].h_offset, LEN_HUND, "%s %s", x_namesake, x_subject);
      }
      /*---(record)----------------------*/
      if (s_header [i].h_type != '!')  {
         poly_header__encode (a_proj->j_header, i, s_header [i].h_abbr,
               (long) a_proj + s_header [i].h_offset,
               s_header [i].h_min, s_header [i].h_low, s_header [i].h_high, s_header [i].h_max); }
      /*---(done)------------------------*/
   }
   /*---(complete)----------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
poly_header_read        (tFILE *a_file)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_type      =  '·';
   char        x_curr      [LEN_RECD]  = "";
   char        x_prev      [LEN_RECD]  = "";
   int         l           =    0;
   int         x_bef       =  '·';
   int         x_suf       =  '·';
   int         x_line      =    0;
   int         x_append    =  '-';
   char       *p           = NULL;
   char        x_full      [LEN_RECD]  = "";
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(quick-out)----------------------*/
   x_type = a_file->i_type;
   DEBUG_INPT   yLOG_char    ("x_type"    , x_type);
   if (x_type != 'h') {
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(open file)----------------------*/
   DEBUG_INPT   yLOG_info    ("i_name"    , a_file->i_name);
   rc = poly_shared_open ('c', a_file->i_name);
   DEBUG_INPT   yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(walk)---------------------------*/
   --rce;  while (rc >= 0) {
      /*---(read)------------------------*/
      rc = poly_shared_read ('c', &x_line, x_curr, x_prev);
      DEBUG_INPT   yLOG_value   ("read"      , rc);
      if (rc < 0)  {
         DEBUG_INPT   yLOG_note    ("reading of line failed or eof");
         break;
      }
      DEBUG_INPT   yLOG_value   ("x_line"    , x_line);
      /*---(check multi-line)------------*/
      x_bef = x_suf = ' ';
      ystrltrim (x_curr, ySTR_BOTH, LEN_RECD);
      l = strlen (x_curr);
      if (l >  5)  { x_suf = x_curr [l - 1]; x_bef = x_curr [l - 2]; }
      DEBUG_INPT   yLOG_complex ("chars"     , "%3d, suf=%c, bef=%c", l, x_suf, x_bef);
      if (strncmp (x_curr, "#define ", 8) == 0 && x_suf == '\\' && x_bef != '*') {
         DEBUG_INPT   yLOG_note    ("handle first line of multi-line #define");
         x_append = 'y';
         x_curr [l - 1] = '\0';
         ystrlcpy (x_full, x_curr, LEN_RECD);
         ystrlcat (x_full, "   ", LEN_RECD);
         DEBUG_INPT   yLOG_info    ("x_full"    , x_full);
         continue;
      }
      if (x_append == 'y') {
         DEBUG_INPT   yLOG_note    ("handle continuing line of multi-line #define");
         x_curr [l - 1] = '\0';
         ystrlcat (x_full, x_curr, LEN_RECD);
         ystrlcat (x_full, "   ", LEN_RECD);
         DEBUG_INPT   yLOG_info    ("x_full"    , x_full);
         if (x_suf == '\\' && x_bef != '*') continue;
         x_append = '-';
         ystrlcpy (x_curr, poly_header__macro_fix (x_full), LEN_RECD);
      }
      /*---(check headers)---------------*/
      DEBUG_INPT   yLOG_info    ("x_curr"    , x_curr);
      rc = poly_header__single  (a_file->i_proj, x_curr);
      DEBUG_INPT   yLOG_value   ("oneliner"  , rc);
      /*---(done)------------------------*/
   }
   /*---(close)--------------------------*/
   rc = poly_shared_close ('c');
   DEBUG_INPT   yLOG_value   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                      writing reports                         ----===*/
/*====================------------------------------------====================*/
static void  o___REPORTING_______o () { return; }

char*
poly_header__report     (tPROJ *a_proj, char a_type, char a_label [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   short       n           =    0;
   short       x_max       =    0;
   short       x_len       =    0;
   short       x_pre       =    0;
   short       x_suf       =    0;
   static char x_print     [LEN_HUND]  = "";
   char        t           [LEN_HUND]  = "";
   /*---(default)------------------------*/
   strcpy (x_print, "");
   /*---(find)---------------------------*/
   n = poly_header__find (a_label);
   if (n < 0)  return "((boom))";
   /*---(prepare label)------------------*/
   x_max = s_header [n].h_high;
   x_len = strlen (s_header [n].h_label);
   switch (a_type) {
   case POLY_RPTG_HEAD  :
      if      (x_len + 3 < x_max)  { x_pre = 3;  x_suf = x_max - x_len - x_pre; }
      else if (x_len     < x_max)  { x_pre = x_max - x_len; }
      ystrlcat (x_print, "---", x_pre + 1);
      ystrlcat (x_print, s_header [n].h_label, x_max + 1);
      ystrlcat (x_print, YSTR_DASH           , x_max + 1);
      ystrlcat (x_print, " "                 , x_max + 2);
      break;
   case POLY_RPTG_SIZER :
      ystrlcat (x_print, "Ï", x_max);
      ystrlcat (x_print, YSTR_DASH           , x_max + 1);
      ystrlcat (x_print, "·"                 , x_max + 2);
      break;
   case POLY_RPTG_TITLE :
      if      (x_len     < x_max)  { x_suf = x_max - x_len; }
      ystrlcat (x_print, s_header [n].h_label, x_max + 1);
      ystrlcat (x_print, YSTR_EDOTS          , x_max + 2);
      break;
   case POLY_RPTG_DATA  :
      if (a_proj != NULL)  snprintf (x_print, x_max + 1, "%-*.*s", x_max + 1, x_max + 1, (long) a_proj + s_header [n].h_offset);
      else                 snprintf (x_print, x_max + 1, "((boom))");
      ystrlcat (x_print, " "                 , x_max + 2);
      break;
   }
   return x_print;
}

char
poly_header_report      (tPROJ *a_proj)
{
   int         i           =    0;
   char        s           [LEN_HUND]  = "";
   char        t           [LEN_HUND]  = "";
   char       *x_sep       = "##   ··········  -  -  -  --  ··········´·········´·········´·········´·········´·········´·········´···········  --  ···name·····  - ··ptr ··min ··low ··hig ··max  ···description················";
   char       *p           = NULL;
   uchar       x_pass      =  '·';
   uchar       x_mark      =  '·';
   uchar       x_grade     =  '·';
   char        x_miss      =    0;
   char        x_warn      =    0;
   char        x_fail      =    0;
   int         l           =    0;
   /*> yURG_msg (' ', "##/usr/local/bin/polymnia --htags\n");                         <*/
   /*> yURG_msg (' ', "##");                                                          <*/
   /*> yURG_msg (' ', "##   %s", P_ONELINE);                                          <*/
   /*> yURG_msg (' ', "##   ver %4s, %s", P_VERNUM, P_VERTXT);                        <*/
   /*> yURG_msg (' ', "##   htags reporting file for use with vim-ide");              <*/
   /*> yURG_msg (' ', "##");                                                          <*/
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(summary)------------------------*/
   DEBUG_INPT   yLOG_note    ("summary");
   yURG_msg (' ', "##   %2d headers ·  å%sæ", poly_header_count (), a_proj->j_header);
   yURG_msg (' ', "##          legend å-- focu·greek··o·loca··tech·depend··au·ver··gpl···extr·why·······what····!æ");
   DEBUG_INPT   yLOG_note    ("header");
   yURG_msg (' ', "##");
   yURG_msg (' ', x_sep);
   yURG_msg (' ', "##");
   for (i = 0; i < LEN_FULL; ++i) {
      /*---(next)------------------------*/
      if (s_header [i].h_abbr == 0)  break;
      DEBUG_INPT   yLOG_complex ("line"      , "%2d (%4d) %s", i, s_header [i].h_abbr, s_header [i].h_label);
      /*---(spacers)---------------------*/
      if (s_header [i].h_abbr == 1) {
         yURG_msg (' ', "##");
         yURG_msg (' ', x_sep);
         yURG_msg (' ', "##");
         continue;
      }
      /*---(touch up)--------------------*/
      strcpy  (t, "··  åæ");
      if (s_header [i].h_offset >= 0) {
         p = (long) a_proj + s_header [i].h_offset;
         sprintf (t, "%2d  å%sæ", strlen (p), p);
      } else if (strcmp (s_header [i].h_label, "GRADE") == 0)  {
         strcpy  (t, "··  ");
         l = strlen (t);
         DEBUG_INPT   yLOG_complex ("stats"     , "%2dF, %2dw, %2dm", x_fail, x_warn, x_miss);
         DEBUG_INPT   yLOG_char    ("final"     , a_proj->j_header [i]);
         if (x_fail > 0) {
            sprintf (s, "FAILURES = %2d", x_fail);
            strcat  (t, s);
            if (a_proj->j_header [i] != (uchar) ' ')  a_proj->j_header [i] = '°';
         }
         if (x_warn > 0) {
            if (strlen (t) > l)  strcat (t, "   ");
            sprintf (s, "warnings = %2d", x_warn);
            strcat  (t, s);
            if (a_proj->j_header [i] != (uchar) ' ')  a_proj->j_header [i] = '¡';
         }
         if (x_miss > 0) {
            if (strlen (t) > l)  strcat (t, "   ");
            sprintf (s, "missing  = %2d", x_miss);
            strcat  (t, s);
            if (a_proj->j_header [i] != (uchar) ' ')  a_proj->j_header [i] = '¢';
         }
         DEBUG_INPT   yLOG_char    ("final"     , a_proj->j_header [i]);
         if (x_miss + x_warn + x_fail == 0) {
            strcat  (t, "header audit pass");
         }
      }
      /*---(evaluate)--------------------*/
      x_pass = s_header [i].h_abbr;
      x_mark = a_proj->j_header [i];
      if      (x_pass == x_mark) { x_grade = '´';            }
      else if (x_mark == '·')    { x_grade = '·';  if (s_header [i].h_type == '°')  ++x_miss; }
      else if (x_mark == '-')    { x_grade = '-';            }
      else if (x_mark == '<')    { x_grade = '<';  if (s_header [i].h_type == '°')  ++x_warn; }
      else if (x_mark == '>')    { x_grade = '>';  if (s_header [i].h_type == '°')  ++x_warn; }
      else                       { x_grade = '°';  if (s_header [i].h_type == '°')  ++x_fail; }
      /*---(display)---------------------*/
      yURG_msg (' ', "##   %-10.10s  %c  %c  %c  %-86.86s  %2d  %-12.12s  %c %5d %4dn %4dl %4dh %4dx  %s", s_header [i].h_label, s_header [i].h_abbr, x_mark, x_grade, t, i, s_header [i].h_name, s_header [i].h_type, s_header [i].h_offset, s_header [i].h_min, s_header [i].h_low, s_header [i].h_high, s_header [i].h_max, s_header [i].h_desc);
      /*---(done)------------------------*/
   }
   yURG_msg (' ', "##");
   yURG_msg (' ', x_sep);
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
poly_header_only        (char a_file [LEN_PATH])
{
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   char        x_suffix    [LEN_TERSE] = "";
   tPROJ      *x_proj      = NULL;
   tFILE      *x_file      = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      exit (rce);
   }
   DEBUG_INPT   yLOG_info    ("a_file"    , a_file);
   l = strlen (a_file);
   DEBUG_INPT   yLOG_value   ("l"         , l);
   --rce;  if (l < 3) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      exit (rce);
   }
   ystrlcpy (x_suffix, a_file + l - 2, LEN_TERSE);
   DEBUG_INPT   yLOG_info    ("x_suffix"  , x_suffix);
   --rce;  if (strcmp (x_suffix, ".h") != 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      exit (rce);
   }
   /*---(create fake project)------------*/
   rc = poly_proj_add ("header_audit", "/tmp", &x_proj);
   DEBUG_INPT   yLOG_value   ("proj add"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      exit (rce);
   }
   DEBUG_INPT   yLOG_point   ("x_proj"    , x_proj);
   /*---(create file)--------------------*/
   rc = poly_file_add (x_proj, a_file, 'h', &x_file);
   DEBUG_INPT   yLOG_value   ("file add"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      exit (rce);
   }
   /*---(read file)----------------------*/
   rc = poly_header_read (x_file);
   DEBUG_INPT   yLOG_value   ("read"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      exit (rce);
   }
   /*---(suppmarize)---------------------*/
   rc = poly_header_summarize (x_proj);
   DEBUG_INPT   yLOG_value   ("summarize" , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      exit (rce);
   }
   /*---(write report)-------------------*/
   rc = poly_header_report (x_proj);
   DEBUG_INPT   yLOG_value   ("report"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      exit (rce);
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   exit(1);
}

char* poly_header__show       (tPROJ *a_proj) { if (a_proj == NULL)  return "(null)"; return a_proj->j_header; }

