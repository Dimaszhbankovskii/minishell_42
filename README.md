# Minishell_42 <img alt="C icon" src="./images/C_logo.png" width="50" height="50"> <img alt="42 icon" src="./images/42-logo.svg.png"  width="50" height="50"> <img alt="21 icon" src="./images/21-logo.webp" width="50" height="50">

> The objective of this project is for you to create a simple shell on base bash for Linux and MacOs.

# Contents <a name = "RefContents"></a>

* [General rules](#RefGeneralRules)
* [Shell functionality](#RefShellFunctionality)

## General rules : <a name = "RefGeneralRules"></a>

- Shell program is compiled with a `Makefile` on Linux or Mac.  

- Rules of `Makefile`:
	- `make` (build the program)
	- `make clean` (delete object files *.o)
	- `make fclean` (delete object files *.o and executable program file)
	- `make re` (rebuild the program)

- Run the shell program: `./minishell`

- Compile code with `gcc` and the flags `-Wall -Wextra -Werror`

- Requires `readline` library to work, installation of library on Linux:  

	`sudo apt install libreadline-dev`

[Back to contents](#RefContents)

## Shell functionality : <a name = "RefShellFunctionality"></a>

- Display a prompt when waiting for a new command.

- Have a working history.

- Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).

- Not interpret unclosed quotes or special characters such as `\` (backslash) or `;` (semicolon).

- Handle `'` (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.

- Handle `"` (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign).

- Implement redirections:

	- `<` should redirect input.
	
	- `>` should redirect output.
	
	- `<<` should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!

	- `>>` should redirect output in append mode.

- Implement pipes (`|` character). The output of each command in the pipeline is connected to the input of the next command via a pipe.

- Handle environment variables (`$` followed by a sequence of characters) which should expand to their values.

- Handle `$?` which should expand to the exit status of the most recently executed foreground pipeline.

- Handle `ctrl-C`, `ctrl-D` and `ctrl-\` which should behave like in bash.

- In interactive mode:

	- `ctrl-C` displays a new prompt on a new line.

	- `ctrl-D` exits the shell.

	- `ctrl-\` does nothing.

- Shell has the following builtins:

	- `echo` with option -n

	- `cd` with only a relative or absolute path

	- `pwd` with no options

	- `export` with no options

	- `unset` with no options

	- `env` with no options or arguments

	- `exit` with no options

- The `readline()` function can cause memory leaks. It is acceptable.

[Back to contents](#RefContents)