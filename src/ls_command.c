#include "ls_command.h"
#include <sys/types.h>
#include <dirent.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>  // open(), O_RDONLY 등 사용

void my_ls() {
    DIR *dir;
    struct dirent *entry;
    dir = opendir(".");  // 현재 디렉토리 열기
    if (dir == NULL) {
        perror("opendir");
        return;
    } else {
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_DIR) {
                printf("%s/\n", entry->d_name);
            } else {
                printf("%s\n", entry->d_name);
            }
        }
    }
    closedir(dir);
}

void my_cat(const char *filename) {
    // 파일 열기
    int fd = open(filename, O_RDONLY);
    if (fd < 0) { // 파일을 열지 못한 경우
        perror("cat");
        return;
    }

    // 읽기 및 출력용 버퍼
    char buf[1024];
    ssize_t bytes_read;

    // 파일을 읽어서 출력
    while ((bytes_read = read(fd, buf, sizeof(buf))) > 0) {
        if (write(STDOUT_FILENO, buf, bytes_read) < 0) { // 표준 출력에 쓰기
            perror("write");
            close(fd);
            return;
        }
    }

    // 읽기 오류 처리
    if (bytes_read < 0) {
        perror("read");
    }

    // 파일 닫기
    close(fd);
}

