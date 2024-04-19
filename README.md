# Minishell

## Description

Minishell is a simple Unix shell program that provides a command-line interface for users to interact with the operating system. It supports various functionalities such as executing commands, managing environment variables, and handling redirection and pipelines.

## Installation

To compile Minishell, simply run:

bash
make
This will generate the executable minishell.

## Usage
After compiling, you can run Minishell by executing the generated executable:
./minishell

Once running, you will see a prompt where you can enter commands. Minishell supports various built-in commands as well as executing external programs.

### Built-in Commands

*   `echo [-n] [string ...]`: Display a line of text.
*   `cd [directory]`: Change the current directory.
*   `pwd`: Print the current working directory.
*   `export [name[=value] ...]`: Set environment variables.
*   `unset [name ...]`: Unset environment variables.
*   `env`: Display the environment variables.
*   `exit`: Exit the shell.

### Command Execution

Minishell can execute external commands by specifying the command name. It searches for the command in the directories listed in the `PATH` environment variable.

### Redirection

*   `< file`: Redirect input from a file.
*   `> file`: Redirect output to a file (overwrite).
*   `>> file`: Redirect output to a file (append).
*   `<< delimiter`: Read input until a line containing the delimiter is seen.

### Pipes

Minishell supports piping multiple commands together using the `|` character. The output of each command in the pipeline is connected to the input of the next command via a pipe.

### Environment Variables

You can use environment variables in commands by prefixing them with `$`. They will be expanded to their corresponding values.

### Special Characters

*   `'`: Single quotes prevent interpretation of metacharacters.
*   `"`: Double quotes prevent interpretation of most metacharacters except for `$`.

### Control Characters

*   `ctrl-C`: Displays a new prompt on a new line.
*   `ctrl-D`: Exits the shell.
*   `ctrl-\`: Does nothing.

Authors
-------

This Minishell implementation was created by Deia Eldin (https://github.com/deia-eldin) & Mahmoud Elshafie (https://github.com/MOMO24185).

Acknowledgments
---------------

This project was completed as part of 42 curriculum at 42 Abu Dhabi School.
