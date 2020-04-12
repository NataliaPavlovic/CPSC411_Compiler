;; C Compilation to J-- Code
;; File: MyTestFiles/WorkingCase.wat
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
    (func $printi (param $n i32) (param $pow i32)
        (block $B2
            (loop $L2
                local.get $n
                i32.const 0
                i32.ge_s
                br_if $B2
                local.get $n
                i32.const -1
                i32.mul
                local.set $n
                i32.const 45
                call $printc
            )
        )
        (block $B1
            (loop $L1
                i32.const 0
                local.get $pow
                i32.ge_s
                br_if $B1
                local.get $n
                local.get $pow
                i32.div_u
                i32.const 10
                i32.rem_u
                i32.const 48
                i32.add
                call $printc
                local.get $pow
                i32.const 10
                i32.div_u
                local.set $pow
                br $L1
            )
        )
        i32.const 10	;; print newline character
        call $printc
    )
;; End of standard prelude.
    (global $Gr (mut i32) (i32.const 0))
    (global $Gb (mut i32) (i32.const 0))
    (func $main        
        (local $Ia i32)
        (local $Ib i32)
        (local $Ic i32)
        (local $Id i32)
        (local $Ie i32)
        i32.const 4
        local.set $Ia
        i32.const 0
        local.set $Ib
        local.get $Ia
        i32.const 1
        call $func
        i32.const 1
        local.set $Ic
        i32.const 2
        local.set $Id
        local.get $Ic
        local.get $Id
        i32.le_s
        local.set $Ib
        local.get $Ib
        i32.const 1
        i32.xor
        local.set $Ie
        (block $B0
            local.get $Ie
            i32.eqz
            br_if $B0
            i32.const 3
            local.set $Ic
            (block $B1
                local.get $Ic
                local.get $Id
                i32.gt_s
                i32.eqz
                br_if $B1
                i32.const 4
                local.set $Id
            )
            i32.const 5
            local.set $Ic
        )
        i32.const 65
        local.set $Ia
        i32.const 11
        i32.const 18
        call $prints
    )
    (func $func  (param $It i32)  (param $Ib i32)        
        (local $Ic i32)
        i32.const 6
        local.set $Ic
        i32.const 0
        i32.const 2
        i32.sub
        local.set $It
        return
    )
    (start $main)
    (data 0 (i32.const 0) "true\n")
    (data 0 (i32.const 5) "false\n")
    (memory 1)
)
