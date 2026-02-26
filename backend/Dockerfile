FROM debian:bullseye-slim
RUN apt-get update && apt-get install -y g++ && rm -rf /var/lib/apt/lists/*
WORKDIR /app
COPY app.cpp .
RUN g++ app.cpp -o app
CMD ["./app"]
