# Minishell
Lightweight version of the bash shell. Core functionalities include command execution, file redirection, and piping, complemented by a curated set of built-in commands within a confined mini environment.
This project was made during my time at 42 in collaboration with Elsie Malgouvre.

# Features
Basic mandatory features include :
- Command parsing : breakdown of the command line into tokens based on white space and characters
- Path Resolution : research of the non built-in commands in the PATH env variable
- Command Execution : Once located, the minishell executes the command, creating a new process and providing it with the necessary environment variables and arguments.
- Output Handling : depending on the invocation of the command and the presence of redirection or pipes
- Exit Status : After the command completes execution, it returns an exit status to indicate whether it succeeded or encountered an error.

Specific features :
- Classic, simple prompt and cute user experience
- Working history of commands
- Single and double quote handling
- `<`,  `>` , `<<` and `<<` redirections
- Pipes `|`
- Environment variable expansions `${ENV_VARIABLE}` and exit status `$?`
- `ctrl-C`, `ctrl-D`, `ctrl-\`

Built-in Features :
- `echo` with option `-n`
- `cd` with only a relative or absolute path
- `pwd` with no options
- `export` with no options
- `unset` with no options
- `env` with no options or arguments
- `exit` with no options
