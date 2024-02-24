# Minishell - if you did it, you know hell

Minishell is a simplified shell implementation, providing a command-line interface where users can interact with the operating system by executing various commands.


|    Project Name    |                                                                       minishell                                                                      |
| :----------------: | :-------------------------------------------------------------------------------------------------------------------------------------------------: |
|    Description     |                                             An implementation of C-based shell capable of handling redirections, pipes, environment variables, and various built-in functionalities.                                             |
|    Technologies    | <a href="#"><img alt="C" src="https://custom-icon-badges.demolab.com/badge/C-03599C.svg?logo=c-in-hexagon&logoColor=white&style=for-the-badge"></a> |
| External libraries |     readline(), rl_clear_history(), rl_on_new_line(), rl_replace_line(), rl_redisplay(), add_history(), printf(), malloc(), free(), write(), access(), open(), read(), close(), fork(), wait(), waitpid(), wait3(), wait4(), signal(), sigaction(), sigemptyset(), sigaddset(), kill(), exit(), getcwd(), chdir(), stat(), lstat(), fstat(), unlink(), execve(), dup(), dup2(), pipe(), opendir(), readdir(), closedir(), strerror(), perror(), isatty(), ttyname(), ttyslot(), ioctl(), getenv(), tcsetattr(), tcgetattr(), tgetent(), tgetflag(), tgetnum(), tgetstr(), tgoto(), tputs()      |

## Features

- Command Execution: executes a wide range of commands, including both built-in commands and external commands available in the system.
- Built-in commands: supports several built-in commands such as cd, echo, pwd, export, and unset, which provide additional functionality.
- Redirection and Pipes: supports input/output redirection and pipes, allowing users to redirect command input and output streams.
- Signal Handling: handles various signals such as Ctrl-C and Ctrl-\, providing a graceful termination of running commands.
- Environment Variables: manage environment variables, set new variables, and modify existing ones using the built-in commands.
- Command History

## Usage

```bash
  gcl https://github.com/trobert42/minishell.git
  cd minishell
  make
  ./minishell
```

## 💬
This is the first big project in the common core and to do in teams. It was pretty hard with all the exceptions and little tiny details that we wanted to manage. But it forced us to be more rigorous!  

Thank you Dan for your courage, you can be proud of your first garbage collector :) I won't forget all the breaks we took when we couldn't code anymore.
