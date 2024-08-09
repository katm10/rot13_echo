.section .text
  .global save_and_switch
  .global resume_from_slow
  .global translate_return
 
translate_return:
  # happens after register allocation, save everything
  push %rax
  push %rbp
  push %rdi
  push %rsi
  push %r12

  # update rsp
  mov %rsp, %r12
  mov 0x28(%r12), %rdi
  call translate_return_addr
  mov %rax, %rdx

  # restore everything
  pop %r12
  pop %rsi
  pop %rdi
  pop %rbp
  pop %rax
  mov %rdx, (%rsp)

  ret

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

  // restore slow_stack.rsp
  movq slow_stack+16(%rip), %rsp

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
  popq %rax 
  popq %rcx
  popq %rdx
  popq %rsi
  popq %rdi
  // popq %rsp

  mov $0, %rax

  movq %rbp, %rsp
  popq %rbp

  retq

resume_from_slow:
  // parameters:
  // rdi = rsp to switch to

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

  // save the old stack
  movq %rsp, slow_stack+16(%rip)
  // resume execution on the saved stack
  movq %rdi, %rsp

  // restore the registers from the saved slow stack
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
  popq %rax 
  popq %rcx
  popq %rdx
  popq %rsi
  popq %rdi
  // popq %rsp

  // return addr is at $rsp + 8
  movq 8(%rsp), %rdi
  call translate_return_addr
  movq %rax, 8(%rsp)
  mov $1, %rax

  movq %rbp, %rsp
  popq %rbp

  retq