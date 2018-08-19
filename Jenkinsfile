pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                checkout scm
                sh 'mkdir -p build local'
            }
        }
        stage('Compile') {
            steps {
                sh '''
                	cd build &&
                    conan install .. -s:build_type=Debug &&
                	cmake -D CMAKE_BUILD_TYPE=Debug -D BUILD_TESTING=ON .. &&
                	make
                '''
            }
        }
        stage('Test') {
            steps {
                sh '''
                	cd build &&
                	ctest
                '''
            }
        }
    }
}