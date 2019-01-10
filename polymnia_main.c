/*============================----beg-of-source---============================*/
#include   "htags.h"




int          /*-> tbd --------------------------------[ ------ [gn.842.232.99]*/ /*-[01.0000.000.!]-*/ /*-[--.---.---.--]-*/
main (int argc, char *argv[])
{
   /*---(locals)-----------+-----------+-*/
   char        rc          = 0;
   int         i           =    0;
   /*---(initialize)---------------------*/
   if (rc >= 0)  rc = yURG_logger  (argc, argv);
   if (rc >= 0)  rc = yURG_urgs    (argc, argv);
   if (rc >= 0)  rc = PROG_init    (argc, argv);
   if (rc >= 0)  rc = PROG_args    (argc, argv);
   if (rc >= 0)  rc = PROG_begin   ();
   if (rc >= 0)  rc = PROG_final   ();
   if (rc <  0) {
      PROG_end ();
      return -1;
   }
   /*---(main loop)----------------------*/
   for (i = 0; i < s_nfile; ++i) {
      htags_tags_inventory (i);
      htags_tags_review    (i);
      printf ("   file= %25.25s %3d %3d %3d %3d %3d %3d\n",
            s_files [i].name ,
            s_files [i].lines, s_files [i].empty, 
            s_files [i].docs , s_files [i].debug, 
            s_files [i].code , s_files [i].slocl);
   }
   /*---(wrap-up)------------------------*/
   PROG_end     ();
   /*---(complete)-----------------------*/
   return 0;
}



/*============================----end-of-source---============================*/
