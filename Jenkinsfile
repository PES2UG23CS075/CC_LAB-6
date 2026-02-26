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
                sh 'docker build -t backend-app backend'
            }
        }
        stage('Deploy Backend Containers') {
            steps {
                sh '''
                docker network create lab6-network || true
                docker rm -f backend1 backend2 || true
                docker run -d --name backend1 --network lab6-network backend-app
                docker run -d --name backend2 --network lab6-network backend-app
                sleep 3
                '''
            }
        }
        stage('Deploy NGINX Load Balancer') {
            steps {
                sh '''
                docker rm -f nginx-lb || true
                docker run -d --name nginx-lb --network lab6-network -p 80:80 nginx
                sleep 2
                docker cp nginx/default.conf nginx-lb:/etc/nginx/conf.d/default.conf
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
