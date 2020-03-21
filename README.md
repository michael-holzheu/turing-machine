# Implementation of an Universal Turing Machine in C

Contents of package:

- libmachine: Implementation of a standard Universal Turing Machine (UTM)
- libmachine-paper: Turing Machine that understands the programs from Alan Turing's paper
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

Run the first example from Turing`s paper:

```bash
holzheu:~/src/turing-machine (master)$ examples/example-paper-i -s 32
s=b ................................ # P0
s=b 0............................... # R,R,P1
s=b 0.1............................. # R,R,P0
s=b 0.1.0........................... # R,R,P1
s=b 0.1.0.1......................... # R,R,P0
s=b 0.1.0.1.0....................... # R,R,P1
s=b 0.1.0.1.0.1..................... # R,R,P0
s=b 0.1.0.1.0.1.0................... # R,R,P1
s=b 0.1.0.1.0.1.0.1................. # R,R,P0
s=b 0.1.0.1.0.1.0.1.0............... # R,R,P1
s=b 0.1.0.1.0.1.0.1.0.1............. # R,R,P0
s=b 0.1.0.1.0.1.0.1.0.1.0........... # R,R,P1
s=b 0.1.0.1.0.1.0.1.0.1.0.1......... # R,R,P0
s=b 0.1.0.1.0.1.0.1.0.1.0.1.0....... # R,R,P1
s=b 0.1.0.1.0.1.0.1.0.1.0.1.0.1..... # R,R,P0
s=b 0.1.0.1.0.1.0.1.0.1.0.1.0.1.0... # R,R,P1
s=b 0.1.0.1.0.1.0.1.0.1.0.1.0.1.0.1. # R,R,P0
```
