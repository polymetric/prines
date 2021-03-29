# prines

for beefboinc

- compile:
    - windows (x86_64/amd64):
        - ```c++ main.cpp -o prines_2.3_windows_x86_64.exe -I./include -l:libboinc_api.a -l:libboinc.a -L/usr/local/lib/ -lstdc++ -static -static-libstdc++ -lgmp -Ofast```
    - linux (x86_64/amd64):
        - ```c++ main.cpp -o prines_2.4_x86_64-pc-linux-gnu -static -static-libgcc -static-libstdc++ -lboinc_api -lboinc -lgmp -lgmpxx -pthread -Ofast -Iinclude -Linclude/boinc/lib/lin```
    - linux (aarch64/arm64):
        - ```c++ main.cpp -o prines_2.4_aarch64-unknown-linux-gnu -static -static-libgcc -static-libstdc++ -lboinc_api -lboinc -lgmp -lgmpxx -pthread -Ofast -Iinclude -Linclude/boinc/lib/lin_aarch64```
