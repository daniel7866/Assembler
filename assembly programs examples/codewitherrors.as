;This file will contain errors

mov @r9,@r4
LABEL:		mov 19,20
LABEL: cmp 2,5

STOP: stop this_is_garbage_at_end_of_command
?
Mov 2,l3

STR: .string "this_is_a_bad_string
DATA: .data -3,9 7

.extern l3
.entry LABEL
