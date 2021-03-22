# prines

for beefboinc

- compile:
    - windows:
        - ```c++ main.cpp -o prines_2.3_windows_x86_64.exe -I./include -l:libboinc_api.a -l:libboinc.a -L/usr/local/lib/ -lstdc++ -static -static-libstdc++ -lgmp -Ofast```
    - linux:
        - ```c++ main.cpp -o prines_2.3_x86_64-pc-linux-gnu -I./include -lboinc -lboinc_api -lgmp -lgmpxx -Ofast```
