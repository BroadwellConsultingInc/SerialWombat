#include <xc.inc>

; When assembly code is placed in a psect, it can be manipulated as a
; whole by the linker and placed in memory.  
;
; In this example, barfunc is the program section (psect) name, 'local' means
; that the section will not be combined with other sections even if they have
; the same name.  class=CODE means the barfunc must go in the CODE container.
; PIC18's should have a delta (addressible unit size) of 1 (default) since they
; are byte addressible.  PIC10/12/16's have a delta of 2 since they are word
; addressible.  PIC18's should have a reloc (alignment) flag of 2 for any
; psect which contains executable code.  PIC10/12/16's can use the default
; reloc value of 1.  Use one of the psects below for the device you use:

psect   loadCompleteMarker,local,class=CODE,abs ; PIC10/12/16

  ORG 1FFEh   
    DW 14B7h    ; here we use a symbol defined via xc.inc
;psect  resetstub,global,class=CODE,delta=2,abs
;  ORG 0
;    pagesel 140h
;    GOTO 140h
  
;  ORG 4
;    pagesel 144h
;    GOTO 144h
