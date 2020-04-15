# l'auteur est un specialist du mac, et meme de swift

# Mach-O Executable

creation d'un binaire hello word
```c
# include <stdio.h>

int main(int argc, char *argv[])
{
	printf("Hello World\n");
    return (0);
}
```

quand je compile ce code il se passe:
* Preprocessing 
    - Tokenisation
    - Macro expansion
    - include expansion
* Parsing and Semantic Analysis
    - Translates preprocessor tokens into a parse tree
    - Applies semantic analysis to the parse tree
    - Outputs an abstract Syntax Tree
* Code Generation and Optimization (compilation)
    - Tranlates an AST into low-level intermediate code (LLVM IR)
    - Responsible for optimizing the generated code
    - Target-specific code generation
    - Outputs assembly
* Assembler
    - Translates assembly code into target object file
* Linker
    - Merge multiples object files into an executable (or a dynamic lib)

## Preprocessing
* with the command `xcrun clang -E helloword`
  we stop after preprocessing
* the file is really bigger, because, all the stdio.h
  just be write where was # include <stdio.h>
* the file is also full of `# 1 "/Library/.../_pthread_types.h" 1 3 4`
  - `#` means __linemarker__, next what is what: 
  - '#' lineNumber fileName (flag) startNewFile returningToAFile fromSystemHeader
* At the end of the file, the original content is still here ! :)

## Compilation
* Assembly code `xcrun clang -S -o - helloword.c | open -f`
* line start with "." == assembler directives, other x86_64 assembly.

### First three lines
```asm
	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14	sdk_version 10, 14
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
```
* .section specifies in which section that code goes.
* _globl specifies main as external symbol, it need to be
  visible from outside to start the program.
* align give the program alignment, here 2^4

### Start main
```asm
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
```
* _main is the actual start of main, it's the exported symbol
  the binary keep a reference of it
* .cfi_startproc Call Frame Information, is mostly at the
  start of function.
  - Frame == function 
  - the step in / step out of the debugger set in/out Frame
  - .cfi_endproc == end of function
* after the comment #BB.. the first assembly code,
  the assembly code follow the Application Binary Interface (ABI)
  that says, rbp register must be preserved across function call.
  Main need keep it, so main push into value that will pop at the end.
* next .cfi_def... are debug information

### up until printf
`movq %rsp %rbp` put local variable onto stack
`subq $32, %rsp` move stack ptr to 32 bytes (where land the function)
* edi and rsi registers hold the first/second argument of the function
  edi (32bits) == argc / rsi (64bit) == argv.
* as we call an other function, we stock them.
`movl %edi, -8(%rbp)` put the first argument of printf into edi
`loaq L_.str(%rip), %rdi` put the string, from his table, as first argument
`movb $0, %al` printf is variatic function, his argument number is in al
... blah blah

* at the end, there is another section for the literal,
  that from where came my str hello world.

## Assembler
Simply convert the readable asm code into machine code,
that's the .o file

## Linker
resolve symbols between object files and libraries
`callq _printf`
match the lib and the files between them in the final
binary.

## Sections
* executable have multiple session,
* session have multiple segment.
`xcrun size -x -l -m a.out`

* When the binary is run, let's say the vm will load
  all in memory, in getpagesize() multiple for each section.

* When the VM does this mapping, segment and sections are
 mapped with different properties, permissions

* __TEXT contains our code to be run, it's mapped as
  read-only and executable. The code __cannot alter itself__

* __DATA is mapped read/write but non-executable,
  it contains values that need to be updated.

* the first segment __PAGEZERO, is 4gb large
  these value are not in the file, and this space
  is mapped as nothing, no execution, no read...
  this is why the EXC_BAD_ACCESS when using little
  or NULL ptr. __this is very smart__

#### __TEXT
__text : compiled machine code
__stubs / __stub_helper : dynamic linker (dyld)
__const : ...
__cstring : quoted strings source code

#### __DATA
* read / write data
__nl_symbol_ptr / __la_symbol_ptr, non-lazy / lazy symbol ptr
__bs : static variable, ANSI say they must be set to 0
__common : 












kkkkkkkkkk