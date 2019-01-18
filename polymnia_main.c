/*============================----beg-of-source---============================*/
#include   "polymnia.h"




int          /*-> tbd --------------------------------[ ------ [gn.842.232.99]*/ /*-[01.0000.000.!]-*/ /*-[--.---.---.--]-*/
main (int argc, char *argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tFILE      *x_file      = NULL;
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
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   DEBUG_PROG   yLOG_note    ("review all tags and code");
   x_file = (tFILE *) poly_btree_first (B_FILES);
   DEBUG_PROG   yLOG_point   ("x_file"    , x_file);
   while (x_file != NULL) {
      poly_tags_inventory (x_file);
      poly_tags_review    (x_file);
      /*> printf ("   file= %-25.25s %3d %3d %3d %3d %3d %3d\n",                      <* 
       *>       x_file->name , x_file->lines, x_file->empty,                          <* 
       *>       x_file->docs , x_file->debug, x_file->code , x_file->slocl);          <*/
      x_file = (tFILE *) poly_btree_next  (B_FILES);
      DEBUG_PROG   yLOG_point   ("x_file"    , x_file);
   }
   /*---(prepare for use)----------------*/
   DEBUG_PROG   yLOG_note    ("prepare tags for use");
   rc = poly_btree_dgnome   (B_TAGS);
   DEBUG_PROG   yLOG_value   ("dgnome"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = poly_btree_build (B_TAGS);
   DEBUG_PROG   yLOG_value   ("build"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(function calls)-----------------*/
   DEBUG_PROG   yLOG_note    ("review function calls");
   poly_extern_review ();
   /*> printf ("full= %3d %3d %3d %3d %3d %3d\n",                                     <* 
    *>       s_lines, s_empty,                                                        <* 
    *>       s_docs , s_debug,                                                        <* 
    *>       s_code , s_slocl);                                                       <*/
   PROG_report ('h');
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   /*---(wrap-up)------------------------*/
   PROG_end     ();
   /*---(complete)-----------------------*/
   return 0;
}



/*============================----end-of-source---============================*/
