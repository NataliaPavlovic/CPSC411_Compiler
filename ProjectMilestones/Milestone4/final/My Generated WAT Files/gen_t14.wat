;; C Compilation to J-- Code
;; File: final/gen_t14.wat
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
    (func $main        
        (local $T0 i32)
        (local $T1 i32)
        (local $Ii i32)
        (local $Idelta i32)
        i32.const 0
        local.set $Ii
        i32.const 1000000
        local.set $Idelta
        (block $B0
            (loop $L0
                local.get $Ii
                local.get $Ii
                local.get $Idelta
                i32.sub
                i32.gt_s
                i32.eqz
                br_if $B0
                local.get $Ii
                local.get $Idelta
                i32.add
                local.set $Ii
                br $L0
            )
        )
        local.get $Ii
        local.get $Idelta
        i32.sub
        local.set $Ii
        (block $B1
            (loop $L1
                local.get $Ii
                local.get $Ii
                i32.const 1
                i32.sub
                i32.gt_s
                i32.eqz
                br_if $B1
                local.get $Ii
                i32.const 1
                i32.add
                local.set $Ii
                br $L1
            )
        )
        i32.const 11
        i32.const 10
        call $prints
        local.get $Ii
        call $printi
        i32.const 25
        i32.const 2
        call $prints
    )
    (start $main)
    (data 0 (i32.const 0) "true")
    (data 0 (i32.const 5) "false")
    (data 0 (i32.const 11) "minint is ")
    (data 0 (i32.const 25) "\n")
    (memory 1)
)
