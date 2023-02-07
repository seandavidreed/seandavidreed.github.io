### 2/6/2023
## [The Evolution of CPU Processing Power Part 1: The Mechanics of a CPU](https://www.youtube.com/watch?v=sK-49uz3lGg)

A revolution in miniaturization was kickstarted in the mid-1960s.

March 1971, the Intel 4004 CPU was released. "Announcing a New Era of Integrated Electronics."

Every program, browser, video game, etc. ever made is composed of lists of instructions.

The Intel 4004 was capable of executing between 46,250 and 92,500 instructions per second (46 - 92 KHz). The ENIAC, built 25 years earlier, could only process 500 instructions per second (5 KHz). The 4004 only consumed 1 watt of electricity whereas the ENIAC consumed 180 kilowatts! In 2017, the Intel Core i9 could process 80 billion instructions per second (80 GHz).

8 bits is 1 byte. A number of bytes is a word, e.g. 32-bit word, 64-bit word. The native word size a processor operates on forms the core of its architecture. The Intel 4004 operated on a 4-bit word.

The list of instructions a CPU supports is called its instruction set. Each processors machine code instruction set is assigned a human-readible presentation called an Assembly Language.

We can think of a CPU as an instruction processing machine. They operate by looping through three basic steps:
  1. Fetch
  2. Decode
  3. Execute

CLASSIC RISC PIPELINE (Reduced Instruction Set Computer)
  1. The CPU pulls information from outside itself, forms operations within its environment, and then returns data back.
  2. The data is stored in RAM (Random Access Memory).
  3. The mechanism by which data goes back and forth from RAM to CPU is called a bus, which can be thought of as a superhighway.
  4. The CPU requests the contents of an address in RAM, passing the address on the address bus. The RAM fills the data bus with the requested information. The CPU sees this information and can now decode it.
  5. Fetching data from RAM is a bottleneck.
  6. When an instruction is decoded, the word is broken down into two parts known as bit fields, and opcode and operand. An opcode represents a specific function within the CPU (move, load, etc.). The opcode determines what will be performed on the data, the operand.
  7. The Arithmetic Logic Unit (ALU) is one of the most commonly used section of the CPU. It performs basic arithmetic or bitwise operations.
  8. The clock glues the looping process (Fetch, Decode, Execute) together.
  9. CPU clock rate is measured in Hertz. The Intel 4004 ran at 740 KHz. Modern CPUs can approach 5 GHz.