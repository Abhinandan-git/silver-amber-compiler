FROM ubuntu:latest

RUN apt-get update && apt-get install -y build-essential && apt install -y nasm

WORKDIR /

COPY src/main.cpp src/arena.hpp src/generator.hpp src/parser.hpp src/tokenization ./

RUN g++ ./main.cpp -o sacompiler

CMD [ "./sacompiler", "./source_code.ffo" ]