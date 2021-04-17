pipeline {
    agent any
    environment {
        VERSION = '2.5'
    }

    stages {
        stage('build linux x64') {
            environment {
                CROSS_TRIPLE='x86_64-unknown-linux-gnu'
            }
            steps { script { docker.image('dockcross/linux-x64').inside {
                sh 'mkdir -p build'
                sh "\$CXX main.cpp -o build/prines_${VERSION}_${CROSS_TRIPLE} -I./include -lboinc -lboinc_api -lgmp -lgmpxx -Ofast"
            } } }
        }
        stage('build windows x64') {
            environment {
                CROSS_TRIPLE='x86_64-windows-gnu'
            }
            steps { script { docker.image('dockcross/windows-static-x64').inside {
                sh 'mkdir -p build'
                sh "\$CXX main.cpp -o build/prines_${VERSION}_${CROSS_TRIPLE} -I./include -l:libboinc_api.a -l:libboinc.a -L/usr/local/lib/ -lstdc++ -static -static-libstdc++ -lgmp -lgmpxx -Ofast"
            } } }
        }
        stage('build linux arm64') {
            environment {
                CROSS_TRIPLE='aarch64-unknown-linux-gnu'
            }
            steps { script { docker.image('dockcross/linux-arm64').inside {
                sh 'mkdir -p build'
                sh "\$CXX main.cpp -o build/prines_${VERSION}_${CROSS_TRIPLE} -I./include -lboinc -lboinc_api -lgmp -lgmpxx -Ofast"
            } } }
        }
    }

    post {
        always {
            archiveArtifacts artifacts: "build/prines_${VERSION}_x86_64-unknown-linux-gnu", fingerprint: true
            archiveArtifacts artifacts: "build/prines_${VERSION}_x86_64-windows-gnu", fingerprint: true
            archiveArtifacts artifacts: "build/prines_${VERSION}_aarch64-unknown-linux-gnu", fingerprint: true
            deleteDir()
        }
    }
}
