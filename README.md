# Pico VM
[![MIT Licence](https://badges.frapsoft.com/os/mit/mit.svg?v=103)](https://opensource.org/licenses/mit-license.php)

## What's this?
Pico VM is a small VM I'm writing to learn some more about interpreters and VMs.

## Building
You need clang and GNU Make to build Pico VM.
If you have clang and GNU Make, you can simply use `git clone` to clone it, and use the `make` command to build it.

## Dependencies
Pico VM currently does not have any dependencies, but I'm currently evaluating multiple testing suites, so there might be a dependency for testing soon.

## Future Plans
- [ ] Debug mode with value prints of registers and stack.
- [ ] Basic parsing.
- [x] Basic evaluation.
- [ ] Error handling.
- [ ] Non-debug print.
- [x] Specialised registers.
- [ ] Conditional and unconditional JMP instructions.
- [ ] Unit tests.
- [x] Documentation on how to use Pico VM.

### Instruction set implementation status
- [x] `HLT`
- [x] `NOP`
- [x] `PUSH <val>`
- [x] `POP`
- [x] `ADD`
- [x] `SUB`
- [x] `MUL`
- [x] `DIV`
- [ ] `MOV <val> <reg>`
- [ ] `SMOV <reg>`
- [ ] `JMP <dest>`
- [ ] `JE <val a> <val b> <dest>`
- [ ] `JNE <val a> <val b> <dest>`
- [ ] `JLE <val a> <val b> <dest>`
- [ ] `JL <val a> <val b> <dest>`
- [ ] `JGE <val a> <val b> <dest>`
- [ ] `JG <val a> <val b> <dest>`
- [ ] `JNZ <val> <dest>`
- [ ] `JZ <val> <dest>`
- [ ] `INT`

## License
Pico VM is licensed under the MIT license - see the [attached license](LICENSE.md) for details.

## Acknowledgments
Pico VM is based on or inspired by:
* [Felix Angell's blog post about writing a virtual machine in c](https://felixangell.com/blog/virtual-machine-in-c)