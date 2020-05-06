;; C Compilation to J-- Code
;; File: final/gen_t18.wat
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
    (global $G_havechar (mut i32) (i32.const 0))
    (global $G_char (mut i32) (i32.const 0))
    (global $G_havetoken (mut i32) (i32.const 0))
    (global $G_token (mut i32) (i32.const 0))
    (global $Gattr (mut i32) (i32.const 0))
    (global $GEOF (mut i32) (i32.const 0))
    (global $GTK_EOF (mut i32) (i32.const 0))
    (global $GTK_EOLN (mut i32) (i32.const 0))
    (global $GTK_NUMBER (mut i32) (i32.const 0))
    (global $GTK_ADD (mut i32) (i32.const 0))
    (global $GTK_SUB (mut i32) (i32.const 0))
    (global $GTK_MUL (mut i32) (i32.const 0))
    (global $GTK_DIV (mut i32) (i32.const 0))
    (global $GTK_LPAREN (mut i32) (i32.const 0))
    (global $GTK_RPAREN (mut i32) (i32.const 0))
    (global $GASCII_0 (mut i32) (i32.const 0))
    (global $GASCII_9 (mut i32) (i32.const 0))
    (global $GASCII_PLUS (mut i32) (i32.const 0))
    (global $GASCII_MINUS (mut i32) (i32.const 0))
    (global $GASCII_STAR (mut i32) (i32.const 0))
    (global $GASCII_SLASH (mut i32) (i32.const 0))
    (global $GASCII_LPAREN (mut i32) (i32.const 0))
    (global $GASCII_RPAREN (mut i32) (i32.const 0))
    (global $GASCII_SPACE (mut i32) (i32.const 0))
    (global $GASCII_TAB (mut i32) (i32.const 0))
    (global $GASCII_CR (mut i32) (i32.const 0))
    (global $GASCII_NL (mut i32) (i32.const 0))
    (func $calculator        
        (local $T0 i32)
        (local $T1 i32)
        call $init
        call $parser
    )
    (func $getc (result i32)        
        (local $T0 i32)
        (local $T1 i32)
        (block $B0
            global.get $G_havechar
            i32.eqz
            br_if $B0
            i32.const 0
            global.set $G_havechar
            global.get $G_char
            return
        )
        call $getchar
        local.set $T0
        local.get $T0
        return
        i32.const -1
        return
    )
    (func $ungetc  (param $Ich i32)        
        (local $T0 i32)
        (local $T1 i32)
        (block $B0
            global.get $G_havechar
            i32.eqz
            br_if $B0
            i32.const 11
            i32.const 34
            call $prints
            call $halt
        )
        i32.const 1
        global.set $G_havechar
        local.get $Ich
        global.set $G_char
    )
    (func $peek (result i32)        
        (local $T0 i32)
        (local $T1 i32)
        (block $B0
            global.get $G_havetoken
            i32.eqz
            br_if $B0
            global.get $G_token
            return
        )
        i32.const 1
        global.set $G_havetoken
        call $scanner
        local.set $T0
        local.get $T0
        global.set $G_token
        global.get $G_token
        return
        i32.const -1
        return
    )
    (func $match  (param $Iexpect i32)        
        (local $T0 i32)
        (local $T1 i32)
        (block $B0
            call $peek
            local.set $T0
            local.get $T0
            local.get $Iexpect
            i32.ne
            i32.eqz
            br_if $B0
            i32.const 49
            i32.const 16
            call $prints
            local.get $Iexpect
            call $printc
            i32.const 69
            i32.const 2
            call $prints
            call $halt
        )
        i32.const 0
        global.set $G_havetoken
    )
    (func $scanner (result i32)        
        (local $T0 i32)
        (local $T1 i32)
        (local $Ich i32)
        (block $B0
            (loop $L0
                call $getc
                local.set $T0
                local.get $T0
                local.set $Ich
                local.get $Ich
                call $isspace
                local.set $T0
                local.get $T0
                i32.eqz
                br_if $B0
                br $L0
            )
        )
        (block $B1
            local.get $Ich
            global.get $GEOF
            i32.eq
            i32.eqz
            br_if $B1
            global.get $GTK_EOF
            return
        )
        (block $B2
            local.get $Ich
            global.get $GASCII_NL
            i32.eq
            i32.eqz
            br_if $B2
            global.get $GTK_EOLN
            return
        )
        (block $B3
            local.get $Ich
            global.get $GASCII_PLUS
            i32.eq
            i32.eqz
            br_if $B3
            global.get $GTK_ADD
            return
        )
        (block $B4
            local.get $Ich
            global.get $GASCII_MINUS
            i32.eq
            i32.eqz
            br_if $B4
            global.get $GTK_SUB
            return
        )
        (block $B5
            local.get $Ich
            global.get $GASCII_STAR
            i32.eq
            i32.eqz
            br_if $B5
            global.get $GTK_MUL
            return
        )
        (block $B6
            local.get $Ich
            global.get $GASCII_SLASH
            i32.eq
            i32.eqz
            br_if $B6
            global.get $GTK_DIV
            return
        )
        (block $B7
            local.get $Ich
            global.get $GASCII_LPAREN
            i32.eq
            i32.eqz
            br_if $B7
            global.get $GTK_LPAREN
            return
        )
        (block $B8
            local.get $Ich
            global.get $GASCII_RPAREN
            i32.eq
            i32.eqz
            br_if $B8
            global.get $GTK_RPAREN
            return
        )
        (block $B9
            local.get $Ich
            call $isdigit
            local.set $T0
            local.get $T0
            i32.eqz
            br_if $B9
            i32.const 0
            global.set $Gattr
            (block $B10
                (loop $L1
                    local.get $Ich
                    call $isdigit
                    local.set $T0
                    local.get $T0
                    i32.eqz
                    br_if $B10
                    global.get $Gattr
                    i32.const 10
                    i32.mul
                    local.get $Ich
                    global.get $GASCII_0
                    i32.sub
                    i32.add
                    global.set $Gattr
                    call $getc
                    local.set $T0
                    local.get $T0
                    local.set $Ich
                    br $L1
                )
            )
            local.get $Ich
            call $ungetc
            global.get $GTK_NUMBER
            return
        )
        i32.const 75
        i32.const 27
        call $prints
        call $halt
        i32.const -1
        return
    )
    (func $isdigit  (param $Ich i32) (result i32)        
        (local $T0 i32)
        (local $T1 i32)
        (block $B0
            local.get $Ich
            global.get $GASCII_0
            i32.ge_s
            local.set $T1
            local.get $T1
            i32.eqz
            br_if $B0
            local.get $T1
            local.get $Ich
            global.get $GASCII_9
            i32.le_s
            i32.and
            local.set $T1
        )
        local.get $T1
        return
        i32.const -1
        return
    )
    (func $isspace  (param $Ich i32) (result i32)        
        (local $T0 i32)
        (local $T1 i32)
        (block $B0
            (block $B1
                local.get $Ich
                global.get $GASCII_SPACE
                i32.eq
                local.set $T1
                local.get $T1
                i32.const 1
                i32.eq
                br_if $B1
                local.get $T1
                local.get $Ich
                global.get $GASCII_TAB
                i32.eq
                i32.or
                local.set $T1
            )
            local.get $T1
            local.set $T1
            local.get $T1
            i32.const 1
            i32.eq
            br_if $B0
            local.get $T1
            local.get $Ich
            global.get $GASCII_CR
            i32.eq
            i32.or
            local.set $T1
        )
        local.get $T1
        return
        i32.const -1
        return
    )
    (func $parser        
        (local $T0 i32)
        (local $T1 i32)
        (local $Iresult i32)
        (block $B0
            (loop $L0
                call $peek
                local.set $T0
                local.get $T0
                global.get $GTK_EOF
                i32.ne
                i32.eqz
                br_if $B0
                call $E
                local.set $T0
                local.get $T0
                local.set $Iresult
                global.get $GTK_EOLN
                call $match
                i32.const 106
                i32.const 3
                call $prints
                local.get $Iresult
                call $printi
                i32.const 113
                i32.const 2
                call $prints
                br $L0
            )
        )
    )
    (func $E (result i32)        
        (local $T0 i32)
        (local $T1 i32)
        (local $Il i32)
        (local $Ir i32)
        (local $Itoken i32)
        call $T
        local.set $T0
        local.get $T0
        local.set $Il
        (block $B0
            (loop $L0
                (block $B1
                    call $peek
                    local.set $T0
                    local.get $T0
                    global.get $GTK_ADD
                    i32.eq
                    local.set $T1
                    local.get $T1
                    i32.const 1
                    i32.eq
                    br_if $B1
                    local.get $T1
                    call $peek
                    local.set $T0
                    local.get $T0
                    global.get $GTK_SUB
                    i32.eq
                    i32.or
                    local.set $T1
                )
                local.get $T1
                i32.eqz
                br_if $B0
                call $peek
                local.set $T0
                local.get $T0
                local.set $Itoken
                local.get $Itoken
                call $match
                call $T
                local.set $T0
                local.get $T0
                local.set $Ir
                (block $B2
                    (block $B3
                        local.get $Itoken
                        global.get $GTK_ADD
                        i32.eq
                        i32.eqz
                        br_if $B3
                        local.get $Il
                        local.get $Ir
                        i32.add
                        local.set $Il
                        br $B2
                    )
                    local.get $Il
                    local.get $Ir
                    i32.sub
                    local.set $Il
                )
                br $L0
            )
        )
        local.get $Il
        return
        i32.const -1
        return
    )
    (func $T (result i32)        
        (local $T0 i32)
        (local $T1 i32)
        (local $Il i32)
        (local $Ir i32)
        (local $Itoken i32)
        call $F
        local.set $T0
        local.get $T0
        local.set $Il
        (block $B0
            (loop $L0
                (block $B1
                    call $peek
                    local.set $T0
                    local.get $T0
                    global.get $GTK_MUL
                    i32.eq
                    local.set $T1
                    local.get $T1
                    i32.const 1
                    i32.eq
                    br_if $B1
                    local.get $T1
                    call $peek
                    local.set $T0
                    local.get $T0
                    global.get $GTK_DIV
                    i32.eq
                    i32.or
                    local.set $T1
                )
                local.get $T1
                i32.eqz
                br_if $B0
                call $peek
                local.set $T0
                local.get $T0
                local.set $Itoken
                local.get $Itoken
                call $match
                call $F
                local.set $T0
                local.get $T0
                local.set $Ir
                (block $B2
                    (block $B3
                        local.get $Itoken
                        global.get $GTK_MUL
                        i32.eq
                        i32.eqz
                        br_if $B3
                        local.get $Il
                        local.get $Ir
                        i32.mul
                        local.set $Il
                        br $B2
                    )
                    local.get $Il
                    local.get $Ir
                    i32.div_s
                    local.set $Il
                )
                br $L0
            )
        )
        local.get $Il
        return
        i32.const -1
        return
    )
    (func $F (result i32)        
        (local $T0 i32)
        (local $T1 i32)
        (local $Iresult i32)
        (local $Itoken i32)
        call $peek
        local.set $T0
        local.get $T0
        local.set $Itoken
        (block $B0
            (block $B1
                local.get $Itoken
                global.get $GTK_LPAREN
                i32.eq
                i32.eqz
                br_if $B1
                global.get $GTK_LPAREN
                call $match
                call $E
                local.set $T0
                local.get $T0
                local.set $Iresult
                global.get $GTK_RPAREN
                call $match
                br $B0
            )
            (block $B2
                local.get $Itoken
                global.get $GTK_SUB
                i32.eq
                i32.eqz
                br_if $B2
                global.get $GTK_SUB
                call $match
                i32.const 0
                call $F
                local.set $T0
                local.get $T0
                i32.sub
                local.set $Iresult
                br $B0
            )
            (block $B3
                local.get $Itoken
                global.get $GTK_NUMBER
                i32.eq
                i32.eqz
                br_if $B3
                global.get $GTK_NUMBER
                call $match
                global.get $Gattr
                local.set $Iresult
                br $B0
            )
            i32.const 119
            i32.const 25
            call $prints
            call $halt
        )
        local.get $Iresult
        return
        i32.const -1
        return
    )
    (func $init        
        (local $T0 i32)
        (local $T1 i32)
        i32.const 0
        i32.const 1
        i32.sub
        global.set $GEOF
        i32.const 48
        global.set $GASCII_0
        i32.const 57
        global.set $GASCII_9
        i32.const 43
        global.set $GASCII_PLUS
        i32.const 45
        global.set $GASCII_MINUS
        i32.const 42
        global.set $GASCII_STAR
        i32.const 47
        global.set $GASCII_SLASH
        i32.const 40
        global.set $GASCII_LPAREN
        i32.const 41
        global.set $GASCII_RPAREN
        i32.const 32
        global.set $GASCII_SPACE
        i32.const 9
        global.set $GASCII_TAB
        i32.const 13
        global.set $GASCII_CR
        i32.const 10
        global.set $GASCII_NL
        i32.const 256
        global.set $GTK_EOF
        i32.const 257
        global.set $GTK_NUMBER
        global.get $GASCII_PLUS
        global.set $GTK_ADD
        global.get $GASCII_MINUS
        global.set $GTK_SUB
        global.get $GASCII_STAR
        global.set $GTK_MUL
        global.get $GASCII_SLASH
        global.set $GTK_DIV
        global.get $GASCII_LPAREN
        global.set $GTK_LPAREN
        global.get $GASCII_RPAREN
        global.set $GTK_RPAREN
        global.get $GASCII_NL
        global.set $GTK_EOLN
    )
    (start $calculator)
    (data 0 (i32.const 0) "true")
    (data 0 (i32.const 5) "false")
    (data 0 (i32.const 11) "Internal error: too many ungets!\n")
    (data 0 (i32.const 49) "Error: expected ")
    (data 0 (i32.const 69) "\n")
    (data 0 (i32.const 75) "Error: invalid character.\n")
    (data 0 (i32.const 106) " = ")
    (data 0 (i32.const 113) "\n")
    (data 0 (i32.const 119) "Error: expected factor.\n")
    (memory 1)
)
