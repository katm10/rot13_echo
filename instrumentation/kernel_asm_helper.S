.section .text
  .global save_and_switch
  .global mpns_likely
  .global mpns_unlikely

save_and_switch:
  // rdi = fxn to call, rsi = new rsp, rdx = old rsp
  pushq %rbp 
  movq %rsp, %rbp

  // save the registers
  // pushq %rsp
  pushq %rdi
  pushq %rsi
  pushq %rdx
  pushq %rcx
  pushq %rax
  pushq %r8
  pushq %r9
  pushq %r10
  pushq %r11
  pushq %rbx
  pushq %rbp
  pushq %r12
  pushq %r13
  pushq %r14
  pushq %r15

  // move to the new stack
  movq %rsp, (%rcx)
  movq %rdx, %rsp

  // just here to solve alignment issues
  subq $8, %rsp 

  // save the old stack
  pushq (%rcx)

  // translate and call the function
  pushq %rax
  callq __translate_function
  movq %rax, %rdi
  popq %rax

  callq *%rdi

  // return 0 if it doesn't abort
  movq $0, %rax

  // restore the old stack
  popq %rsp

  // restore the registers
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbp
  popq %rbx
  popq %r11
  popq %r10
  popq %r9
  popq %r8
  // don't let rax be overwritten
  popq %rsi 
  popq %rcx
  popq %rdx
  popq %rsi
  popq %rdi
  // popq %rsp

  movq %rbp, %rsp
  popq %rbp

  retq

mpns_likely:
  # called with mpns_likely(int condition, char* name, int id, void* fn)

  # Params: %rdi = condition, %rsi = name, %rdx = id, %rcx = fn
  pushq %rbp
  movq %rsp, %rbp
  cmp $0, %rdi
  jne .done_likely

  mov %rcx, %rdi
  jmp __abort

.done_likely:
  movq $1, %rax
  movq %rbp, %rsp
  pop %rbp
  ret


mpns_unlikely:
  # called with mpns_unlikely(int condition, char* name, int id, void* fn)

  # Params: %rdi = condition, %rsi = old rsp
  pushq %rbp
  movq %rsp, %rbp
  cmp $0, %rdi
  je .done_unlikely

  mov %rcx, %rdi
  jmp __abort

.done_unlikely:
  movq $0, %rax
  movq %rbp, %rsp
  pop %rbp
  ret

__abort:
  // NOTE: ASSUMES rb HAS BEEN DECLARED GLOBALLY
  // rdi = old rsp
  // save the registers

  // %rdi = new rsp, %rsi = name, %rdx = id
  // call print_abort

  // pushq %rsp
  pushq %rdi
  pushq %rsi
  pushq %rdx
  pushq %rcx
  pushq %rax
  pushq %r8
  pushq %r9
  pushq %r10
  pushq %r11
  pushq %rbx
  pushq %rbp
  pushq %r12
  pushq %r13
  pushq %r14
  pushq %r15

  // save the old rsp
  movq %rdi, %r12

  // set up the parameters for enqueue
  movq rb(%rip), %rdi
  movq %rsp, %rsi

  pushq %rsp
  // enqueue this stack
  call enqueue_fxn

  // restore the old stack
  mov %r12, %rsp
  // subq $8, %rsp

  // return 1
  movq $1, %rax

  // restore the registers
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbp
  popq %rbx
  popq %r11
  popq %r10
  popq %r9
  popq %r8
  // don't let rax be overwritten
  popq %rsi 
  popq %rcx
  popq %rdx
  popq %rsi
  popq %rdi
  // popq %rsp

  movq %rbp, %rsp
  popq %rbp

  retq
