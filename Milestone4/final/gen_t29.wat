;; C Compilation to J-- Code
;; File: final/gen_t29.wat
;; Standard prelude:
(module
    (import "host" "exit" (func $exit))
    (import "host" "getchar" (func $getchar (result i32)))
    (import "host" "putchar" (func $putchar (param i32)))
    (func $halt
        call $exit
    )
    (func $printc (param $char i32)
        local.get $char
        call $putchar
    )
    (func $prints (param $offset i32) (param $length i32)
        (local $I0 i32)
        i32.const 0
        local.set $I0
        (block $B1
            (loop $L1
                local.get $length
                local.get $I0
                i32.le_s
                br_if $B1
                local.get $offset
                local.get $I0
                i32.add
                i32.load
                call $printc
                local.get $I0
                i32.const 1
                i32.add
                local.set $I0
                br $L1
            )
        )
    )
    (func $printb (param $b i32)
    ;; select with 3rd operand 0 selects 2nd operand
    ;; select with 3rd operand 1 selects 1st operand
        (local $I0 i32)
        i32.const 5
        i32.const 6
        local.get $b
        select
        local.set $I0
        i32.const 0
        i32.const 5
        local.get $b
        select
        local.get $I0
        call $prints
    )
    (func $printi (param $n i32)
        (local $I0 i32)
        (local $I1 i32)
        (block $B5
            local.get $n
            i32.const 0
            i32.ne
            br_if $B5
            i32.const 48
            call $printc
            return
        )
            i32.const 1000000000
            local.set $I0
            (block $B0
            (loop $L0
                local.get $n
                local.get $I0
                i32.div_s
                i32.const 0
                i32.gt_u
                br_if $B0
                local.get $I0
                i32.const 10
                i32.div_s
                local.set $I0
                br $L0
            )
        )
        (block $B2
            (loop $L2
                local.get $n
                i32.const 0
                i32.ge_s
                br_if $B2
                i32.const 45
                call $printc
            )
        )
        (block $B1
            (loop $L1
                local.get $I0
                i32.eqz
                br_if $B1
                local.get $n
                local.get $I0
                i32.div_s
                local.set $I1
                (block $B3
                    local.get $I1
                    i32.const 0
                    i32.gt_s
                    br_if $B3
                    i32.const 0
                    local.get $I1
                    i32.sub
                    local.set $I1
                )
                local.get $I1
                i32.const 10
                i32.rem_u
                i32.const 48
                i32.add
                call $printc
                local.get $I0
                i32.const 10
                i32.div_s
                local.set $I0
                br $L1
            )
        )
    )
;; End of standard prelude.
    (global $Ga (mut i32) (i32.const 0))
    (global $Gb (mut i32) (i32.const 0))
    (global $Gc (mut i32) (i32.const 0))
    (func $A (result i32)        
        (local $T0 i32)
        i32.const 11
        i32.const 13
        call $prints
        global.get $Ga
        return
        i32.const -1
        return
    )
    (func $B (result i32)        
        (local $T0 i32)
        i32.const 28
        i32.const 13
        call $prints
        global.get $Gb
        return
        i32.const -1
        return
    )
    (func $C (result i32)        
        (local $T0 i32)
        i32.const 45
        i32.const 13
        call $prints
        global.get $Gc
        return
        i32.const -1
        return
    )
    (func $eval  (param $Inewa i32)  (param $In00b i32)  (param $Inewc i32)        
        (local $T0 i32)
        local.get $Inewa
        global.set $Ga
        local.get $In00b
        global.set $Gb
        local.get $Inewc
        global.set $Gc
        i32.const 62
        i32.const 44
        call $prints
        global.get $Ga
        call $printb
        i32.const 110
        i32.const 3
        call $prints
        global.get $Gb
        call $printb
        i32.const 117
        i32.const 3
        call $prints
        global.get $Gc
        call $printb
        i32.const 124
        i32.const 2
        call $prints
        (block $B0
            (block $B1
                call $A
                local.set $T0
                local.get $T0
                call $B
                local.set $T0
                local.get $T0
                i32.and
                call $C
                local.set $T0
                local.get $T0
                i32.or
                i32.eqz
                br_if $B1
                i32.const 130
                i32.const 18
                call $prints
                br $B0
            )
            i32.const 152
            i32.const 20
            call $prints
        )
    )
    (func $assign  (param $Inewa i32)  (param $Inewb i32)  (param $Inewc i32)        
        (local $T0 i32)
        (local $Ix i32)
        local.get $Inewa
        global.set $Ga
        local.get $Inewb
        global.set $Gb
        local.get $Inewc
        global.set $Gc
        i32.const 176
        i32.const 27
        call $prints
        global.get $Ga
        call $printb
        i32.const 207
        i32.const 3
        call $prints
        global.get $Gb
        call $printb
        i32.const 214
        i32.const 3
        call $prints
        global.get $Gc
        call $printb
        i32.const 221
        i32.const 2
        call $prints
        call $A
        local.set $T0
        local.get $T0
        call $B
        local.set $T0
        local.get $T0
        i32.const 1
        i32.xor
        i32.and
        call $C
        local.set $T0
        local.get $T0
        i32.or
        local.set $Ix
        i32.const 227
        i32.const 2
        call $prints
        local.get $Ix
        call $printb
        i32.const 233
        i32.const 2
        call $prints
    )
    (func $main        
        (local $T0 i32)
        i32.const 0
        i32.const 0
        i32.const 0
        call $eval
        i32.const 239
        i32.const 2
        call $prints
        i32.const 0
        i32.const 0
        i32.const 1
        call $eval
        i32.const 245
        i32.const 2
        call $prints
        i32.const 0
        i32.const 1
        i32.const 0
        call $eval
        i32.const 251
        i32.const 2
        call $prints
        i32.const 0
        i32.const 1
        i32.const 1
        call $eval
        i32.const 257
        i32.const 2
        call $prints
        i32.const 1
        i32.const 0
        i32.const 0
        call $eval
        i32.const 263
        i32.const 2
        call $prints
        i32.const 1
        i32.const 0
        i32.const 1
        call $eval
        i32.const 269
        i32.const 2
        call $prints
        i32.const 1
        i32.const 1
        i32.const 0
        call $eval
        i32.const 275
        i32.const 2
        call $prints
        i32.const 1
        i32.const 1
        i32.const 1
        call $eval
        i32.const 281
        i32.const 2
        call $prints
        i32.const 0
        i32.const 0
        i32.const 0
        call $assign
        i32.const 287
        i32.const 2
        call $prints
        i32.const 0
        i32.const 0
        i32.const 1
        call $assign
        i32.const 293
        i32.const 2
        call $prints
        i32.const 0
        i32.const 1
        i32.const 0
        call $assign
        i32.const 299
        i32.const 2
        call $prints
        i32.const 0
        i32.const 1
        i32.const 1
        call $assign
        i32.const 305
        i32.const 2
        call $prints
        i32.const 1
        i32.const 0
        i32.const 0
        call $assign
        i32.const 311
        i32.const 2
        call $prints
        i32.const 1
        i32.const 0
        i32.const 1
        call $assign
        i32.const 317
        i32.const 2
        call $prints
        i32.const 1
        i32.const 1
        i32.const 0
        call $assign
        i32.const 323
        i32.const 2
        call $prints
        i32.const 1
        i32.const 1
        i32.const 1
        call $assign
    )
    (start $main)
    (data 0 (i32.const 0) "true")
    (data 0 (i32.const 5) "false")
    (data 0 (i32.const 11) "evaluated A\n")
    (data 0 (i32.const 28) "evaluated B\n")
    (data 0 (i32.const 45) "evaluated C\n")
    (data 0 (i32.const 62) "if ((A && B) || C) {...} else {...}, with A=")
    (data 0 (i32.const 110) " B=")
    (data 0 (i32.const 117) " C=")
    (data 0 (i32.const 124) "\n")
    (data 0 (i32.const 130) "if-part executed\n")
    (data 0 (i32.const 152) "else-part executed\n")
    (data 0 (i32.const 176) "x = (A && !B) || C, with A=")
    (data 0 (i32.const 207) " B=")
    (data 0 (i32.const 214) " C=")
    (data 0 (i32.const 221) "\n")
    (data 0 (i32.const 227) "x=")
    (data 0 (i32.const 233) "\n")
    (data 0 (i32.const 239) "\n")
    (data 0 (i32.const 245) "\n")
    (data 0 (i32.const 251) "\n")
    (data 0 (i32.const 257) "\n")
    (data 0 (i32.const 263) "\n")
    (data 0 (i32.const 269) "\n")
    (data 0 (i32.const 275) "\n")
    (data 0 (i32.const 281) "\n")
    (data 0 (i32.const 287) "\n")
    (data 0 (i32.const 293) "\n")
    (data 0 (i32.const 299) "\n")
    (data 0 (i32.const 305) "\n")
    (data 0 (i32.const 311) "\n")
    (data 0 (i32.const 317) "\n")
    (data 0 (i32.const 323) "\n")
    (memory 1)
)
