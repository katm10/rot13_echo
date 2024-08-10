	.text
	.file	"server.c"
	.globl	handle_request                  # -- Begin function handle_request
	.p2align	4, 0x90
	.type	handle_request,@function
	.long	0                               # @handle_request
	.long	0
	.long	0
	.long	0
handle_request:
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$2144, %rsp                     # imm = 0x860
	callq	sockfd__addr@PLT
	movl	(%rax), %eax
	movl	%eax, -2100(%rbp)               # 4-byte Spill
	leaq	-2064(%rbp), %rax
	movq	%rax, -2096(%rbp)               # 8-byte Spill
	callq	clientaddr__addr@PLT
	movq	%rax, -2088(%rbp)               # 8-byte Spill
	callq	clientlen__addr@PLT
	movl	-2100(%rbp), %edi               # 4-byte Reload
	movq	-2096(%rbp), %rsi               # 8-byte Reload
	movq	-2088(%rbp), %r8                # 8-byte Reload
	movq	%rax, %r9
	movl	$2048, %edx                     # imm = 0x800
	xorl	%ecx, %ecx
	callq	recvfrom@PLT
                                        # kill: def $eax killed $eax killed $rax
	movl	%eax, -2068(%rbp)
	xorl	%eax, %eax
                                        # kill: def $al killed $al killed $eax
	cmpl	$0, -2068(%rbp)
	movb	%al, -2073(%rbp)                # 1-byte Spill
	jge	.LBB0_2
# %bb.1:                                # %land.rhs
	movb	$1, %al
	movb	%al, -2073(%rbp)                # 1-byte Spill
	jmp	.LBB0_2
.LBB0_2:                                # %land.end
	movb	-2073(%rbp), %al                # 1-byte Reload
	andb	$1, %al
	movzbl	%al, %edi
	movq	fast_stack@GOTPCREL(%rip), %rax
	movq	16(%rax), %rcx
	leaq	.L.str(%rip), %rsi
	xorl	%edx, %edx
	callq	mpns_unlikely@PLT
	cmpl	$0, %eax
	je	.LBB0_4
# %bb.3:                                # %if.then
	movl	$-1, -4(%rbp)
	jmp	.LBB0_28
.LBB0_4:                                # %if.end
	movsbl	-2064(%rbp), %ecx
	xorl	%eax, %eax
                                        # kill: def $al killed $al killed $eax
	cmpl	$63, %ecx
	movb	%al, -2101(%rbp)                # 1-byte Spill
	jne	.LBB0_6
# %bb.5:                                # %land.rhs9
	movb	$1, %al
	movb	%al, -2101(%rbp)                # 1-byte Spill
	jmp	.LBB0_6
.LBB0_6:                                # %land.end10
	movb	-2101(%rbp), %al                # 1-byte Reload
	andb	$1, %al
	movzbl	%al, %edi
	movq	fast_stack@GOTPCREL(%rip), %rax
	movq	16(%rax), %rcx
	leaq	.L.str(%rip), %rsi
	movl	$1, %edx
	callq	mpns_unlikely@PLT
	cmpl	$0, %eax
	je	.LBB0_23
# %bb.7:                                # %if.then14
	movl	$0, -2072(%rbp)
.LBB0_8:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	movl	-2072(%rbp), %eax
	cmpl	-2068(%rbp), %eax
	jge	.LBB0_22
# %bb.9:                                # %for.body
                                        #   in Loop: Header=BB0_8 Depth=1
	movslq	-2072(%rbp), %rax
	movsbl	-2064(%rbp,%rax), %ecx
	xorl	%eax, %eax
                                        # kill: def $al killed $al killed $eax
	cmpl	$65, %ecx
	movb	%al, -2102(%rbp)                # 1-byte Spill
	jl	.LBB0_12
# %bb.10:                               # %land.lhs.true
                                        #   in Loop: Header=BB0_8 Depth=1
	movslq	-2072(%rbp), %rax
	movsbl	-2064(%rbp,%rax), %ecx
	xorl	%eax, %eax
                                        # kill: def $al killed $al killed $eax
	cmpl	$90, %ecx
	movb	%al, -2102(%rbp)                # 1-byte Spill
	jg	.LBB0_12
# %bb.11:                               # %land.rhs26
                                        #   in Loop: Header=BB0_8 Depth=1
	movb	$1, %al
	movb	%al, -2102(%rbp)                # 1-byte Spill
	jmp	.LBB0_12
.LBB0_12:                               # %land.end27
                                        #   in Loop: Header=BB0_8 Depth=1
	movb	-2102(%rbp), %al                # 1-byte Reload
	andb	$1, %al
	movzbl	%al, %edi
	movq	fast_stack@GOTPCREL(%rip), %rax
	movq	16(%rax), %rcx
	leaq	.L.str(%rip), %rsi
	movl	$2, %edx
	callq	mpns_unknown
	cmpl	$0, %eax
	je	.LBB0_14
# %bb.13:                               # %if.then31
                                        #   in Loop: Header=BB0_8 Depth=1
	movslq	-2072(%rbp), %rax
	movsbl	-2064(%rbp,%rax), %eax
	subl	$65, %eax
	addl	$13, %eax
	movl	$26, %ecx
	cltd
	idivl	%ecx
	addl	$65, %edx
	movb	%dl, %cl
	movslq	-2072(%rbp), %rax
	movb	%cl, -2064(%rbp,%rax)
	jmp	.LBB0_20
.LBB0_14:                               # %if.else
                                        #   in Loop: Header=BB0_8 Depth=1
	movslq	-2072(%rbp), %rax
	movsbl	-2064(%rbp,%rax), %ecx
	xorl	%eax, %eax
                                        # kill: def $al killed $al killed $eax
	cmpl	$97, %ecx
	movb	%al, -2103(%rbp)                # 1-byte Spill
	jl	.LBB0_17
# %bb.15:                               # %land.lhs.true44
                                        #   in Loop: Header=BB0_8 Depth=1
	movslq	-2072(%rbp), %rax
	movsbl	-2064(%rbp,%rax), %ecx
	xorl	%eax, %eax
                                        # kill: def $al killed $al killed $eax
	cmpl	$122, %ecx
	movb	%al, -2103(%rbp)                # 1-byte Spill
	jg	.LBB0_17
# %bb.16:                               # %land.rhs50
                                        #   in Loop: Header=BB0_8 Depth=1
	movb	$1, %al
	movb	%al, -2103(%rbp)                # 1-byte Spill
	jmp	.LBB0_17
.LBB0_17:                               # %land.end51
                                        #   in Loop: Header=BB0_8 Depth=1
	movb	-2103(%rbp), %al                # 1-byte Reload
	andb	$1, %al
	movzbl	%al, %edi
	movq	fast_stack@GOTPCREL(%rip), %rax
	movq	16(%rax), %rcx
	leaq	.L.str(%rip), %rsi
	movl	$3, %edx
	callq	mpns_unknown
	cmpl	$0, %eax
	je	.LBB0_19
# %bb.18:                               # %if.then55
                                        #   in Loop: Header=BB0_8 Depth=1
	movslq	-2072(%rbp), %rax
	movsbl	-2064(%rbp,%rax), %eax
	subl	$97, %eax
	addl	$13, %eax
	movl	$26, %ecx
	cltd
	idivl	%ecx
	addl	$97, %edx
	movb	%dl, %cl
	movslq	-2072(%rbp), %rax
	movb	%cl, -2064(%rbp,%rax)
.LBB0_19:                               # %if.end66
                                        #   in Loop: Header=BB0_8 Depth=1
	jmp	.LBB0_20
.LBB0_20:                               # %if.end67
                                        #   in Loop: Header=BB0_8 Depth=1
	jmp	.LBB0_21
.LBB0_21:                               # %for.inc
                                        #   in Loop: Header=BB0_8 Depth=1
	movl	-2072(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -2072(%rbp)
	jmp	.LBB0_8
.LBB0_22:                               # %for.end
	jmp	.LBB0_23
.LBB0_23:                               # %if.end68
	callq	sockfd__addr@PLT
	movl	(%rax), %eax
	movl	%eax, -2132(%rbp)               # 4-byte Spill
	leaq	-2064(%rbp), %rax
	movq	%rax, -2128(%rbp)               # 8-byte Spill
	movslq	-2068(%rbp), %rax
	movq	%rax, -2120(%rbp)               # 8-byte Spill
	callq	clientaddr__addr@PLT
	movq	%rax, -2112(%rbp)               # 8-byte Spill
	callq	clientlen__addr@PLT
	movl	-2132(%rbp), %edi               # 4-byte Reload
	movq	-2128(%rbp), %rsi               # 8-byte Reload
	movq	-2120(%rbp), %rdx               # 8-byte Reload
	movq	-2112(%rbp), %r8                # 8-byte Reload
	movl	(%rax), %r9d
	xorl	%ecx, %ecx
	callq	sendto@PLT
                                        # kill: def $eax killed $eax killed $rax
	movl	%eax, -2068(%rbp)
	xorl	%eax, %eax
                                        # kill: def $al killed $al killed $eax
	cmpl	$0, -2068(%rbp)
	movb	%al, -2104(%rbp)                # 1-byte Spill
	jge	.LBB0_25
# %bb.24:                               # %land.rhs78
	movb	$1, %al
	movb	%al, -2104(%rbp)                # 1-byte Spill
	jmp	.LBB0_25
.LBB0_25:                               # %land.end79
	movb	-2104(%rbp), %al                # 1-byte Reload
	andb	$1, %al
	movzbl	%al, %edi
	movq	fast_stack@GOTPCREL(%rip), %rax
	movq	16(%rax), %rcx
	leaq	.L.str(%rip), %rsi
	movl	$4, %edx
	callq	mpns_unlikely@PLT
	cmpl	$0, %eax
	je	.LBB0_27
# %bb.26:                               # %if.then83
	movl	$-1, -4(%rbp)
	jmp	.LBB0_28
.LBB0_27:                               # %if.end84
	movl	$0, -4(%rbp)
.LBB0_28:                               # %return
	movl	-4(%rbp), %eax
	addq	$2144, %rsp                     # imm = 0x860
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
	retq
.Lfunc_end0:
	.size	handle_request, .Lfunc_end0-handle_request
	.cfi_endproc
                                        # -- End function
	.p2align	4, 0x90                         # -- Begin function mpns_unknown
	.type	mpns_unknown,@function
	.long	-1                              # @mpns_unknown
	.long	-1
	.long	0
	.long	0
mpns_unknown:
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -20(%rbp)
	movq	%rcx, -32(%rbp)
	movl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
	retq
.Lfunc_end1:
	.size	mpns_unknown, .Lfunc_end1-mpns_unknown
	.cfi_endproc
                                        # -- End function
	.weak	handle_request__addr            # -- Begin function handle_request__addr
	.p2align	4, 0x90
	.type	handle_request__addr,@function
	.long	-1                              # @handle_request__addr
	.long	-1
	.long	0
	.long	0
handle_request__addr:
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	leaq	handle_request(%rip), %rax
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end2:
	.size	handle_request__addr, .Lfunc_end2-handle_request__addr
	.cfi_endproc
                                        # -- End function
	.type	clientlen,@object               # @clientlen
	.data
	.globl	clientlen
	.p2align	2, 0x0
clientlen:
	.long	16                              # 0x10
	.size	clientlen, 4

	.type	.L.str,@object                  # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"handle_request"
	.size	.L.str, 15

	.type	sockfd,@object                  # @sockfd
	.bss
	.globl	sockfd
	.p2align	2, 0x0
sockfd:
	.long	0                               # 0x0
	.size	sockfd, 4

	.type	servaddr,@object                # @servaddr
	.globl	servaddr
	.p2align	2, 0x0
servaddr:
	.zero	16
	.size	servaddr, 16

	.type	clientaddr,@object              # @clientaddr
	.globl	clientaddr
	.p2align	2, 0x0
clientaddr:
	.zero	16
	.size	clientaddr, 16

	.ident	"clang version 18.0.0 (https://github.com/llvm/llvm-project.git e5bf66b22fa6e8d56861c5f4da76f0fadb4deec5)"
	.section	".note.GNU-stack","",@progbits
