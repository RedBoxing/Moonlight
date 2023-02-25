pipeline {
    agent {
      kubernetes  {
            label 'jenkins-slave'
             defaultContainer 'jnlp'
      yaml """
apiVersion: v1
kind: Pod
spec:
  containers:
  - name: devkitpro
    image: devkitpro/devkita64
    command:
    - cat
    tty: true
"""
        }
    }
  stages {
    stage('Build') {
      steps {
        container("devkitpro") {
            // Build the project
            sh "make -j10 build"

            // prepare the deploy folder
            sh "mkdir  atmosphere/contents/01006F8002326000/exefs"
            sh "mv deploy/* atmosphere/contents/01006F8002326000/exefs"
            // zip the atmosphere folder
            sh "zip -r deploy/Moonlight.zip atmosphere"
        }
      }
    }
  }
  post {
    always {
        archiveArtifacts artifacts: 'deploy/Moonlight.zip', onlyIfSuccessful: true
    }
  }
}