# Universal Turing Machine in C

Contents of package:

- libmachine: Implementation of a standard Universal Turing Machine (UTM)
  - include/lib/machine.h: Prototypes
- libmachine-paper: Turing Machine that understands the programs from Alan Turing's paper
  - include/lib/machine-paper.h: Prototypes
- libutil: Helper functions from s390-tools package
- examples: Sample Turing machines

Build:

```bash
~/src/turing-machine (master)$ make
```

Run an example:

```bash
~/src/turing-machine (master)$ examples/example-add-one
s=a 1011............................................................ w=1 m=R s=a # Skip 1s
s=a 1011............................................................ w=0 m=R s=a # Skip 0s
s=a 1011............................................................ w=1 m=R s=a # Skip 1s
s=a 1011............................................................ w=1 m=R s=a # Skip 1s
s=a 1011............................................................ w=. m=L s=b # Found blank
s=b 1011............................................................ w=0 m=L s=b # 1 + 1 = 0 + carry
s=b 1010............................................................ w=0 m=L s=b # 1 + 1 = 0 + carry
s=b 1000............................................................ w=1 m=L s=c # 0 + 1 = 1 > done
s=c 1100............................................................ w=* m=N s=- # Accpeting state
```

Show the action table of the first example from Turing`s paper:


```bash
~/src/turing-machine (master)$ examples/example-paper-i -l
s=b:00 r=. w=0 m=N, ns=b:01 # P0,R
s=b:01 r=* w=* m=R, ns=c:00 # P0,R
s=c:00 r=. w=* m=R, ns=e:00 # R
s=e:00 r=. w=1 m=N, ns=e:04 # P1,R
s=e:04 r=* w=* m=R, ns=f:00 # P1,R
s=f:00 r=. w=* m=R, ns=b:00 # R
```

Run the first example from Turing`s paper on a tape with 16 bytes:


```
~/src/turing-machine (master)$ examples/example-paper-i -s 16
s=b ................ # P0,R
s=c 0............... # R
s=e 0............... # P1,R
s=f 0.1............. # R
s=b 0.1............. # P0,R
s=c 0.1.0........... # R
s=e 0.1.0........... # P1,R
s=f 0.1.0.1......... # R
s=b 0.1.0.1......... # P0,R
s=c 0.1.0.1.0....... # R
s=e 0.1.0.1.0....... # P1,R
s=f 0.1.0.1.0.1..... # R
s=b 0.1.0.1.0.1..... # P0,R
s=c 0.1.0.1.0.1.0... # R
s=e 0.1.0.1.0.1.0... # P1,R
s=f 0.1.0.1.0.1.0.1. # R
example-paper-i: Out of tape memory at position 16
```
