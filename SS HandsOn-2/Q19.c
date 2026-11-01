
echo "=== 1. Create FIFO using mknod command ==="
mknod fifo_mknod_cmd p 2>/dev/null
ls -l fifo_mknod_cmd

echo -e "\n=== 2. Create FIFO using mkfifo command ==="
mkfifo fifo_mkfifo_cmd
ls -l fifo_mkfifo_cmd

echo -e "\n=== 3. Create FIFO using mknod system call (C program) ==="
cat <<'EOF' > fifo_mknod_sys.c
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
int main() {
    if (mknod("fifo_mknod_sys", S_IFIFO | 0666, 0) == -1) perror("mknod failed");
    else printf("FIFO created: fifo_mknod_sys\n");
    return 0;
}
EOF

gcc fifo_mknod_sys.c -o fifo_mknod_sys
./fifo_mknod_sys
ls -l fifo_mknod_sys

echo -e "\n=== 4. Create FIFO using mkfifo library function (C program) ==="
cat <<'EOF' > fifo_mkfifo_sys.c
#include <stdio.h>
#include <sys/stat.h>
int main() {
    if (mkfifo("fifo_mkfifo_sys", 0666) == -1) perror("mkfifo failed");
    else printf("FIFO created: fifo_mkfifo_sys\n");
    return 0;
}
EOF

gcc fifo_mkfifo_sys.c -o fifo_mkfifo_sys
./fifo_mkfifo_sys
ls -l fifo_mkfifo_sys

echo -e "\n=== 5. Compare strace outputs ==="
echo "strace of mknod command:"
strace -o strace_mknod.txt mknod fifo_strace_test p 2>/dev/null
cat strace_mknod.txt | grep mknod

echo -e "\nstrace of mkfifo command:"
strace -o strace_mkfifo.txt mkfifo fifo_strace_test2 2>/dev/null
cat strace_mkfifo.txt | grep mknod

echo -e "\nAll FIFO files created successfully."
ls -l fifo_*



/*
====================== Compilation & Execution ======================

chmod +x Q19.sh
./Q19.sh 2>&1 | tee -a Q19_output.txt


====================== Sample Output ================================

=== 1. Create FIFO using mknod command ===
prw-rw-r-- 1 user user 0 Sep 30 10:45 fifo_mknod_cmd

=== 2. Create FIFO using mkfifo command ===
prw-rw-r-- 1 user user 0 Sep 30 10:45 fifo_mkfifo_cmd

=== 3. Create FIFO using mknod system call (C program) ===
FIFO created: fifo_mknod_sys
prw-rw-r-- 1 user user 0 Sep 30 10:45 fifo_mknod_sys

=== 4. Create FIFO using mkfifo library function (C program) ===
FIFO created: fifo_mkfifo_sys
prw-rw-r-- 1 user user 0 Sep 30 10:45 fifo_mkfifo_sys

=== 5. Compare strace outputs ===
strace of mknod command:
mknod("fifo_strace_test", S_IFIFO|0666, 0) = 0

strace of mkfifo command:
mknod("fifo_strace_test2", S_IFIFO|0666, 0) = 0

All FIFO files created successfully.
prw-rw-r-- 1 user user 0 Sep 30 10:45 fifo_mknod_cmd
prw-rw-r-- 1 user user 0 Sep 30 10:45 fifo_mkfifo_cmd
prw-rw-r-- 1 user user 0 Sep 30 10:45 fifo_mknod_sys
prw-rw-r-- 1 user user 0 Sep 30 10:45 fifo_mkfifo_sys
prw-rw-r-- 1 user user 0 Sep 30 10:45 fifo_strace_test
prw-rw-r-- 1 user user 0 Sep 30 10:45 fifo_strace_test2


=====================================================================
*/

