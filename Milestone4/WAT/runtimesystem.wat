(module
  (import "host" "exit" (func $exit))
  (import "host" "getchar" (func $getchar (result i32)))
  (import "host" "putchar" (func $putchar (param i32)))
  (func $main
    i32.const 11
    i32.const 13
    call $prints
    i32.const 0
    call $printb
    i32.const 1234
    i32.const 1000
    call $printi
    call $halt
  )
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
   i32.const 10 ;;print newline character
   call $printc
  )
  (start $main)
  (data 0 (i32.const 0) "true\n")
  (data 0 (i32.const 5) "false\n")
  (data 0 (i32.const 11) "Hello World!\n")
  (memory 1)
)

