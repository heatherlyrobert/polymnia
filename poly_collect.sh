rm -f /var/lib/polymnia/external.txt

for X_FILE in $(cat /var/lib/polymnia/ext_files.txt); do
   printf "$X_FILE\n"
   ctags --language-force=c -x --sort=no --c-kinds=d  $X_FILE     | grep "^[A-Z][A-Z_ ][A-Z_ ][A-Z_ ][A-Z_ ][A-Z_ ][A-Z_ ][A-Z_ ][A-Z_ ]" | sort | uniq -w 20   >> /var/lib/polymnia/external.txt
   ctags --language-force=c -x --sort=no --c-kinds=p  $X_FILE     | grep "^[A-Za-z][A-Za-z0-9_ ][A-Za-z0-9_ ][A-Za-z0-9_ ][A-Za-z0-9_ ]"  | sort | uniq -w 20   >> /var/lib/polymnia/external.txt
   ctags --language-force=c -x --sort=no --c-kinds=x  $X_FILE     | grep "^[A-Za-z][A-Za-z0-9_ ][A-Za-z0-9_ ][A-Za-z0-9_ ][A-Za-z0-9_ ]"  | sort | uniq -w 20   >> /var/lib/polymnia/external.txt
done

sort       <    /var/lib/polymnia/external.txt > /tmp/polymnia_sorted.txt
uniq -w 20 <    /tmp/polymnia_sorted.txt       > /var/lib/polymnia/external.txt
rm -f /tmp/polymnia_sorted.txt

