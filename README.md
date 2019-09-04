# Huffman Algorithm

![alt tag](https://i.imgur.com/bWdAgbu.png)

A C implementation of the Huffman Algorithm. [More info](https://www.codesdope.com/course/algorithms-huffman-codes/)

## Getting Started

These instructions will help you run the project and test the functionality of it.

### Prerequisites

* GCC

### Running

1. Open the project folder in the terminal.
2. Compile the project using GCC.
```
gcc CHuff.c -o CHuff
```
3. Run the project and Encode the Seed.txt file.
```
./CHuff
1
Seed.txt
// Check the Encode.txt and Dictionary.txt files generated!
```
4. Run the project again and Decode the Encode.txt file using the Dictionary.txt file generated.
```
./CHuff
2
Dictionary.txt
Encode.txt
// Check the Decode.txt file generated and it will be the same as the Seed.txt used!
```

### Testing

You can edit the Seed.txt content to test the Algorithm with different texts than the provided by default.

## Built With

* C - The programming language used.
* [GCC](https://gcc.gnu.org/) - The GNU Compiler Collection.

## Authors

* **Antonio Garcia** - *Algorithm, Files* - [lantoniogc](https://github.com/lantoniogc/)
* **Julio Flores** - *Interface, Files*

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.
