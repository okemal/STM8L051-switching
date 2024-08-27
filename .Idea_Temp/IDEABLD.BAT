REM       COMMAND FILE BUILT BY IDEA 
REM       Tue Aug 27 11:40:40 2024
REM
cxstm8 -v  +debug +modsl0 "stm8l051-switching_vector.c"
cxstm8 -v  +debug +modsl0 "main.c"
clnk -l"C:\Program Files (x86)\COSMIC\FSE_Compilers\CXSTM8\LIB" -o "STM8L051-switching.sm8" "STM8L051-switching.lkf"
