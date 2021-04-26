pipeline {
    agent any
    environment {
        VERSION = '2.5'
        APPNAME = 'prines'
        GMP_VERSION = '6.2.1'
        BOINC_VERSION = '3f8135e46b725fcaf08b80c5c53db8a988a01cbf'
    }
    stages {
        stage('build linux x64') {
            agent { docker {
                image 'dockcross/linux-x64'
                args '-u root:root'
            } }
            environment {
                CROSS_TRIPLE='x86_64-unknown-linux-gnu'
				NUM_CPUS="""${sh(
                    returnStdout: true,
                    script: "lscpu | grep -E '^CPU\\(s\\):' | awk '{print \$2}'"
                )}"""
            }
            steps {
                sh 'set eux'

                // build boinc libs
                sh 'rm -rf boinc'
                sh 'git clone https://github.com/BOINC/boinc.git'
                dir ('boinc') {
                    sh "git checkout ${BOINC_VERSION}"
                    sh './_autosetup'
                    sh "./configure --disable-client --disable-server --disable-fcgi --disable-manager --enable-generic-processor --enable-libraries --enable-install-headers --enable-static --host=${CROSS_TRIPLE}"
                    sh 'make -j\${NUM_CPUS}'
                    sh 'make DESTDIR=/work/temproot install'
                }

                // build gmp
                sh 'rm -rf gmp*'
                sh 'wget https://gmplib.org/download/gmp/gmp-${GMP_VERSION}.tar.xz'
                sh 'tar xf gmp-${GMP_VERSION}.tar.xz'
                dir ('gmp-${GMP_VERSION}') {
                    sh "./configure --host ${CROSS_TRIPLE} --enable-fat --enable-cxx --enable-static"
                    sh 'make -j\${NUM_CPUS}'
//                  sh 'make check'
                    sh 'make DESTDIR=/work/temproot install'
                }

                // build prines
                sh 'mkdir -p build'
                sh "\$CXX main.cpp -o build/prines_${VERSION}_${CROSS_TRIPLE} -I/work/temproot/usr/local/include -L/work/temproot/usr/local/lib -pthread -lboinc_api -lboinc -lgmp -lgmpxx -Ofast -static"
                // assert that the resulting executable is fully static
                sh "[ \"\$(ldd build/prines_${VERSION}_${CROSS_TRIPLE} | xargs)\" = 'not a dynamic executable' ]"
                stash includes: "build/prines_${VERSION}_${CROSS_TRIPLE}", name: 'bin linux x64'
            }
        }
        stage('build linux arm64') {
            agent { docker {
                image 'dockcross/linux-arm64'
                args '-u root:root'
            } }
            environment {
                CROSS_TRIPLE='aarch64-unknown-linux-gnu'
				NUM_CPUS="""${sh(
                    returnStdout: true,
                    script: "lscpu | grep -E '^CPU\\(s\\):' | awk '{print \$2}'"
                )}"""
            }
            steps {
                sh 'set eux'

                // build boinc libs
                sh 'rm -rf boinc'
                sh 'git clone https://github.com/BOINC/boinc.git'
                dir ('boinc') {
                    sh "git checkout ${BOINC_VERSION}"
                    sh './_autosetup'
                    sh "./configure --disable-client --disable-server --disable-fcgi --disable-manager --enable-generic-processor --enable-libraries --enable-install-headers --enable-static --host=${CROSS_TRIPLE}"
                    sh 'make -j\${NUM_CPUS}'
                    sh 'make DESTDIR=/work/temproot install'
                }

                // build gmp
                sh 'rm -rf gmp*'
                sh 'wget https://gmplib.org/download/gmp/gmp-${GMP_VERSION}.tar.xz'
                sh 'tar xf gmp-${GMP_VERSION}.tar.xz'
                dir ('gmp-${GMP_VERSION}') {
                    sh "./configure --host ${CROSS_TRIPLE} --enable-fat --enable-cxx --enable-static"
                    sh 'make -j\${NUM_CPUS}'
//                  sh 'make check'
                    sh 'make DESTDIR=/work/temproot install'
                }

                // build prines
                sh 'mkdir -p build'
                sh "\$CXX main.cpp -o build/prines_${VERSION}_${CROSS_TRIPLE} -I/work/temproot/usr/local/include -L/work/temproot/usr/local/lib -pthread -lboinc_api -lboinc -lgmp -lgmpxx -Ofast -static"
                // assert that the resulting executable is fully static
                sh "[ \"\$(ldd build/prines_${VERSION}_${CROSS_TRIPLE} | xargs)\" = 'not a dynamic executable' ]"
                stash includes: "build/prines_${VERSION}_${CROSS_TRIPLE}", name: 'bin linux arm64'
            }
        }
        stage('build linux armv7') {
            agent { docker {
                image 'dockcross/linux-armv7'
                args '-u root:root'
            } }
            environment {
                CROSS_TRIPLE='arm-unknown-linux-gnueabihf'
				NUM_CPUS="""${sh(
                    returnStdout: true,
                    script: "lscpu | grep -E '^CPU\\(s\\):' | awk '{print \$2}'"
                )}"""
            }
            steps {
                sh 'set eux'

                // build boinc libs
                sh 'rm -rf boinc'
                sh 'git clone https://github.com/BOINC/boinc.git'
                dir ('boinc') {
                    sh "git checkout ${BOINC_VERSION}"
                    sh './_autosetup'
                    sh "./configure --disable-client --disable-server --disable-fcgi --disable-manager --enable-generic-processor --enable-libraries --enable-install-headers --enable-static --host=${CROSS_TRIPLE}"
                    sh 'make -j\${NUM_CPUS}'
                    sh 'make DESTDIR=/work/temproot install'
                }

                // build gmp
                sh 'rm -rf gmp*'
                sh 'wget https://gmplib.org/download/gmp/gmp-${GMP_VERSION}.tar.xz'
                sh 'tar xf gmp-${GMP_VERSION}.tar.xz'
                dir ('gmp-${GMP_VERSION}') {
                    sh "./configure --host ${CROSS_TRIPLE} --enable-fat --enable-cxx --enable-static"
                    sh 'make -j\${NUM_CPUS}'
//                  sh 'make check'
                    sh 'make DESTDIR=/work/temproot install'
                }

                // build prines
                sh 'mkdir -p build'
                sh "\$CXX main.cpp -o build/prines_${VERSION}_${CROSS_TRIPLE} -I/work/temproot/usr/local/include -L/work/temproot/usr/local/lib -pthread -lboinc_api -lboinc -lgmp -lgmpxx -Ofast -static"
                // assert that the resulting executable is fully static
                sh "[ \"\$(ldd build/prines_${VERSION}_${CROSS_TRIPLE} | xargs)\" = 'not a dynamic executable' ]"
                stash includes: "build/prines_${VERSION}_${CROSS_TRIPLE}", name: 'bin linux armv7'
            }
        }
        stage('build windows x64') {
            agent { docker {
                image 'dockcross/windows-static-x64'
                args '-u root:root'
            } }
            environment {
                CROSS_TRIPLE='x86_64-windows-gnu'
				NUM_CPUS="""${sh(
                    returnStdout: true,
                    script: "lscpu | grep -E '^CPU\\(s\\):' | awk '{print \$2}'"
                )}"""
            }
            steps {
                sh 'set eux'

                // build boinc libs
                // this is commented out cause cross compiling is broken
                // we just use the pre-compiled one in the include directory
                // for now
//              sh 'rm -rf boinc'
//              sh 'git clone https://github.com/BOINC/boinc.git'
//              dir ('boinc') {
//                  sh "git checkout ${BOINC_VERSION}"
//                  sh './_autosetup'
//                  sh "./configure --disable-client --disable-server --disable-fcgi --disable-manager --enable-generic-processor --enable-libraries --enable-install-headers --enable-static --host=${CROSS_TRIPLE}"
//                  sh 'make -j\${NUM_CPUS}'
//                  sh 'make DESTDIR=/work/temproot install'
//              }

                // build gmp
                sh 'rm -rf gmp*'
                sh 'wget https://gmplib.org/download/gmp/gmp-${GMP_VERSION}.tar.xz'
                sh 'tar xf gmp-${GMP_VERSION}.tar.xz'
                dir ('gmp-${GMP_VERSION}') {
                    sh "./configure --host ${CROSS_TRIPLE} --disable-assembly --enable-cxx --enable-static"
                    sh 'make -j\${NUM_CPUS}'
                    //sh 'make check'
                    sh 'make DESTDIR=/work/temproot install'
                }

                // build prines
                sh 'mkdir -p build'
                // use precompiled boinc libs
                sh "\$CXX main.cpp -o build/prines_${VERSION}_${CROSS_TRIPLE}.exe -I/work/temproot/usr/local/include -L/work/temproot/usr/local/lib -L./include/boinc/lib/win -pthread -lboinc_api -lboinc -lgmp -lgmpxx -Ofast -static"
                // assert that the resulting executable is fully static
                sh "[ \"\$(ldd build/prines_${VERSION}_${CROSS_TRIPLE}.exe | xargs)\" = 'not a dynamic executable' ]"
                stash includes: "build/prines_${VERSION}_${CROSS_TRIPLE}.exe", name: 'bin windows x64'
            }
        }
        stage('package') {
            steps {
                unstash 'bin linux x64'
//              unstash 'bin windows x64'
                unstash 'bin linux arm64'
                sh "./package add-version ${APPNAME} ${VERSION} x86_64-pc-linux-gnu build/prines_${VERSION}_x86_64-unknown-linux-gnu"
//              sh "./package add-version ${APPNAME} ${VERSION} windows_x86_64 build/prines_${VERSION}_x86_64-windows-gnu"
                sh "./package add-version ${APPNAME} ${VERSION} aarch64-unknown-linux-gnu build/prines_${VERSION}_aarch64-unknown-linux-gnu"
                sh "./package archive ${APPNAME}_${VERSION}"
                stash includes: "${APPNAME}_${VERSION}.tar.xz", name: 'package'
            }
        }
    }

    post {
        always {
            unstash 'bin linux x64'
//          unstash 'bin windows x64'
            unstash 'bin linux arm64'
            unstash 'package'
            archiveArtifacts artifacts: "build/prines_${VERSION}_x86_64-unknown-linux-gnu", fingerprint: true
//          archiveArtifacts artifacts: "build/prines_${VERSION}_x86_64-windows-gnu", fingerprint: true
            archiveArtifacts artifacts: "build/prines_${VERSION}_aarch64-unknown-linux-gnu", fingerprint: true
//          archiveArtifacts artifacts: "build/prines_${VERSION}_x86_64-apple-darwin", fingerprint: true
            archiveArtifacts artifacts: "${APPNAME}_${VERSION}.tar.xz", fingerprint: true
            deleteDir()
        }
    }
}
