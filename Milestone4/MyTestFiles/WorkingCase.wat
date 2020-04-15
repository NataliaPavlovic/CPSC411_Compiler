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
    (global $Gr (mut i32) (i32.const 0))
    (global $Gb (mut i32) (i32.const 0))
    (func $main        
        (local $T0 i32)
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
        i32.const 2
        local.get $Ia
        call $func
        local.set $T0
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
        local.get $Ia
        call $printc
        (block $B2
            (loop $L0
                i32.const 1
                i32.eqz
                br_if $B2
                br $B2
                br $L0
            )
        )
        call $getchar
        local.set $T0
        local.get $T0
        local.set $Ic
        local.get $Ic
        call $printc
        i32.const 0
        i32.const 2147483648
        i32.sub
        call $printi
    )
    (func $findpow  (param $In i32) (result i32)        
        (local $T0 i32)
        (local $Ii i32)
        i32.const 10
        local.set $Ii
        (block $B0
            (loop $L0
                local.get $In
                local.get $Ii
                i32.div_s
                i32.const 0
                i32.gt_s
                i32.eqz
                br_if $B0
                local.get $Ii
                i32.const 10
                i32.mul
                local.set $Ii
                br $L0
            )
        )
        local.get $Ii
        i32.const 10
        i32.div_s
        local.set $Ii
        local.get $Ii
        return
        i32.const -1
        return
    )
    (func $func  (param $It i32)  (param $Ii i32)  (param $Iq i32) (result i32)        
        (local $T0 i32)
        (local $Ic i32)
        i32.const 6
        local.set $Ic
        i32.const 0
        i32.const 2
        i32.sub
        local.set $It
        (block $B0
            (loop $L0
                i32.const 1
                i32.eqz
                br_if $B0
                (block $B1
                    (loop $L1
                        i32.const 0
                        i32.eqz
                        br_if $B1
                        br $B1
                        br $L1
                    )
                )
                br $B0
                br $L0
            )
        )
        (block $B2
            (block $B3
                local.get $Ic
                local.get $It
                i32.lt_s
                i32.eqz
                br_if $B3
                i32.const 2
                local.set $Ic
                br $B2
            )
            (block $B4
                local.get $Ic
                local.get $It
                i32.eq
                i32.eqz
                br_if $B4
                i32.const 3
                local.set $Ic
                br $B2
            )
            (block $B5
                local.get $Ic
                local.get $It
                i32.gt_s
                i32.eqz
                br_if $B5
                i32.const 4
                local.set $It
                br $B2
            )
        )
        (block $B6
            (loop $L2
                local.get $Ic
                local.get $It
                i32.lt_s
                i32.eqz
                br_if $B6
                (block $B7
                    (loop $L3
                        i32.const 0
                        i32.eqz
                        br_if $B7
                        br $B7
                        br $L3
                    )
                )
                (block $B8
                    local.get $Ic
                    local.get $It
                    i32.eq
                    i32.eqz
                    br_if $B8
                    br $B6
                )
                br $L2
            )
        )
        i32.const 11
        i32.const 13
        call $prints
        i32.const 2
        i32.const 5
        i32.add
        return
        i32.const -1
        return
    )
    (start $main)
    (data 0 (i32.const 0) "true")
    (data 0 (i32.const 5) "false")
    (data 0 (i32.const 11) "Hello World\n")
    (memory 1)
)
