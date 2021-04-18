pipeline {
    agent any
    environment {
        VERSION = '2.5'
    }
    stages {
        stage('build linux x64') {
            agent { docker { image 'dockcross/linux-x64' } }
            environment {
                CROSS_TRIPLE='x86_64-unknown-linux-gnu'
            }
            steps {
                sh 'mkdir -p build'
                sh 'set -e \
                    && apt-get update \
                    && apt-get install \
                        libgmp-dev \
                    && rm -rf /var/lib/apt/lists/ \
                '
                sh "\$CXX main.cpp -o build/prines_${VERSION}_${CROSS_TRIPLE} -I./include -lboinc -lboinc_api -lgmp -lgmpxx -Ofast"
                stash includes: "build/prines_${VERSION}_${CROSS_TRIPLE}.exe", name: 'bin linux x64'
            }
        }
        stage('build windows x64') {
            agent { docker { image 'dockcross/windows-static-x64' } }
            environment {
                CROSS_TRIPLE='x86_64-windows-gnu'
            }
            steps {
                sh 'mkdir -p build'
                sh "\$CXX main.cpp -o build/prines_${VERSION}_${CROSS_TRIPLE} -I./include -l:libboinc_api.a -l:libboinc.a -L/usr/local/lib/ -lstdc++ -static -static-libstdc++ -lgmp -lgmpxx -Ofast"
                stash includes: "build/prines_${VERSION}_${CROSS_TRIPLE}.exe", name: 'bin windows x64'
            }
        }
        stage('build linux arm64') {
            agent { docker { image 'dockcross/linux-arm64' } }
            environment {
                CROSS_TRIPLE='aarch64-unknown-linux-gnu'
            }
            steps {
                sh 'mkdir -p build'
                sh "\$CXX main.cpp -o build/prines_${VERSION}_${CROSS_TRIPLE} -I./include -lboinc -lboinc_api -lgmp -lgmpxx -Ofast"
                stash includes: "build/prines_${VERSION}_${CROSS_TRIPLE}", name: 'bin linux arm64'
            }
        }
        stage('package') {
            steps {
                unstash 'bin linux x64'
                unstash 'bin windows x64'
                unstash 'bin linux arm64'
                sh "./package add-version ${APPNAME} ${VERSION} x86_64-pc-linux-gnu build/prines_${VERSION}_x86_64-unknown-linux-gnu"
                sh "./package add-version ${APPNAME} ${VERSION} windows_x86_64 build/prines_${VERSION}_x86_64-windos-gnu"
                sh "./package add-version ${APPNAME} ${VERSION} windows_x86_64 build/prines_${VERSION}_x86_64-windos-gnu"
                sh "./package archive ${APPNAME}_${VERSION}.tar.xz"
                stash includes: "${APPNAME}_${VERSION}.tar.xz", name: 'package'
            }
        }
    }

    post {
        always {
            unstash 'bin linux x64'
            unstash 'bin windows x64'
            unstash 'bin linux arm64'
            archiveArtifacts artifacts: "build/prines_${VERSION}_x86_64-unknown-linux-gnu", fingerprint: true
            archiveArtifacts artifacts: "build/prines_${VERSION}_x86_64-windows-gnu", fingerprint: true
            archiveArtifacts artifacts: "build/prines_${VERSION}_aarch64-unknown-linux-gnu", fingerprint: true
//          archiveArtifacts artifacts: "build/prines_${VERSION}_x86_64-apple-darwin", fingerprint: true
            archiveArtifacts artifacts: "${APPNAME}_${VERSION}.tar.xz", fingerprint: true
            deleteDir()
        }
    }
}
