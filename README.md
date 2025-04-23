# holbertonschool-simple_shell

## Description

The simple shell is a basic UNIX comand line interpreter written in C. I replicates the shell behavior, allowing users to execute commands.

The shell supports:

- Execution of external commands using ```PATH```

- Build-in commands:
    - ```env```: prints thr current environment
    - ```exit```: exit the shell
- Parsing user input into arguments
- Manual implementation of command lookup and execution via ```execve```
- Error handling for commands not found
- Core system calls like ```fork```,  ```wait``` and ```strtok```

This end of first trimester project showcases core concepts such as process control, input parsing and environment handling.



## Tasks
0. README, man, AUTHORS
1. Betty would be proud
2. Simple shell 0.1
3. Simple shell 0.2
4. Simple shell 0.3
5. Simple shell 0.4
6. Simple shell 1.0


## Usage

Run the shell from terminal:

./simple_shell

Then [enter]

```
$ ls -l
$ echo Hello, World!
$ exit
```

## Features 
 
- Interactive shell mode
- Non-interactive (script) mode
- Command execution with PATH resolution
- Build-in commands ( 'exit', 'env', etc.)
- Handling of child processes via 'fork', 'execve' and 'wait'
- Basic error handling

## Contributing

Pulls are welcomed however, please open an issue or contact mantainers before starting any major contribution.

## Authors
- <a href="https://github.com/YiliPR" target="_blank">Eli Figueroa</a>
- <a href="https://github.com/Paola-cmyk" target="_blank">Paola Gonzalez</a>
- <a href="https://github.com/Bryanjose001" target="_blank">Bryan Camacho</a>

Proyect originally developed at Holberton Coding School, Ponce, PR, 2025.

## License
This project is an open souce and available under the <a href= "https://github.com/Paola-cmyk/holbertonschool-simple_shell/blob/main/MIT%20License" target="_blank">MIT License</a>