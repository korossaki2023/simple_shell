#ifndef _UNISTD_H
#define _UNISTD_H

// Constants
#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

// Function Declarations
ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
int access(const char *pathname, int mode);
int execve(const char *filename, char *const argv[], char *const envp[]);
int fork(void);
int execvp(const char *file, char *const argv[]);
void _exit(int status);
void perror(const char *s);
unsigned int alarm(unsigned int seconds);
int chdir(const char *path);
int close(int fd);
int dup2(int oldfd, int newfd);
pid_t getpid(void);
int isatty(int fd);
off_t lseek(int fd, off_t offset, int whence);
int pipe(int pipefd[2]);
int unlink(const char *pathname);
unsigned int sleep(unsigned int seconds);
pid_t waitpid(pid_t pid, int *status, int options);
char *getcwd(char *buf, size_t size);
char *strdup(const char *s);

#endif /* _UNISTD_H */
