# Compiling

Compiling a c++ code may imply different thinks. Recall that compilation is a chain of sub-processes aimed to built a binary file that let the computer read it directly. In order to reach that, the compiler follows: preprocessing, comilation, assembling and linking. More details are pretty well explained in this [post](https://www.toptal.com/c-plus-plus/c-plus-plus-understanding-compilation) and this [book](https://subscription.packtpub.com/book/programming/9781789801491/1/ch01lvl1sec03/the-c-compilation-model).

Then to perform this process (by using g++ compiler) we will run:

```console
g++ src/Options.cpp -o options
```

-----

# Boost library
This project requires Boost C++ library. For installing it is necessary to follow the steps described in the official [webpage](https://www.boost.org/doc/libs/1_83_0/more/getting_started/unix-variants.html)

* This [video](https://www.youtube.com/watch?v=s5BV7Lb6b08) may help on the installation as well.

```console
tar xzvf boost_1_55_0.tar.gz
cd boost_1_55_0/
```

```console
sudo apt-get update
sudo apt-get install build-essential g++ python-dev autotools-dev libicu-dev libbz2-dev libboost-all-dev

sudo ./bootstrap.sh --prefix=/usr/local
sudo ./b2 install
```

* Checking into */usr/local/include/boost*

## Letting VS Code to identify the headers

Follow the steps described in [here](https://stackoverflow.com/questions/65109262/how-to-tell-vs-code-where-to-find-header-and-source-files-in-a-cmake-project).

# Compiling

To compile the **.cpp** file you can run the command below which will yield another object with extension **.o**

```console
g++ -c src/Options.cpp
```

To see the symbols of the compiled object run

```console
nm src/Options.o
```

or to see the object information run (Other interesting explanation can be found in this [post](https://upload.wikimedia.org/wikipedia/commons/e/e4/ELF_Executable_and_Linkable_Format_diagram_by_Ange_Albertini.png)) about ELF systems.

```console
objdump -d src/Options.o
```

## Linking

Linking objects 

```console
g++ -o options_executable options.o
```

# Using CMAKE
I do prefer this approach because you don't depend on tools with any license. In order to do the compilation of the codes addressing the dependencies, we can use CMake.

Great explanation in these [video 1](https://www.youtube.com/watch?v=nlKcXPUJGwA&list=PLalVdRk2RC6o5GHu618ARWh0VO0bFlif4) and [video 2](https://www.youtube.com/watch?v=gGxi500Q5uE)

 ## building

* Install CMake Tool extension in VS Code
* call the **CMake::Quick Start** option (ctrl + shift + P) to build your CMakeFiles file.
* Then in your CMakeFiles file you should have something like

```text
cmake_minimum_required(VERSION 3.28.3)
project(options VERSION 0.1.0 LANGUAGES C CXX)

add_executable(${PROJECT_NAME} Options.cpp)
```

* Check the version of your CMake is the same pointed out in the first line.

Once you have the correct CMakeFiles run the command bellow. This command will add the necesary files into **out/build/Makefile** file, which is in turn used to compile your final version.

```console
mkdir -p out/build
cd out/build
cmake ../../ -B .
make
```

Then it will create a file name **options**, which is the name we stablished in the CMakeFiles when calling the function *project*.