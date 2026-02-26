pipeline {
    agent any
    stages {
        stage('Checkout SCM') {
            steps {
                checkout scm
            }
        }
        stage('Build Backend Image') {
            steps {
                sh 'docker build -t backend-app CC_LAB-6/backend'
            }
        }
        stage('Deploy Backend Containers') {
            steps {
                sh '''
                docker rm -f backend1 backend2 || true
                docker run -d --name backend1 backend-app
                docker run -d --name backend2 backend-app
                sleep 3
                '''
            }
        }
        stage('Deploy NGINX Load Balancer') {
            steps {
                sh '''
                docker rm -f nginx-lb || true
                docker run -d --name nginx-lb -p 80:80 nginx
                sleep 2
                docker cp CC_LAB-6/nginx/default.conf nginx-lb:/etc/nginx/conf.d/default.conf
                docker exec nginx-lb nginx -s reload
                '''
            }
        }
    }
    post {
        always {
            echo 'Pipeline executed successfully. NGINX load balancer is running.'
        }
    }
}
