(module
  (import "host" "exit" (func $Lhalt))
  (import "host" "getchar" (func $Lgetchar (result i32)))
  (import "host" "putchar" (func $Lprintc (param i32)))
  ;;
  (start $L0)
  (global $G0 (mut i32) (i32.const 0))
  (global $G1 (mut i32) (i32.const 0))
  (global $G2 (mut i32) (i32.const 0))
  (global $G3 (mut i32) (i32.const 0))
  (global $G4 (mut i32) (i32.const 0))
  (global $G5 (mut i32) (i32.const 0))
  (global $G6 (mut i32) (i32.const 0))
  (global $G7 (mut i32) (i32.const 0))
  (global $G8 (mut i32) (i32.const 0))
  (global $G9 (mut i32) (i32.const 0))
  (global $G10 (mut i32) (i32.const 0))
  (global $G11 (mut i32) (i32.const 0))
  (global $G12 (mut i32) (i32.const 0))
  (global $G13 (mut i32) (i32.const 0))
  (global $G14 (mut i32) (i32.const 0))
  (global $G15 (mut i32) (i32.const 0))
  (global $G16 (mut i32) (i32.const 0))
  (global $G17 (mut i32) (i32.const 0))
  (global $G18 (mut i32) (i32.const 0))
  (global $G19 (mut i32) (i32.const 0))
  (global $G20 (mut i32) (i32.const 0))
  (global $G21 (mut i32) (i32.const 0))
  (global $G22 (mut i32) (i32.const 0))
  (global $G23 (mut i32) (i32.const 0))
  (global $G24 (mut i32) (i32.const 0))
  (global $G25 (mut i32) (i32.const 0))
  (global $G26 (mut i32) (i32.const 0))
  ;;
  ;; calculator
  ;;
  (func $L0
    call $L12
    call $L8
  )
  ;;
  ;; getc
  ;;
  (func $L1
    (result i32)
    (local $B0 i32)
    (local $I0 i32)
    global.get $G0
    local.set $B0
    local.get $B0
    (if
      (then
        i32.const 0
        local.set $B0
        local.get $B0
        global.set $G0
        global.get $G1
        local.set $I0
        local.get $I0
        return
      )
    )
    call $Lgetchar
    local.set $I0
    local.get $I0
    return
    (i32.const 0)
    call $_Lerror
    (i32.const 12345)
  )
  ;;
  ;; ungetc
  ;;
  (func $L2
    (param $C0 i32)
    (local $B0 i32)
    (local $I0 i32)
    global.get $G0
    local.set $B0
    local.get $B0
    (if
      (then
        i32.const 36
        i32.const 33
        call $Lprints
        call $Lhalt
      )
    )
    i32.const 1
    local.set $B0
    local.get $B0
    global.set $G0
    local.get $C0
    local.set $I0
    local.get $I0
    global.set $G1
  )
  ;;
  ;; peek
  ;;
  (func $L3
    (result i32)
    (local $B0 i32)
    (local $I0 i32)
    global.get $G2
    local.set $B0
    local.get $B0
    (if
      (then
        global.get $G3
        local.set $I0
        local.get $I0
        return
      )
    )
    i32.const 1
    local.set $B0
    local.get $B0
    global.set $G2
    call $L5
    local.set $I0
    local.get $I0
    global.set $G3
    local.get $I0
    return
    (i32.const 69)
    call $_Lerror
    (i32.const 12345)
  )
  ;;
  ;; match
  ;;
  (func $L4
    (param $C0 i32)
    (local $B0 i32)
    (local $I0 i32)
    (local $I1 i32)
    call $L3
    local.set $I0
    local.get $C0
    local.set $I1
    local.get $I0
    local.get $I1
    i32.ne
    local.set $B0
    local.get $B0
    (if
      (then
        i32.const 105
        i32.const 16
        call $Lprints
        local.get $C0
        local.set $I0
        local.get $I0
        call $Lprintc
        i32.const 121
        i32.const 1
        call $Lprints
        call $Lhalt
      )
    )
    i32.const 0
    local.set $B0
    local.get $B0
    global.set $G2
  )
  ;;
  ;; scanner
  ;;
  (func $L5
    (result i32)
    (local $B0 i32)
    (local $I0 i32)
    (local $I1 i32)
    (local $I2 i32)
    (local $I3 i32)
    (local $T0 i32)
    (block $L1
      (loop $L0
        call $L1
        local.set $I0
        local.get $I0
        local.set $T0
        local.get $I0
        call $L7
        local.set $B0
        local.get $B0
        i32.eqz
        br_if $L1
        br $L0
      )
    )
    local.get $T0
    local.set $I0
    global.get $G5
    local.set $I1
    local.get $I0
    local.get $I1
    i32.eq
    local.set $B0
    local.get $B0
    (if
      (then
        global.get $G6
        local.set $I0
        local.get $I0
        return
      )
    )
    local.get $T0
    local.set $I1
    global.get $G26
    local.set $I0
    local.get $I1
    local.get $I0
    i32.eq
    local.set $B0
    local.get $B0
    (if
      (then
        global.get $G7
        local.set $I1
        local.get $I1
        return
      )
    )
    local.get $T0
    local.set $I0
    global.get $G17
    local.set $I1
    local.get $I0
    local.get $I1
    i32.eq
    local.set $B0
    local.get $B0
    (if
      (then
        global.get $G9
        local.set $I0
        local.get $I0
        return
      )
    )
    local.get $T0
    local.set $I1
    global.get $G18
    local.set $I0
    local.get $I1
    local.get $I0
    i32.eq
    local.set $B0
    local.get $B0
    (if
      (then
        global.get $G10
        local.set $I1
        local.get $I1
        return
      )
    )
    local.get $T0
    local.set $I0
    global.get $G19
    local.set $I1
    local.get $I0
    local.get $I1
    i32.eq
    local.set $B0
    local.get $B0
    (if
      (then
        global.get $G11
        local.set $I0
        local.get $I0
        return
      )
    )
    local.get $T0
    local.set $I1
    global.get $G20
    local.set $I0
    local.get $I1
    local.get $I0
    i32.eq
    local.set $B0
    local.get $B0
    (if
      (then
        global.get $G12
        local.set $I1
        local.get $I1
        return
      )
    )
    local.get $T0
    local.set $I0
    global.get $G21
    local.set $I1
    local.get $I0
    local.get $I1
    i32.eq
    local.set $B0
    local.get $B0
    (if
      (then
        global.get $G13
        local.set $I0
        local.get $I0
        return
      )
    )
    local.get $T0
    local.set $I1
    global.get $G22
    local.set $I0
    local.get $I1
    local.get $I0
    i32.eq
    local.set $B0
    local.get $B0
    (if
      (then
        global.get $G14
        local.set $I1
        local.get $I1
        return
      )
    )
    local.get $T0
    local.set $I0
    local.get $I0
    call $L6
    local.set $B0
    local.get $B0
    (if
      (then
        i32.const 0
        local.set $I1
        local.get $I1
        global.set $G4
        (block $L3
          (loop $L2
            local.get $T0
            local.set $I0
            local.get $I0
            call $L6
            local.set $B0
            local.get $B0
            i32.eqz
            br_if $L3
            global.get $G4
            local.set $I1
            i32.const 10
            local.set $I0
            local.get $I1
            local.get $I0
            i32.mul
            local.set $I2
            local.get $T0
            local.set $I1
            global.get $G15
            local.set $I0
            local.get $I1
            local.get $I0
            i32.sub
            local.set $I3
            local.get $I2
            local.get $I3
            i32.add
            local.set $I1
            local.get $I1
            global.set $G4
            call $L1
            local.set $I0
            local.get $I0
            local.set $T0
            br $L2
          )
        )
        local.get $T0
        local.set $I2
        local.get $I2
        call $L2
        global.get $G8
        local.set $I3
        local.get $I3
        return
      )
    )
    i32.const 122
    i32.const 26
    call $Lprints
    call $Lhalt
    (i32.const 148)
    call $_Lerror
    (i32.const 12345)
  )
  ;;
  ;; isdigit
  ;;
  (func $L6
    (param $C0 i32)
    (result i32)
    (local $B0 i32)
    (local $B1 i32)
    (local $I0 i32)
    (local $I1 i32)
    local.get $C0
    local.set $I0
    global.get $G15
    local.set $I1
    local.get $I0
    local.get $I1
    i32.ge_s
    local.set $B1
    local.get $B1
    local.tee $B0
    (if
      (then
        local.get $C0
        local.set $I0
        global.get $G16
        local.set $I1
        local.get $I0
        local.get $I1
        i32.le_s
        local.set $B1
        local.get $B1
        local.set $B0
      )
    )
    local.get $B0
    return
    (i32.const 187)
    call $_Lerror
    (i32.const 12345)
  )
  ;;
  ;; isspace
  ;;
  (func $L7
    (param $C0 i32)
    (result i32)
    (local $B0 i32)
    (local $B1 i32)
    (local $B2 i32)
    (local $I0 i32)
    (local $I1 i32)
    local.get $C0
    local.set $I0
    global.get $G23
    local.set $I1
    local.get $I0
    local.get $I1
    i32.eq
    local.set $B2
    local.get $B2
    local.tee $B1
    i32.eqz
    (if
      (then
        local.get $C0
        local.set $I0
        global.get $G24
        local.set $I1
        local.get $I0
        local.get $I1
        i32.eq
        local.set $B2
        local.get $B2
        local.set $B1
      )
    )
    local.get $B1
    local.tee $B0
    i32.eqz
    (if
      (then
        local.get $C0
        local.set $I0
        global.get $G25
        local.set $I1
        local.get $I0
        local.get $I1
        i32.eq
        local.set $B2
        local.get $B2
        local.set $B0
      )
    )
    local.get $B0
    return
    (i32.const 226)
    call $_Lerror
    (i32.const 12345)
  )
  ;;
  ;; parser
  ;;
  (func $L8
    (local $B0 i32)
    (local $I0 i32)
    (local $I1 i32)
    (local $T0 i32)
    (block $L1
      (loop $L0
        call $L3
        local.set $I0
        global.get $G6
        local.set $I1
        local.get $I0
        local.get $I1
        i32.ne
        local.set $B0
        local.get $B0
        i32.eqz
        br_if $L1
        call $L9
        local.set $I0
        local.get $I0
        local.set $T0
        global.get $G7
        local.set $I1
        local.get $I1
        call $L4
        i32.const 265
        i32.const 3
        call $Lprints
        local.get $T0
        local.set $I0
        local.get $I0
        call $Lprinti
        i32.const 121
        i32.const 1
        call $Lprints
        br $L0
      )
    )
  )
  ;;
  ;; E
  ;;
  (func $L9
    (result i32)
    (local $B0 i32)
    (local $B1 i32)
    (local $I0 i32)
    (local $I1 i32)
    (local $I2 i32)
    (local $T0 i32)
    (local $T1 i32)
    (local $T2 i32)
    call $L10
    local.set $I0
    local.get $I0
    local.set $T0
    (block $L1
      (loop $L0
        call $L3
        local.set $I0
        global.get $G9
        local.set $I1
        local.get $I0
        local.get $I1
        i32.eq
        local.set $B1
        local.get $B1
        local.tee $B0
        i32.eqz
        (if
          (then
            call $L3
            local.set $I0
            global.get $G10
            local.set $I1
            local.get $I0
            local.get $I1
            i32.eq
            local.set $B1
            local.get $B1
            local.set $B0
          )
        )
        local.get $B0
        i32.eqz
        br_if $L1
        call $L3
        local.set $I0
        local.get $I0
        local.set $T2
        local.get $I0
        call $L4
        call $L10
        local.set $I1
        local.get $I1
        local.set $T1
        local.get $T2
        local.set $I0
        global.get $G9
        local.set $I1
        local.get $I0
        local.get $I1
        i32.eq
        local.set $B1
        local.get $B1
        (if
          (then
            local.get $T0
            local.set $I0
            local.get $T1
            local.set $I1
            local.get $I0
            local.get $I1
            i32.add
            local.set $I2
            local.get $I2
            local.set $T0
          )
          (else
            local.get $T0
            local.set $I0
            local.get $T1
            local.set $I1
            local.get $I0
            local.get $I1
            i32.sub
            local.set $I2
            local.get $I2
            local.set $T0
          )
        )
        br $L0
      )
    )
    local.get $T0
    local.set $I0
    local.get $I0
    return
    (i32.const 268)
    call $_Lerror
    (i32.const 12345)
  )
  ;;
  ;; T
  ;;
  (func $L10
    (result i32)
    (local $B0 i32)
    (local $B1 i32)
    (local $I0 i32)
    (local $I1 i32)
    (local $I2 i32)
    (local $T0 i32)
    (local $T1 i32)
    (local $T2 i32)
    call $L11
    local.set $I0
    local.get $I0
    local.set $T0
    (block $L1
      (loop $L0
        call $L3
        local.set $I0
        global.get $G11
        local.set $I1
        local.get $I0
        local.get $I1
        i32.eq
        local.set $B1
        local.get $B1
        local.tee $B0
        i32.eqz
        (if
          (then
            call $L3
            local.set $I0
            global.get $G12
            local.set $I1
            local.get $I0
            local.get $I1
            i32.eq
            local.set $B1
            local.get $B1
            local.set $B0
          )
        )
        local.get $B0
        i32.eqz
        br_if $L1
        call $L3
        local.set $I0
        local.get $I0
        local.set $T2
        local.get $I0
        call $L4
        call $L11
        local.set $I1
        local.get $I1
        local.set $T1
        local.get $T2
        local.set $I0
        global.get $G11
        local.set $I1
        local.get $I0
        local.get $I1
        i32.eq
        local.set $B1
        local.get $B1
        (if
          (then
            local.get $T0
            local.set $I0
            local.get $T1
            local.set $I1
            local.get $I0
            local.get $I1
            i32.mul
            local.set $I2
            local.get $I2
            local.set $T0
          )
          (else
            local.get $T0
            local.set $I0
            local.get $T1
            local.set $I1
            local.get $I1
            i32.eqz
            (if
              (then
                i32.const 301
                call $_Lerror
              )
            )
            local.get $I0
            i32.const -2147483648
            i32.eq
            (if
              (then
                local.get $I1
                i32.const -1
                i32.eq
                (if
                  (then
                    i32.const 318
                    call $_Lerror
                  )
                )
              )
            )
            local.get $I0
            local.get $I1
            i32.div_s
            local.set $I2
            local.get $I2
            local.set $T0
          )
        )
        br $L0
      )
    )
    local.get $T0
    local.set $I0
    local.get $I0
    return
    (i32.const 335)
    call $_Lerror
    (i32.const 12345)
  )
  ;;
  ;; F
  ;;
  (func $L11
    (result i32)
    (local $B0 i32)
    (local $I0 i32)
    (local $I1 i32)
    (local $T0 i32)
    (local $T1 i32)
    call $L3
    local.set $I0
    local.get $I0
    local.set $T1
    local.get $T1
    local.set $I0
    global.get $G13
    local.set $I1
    local.get $I0
    local.get $I1
    i32.eq
    local.set $B0
    local.get $B0
    (if
      (then
        global.get $G13
        local.set $I0
        local.get $I0
        call $L4
        call $L9
        local.set $I1
        local.get $I1
        local.set $T0
        global.get $G14
        local.set $I0
        local.get $I0
        call $L4
      )
      (else
        local.get $T1
        local.set $I1
        global.get $G10
        local.set $I0
        local.get $I1
        local.get $I0
        i32.eq
        local.set $B0
        local.get $B0
        (if
          (then
            global.get $G10
            local.set $I1
            local.get $I1
            call $L4
            call $L11
            local.set $I0
            i32.const 0
            local.get $I0
            i32.sub
            local.set $I0
            local.get $I0
            local.set $T0
          )
          (else
            local.get $T1
            local.set $I1
            global.get $G8
            local.set $I0
            local.get $I1
            local.get $I0
            i32.eq
            local.set $B0
            local.get $B0
            (if
              (then
                global.get $G8
                local.set $I1
                local.get $I1
                call $L4
                global.get $G4
                local.set $I0
                local.get $I0
                local.set $T0
              )
              (else
                i32.const 368
                i32.const 24
                call $Lprints
                call $Lhalt
              )
            )
          )
        )
      )
    )
    local.get $T0
    local.set $I1
    local.get $I1
    return
    (i32.const 392)
    call $_Lerror
    (i32.const 12345)
  )
  ;;
  ;; init
  ;;
  (func $L12
    (local $I0 i32)
    i32.const -1
    local.set $I0
    local.get $I0
    global.set $G5
    i32.const 48
    local.set $I0
    local.get $I0
    global.set $G15
    i32.const 57
    local.set $I0
    local.get $I0
    global.set $G16
    i32.const 43
    local.set $I0
    local.get $I0
    global.set $G17
    i32.const 45
    local.set $I0
    local.get $I0
    global.set $G18
    i32.const 42
    local.set $I0
    local.get $I0
    global.set $G19
    i32.const 47
    local.set $I0
    local.get $I0
    global.set $G20
    i32.const 40
    local.set $I0
    local.get $I0
    global.set $G21
    i32.const 41
    local.set $I0
    local.get $I0
    global.set $G22
    i32.const 32
    local.set $I0
    local.get $I0
    global.set $G23
    i32.const 9
    local.set $I0
    local.get $I0
    global.set $G24
    i32.const 13
    local.set $I0
    local.get $I0
    global.set $G25
    i32.const 10
    local.set $I0
    local.get $I0
    global.set $G26
    i32.const 256
    local.set $I0
    local.get $I0
    global.set $G6
    i32.const 257
    local.set $I0
    local.get $I0
    global.set $G8
    global.get $G17
    local.set $I0
    local.get $I0
    global.set $G9
    global.get $G18
    local.set $I0
    local.get $I0
    global.set $G10
    global.get $G19
    local.set $I0
    local.get $I0
    global.set $G11
    global.get $G20
    local.set $I0
    local.get $I0
    global.set $G12
    global.get $G21
    local.set $I0
    local.get $I0
    global.set $G13
    global.get $G22
    local.set $I0
    local.get $I0
    global.set $G14
    global.get $G26
    local.set $I0
    local.get $I0
    global.set $G7
  )
  ;;
  ;; RTS
  ;;
  ;; (insert RTS here)
  ;;
  (data 0 (i32.const 0) "function \22getc\22 must return a value\00")
  (data 0 (i32.const 36) "Internal error: too many ungets!\n")
  (data 0 (i32.const 69) "function \22peek\22 must return a value\00")
  (data 0 (i32.const 105) "Error: expected ")
  (data 0 (i32.const 121) "\n")
  (data 0 (i32.const 122) "Error: invalid character.\n")
  (data 0 (i32.const 148) "function \22scanner\22 must return a value\00")
  (data 0 (i32.const 187) "function \22isdigit\22 must return a value\00")
  (data 0 (i32.const 226) "function \22isspace\22 must return a value\00")
  (data 0 (i32.const 265) " = ")
  (data 0 (i32.const 268) "function \22E\22 must return a value\00")
  (data 0 (i32.const 301) "division by zero\00")
  (data 0 (i32.const 318) "integer overflow\00")
  (data 0 (i32.const 335) "function \22T\22 must return a value\00")
  (data 0 (i32.const 368) "Error: expected factor.\n")
  (data 0 (i32.const 392) "function \22F\22 must return a value\00")
  (memory 1)
